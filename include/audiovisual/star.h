// Copyright (c) 2020 Leonard Galindo. All rights reserved.
#ifndef FINALPROJECT_STAR_H
#define FINALPROJECT_STAR_H
#include <cinder/gl/gl.h>

namespace audiovisual {
class Star {
 public:
  Star(const glm::vec3& position, cinder::gl::BatchRef& batch_sphere_);
  // This draws it using opengl taking in a scale of frequency
  void DrawStar(float magnitude);

 private:
  glm::vec3 position;
  cinder::gl::BatchRef batch_sphere_;
};
}

#endif  // FINALPROJECT_STAR_H
