// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <audiovisual/terrain.h>
#include <audiovisual/utilities.h>

#include <catch2/catch.hpp>

TEST_CASE("Valid Music File Path", "[file-handling]") {
  std::vector<fs::path> file_paths{
      "D:\\Documents\\Cinder\\my-projects\\final-project-"
      "Leundai\\tests\\assets\\caravan.mp3",
      "D:\\Documents\\Cinder\\my-projects\\final-project-"
      "Leundai\\tests\\assets\\caravan.mp3"};
  bool is_valid = audiovisual::AreValidFiles(file_paths);
  REQUIRE(is_valid);
}

TEST_CASE("Wav Files Test", "[file-handling]") {
  std::vector<fs::path> file_paths{
      "D:\\Documents\\Cinder\\my-projects\\final-project-"
      "Leundai\\tests\\assets\\atom.wav"};
  bool is_valid = audiovisual::AreValidFiles(file_paths);
  REQUIRE(is_valid);
}

TEST_CASE("Invalid Music Path", "[file-handling]") {
  std::vector<fs::path> file_paths{
      "D:\\Documents\\Cinder\\my-projects\\final-project-"
      "Leundai\\tests\\assets\\fake.wav"};
  bool is_valid = audiovisual::AreValidFiles(file_paths);
  REQUIRE_FALSE(is_valid);
}

TEST_CASE("Sanitize Non Music Files", "[file-handling]") {
  std::vector<fs::path> file_paths{
      "D:\\Documents\\Cinder\\my-projects\\final-project-"
      "Leundai\\tests\\assets"};
  bool is_valid = audiovisual::AreValidFiles(file_paths);
  REQUIRE(is_valid);
  REQUIRE(file_paths.size() == 3);
}

TEST_CASE("Mapping Correctness", "[map]") {
  float mapped = audiovisual::Map(5, 0, 10, 0, 1);
  REQUIRE(mapped == .5f);
}

TEST_CASE("Mapping Uneven Values", "[map]") {
  float mapped = audiovisual::Map(.1, 0, .4, 0, 9);
  REQUIRE(mapped < 4.5f);
}

TEST_CASE("Reduction Mapping", "[map]") {
  float mapped = audiovisual::Map(10, 0, 50, 0, 1);
  REQUIRE(mapped == .2f);
}

TEST_CASE("Simplex Noise Terrain Test", "[terrain]") {
  audiovisual::Terrain terrain(2, 2, 10, true);
  std::vector<std::vector<float>> z_values = terrain.UpdateZValues(0, 0, 0);
  REQUIRE(!z_values.empty());

  SECTION("Test Corners have a value") {
    z_values = terrain.UpdateZValues(.5, .5, .5);
    REQUIRE(z_values[1][1] != 0);
    REQUIRE(z_values[0][0] != 0);
  }
}