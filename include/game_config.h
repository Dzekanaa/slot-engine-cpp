#pragma once
#include "payline.h"
#include "paytable.h"
#include "reel.h"
#include <vector>

namespace SlotEngine {

struct GameConfig {
  int visibleRows = 3;
  std::vector<Reel> reels;
  std::vector<Payline> paylines;
  PayTable paytable;

  bool enableBaseGame = true;
  bool enableScatter = true;
  bool enableFreeSpins = true;

  double expectedRTP = 96.5;
  int maxFreeSpins = 100;

  explicit GameConfig(int paylineCount = 20);

  static GameConfig CreateClassicConfig();
  static GameConfig CreateHighVolatilityConfig();
  static GameConfig CreateLowVolatilityConfig();
};

} // namespace SlotEngine
