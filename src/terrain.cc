// Copyright (c) 2020 Leonardo Galindo. All rights reserved.
// Map Code / Terrain Generation Sourced from here:
// https://www.youtube.com/watch?v=IKB1hWWedMk

#include <Simplex.h>
#include <audiovisual/terrain.h>
#include <audiovisual/utilities.h>
#include <cinder/gl/gl.h>

namespace audiovisual {
// Ranges of the z-values of the mountains
const int kHighPoint = 50;
const int kLowPoint = -50;
// The increment of the simplex noise it is fed
const float kXIncrement = 0.03;
const float kYIncrement = 0.05;

void Terrain::DrawTerrain() {
  auto f_scale = (float)scale;
  ci::gl::ScopedPolygonMode poly(GL_LINE);
  for (int y = 0; y < height - 1; y++) {
    cinder::gl::begin(GL_TRIANGLE_STRIP);
    for (int x = 0; x < width; x++) {
      // Using triangle strips it scales it to opengl window
      cinder::gl::vertex((float)x * f_scale, (float)y * f_scale,
                         z_values.at(y).at(x));
      cinder::gl::vertex((float)x * f_scale, ((float)y + 1) * f_scale,
                         z_values.at(y + 1).at(x));
    }
    cinder::gl::end();
  }
}

float past_center_spec = 0;  // This is meant to average out the last spectroid
std::vector<std::vector<float>> Terrain::UpdateZValues(float y_pos,
                                                       float bass_vol,
                                                       float center_spec) {
  float mapped_y_volume = 0;
  float mapped_x_volume = 0;
  if (can_shake) {
    mapped_y_volume = Map(bass_vol, 0, .1, 0, .01);
    mapped_x_volume =
        Map((center_spec + past_center_spec) / 2, 0, 10000, 0, .1);
    // Volume ranges for DFT are 0 to 1, and we want to map it to a smaller
    // value of 0 to .005 for our Simplex Noise to not shake too much
  }
  past_center_spec = center_spec;

  float noise_y = y_pos;
  for (int y = 0; y < height; y++) {
    float noise_x = 0;
    for (int x = 0; x < width; x++) {
      z_values.at(y).at(x) =
          (Map(Simplex::noise(glm::vec3(noise_x, noise_y, mapped_x_volume)), 0,
               1, kLowPoint, kHighPoint));
      // Range of -50 to 50 for our max Z values, can be changed
      noise_x += kXIncrement + mapped_y_volume;
    }
    noise_y += kYIncrement;
  }
  return z_values;
}

Terrain::Terrain(int height, int width, int scale, bool can_shake) {
  this->height = height;
  this->width = width;
  this->scale = scale;
  this->can_shake = can_shake;

  // Allocate memory for our z_values and initialize
  for (int y = 0; y < height; y++) {
    z_values.emplace_back();
    for (int x = 0; x < width; x++) {
      z_values.at(y).push_back(0);
    }
  }
}

void Terrain::ToggleCanShake() { can_shake = !can_shake; }
}  // namespace audiovisual
