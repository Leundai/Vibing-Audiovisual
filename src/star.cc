// Copyright (c) 2020 Leonardo Galindo. All rights reserved.

#include "audiovisual/star.h"
#include <cinder/gl/gl.h>

namespace audiovisual {
Star::Star(const glm::vec3& position, cinder::gl::BatchRef& batch_sphere_) {
  this->position = position;
  this->batch_sphere_ = batch_sphere_;
}

void Star::DrawStar(float magnitude) {
  {
    cinder::gl::pushModelMatrix();
    cinder::gl::translate(position);
    cinder::gl::scale(glm::vec3(10 + magnitude));
    batch_sphere_->draw();
    cinder::gl::popModelMatrix();
  }
}
}