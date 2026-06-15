#pragma once
#include "symbol.h"
#include <unordered_map>

namespace SlotEngine {

struct PayoutValues {
  int three;
  int four;
  int five;
};

class PayTable {
public:
  void SetPayout(Symbol symbol, int three, int four, int five);
  int GetPayout(Symbol symbol, int count) const;

private:
  std::unordered_map<int, PayoutValues> payouts;
};

} // namespace SlotEngine
