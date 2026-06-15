#pragma once
#include "game_config.h"
#include "screen.h"
#include "winning_line.h"
#include <vector>

class WinEvaluator {
public:
  static std::vector<WinningLine> Evaluate(const Screen &screen,
                                           const GameConfig &config);

private:
  static Symbol GetBaseSymbol(const Screen &screen, int reel, int row);
  static int CountMatches(const Screen &screen, const std::vector<int> &rows,
                          Symbol &matchedSymbol);
};
