#pragma once
#include "game_config.h"
#include "spin_result.h"
#include <random>

namespace SlotEngine {

/**
 * @brief Core engine responsible for executing slot machine spins.
 *
 * The SpinEngine generates spin results based on the game configuration,
 * random number generator, and current game mode (base game or free spin).
 * It coordinates reel generation, screen creation, and win evaluation.
 *
 * Methods:
 * 1. PerformSpin() - Performs a single spin of the slot machine.
 */
class SpinEngine {
public:
  /**
   * @brief Constructs the SpinEngine with a given game configuration.
   *
   * @param config Game configuration containing reels, paylines, paytable, etc.
   */
  explicit SpinEngine(const GameConfig &config);

  /**
   * @brief Performs a single spin of the slot machine.
   *
   * Generates a random outcome using the provided RNG, builds the screen,
   * evaluates wins, and returns the complete spin result.
   *
   * @param rng Random number generator used for spin randomness.
   * @param isFreeSpin Indicates whether the spin is part of a free spin round.
   * @return Complete result of the spin including wins and triggers.
   */
  SpinResult PerformSpin(std::mt19937 &rng, bool isFreeSpin = false);

private:
  GameConfig config;

  /**
   * @brief Calculates number of free spins awarded based on scatter count.
   *
   * @param scatterCount Number of scatter symbols on the screen.
   * @return Number of free spins awarded.
   */
  int GetFreeSpinsCount(int scatterCount) const;
};

} // namespace SlotEngine
