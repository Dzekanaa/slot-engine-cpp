#include "../include/spin_engine.h"
#include "../include/win_evaluator.h"

SpinEngine::SpinEngine(GameConfig config) : config(std::move(config)) {}

SpinResult SpinEngine::Spin(std::mt19937 &rng) const {
  SpinResult result;

  std::vector<std::vector<Symbol>> columns;

  for (const Reel &reel : config.reels) {
    std::uniform_int_distribution<int> dist(0, reel.Size() - 1);

    int stop = dist(rng);

    result.stopPositions.push_back(stop);

    std::vector<Symbol> visible;

    for (int row = 0; row < config.visibleRows; row++) {
      visible.push_back(reel.GetSymbol(stop + row));
    }

    columns.push_back(visible);
  }

  result.screen = Screen(columns);

  result.winningLines = WinEvaluator::Evaluate(result.screen, config);

  for (const auto &win : result.winningLines) {
    result.totalWin += win.payout;
  }

  return result;
}
