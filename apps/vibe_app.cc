// Copyright (c) 2020 Leonardo Galindo. All rights reserved.

#include "vibe_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

namespace myapp {

using namespace cinder;
using cinder::app::KeyEvent;

MyApp::MyApp(): terrain(getWindowHeight()/15, getWindowWidth()/25, 20) { }

void MyApp::setup() {
  mCam.lookAt( vec3( getWindowWidth()/2, 0 , cam_z_pos), vec3( getWindowWidth()/2, getWindowHeight(), 0 ) );
  mCam.setFovHorizontal(50);
  gl::enableDepthRead();
  gl::enableDepthWrite();
}

void MyApp::update() {

}

void MyApp::draw() {
  noise_y += .004;
  gl::clear();
  gl::setMatrices( mCam );

  mCam.setEyePoint(vec3(getWindowWidth()/2, 0 , cam_z_pos));
  terrain.DrawTerrain();

  const auto time = std::chrono::system_clock::now();
  if (time - last_draw_time_ >= std::chrono::milliseconds(draw_interval_)) {
    terrain.UpdateZValues(noise_y);
    last_draw_time_ = time;
  }
}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
