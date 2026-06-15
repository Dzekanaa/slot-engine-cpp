#pragma once

#include "symbol.h"

struct WinningLine {
  int paylineIndex;
  Symbol symbol;
  int matchCount;
  int payout;
};
