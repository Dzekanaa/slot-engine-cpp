#pragma once
#include "payline.h"
#include "paytable.h"
#include "reel.h"
#include <vector>

namespace SlotEngine {

/**
 * @brief Central configuration structure for the slot machine game.
 *
 * GameConfig defines all parameters required to run a slot engine,
 * including reels, paylines, paytable, game feature toggles, and
 * mathematical constraints such as RTP and free spin limits.
 */
struct GameConfig {
  int visibleRows = 3;
  std::vector<Reel> reels;
  std::vector<Payline> paylines;
  PayTable paytable;

  bool enableBaseGame = true;
  bool enableScatter = true;
  bool enableFreeSpins = true;

  double expectedRTP = 96.5;
  int maxFreeSpins = 100;

  /**
   * @brief Constructs a configuration with a given number of paylines.
   *
   * @param paylineCount Number of paylines to generate.
   */
  explicit GameConfig(int paylineCount = 20);

  /**
   * @brief Creates a classic slot machine configuration.
   *
   * @return GameConfig with standard balanced settings.
   */
  static GameConfig CreateClassicConfig();

  /**
   * @brief Creates a high volatility configuration.
   *
   * Higher variance, less frequent wins, but larger payouts.
   */
  static GameConfig CreateHighVolatilityConfig();

  /**
   * @brief Creates a low volatility configuration.
   *
   * More frequent wins, but smaller payouts.
   */
  static GameConfig CreateLowVolatilityConfig();

private:
  /**
   * @brief Generates a set of paylines.
   *
   * @param count Number of paylines to create.
   * @return Vector of generated paylines.
   */
  static std::vector<Payline> CreatePaylines(int count);

  /**
   * @brief Creates default reel strips for the game.
   *
   * @return Vector of initialized reels.
   */
  static std::vector<Reel> CreateDefaultReels();

  /**
   * @brief Initializes default payout values for all symbols.
   *
   * @param paytable PayTable to initialize.
   */
  static void SetupDefaultPaytable(PayTable &paytable);
};
} // namespace SlotEngine
