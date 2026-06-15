#pragma once
#include "game_config.h"
#include "screen.h"
#include "winning_line.h"
#include <vector>

class WinEvaluator {
public:
  static std::vector<WinningLine> Evaluate(const Screen &screen,
                                           const GameConfig &config);
};
