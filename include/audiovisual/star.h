// Copyright (c) 2020 Leonard Galindo. All rights reserved.
#ifndef FINALPROJECT_STAR_H
#define FINALPROJECT_STAR_H
#include <cinder/gl/gl.h>

namespace audiovisual {
class Star {
 public:
  Star (cinder::ColorAf color, glm::vec3 position, cinder::gl::BatchRef &mSphere);
  void DrawStar(float magnitude);
 private:
  cinder::Color color;
  glm::vec3 position;
  cinder::gl::BatchRef mSphere;
  cinder::gl::GlslProgRef mGlsl;
};
}

#endif  // FINALPROJECT_STAR_H
