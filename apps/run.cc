// Copyright (c) 2020 Leonardo Galindo. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>

#include "vibe_app.h"

using cinder::app::App;
using cinder::app::RendererGl;


namespace myapp {

const int kSamples = 8;
const int kWidth = 1500;
const int kHeight = 1000;
const int kFramerate = 60;

void SetUp(App::Settings* settings) {
  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("Synthwave vibe");
  settings->setFrameRate(kFramerate);
  // settings->setFullScreen();
}

}  // namespace myapp


// This is a macro that runs the application.
CINDER_APP(myapp::MyApp,
           RendererGl(RendererGl::Options().msaa(myapp::kSamples)),
           myapp::SetUp)
