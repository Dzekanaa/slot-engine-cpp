#pragma once
#include "symbol.h"

namespace SlotEngine {

/**
 * @brief Represents a single winning line in a slot machine spin.
 *
 * A WinningLine stores information about a payline that resulted in a win,
 * including which payline was hit, which symbol formed the win, how many
 * consecutive matches occurred, and the resulting payout.
 */
struct WinningLine {
  int paylineIndex;
  Symbol symbol;
  int matchCount;
  int payout;
};

} // namespace SlotEngine
