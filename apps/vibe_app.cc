// Copyright (c) 2020 Leonardo Galindo. All rights reserved.

#include "vibe_app.h"

#include <CinderImGui.h>
#include <audiovisual/star.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

#include "cinder/Log.h"

namespace app {

using namespace cinder;
using cinder::app::KeyEvent;

VibeApp::VibeApp()  // The divisions are scalings of the size of the terrain.
    : terrain_(getWindowHeight() / 14, getWindowWidth() / 25, 22, true) {
  song_index = 0;
  is_cleared = false;
  num_bins = 0;
  volume = 1;
  color_pick[3] = 255;  // Alpha setting for color
}

void VibeApp::setup() {
  // Audio setup
  auto ctx = audio::Context::master();

  // We now start nodes both for analyzing the music realtime and playing it
  auto monitorFormat =
      audio::MonitorSpectralNode::Format().fftSize(1024).windowSize(512);
  monitor_node_ = ctx->makeNode(new audio::MonitorSpectralNode(monitorFormat));

  // Dialog to load music
  try {
    // Have only tested mp3 and wav so only allow those
    fs::path path = getOpenFilePath("", {"mp3", "wav"});
    playlist.push_back(path);
    if (!path.empty()) {
      SetUpSong();
    }
  } catch (Exception &exc) {
    CI_LOG_EXCEPTION("failed to load music.", exc)
  }

  // Enable in order to be able to be analyzed and we also start music
  ctx->enable();
  music_output_->start();
  monitor_node_->setSmoothingFactor(.75);

  // Graphical Setup For 3D View
  camera_.lookAt(vec3(getWindowWidth() / 2, 0, cam_z_pos),
                 vec3(getWindowWidth() / 2, getWindowHeight(), 0));
  camera_.setFovHorizontal(50);
  SetUpStars();
  ImGui::initialize();
}

void VibeApp::SetUpStars() {
  // GLSL Setup for sphere
  glsl_sphere_ = gl::GlslProg::create(
      gl::GlslProg::Format()
          .vertex(CI_GLSL(
              150, uniform mat4 ciModelViewProjection; in vec4 ciPosition;

              void main(void) {
                gl_Position = ciModelViewProjection * ciPosition;
              }))
          .fragment(CI_GLSL(
              150, out vec4 oColor; uniform vec4 iColor;

              void main(void) { oColor = iColor; })));
  glsl_sphere_->uniform("iColor", vec4(1, 0.5, 0.25, 1));
  batch_sphere_ =
      gl::Batch::create(geom::Sphere().subdivisions(100), glsl_sphere_);

  // Initializes stars
  float x;
  float y;
  float z;
  float scale_pos = 3.5;  // Shifts X position of sphere on a scaling scale/16
  float kBaseZPos = 200.0;

  for (int star_index = 1; star_index <= monitor_node_->getNumBins() / 64;
       star_index++) {
    x = (float)getWindowWidth() * ((scale_pos + (float)star_index) / 16);
    y = ((float)getWindowHeight() * 4) / 5;  // Closer Y will hide sphere
    z = kBaseZPos -
        (float)(75 * (star_index % 2));  // Varies between KBaseZ and - 75
    vec3 position(x, y, z);
    audiovisual::Star star(position, batch_sphere_);
    stars.push_back(star);
  }
}

void VibeApp::update() {
  music_output_->setVolume(volume);
  noise_y += .005;  // Allows for shifting of terrain and updates
  freq_mag = monitor_node_->getMagSpectrum();
  num_bins = monitor_node_->getNumBins();

  if (!music_output_->isPlaying() && !is_paused) {
    SwitchSong(true);
  }
}

void VibeApp::draw() {
  gl::clear(Color(0.2f, 0.2f, 0.2f));

  gl::enableDepthRead();
  gl::enableDepthWrite();
  gl::setMatrices(camera_);
  camera_.setEyePoint(vec3(getWindowWidth() / 2, 0, cam_z_pos));
  camera_.setAspectRatio((float)getWindowWidth() / (float)getWindowHeight());

  terrain_.DrawTerrain();
  DrawGUI();

  // Interval in order to be able to be able to update our audiovisual
  const auto time = std::chrono::system_clock::now();
  if (time - last_draw_time_ >= std::chrono::milliseconds(draw_interval)) {
    terrain_.UpdateZValues(noise_y, freq_mag[0],
                           monitor_node_->getSpectralCentroid());
    last_draw_time_ = time;
  }
}

void VibeApp::DrawGUI() {
  ImGui::Begin("Controls");

  if (!is_cleared) {
    ImGui::BeginGroup();
    std::string music_name;
    if (!playlist.empty())
      music_name = "Song: " + playlist.at(song_index).stem().string();
    ImGui::Text("%s", music_name.c_str());
    if (ImGui::ArrowButton("Back", ImGuiDir_Left)) SwitchSong(false);
    ImGui::SameLine();
    if (ImGui::Button("Play")) {
      is_paused = false;
      music_output_->start();
    }
    ImGui::SameLine();
    if (ImGui::Button("Pause")) {
      is_paused = true;
      music_output_->pause();
    }
    ImGui::SameLine();
    if (ImGui::ArrowButton("Forward", ImGuiDir_Right)) SwitchSong(true);
    ImGui::EndGroup();

    ImGui::SliderFloat("Volume", &volume, 0.0f, 1.0f);
  }
  static int e = 0;
  ImGui::RadioButton("Musical Colors", &e, 0);
  ImGui::SameLine();
  ImGui::RadioButton("Choose Color", &e, 1);
  if (e == 1) {
    if (ImGui::ColorEdit4("Color Of Stars", color_pick)) {
      glsl_sphere_->uniform("iColor", vec4(color_pick[0], color_pick[1],
                                           color_pick[2], color_pick[3]));
    }
  } else {
    MusicalColors();
  }

  if (ImGui::Button("Toggle Shake")) terrain_.ToggleCanShake();
  ImGui::SameLine();
  if (ImGui::Button("Clear Playlist")) {
    music_output_->pause();
    is_paused = true;
    is_cleared = true;
    song_index = 0;
    playlist.clear();
  }

  ImGui::Separator();
  ImGui::BeginChild("Scrolling");
  for (auto &n : playlist) ImGui::Text("%s", n.stem().string().c_str());
  ImGui::EndChild();
  ImGui::End();

  ImGui::Begin("Helper");
  for (int bin_index = 0; bin_index < num_bins / 64; bin_index++) {
    ImGui::Text("%s", std::to_string(freq_mag[bin_index * 64]).c_str());
    stars.at(bin_index).DrawStar(
        audio::linearToDecibel(freq_mag[bin_index * 64]));
  }
  ImGui::Text("%s",
              std::to_string(monitor_node_->getSpectralCentroid()).c_str());
  ImGui::Text("%s", std::to_string(monitor_node_->getVolume()).c_str());
  ImGui::End();
}

void VibeApp::SwitchSong(bool forward) {
  music_output_->stop();
  music_output_.reset();
  if (forward) {
    if (song_index == playlist.size() - 1)
      song_index = 0;
    else
      song_index++;
  } else {
    if (song_index == 0)
      song_index = (int)playlist.size() - 1;
    else
      song_index--;
  }
  SetUpSong();
  music_output_->start();
  is_paused = false;
}

void VibeApp::SetUpSong() {
  try {
    audio::SourceFileRef sourceFile =
        audio::load(loadFile(playlist.at(song_index)));
    music_output_ = cinder::audio::Voice::create(sourceFile);
  } catch (Exception &exc) {
    CI_LOG_EXCEPTION("failed to load music.", exc)
  }

  music_output_->getOutputNode() >> monitor_node_;
}

void VibeApp::MusicalColors() {
  // Mapping values are based on how strong each magnitude is per frequency
  // The higher ones are not as strong so are they are given a boost and smaller
  // range
  float r = audiovisual::Map(freq_mag[0], 0, 1, 0, 255);
  float g = audiovisual::Map(freq_mag[num_bins / 2], 0, .2, 0, 200);
  float b =
      audiovisual::Map(freq_mag[(num_bins * 7) / 8], 0, .0075, 0, 200) * 2;

  glsl_sphere_->uniform("iColor", vec4(r, g, b, 255));
}

void VibeApp::fileDrop(ci::app::FileDropEvent event) {
  std::vector<fs::path> file_paths = event.getFiles();
  if (file_paths.size() == 1 && fs::is_directory(file_paths[0])) {
    fs::path folder_path = file_paths[0];
    file_paths.clear();
    for (const auto &entry : fs::directory_iterator(folder_path)) {
      if (entry.path().extension() == ".mp3" ||
          entry.path().extension() == ".wav") {
        file_paths.push_back(entry);
      }
    }
  }
  bool is_sanitized = true;
  for (const auto &entry : file_paths) {
    if (entry.extension() == ".mp3" || entry.extension() == ".wav") {
      continue;
    } else {
      is_sanitized = false;
    }
  }
  if (is_sanitized) {
    playlist.insert(playlist.end(), file_paths.begin(), file_paths.end());
    if (is_cleared) {
      SetUpSong();
      is_cleared = false;
    }
  }
}

void VibeApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_LEFT: {
      SwitchSong(false);
      break;
    }
    case KeyEvent::KEY_RIGHT: {
      SwitchSong(true);
      break;
    }
    case KeyEvent::KEY_SPACE:  // Fall Through
    case KeyEvent::KEY_PAUSE:  // Fall Through
    case KeyEvent::KEY_p: {
      if (is_paused) {
        music_output_->start();
      } else {
        music_output_->pause();
      }
      is_paused = !is_paused;
      break;
    }
  }
}

}  // namespace app
