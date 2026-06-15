#pragma once

#include <vector>

#include "payline.h"
#include "paytable.h"
#include "reel.h"

struct GameConfig {
  int visibleRows = 3;

  std::vector<Reel> reels;
  std::vector<Payline> paylines;
  PayTable paytable;

  explicit GameConfig(int paylineCount = 20);

private:
  static std::vector<Payline> CreatePaylines(int count);
  static std::vector<Reel> CreateDefaultReels();
  static void SetupDefaultPaytable(PayTable &paytable);
};
