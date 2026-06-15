#pragma once

#include "symbol.h"
#include <unordered_map>

struct SymbolPayout {
  int three;
  int four;
  int five;
};

class PayTable {
private:
  std::unordered_map<int, SymbolPayout> payouts;

public:
  void SetPayout(Symbol symbol, int three, int four, int five);

  int GetPayout(Symbol symbol, int count) const;
};
