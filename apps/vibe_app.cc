// Copyright (c) 2020 Leonardo Galindo. All rights reserved.

#include "vibe_app.h"

#include <audiovisual/star.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

#include "cinder/Log.h"

namespace app {

using namespace cinder;
using cinder::app::KeyEvent;

MyApp::MyApp()
    : terrain(getWindowHeight() / 14, getWindowWidth() / 25, 22, true) {}

void MyApp::setup() {
  srand(cinder::app::getElapsedSeconds());
  // Audio setup
  auto ctx = audio::Context::master();

  // Dialog to load music
  try {
    fs::path path = getOpenFilePath("");
    audio::SourceFileRef sourceFile = audio::load(loadFile(path));
    if (!path.empty()) {
      mMusic = cinder::audio::Voice::create(sourceFile);
    }
  } catch (Exception &exc) {
    CI_LOG_EXCEPTION("failed to load music.", exc);
  }

  // We now start nodes both for analyzing the music realtime and playing it
  auto monitorFormat =
      audio::MonitorSpectralNode::Format().fftSize(1024).windowSize(512);
  mMonitorSpectralNode =
      ctx->makeNode(new audio::MonitorSpectralNode(monitorFormat));
  mMusic->getOutputNode() >> mMonitorSpectralNode;

  // Enable in order to be able to be analyzed and we also start music
  ctx->enable();
  mMusic->start();

  // Graphical Setup For 3D View
  mCam.lookAt(vec3(getWindowWidth() / 2, 0, cam_z_pos),
              vec3(getWindowWidth() / 2, getWindowHeight(), 0));
  mCam.setFovHorizontal(50);
  setUpStars();
}

void MyApp::setUpStars() {
  mGlsl = gl::GlslProg::create(
      gl::GlslProg::Format()
          .vertex(CI_GLSL(
              150, uniform mat4 ciModelViewProjection; in vec4 ciPosition;

              void main(void) {
                gl_Position = ciModelViewProjection * ciPosition;
              }))
          .fragment(CI_GLSL(
              150, out vec4 oColor;

              void main(void) { oColor = vec4(1, 0.5, 0.25, 1); })));
  mSphere = gl::Batch::create(geom::Sphere().subdivisions(100), mGlsl);

  for (int star_index = 1;
       star_index <= mMonitorSpectralNode->getNumBins() / 64; star_index++) {
    ColorAf rand_color(vec4(rand(), rand(), rand(), .75));
    float x = (float)getWindowWidth() * ((float)star_index + 3.5) / 16;
    float y = ((float)getWindowHeight() * 4) / 5;
    float z = (float)200 - (float)(75 * (star_index % 2));
    vec3 position(x, y, z);
    audiovisual::Star star(rand_color, position, mSphere);
    stars.push_back(star);
  }
}

void MyApp::update() { noise_y += .005; }

void MyApp::draw() {
  gl::clear(Color(0.2f, 0.2f, 0.2f));

  gl::enableDepthRead();
  gl::enableDepthWrite();
  gl::setMatrices(mCam);
  mCam.setEyePoint(vec3(getWindowWidth() / 2, 0, cam_z_pos));
  mCam.setAspectRatio((float)getWindowWidth() / (float)getWindowHeight());

  terrain.DrawTerrain();

  // TODO: Move the sphere to a different cpp file
  mMonitorSpectralNode->setSmoothingFactor(.75);
  std::vector<float> mag = mMonitorSpectralNode->getMagSpectrum();
  int bins = mMonitorSpectralNode->getNumBins();
  for (int bin_index = 0; bin_index < bins / 64; bin_index++) {
    stars.at(bin_index).DrawStar(audio::linearToDecibel(mag[bin_index * 64]));
  }

  // Interval in order to be able to be able to update our audiovisual
  const auto time = std::chrono::system_clock::now();
  if (time - last_draw_time_ >= std::chrono::milliseconds(draw_interval_)) {
    terrain.UpdateZValues(noise_y, mMonitorSpectralNode->getVolume());
    last_draw_time_ = time;
  }
}

void MyApp::keyDown(KeyEvent event) {}
void MyApp::mouseDown(cinder::app::MouseEvent event) {}

}  // namespace app
