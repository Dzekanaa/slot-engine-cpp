#include "../include/spin_engine.h"
#include "../include/screen.h"
#include "../include/win_evaluator.h"
#include <random>

namespace SlotEngine {

SpinEngine::SpinEngine(const GameConfig &cfg) : config(cfg) {}

SpinResult SpinEngine::PerformSpin(std::mt19937 &rng, bool isFreeSpinMode) {
  SpinResult result;

  // 1. Generiši vidljive simbole
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

  // 2. Evaluacija svih dobitaka
  auto wins = WinEvaluator::Evaluate(screen, config);

  // 3. Popuni rezultat
  result.totalWin = 0;
  result.baseGameWin = 0;
  result.scatterWin = 0;
  result.bonusWin = 0;
  result.triggeredFreeSpins = false;
  result.freeSpinsAwarded = 0;

  for (const auto &win : wins) {
    int payout = win.payout;

    // Primeni 2x multiplier samo ako je free spin
    if (isFreeSpinMode) {
      payout *= 2;
    }

    result.totalWin += payout;
    result.winningLines.push_back(win);

    if (win.paylineIndex == -1 || win.symbol == Symbol::Scatter) {
      result.scatterWin += payout;

      // Tokom free spinova, triggeruj dodatne free spinove
      if (config.enableFreeSpins && win.matchCount >= 3) {
        result.triggeredFreeSpins = true;
        result.freeSpinsAwarded = GetFreeSpinsCount(win.matchCount);
      }
    } else {
      result.baseGameWin += payout;
    }
  }

  // 4. Simuliraj free spinove (samo iz base game-a, ne iz free spinova)
  if (result.triggeredFreeSpins && config.enableFreeSpins && !isFreeSpinMode) {
    int freeSpinsRemaining = result.freeSpinsAwarded;

    while (freeSpinsRemaining > 0) {
      auto freeSpinResult = PerformSpin(rng, true); // ← true = free spin mode
      result.bonusWin += freeSpinResult.totalWin;

      // Ako se triggeruju novi free spinovi, dodaj ih
      if (freeSpinResult.triggeredFreeSpins) {
        freeSpinsRemaining += freeSpinResult.freeSpinsAwarded;
      }

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
