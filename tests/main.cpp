#include <iostream>
#include <random>

#include "../include/spin_engine.h"

void PrintScreen(const Screen &screen) {
  for (int row = 0; row < screen.Rows(); row++) {
    for (int col = 0; col < screen.Columns(); col++) {
      std::cout << SymbolToString(screen.GetSymbol(col, row)) << " ";
    }

    std::cout << '\n';
  }
}

int main() {
  GameConfig config(40);

  std::mt19937 rng(std::random_device{}());

  SpinEngine engine(config);

  auto result = engine.Spin(rng);

  std::cout << "\nSCREEN\n\n";

  PrintScreen(result.screen);

  std::cout << "\nTOTAL WIN: " << result.totalWin << "\n";

  for (const auto &win : result.winningLines) {
    std::cout << "Line " << win.paylineIndex << " "
              << SymbolToString(win.symbol) << " x" << win.matchCount << " -> "
              << win.payout << "\n";
  }

  long long totalBet = 0;
  long long totalWin = 0;

  for (long long i = 0; i < 1000000; i++) {
    auto spin = engine.Spin(rng);

    totalBet += 1;
    totalWin += spin.totalWin;
  }

  double rtp = static_cast<double>(totalWin) / static_cast<double>(totalBet);

  std::cout << "rtp: " << rtp * 100 << '%' << std::endl;
}
