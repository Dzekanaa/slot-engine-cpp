#include "../include/spin_engine.h"
#include "../include/screen.h"
#include "../include/win_evaluator.h"
#include <random>

namespace SlotEngine {

SpinEngine::SpinEngine(const GameConfig &cfg) : config(cfg) {}

SpinResult SpinEngine::PerformSpin(std::mt19937 &rng, bool isFreeSpin) {
  SpinResult result;

  std::vector<std::vector<Symbol>> visibleSymbols;
  for (const auto &reel : config.reels) {
    std::uniform_int_distribution<int> dist(0, reel.Size() - 1);
    int startPos = dist(rng);

    std::vector<Symbol> column;
    for (int row = 0; row < config.visibleRows; ++row) {
      column.push_back(reel.GetSymbol(startPos + row));
    }
    visibleSymbols.push_back(column);
  }

  Screen screen(visibleSymbols);

  std::vector<WinningLine> wins = WinEvaluator::Evaluate(screen, config);

  result.totalWin = 0;
  result.baseGameWin = 0;
  result.scatterWin = 0;
  result.bonusWin = 0;
  result.triggeredFreeSpins = false;
  result.freeSpinsAwarded = 0;

  for (const auto &win : wins) {
    result.totalWin += win.payout;
    result.winningLines.push_back(win);

    if (win.paylineIndex == -1 || win.symbol == Symbol::Scatter) {
      result.scatterWin += win.payout;

      // Check for free spin trigger only if NOT already in a free spin
      if (!isFreeSpin && config.enableFreeSpins && win.matchCount >= 3) {
        result.triggeredFreeSpins = true;
        result.freeSpinsAwarded = GetFreeSpinsCount(win.matchCount);
      }
    } else {
      result.baseGameWin += win.payout;
    }
  }

  // Handle free spins - but only if triggered and not already in a free spin
  if (result.triggeredFreeSpins && !isFreeSpin && config.enableFreeSpins) {
    int freeSpinsRemaining = result.freeSpinsAwarded;
    int freeSpinsMultiplier = 1; // Could be configurable

    while (freeSpinsRemaining > 0) {
      auto freeSpinResult =
          PerformSpin(rng, true); // Pass true to prevent re-trigger

      int multipliedWin = freeSpinResult.totalWin * freeSpinsMultiplier;
      result.bonusWin += multipliedWin;

      // TODO : track scatter wind form free spins separately
      freeSpinsRemaining--;
    }

    result.totalWin += result.bonusWin;
  }

  return result;
}

int SpinEngine::GetFreeSpinsCount(int scatterCount) const {
  switch (scatterCount) {
  case 3:
    return 10;
  case 4:
    return 15;
  case 5:
    return 20;
  default:
    return 0;
  }
}

} // namespace SlotEngine
