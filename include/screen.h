#pragma once
#include "symbol.h"
#include <vector>

namespace SlotEngine {

/**
 * @brief Represents the visible screen of the slot engine.
 *
 * The Screen stores a 2D matrix of symbols where each column corresponds
 * to a reel and each row represents a visible position on that reel.
 * It is used to model the final displayed state after each spin.
 *
 * Methods:
 * 1. GetSymbol() - Returns the sumbols at the given reel and row position.
 * 2. Rows() - Returns the number of rows in the screen.
 * 3. Columns() - Returns the number of reels (columns) in the screen.
 */
class Screen {
private:
  std::vector<std::vector<Symbol>> columns;

public:
  /**
   * @brief Constructs a Screen from a matrix of symbol columns.
   *
   * @param columns 2D vector representing reels and their visible symbols.
   */
  Screen(const std::vector<std::vector<Symbol>> &columns);

  /**
   * @brief Returns the sumbols at the given reel and row position.
   *
   * @param reel Index of the reel (column).
   * @param row Index of a row within that reel.
   * @return Symbol at the specified position.
   */
  Symbol GetSymbol(int reel, int row) const;
  /**
   * @brief Returns the number of rows in the screen.
   *
   * @return Number of visible rows.
   */
  int Rows() const;
  /**
   * @brief Returns the number of reels (columns) in the screen.
   *
   * @return Number of visible columns in the screen.
   */
  int Columns() const;
};

} // namespace SlotEngine
