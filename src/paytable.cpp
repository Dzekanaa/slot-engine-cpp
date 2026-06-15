#include "../include/paytable.h"

namespace SlotEngine {

void PayTable::SetPayout(Symbol symbol, int three, int four, int five) {
  payouts[(int)symbol] = {three, four, five};
}

int PayTable::GetPayout(Symbol symbol, int count) const {
  auto it = payouts.find((int)symbol);

  if (it == payouts.end())
    return 0;

  if (count == 3)
    return it->second.three;

  if (count == 4)
    return it->second.four;

  if (count == 5)
    return it->second.five;

  return 0;
}

} // namespace SlotEngine
