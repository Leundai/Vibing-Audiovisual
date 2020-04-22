// Copyright (c) 2020 Leonardo Galindo. All rights reserved.

#include "vibe_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

namespace myapp {

using namespace cinder;
using cinder::app::KeyEvent;

MyApp::MyApp() : terrain(getWindowHeight() / 14, getWindowWidth() / 25, 22) {}

void MyApp::setup() {
  auto ctx = audio::Context::master();
  audio::SourceFileRef sourceFile = audio::load(loadAsset("caravan.mp3"));
  mMusic = cinder::audio::Voice::create(sourceFile);

  auto monitorFormat =
      audio::MonitorSpectralNode::Format().fftSize(2048).windowSize(1024);
  mMonitorSpectralNode =
      ctx->makeNode(new audio::MonitorSpectralNode(monitorFormat));

  mMusic->getOutputNode() >> mMonitorSpectralNode;

  ctx->enable();
  mMusic->start();

  mCam.lookAt(vec3(getWindowWidth() / 2, 0, cam_z_pos),
              vec3(getWindowWidth() / 2, getWindowHeight(), 0));
  mCam.setFovHorizontal(50);
}

void MyApp::update() {

}

void MyApp::draw() {
  noise_y += .005;
  cam_y += 1;
  gl::clear();
  gl::setMatrices(mCam);

  mCam.setEyePoint(vec3(getWindowWidth() / 2, 0, cam_z_pos));
  terrain.DrawTerrain(cam_y);
  const auto time = std::chrono::system_clock::now();
  if (time - last_draw_time_ >= std::chrono::milliseconds(draw_interval_)) {
    terrain.UpdateZValues(noise_y, mMonitorSpectralNode->getVolume());
    last_draw_time_ = time;
  }
}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
