#pragma once
#include "symbol.h"

namespace SlotEngine {

struct WinningLine {
  int paylineIndex;
  Symbol symbol;
  int matchCount;
  int payout;
};

} // namespace SlotEngine
