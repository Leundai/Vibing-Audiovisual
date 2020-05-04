// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <audiovisual/star.h>
#include <audiovisual/terrain.h>
#include <cinder/app/App.h>
#include <cinder/audio/audio.h>
#include <cinder/gl/gl.h>

#include <filesystem>

namespace app {

class VibeApp : public cinder::app::App {
 public:
  VibeApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void fileDrop(ci::app::FileDropEvent event) override;

 private:
  void SetUpStars();  // Initialize the vector of spheres and shaders
  void SwitchSong(
      bool forward);     // Handles switching between songs back or skip
  void MusicalColors();  // Maps the 3 frequency magnitudes to colors r g b
  void DrawGUI();        // Called to Draw the IMGUI
  void SetUpSong();

 private:
  cinder::audio::MonitorSpectralNodeRef monitor_node_;
  cinder::audio::VoiceRef music_output_;
  cinder::CameraPersp camera_;
  cinder::gl::BatchRef batch_sphere_;
  cinder::gl::GlslProgRef glsl_sphere_;
  std::chrono::time_point<std::chrono::system_clock> last_draw_time_;
  audiovisual::Terrain terrain_;
  std::vector<audiovisual::Star> stars;
  std::vector<std::experimental::filesystem::path> playlist;
  std::vector<float> freq_mag;

  float color_pick[4]{};
  float noise_y = 0;
  int cam_z_pos = 150;
  int draw_interval = 17;
  int song_index;
  bool is_paused{};
  bool is_cleared;
  float volume;
  int num_bins;
};

}  // namespace app

#endif  // FINALPROJECT_APPS_MYAPP_H_
