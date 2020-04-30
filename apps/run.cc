// Copyright (c) 2020 Leonardo Galindo. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>

#include "vibe_app.h"

using cinder::app::App;
using cinder::app::RendererGl;


namespace app {

const int kSamples = 8;
const int kWidth = 1920;
const int kHeight = 1080;
const int kFramerate = 60;

void SetUp(App::Settings* settings) {
  settings->setWindowSize(kWidth, kHeight);
  settings->setFrameRate(kFramerate);
  settings->setTitle("Synthwave vibe");
  //settings->setFullScreen();
}

}  // namespace app


// This is a macro that runs the application.
CINDER_APP(app::MyApp,
           RendererGl(RendererGl::Options().msaa(app::kSamples)), app::SetUp)
