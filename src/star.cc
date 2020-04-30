// Copyright (c) 2020 Leonardo Galindo. All rights reserved.

#include "audiovisual/star.h"
#include <cinder/gl/gl.h>

namespace audiovisual {
Star::Star(cinder::ColorAf color, glm::vec3 position,
           cinder::gl::BatchRef &mSphere) {
  this->color = color;
  this->position = position;
  this->mSphere = mSphere;
}


void Star::DrawStar(float magnitude) {
  {
    cinder::gl::pushModelMatrix();
    cinder::gl::translate(position);
    cinder::gl::scale(glm::vec3(10 + magnitude));
    //cinder::gl::ScopedColor scopedColor(glm::vec4(.1f, .5f, .5f, .75f));
    mSphere->draw();
    cinder::gl::popModelMatrix();
  }
}
}