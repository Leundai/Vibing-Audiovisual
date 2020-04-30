// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <audiovisual/terrain.h>
#include <audiovisual/star.h>
#include <cinder/app/App.h>
#include <cinder/audio/audio.h>
#include <cinder/gl/gl.h>

namespace app {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void mouseDown( cinder::app::MouseEvent event ) override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  void setUpStars();
  cinder::audio::MonitorSpectralNodeRef mMonitorSpectralNode;
  cinder::audio::VoiceRef mMusic;
  cinder::audio::OutputNodeRef output;
  std::chrono::time_point<std::chrono::system_clock> last_draw_time_;
  cinder::CameraPersp mCam;
  cinder::gl::BatchRef mSphere;
  cinder::gl::GlslProgRef mGlsl;
  audiovisual::Terrain terrain;
  std::vector<audiovisual::Star> stars;

  float noise_y = 0;
  int cam_z_pos = 150;
  int draw_interval_ = 17;
};

}  // namespace app

#endif  // FINALPROJECT_APPS_MYAPP_H_
