// Copyright (c) 2020 Leonardo Galindo. All rights reserved.
// Map Code / Terrain Generation Sourced from here:
// https://www.youtube.com/watch?v=IKB1hWWedMk

#include <Simplex.h>
#include <audiovisual/terrain.h>
#include <cinder/gl/gl.h>

namespace terrain {

void Terrain::DrawTerrain(float y_offset) {
  cinder::gl::polygonMode(GL_FRONT, GL_LINE);
  for (int y = 0; y < height - 1; y++) {
    cinder::gl::begin(GL_TRIANGLE_STRIP);
    for (int x = 0; x < width; x++) {
      cinder::gl::vertex(x * scale, y * scale, random.at(y).at(x));
      cinder::gl::vertex(x * scale, (y + 1) * scale, random.at(y + 1).at(x));
    }
    cinder::gl::end();
  }
}

// Sourced: https://stackoverflow.com/questions/3451553/value-remapping
float Map( float value, float low1, float high1, float low2, float high2) {
  return low2 + (value - low1) * (high2 - low2) / (high1 - low1);
}

void Terrain::UpdateZValues(float y_pos, float loud) {
  //  random.erase(random.begin());
  //  random.emplace_back();
  //  float x_pos = 0;
  //  for (int x = 0; x < width; x++) {
  //    random.at(random.size()-1).push_back(Map(Simplex::noise(glm::vec2(y_pos
  //    + y_noise, x_pos)) + (loud*2), 0, 1, -50, 50)); x_pos += .04;
  //  }
  //  y_noise += .06;
  //  if (y_noise > (height * .06)) {
  //    y_noise = 0;
  //  }
  float y_off = y_pos;
  for (int y = 0; y < height; y++) {
    float x_off = 0;
    for (int x = 0; x < width; x++) {
      float thresh_hold_vol = 0;
      if (loud > .2) {
        thresh_hold_vol = loud;
      }
      random.at(y).at(x) =
          (Map(Simplex::noise(glm::vec2(x_off, y_off + thresh_hold_vol)), 0, 1,
               -50, 50));
      x_off += 0.055;
    }
    y_off += 0.075;
  }
}


Terrain::Terrain() {}

Terrain::Terrain(int height, int width, int scale) {
  this->height = height;
  this->width = width;
  this->scale = scale;
  y_noise = 0;

  float y_off = 0;
  for (int y = 0; y < height; y++) {
    float x_off = 0;
    random.emplace_back();
    for (int x = 0; x < width; x++) {
      random.at(y).push_back(
          Map(Simplex::noise(glm::vec2(x_off, y_off)), 0, 1, -50, 50));
      x_off += .04;
    }
    y_off += 0.075;
  }
}
}  // namespace terrain
