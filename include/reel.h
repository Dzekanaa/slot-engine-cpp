#pragma once

#include "symbol.h"
#include <vector>

namespace SlotEngine {
/**
 * @brief Represents a single reel in the slot engine.
 *
 * A reel contains a ordered sequence of symbols (called a strip)
 * During a spin, symbols are selected from the strip based on a stop
 * position and displayed on the game screen.
 *
 * Methods:
 * 1. GetSymbol() - Returns the symbol on the specified position.
 * 2. GetSize() - Returns number of symbols on the reel.
 */
class Reel {
private:
  std::vector<Symbol> strip;

public:
  Reel() = default;

  /**
   * @brief Constructs a reel with the specified symbol strip.
   *
   * @param strip Ordered list of symbols that make up the reel.
   */
  explicit Reel(const std::vector<Symbol> &strip);

  /**
   * @brief Returns the symbol on the specified position.
   *
   * @param index Position within the reel strip.
   * @return Symbol stored at the given position.
   */
  Symbol GetSymbol(int index) const;

  /**
   * @brief Returns number of symbols on the reel.
   *
   * @return Size of the reel strip.
   */
  int Size() const;
};
} // namespace SlotEngine
