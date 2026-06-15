#include "../include/win_evaluator.h"
#include "../include/game_config.h"
#include "../include/screen.h"

namespace SlotEngine {

Symbol WinEvaluator::GetBaseSymbol(const Screen &screen, int reel, int row) {
  Symbol sym = screen.GetSymbol(reel, row);

  if (sym == Symbol::Wild) {
    return Symbol::Wild;
  }
  return sym;
}

int WinEvaluator::CountMatches(const Screen &screen,
                               const std::vector<int> &rows,
                               Symbol &matchedSymbol) {
  int matches = 0;
  matchedSymbol = Symbol::Wild;

  for (size_t reel = 0; reel < rows.size(); ++reel) {
    Symbol current = screen.GetSymbol(reel, rows[reel]);

    // Ignoriši Scatter u regularnim paylinama
    if (current == Symbol::Scatter) {
      continue;
    }

    if (current == Symbol::Wild) {
      matches++;
      continue;
    }

    if (matchedSymbol == Symbol::Wild) {
      matchedSymbol = current;
      matches++;
      continue;
    }

    if (current == matchedSymbol) {
      matches++;
    } else {
      break;
    }
  }

  return matches;
}

int WinEvaluator::CountScatterSymbols(const Screen &screen) {
  int count = 0;

  // Prolazi kroz sve kolone (reelove) i sve redove
  for (int reel = 0; reel < screen.Columns(); ++reel) {
    for (int row = 0; row < screen.Rows(); ++row) {
      if (screen.GetSymbol(reel, row) == Symbol::Scatter) {
        count++;
      }
    }
  }

  return count;
}

std::vector<WinningLine>
WinEvaluator::EvaluateScatter(const Screen &screen, const GameConfig &config) {
  std::vector<WinningLine> scatterWins;

  int scatterCount = CountScatterSymbols(screen);

  if (scatterCount >= 3) {
    int payout = config.paytable.GetPayout(Symbol::Scatter, scatterCount);

    if (payout > 0) {
      scatterWins.push_back({-1, Symbol::Scatter, scatterCount, payout});
    }
  }

  return scatterWins;
}

std::vector<WinningLine> WinEvaluator::Evaluate(const Screen &screen,
                                                const GameConfig &config) {
  std::vector<WinningLine> wins;

  // Evaluacija regularnih paylina
  for (size_t lineIndex = 0; lineIndex < config.paylines.size(); ++lineIndex) {
    const auto &payline = config.paylines[lineIndex];

    Symbol matchedSymbol;
    int matches = CountMatches(screen, payline.rows, matchedSymbol);

    if (matches >= 3 && matchedSymbol != Symbol::Wild &&
        matchedSymbol != Symbol::Scatter) {
      int payout = config.paytable.GetPayout(matchedSymbol, matches);

      if (payout > 0) {
        wins.push_back(
            {static_cast<int>(lineIndex), matchedSymbol, matches, payout});
      }
    }
  }

  // Dodaj scatter dobitke
  std::vector<WinningLine> scatterWins = EvaluateScatter(screen, config);
  wins.insert(wins.end(), scatterWins.begin(), scatterWins.end());

  return wins;
}

} // namespace SlotEngine
