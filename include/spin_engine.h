#pragma once
#include "game_config.h"
#include "spin_result.h"
#include <random>

namespace SlotEngine {

class SpinEngine {
public:
  explicit SpinEngine(const GameConfig &config);

  SpinResult PerformSpin(std::mt19937 &rng, bool isFreeSpin = false);

private:
  GameConfig config;
  int GetFreeSpinsCount(int scatterCount) const;
};

} // namespace SlotEngine
