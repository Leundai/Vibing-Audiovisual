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
  void SetUpSong();      // Adds a song to the voice node but does not play it

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
  float noise_y;
  float volume;
  int cam_z_pos;
  int draw_interval;
  int song_index;
  int num_bins;
  bool is_paused{};
  bool is_cleared;
};

}  // namespace app

#endif  // FINALPROJECT_APPS_MYAPP_H_
