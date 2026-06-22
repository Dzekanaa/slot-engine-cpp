#pragma once
#include "symbol.h"
#include <unordered_map>

namespace SlotEngine {

/**
 * @brief Stores payout values for a symbol based on match count.
 *
 * Each symbol can have different payouts depending on how many times
 * it appears consecutively (e.g. 3, 4, or 5 matches).
 * Matching symbols are counted strictly from the left.
 */
struct PayoutValues {
  int three;
  int four;
  int five;
};

/**
 * @brief Represents the paytable of a slot machine.
 *
 * The PayTable maps each symbol to its payout values, which define
 * how much the player wins depending on the number of matched symbols.
 *
 * Methods:
 * 1. SetPayout - Sets payout values for a specific symbol.
 * 2. GetPayout - Returns payout for a symbol based on match count.
 */
class PayTable {
public:
  /**
   * @brief Sets payout values for a specific symbol.
   *
   * @param symbol The symbol for which payout is defined.
   * @param three Payout for 3 matches.
   * @param four Payout for 4 matches.
   * @param five Payout for 5 matches.
   */
  void SetPayout(Symbol symbol, int three, int four, int five);

  /**
   * @brief Returns payout for a symbol based on match count.
   *
   * @param symbol The symbol being evaluated.
   * @param count Number of matching symbols (typically 3–5).
   * @return Payout value, or 0 if no valid payout exists.
   */
  int GetPayout(Symbol symbol, int count) const;

private:
  std::unordered_map<int, PayoutValues>
      payouts; // TODO : change int to type Symbol for stronger typing.
};

} // namespace SlotEngine
