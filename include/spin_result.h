#pragma once
#include "winning_line.h"
#include <vector>

namespace SlotEngine {

/**
 * @brief Represents the result of a single slot machine spin.
 *
 * Contains all win-related information produced after evaluating a spin,
 * including base game wins, scatter wins, bonus wins, and triggered features
 * such as free spins or bonus games.
 *
 * Methods:
 * 1. IsHit() - Checks whether the spin resulted in any win.
 */
struct SpinResult {
  int totalWin = 0;
  int baseGameWin = 0;
  int scatterWin = 0;
  int bonusWin = 0;
  bool triggeredFreeSpins = false;
  int freeSpinsAwarded = 0;
  bool triggeredBonusGame = false;

  /**
   * @brief Checks whether the spin resulted in any win.
   *
   * @return true if totalWin is greater than 0, otherwise false.
   */
  bool IsHit() const { return totalWin > 0; }

  std::vector<WinningLine> winningLines;
};

} // namespace SlotEngine
