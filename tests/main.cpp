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

  config.visibleRows = 3;

  Reel reel({Symbol::A, Symbol::K, Symbol::Q, Symbol::J, Symbol::T,
             Symbol::Nine, Symbol::Eight, Symbol::Seven, Symbol::Six,
             Symbol::Five});

  config.reels = {reel, reel, reel, reel, reel};

  config.paytable.SetPayout(Symbol::A, 10, 50, 200);

  config.paytable.SetPayout(Symbol::K, 8, 40, 150);

  config.paytable.SetPayout(Symbol::Q, 6, 30, 100);

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
