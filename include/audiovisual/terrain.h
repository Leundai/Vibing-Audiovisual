// Copyright (c) 2020 Leonard Galindo. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <vector>

namespace audiovisual {

float Map( float value, float low1, float high1, float low2, float high2);

class Terrain {
 public:
  Terrain(int height, int width, int scale, bool can_shake);
  void DrawTerrain();
  void UpdateZValues(float y_pos, float bass_vol, float center_spec);
  void ToggleCanShake();

 private:
  std::vector<std::vector<float>> z_values;
  int height{};
  int width{};
  int scale{};
  bool can_shake{};
};

}  // namespace audiovisual


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
