#pragma once

#include <random>

#include "game_config.h"
#include "spin_result.h"

class SpinEngine {
private:
  GameConfig config;

public:
  explicit SpinEngine(GameConfig config);

  SpinResult Spin(std::mt19937 &rng) const;
};
