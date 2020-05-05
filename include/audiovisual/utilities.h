// Copyright (c) 2020 Leonardo Galindo. All rights reserved.

#ifndef FINALPROJECT_UTILITIES_H
#define FINALPROJECT_UTILITIES_H
#include <filesystem>

namespace fs = std::experimental::filesystem;

namespace audiovisual {
// Maps the values to a certain range from a given range
float Map(float value, float low1, float high1, float low2, float high2);

// Validates certain files specifically .mp3 and .wav
bool AreValidFiles(std::vector<fs::path> &file_paths);
}  // namespace audiovisual

#endif  // FINALPROJECT_UTILITIES_H
