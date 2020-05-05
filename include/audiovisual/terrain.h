// Copyright (c) 2020 Leonard Galindo. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <vector>

namespace audiovisual {

class Terrain {
 public:
  Terrain(int height, int width, int scale, bool can_shake);
  // Drawing using Opengl
  void DrawTerrain();
  // Updating the 2-Dimensional Vector with z-values across terrain
  // Takes in the bass volume and also the brightness in hertz
  std::vector<std::vector<float>> UpdateZValues(float y_pos, float bass_vol,
                                                float center_spec);
  // Shaking of the terrain when bass is loud
  void ToggleCanShake();

 private:
  std::vector<std::vector<float>> z_values;
  int height{};
  int width{};
  int scale{};
  bool can_shake{};
};

}  // namespace audiovisual

#endif  // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
