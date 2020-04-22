// Copyright (c) 2020 Leonard Galindo. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <vector>

namespace terrain {

class Terrain {
 public:
  Terrain();
  Terrain(int height, int width, int scale);
  void DrawTerrain(float y_offset);
  void UpdateZValues(float y_pos, float loud);

 private:
  std::vector<std::vector<float>> random;
  int height;
  int width;
  int scale;
  float y_noise;
};

}  // namespace terrain


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
