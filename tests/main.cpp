#include "../include/game_config.h"
#include "../include/slot_engine.h"
#include <iostream>

using namespace SlotEngine;

int main() {
  std::cout << "Testing Slot Engine...\n";

  GameConfig config(20);

  std::unique_ptr<ISlotEngine> engine = CreateSlotEngine(config);

  const int numSpins = 10;
  int totalWins = 0;

  for (int i = 0; i < numSpins; ++i) {
    SpinResult result = engine->Spin();
    totalWins += result.totalWin;

    std::cout << "Spin " << i + 1 << ": Won " << result.totalWin
              << " coins (Base: " << result.baseGameWin
              << ", Scatter: " << result.scatterWin
              << ", Bonus: " << result.bonusWin << ")\n";

    if (result.triggeredFreeSpins) {
      std::cout << "  -> Triggered " << result.freeSpinsAwarded
                << " free spins!\n";
    }
  }

  std::cout << "\nTotal wins after " << numSpins << " spins: " << totalWins
            << "\n";

  return 0;
}
