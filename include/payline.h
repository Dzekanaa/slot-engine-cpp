#pragma once

#include <vector>

namespace SlotEngine {

/**
 * @brief Represents a payline in a slot engine.
 *
 * A payline defines the pattern of rows across reels that is used to
 * evaluate winning combinations. Each element in `rows` corresponds to
 * the selected row index for a specific reel.
 */
struct Payline {
  std::vector<int> rows;
};
} // namespace SlotEngine
