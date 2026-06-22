#pragma once
#include "game_config.h"
#include "screen.h"
#include "winning_line.h"
#include <vector>

namespace SlotEngine {

// TODO : namespace WinEvaluator instead of class WinEvaluator for better design
/**
 * @brief Evaluates winning combinations on a slot machine screen.
 *
 * The WinEvaluator is responsible for analyzing a Screen state and
 * determining all winning outcomes based on the game's rules defined
 * in GameConfig. It supports both standard payline wins and scatter wins.
 *
 * Methods:
 * 1. Evaluate() - Evaluates all payline-based wins on the screen.
 * 2. EvaluateScatter() - Evaluates scatter symbol wins on the screen.
 */
class WinEvaluator {
public:
  /**
   * @brief Evaluates all payline-based wins on the screen.
   *
   * @param screen Current slot machine screen state.
   * @param config Game configuration containing paylines and paytable.
   * @return A list of all winning lines detected.
   */
  static std::vector<WinningLine> Evaluate(const Screen &screen,
                                           const GameConfig &config);

  /**
   * @brief Evaluates scatter symbol wins on the screen.
   *
   * Scatter wins are independent of paylines and are based on total
   * occurrences of scatter symbols across the screen.
   *
   * @param screen Current slot machine screen state.
   * @param config Game configuration (may define scatter rules/payouts).
   * @return A list of scatter-based winning lines.
   */
  static std::vector<WinningLine> EvaluateScatter(const Screen &screen,
                                                  const GameConfig &config);

private:
  /**
   * @brief Returns the base symbol from a specific reel position.
   *
   * Used as the starting symbol when evaluating a payline.
   */
  static Symbol GetBaseSymbol(const Screen &screen, int reel, int row);

  /**
   * @brief Counts consecutive matching symbols along a payline.
   *
   * Traverses the screen following the provided row pattern and counts
   * how many symbols match the initial symbol.
   *
   * @param screen Current screen state.
   * @param rows Payline row positions for each reel.
   * @param matchedSymbol Output parameter representing the symbol being
   * matched.
   * @return Number of consecutive matches from left to right.
   */
  static int CountMatches(const Screen &screen, const std::vector<int> &rows,
                          Symbol &matchedSymbol);

  /**
   * @brief Counts the number of scatter symbols on the screen.
   *
   * @param screen Current screen state.
   * @return Total number of scatter symbols found.
   */
  static int CountScatterSymbols(const Screen &screen);
};

} // namespace SlotEngine
