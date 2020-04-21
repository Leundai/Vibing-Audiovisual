// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <audiovisual/terrain.h>

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
 private:
  std::chrono::time_point<std::chrono::system_clock> last_draw_time_;
  cinder::CameraPersp mCam;
  terrain::Terrain terrain;
  float noise_y = 0;
  int cam_z_pos = 125;
  int draw_interval_ = 17;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
