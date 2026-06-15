#include "../include/win_evaluator.h"

std::vector<WinningLine> WinEvaluator::Evaluate(const Screen &screen,
                                                const GameConfig &config) {
  std::vector<WinningLine> wins;

  for (size_t lineIndex = 0; lineIndex < config.paylines.size(); ++lineIndex) {
    const auto &payline = config.paylines[lineIndex];

    Symbol first = screen.GetSymbol(0, payline.rows[0]);

    int matches = 1;

    for (size_t reel = 1; reel < payline.rows.size(); ++reel) {
      Symbol current = screen.GetSymbol(reel, payline.rows[reel]);

      if (current == first)
        matches++;
      else
        break;
    }

    if (matches >= 3) {
      int payout = config.paytable.GetPayout(first, matches);

      if (payout > 0) {
        wins.push_back({static_cast<int>(lineIndex), first, matches, payout});
      }
    }
  }

  return wins;
}
