#pragma once
#include "winning_line.h"
#include <vector>

namespace SlotEngine {

struct SpinResult {
  int totalWin = 0;
  int baseGameWin = 0;
  int scatterWin = 0;
  int bonusWin = 0;
  bool triggeredFreeSpins = false;
  int freeSpinsAwarded = 0;
  bool triggeredBonusGame = false;

  bool IsHit() const { return totalWin > 0; }

  std::vector<WinningLine> winningLines;
};

} // namespace SlotEngine
