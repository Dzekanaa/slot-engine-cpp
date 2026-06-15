#pragma once

#include <vector>

#include "screen.h"
#include "winning_line.h"

struct SpinResult {
  Screen screen;

  std::vector<int> stopPositions;

  int totalWin = 0;

  std::vector<WinningLine> winningLines;
};
