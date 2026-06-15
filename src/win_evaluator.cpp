#include "../include/win_evaluator.h"

Symbol WinEvaluator::GetBaseSymbol(const Screen &screen, int reel, int row) {
  Symbol sym = screen.GetSymbol(reel, row);

  // Ako je Wild, tražimo prvi ne-Wild simbol od pozicije 0 pa nadalje
  if (sym == Symbol::Wild) {
    // Ovo će se koristiti za određivanje baznog simbola za paylinu
    return Symbol::Wild; // Vraćamo Wild, ali će logika kasnije tretirati
                         // posebno
  }
  return sym;
}

int WinEvaluator::CountMatches(const Screen &screen,
                               const std::vector<int> &rows,
                               Symbol &matchedSymbol) {
  int matches = 0;
  matchedSymbol = Symbol::Wild; // Počinjemo sa Wild kao placeholder

  for (size_t reel = 0; reel < rows.size(); ++reel) {
    Symbol current = screen.GetSymbol(reel, rows[reel]);

    // Ako je trenutni simbol Wild
    if (current == Symbol::Wild) {
      matches++;
      continue;
    }

    // Ako smo tek počeli ili je matchedSymbol još uvek Wild
    if (matchedSymbol == Symbol::Wild) {
      matchedSymbol = current;
      matches++;
      continue;
    }

    // Ako se podudara sa matchedSymbol
    if (current == matchedSymbol) {
      matches++;
    } else {
      // Prekidamo niz ako nije Wild i ne podudara se
      break;
    }
  }

  // Ako su svi simboli Wild, matchedSymbol ostaje Wild (što nema payout)
  // Ako imamo bar jedan pravi simbol, matchedSymbol je taj simbol
  return matches;
}

std::vector<WinningLine> WinEvaluator::Evaluate(const Screen &screen,
                                                const GameConfig &config) {
  std::vector<WinningLine> wins;

  for (size_t lineIndex = 0; lineIndex < config.paylines.size(); ++lineIndex) {
    const auto &payline = config.paylines[lineIndex];

    Symbol matchedSymbol;
    int matches = CountMatches(screen, payline.rows, matchedSymbol);

    // Proveravamo samo ako imamo 3+ podudaranja i matchedSymbol nije Wild
    // (Wild nema svoj payout, samo zamenjuje druge simbole)
    if (matches >= 3 && matchedSymbol != Symbol::Wild) {
      int payout = config.paytable.GetPayout(matchedSymbol, matches);

      if (payout > 0) {
        wins.push_back(
            {static_cast<int>(lineIndex), matchedSymbol, matches, payout});
      }
    }
  }

  return wins;
}
