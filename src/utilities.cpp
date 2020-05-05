// Copyright (c) 2020 Leonardo Galindo. All rights reserved.

#include "audiovisual/utilities.h"

namespace audiovisual {

// Sourced: https://stackoverflow.com/questions/3451553/value-remapping
float Map(float value, float low1, float high1, float low2, float high2) {
  return low2 + (high2 - low2) * ((value - low1) / (high1 - low1));
}

// This program only accepts single folders with music
void SanitizeGivenPaths(std::vector<fs::path> &file_paths) {
  if (file_paths.size() == 1 && fs::is_directory(file_paths[0])) {
    fs::path folder_path = file_paths[0];
    file_paths.clear();
    for (const auto &entry : fs::directory_iterator(folder_path)) {
      if (entry.path().extension() == ".mp3" ||
          entry.path().extension() == ".wav") {
        file_paths.push_back(entry);
      }
    }
  }
}

bool AreValidFiles(std::vector<fs::path> &file_paths) {
  SanitizeGivenPaths(file_paths);

  for (const auto &entry : file_paths) {
    if ((entry.extension() == ".mp3" || entry.extension() == ".wav") &&
        fs::exists(entry)) {
      continue;
    } else {
      return false;
    }
  }
  return true;
}

}  // namespace audiovisual
