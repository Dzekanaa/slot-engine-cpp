#include "../include/game_config.h"

#include <stdexcept>

GameConfig::GameConfig(int paylineCount) {
  paylines = CreatePaylines(paylineCount);
  reels = CreateDefaultReels();
  SetupDefaultPaytable(paytable);
}

std::vector<Reel> GameConfig::CreateDefaultReels() {
  std::vector<Symbol> defaultStrip = {
      Symbol::A,    Symbol::K,     Symbol::Q,     Symbol::J,   Symbol::T,
      Symbol::Nine, Symbol::Eight, Symbol::Seven, Symbol::Six, Symbol::Five};

  Reel defaultReel(defaultStrip);
  return {defaultReel, defaultReel, defaultReel, defaultReel, defaultReel};
}

void GameConfig::SetupDefaultPaytable(PayTable &paytable) {
  paytable.SetPayout(Symbol::A, 10, 50, 200);
  paytable.SetPayout(Symbol::K, 8, 40, 150);
  paytable.SetPayout(Symbol::Q, 6, 30, 100);
}

// ... tvoj postojeći CreatePaylines metod ...

std::vector<Payline> GameConfig::CreatePaylines(int count) {
  std::vector<Payline> lines = {
      {{0, 0, 0, 0, 0}}, {{1, 1, 1, 1, 1}}, {{2, 2, 2, 2, 2}},

      {{0, 1, 2, 1, 0}}, {{2, 1, 0, 1, 2}},

      {{0, 0, 1, 0, 0}}, {{2, 2, 1, 2, 2}}, {{1, 0, 0, 0, 1}},
      {{1, 2, 2, 2, 1}}, {{0, 1, 1, 1, 0}},

      {{2, 1, 1, 1, 2}}, {{0, 1, 0, 1, 0}}, {{2, 1, 2, 1, 2}},
      {{1, 0, 1, 0, 1}}, {{1, 2, 1, 2, 1}}, {{0, 2, 0, 2, 0}},
      {{2, 0, 2, 0, 2}}, {{0, 2, 2, 2, 0}}, {{2, 0, 0, 0, 2}},
      {{1, 1, 0, 1, 1}},

      {{1, 1, 2, 1, 1}}, {{0, 0, 2, 0, 0}}, {{2, 2, 0, 2, 2}},
      {{0, 2, 1, 2, 0}}, {{2, 0, 1, 0, 2}}, {{1, 0, 2, 0, 1}},
      {{1, 2, 0, 2, 1}}, {{0, 1, 2, 2, 2}}, {{2, 1, 0, 0, 0}},
      {{2, 2, 2, 1, 0}},

      {{0, 0, 0, 1, 2}}, {{0, 1, 2, 1, 2}}, {{2, 1, 0, 1, 0}},
      {{0, 1, 0, 1, 2}}, {{2, 1, 2, 1, 0}}, {{1, 0, 2, 2, 1}},
      {{1, 2, 0, 0, 1}}, {{0, 2, 1, 0, 2}}, {{2, 0, 1, 2, 0}},
      {{1, 0, 1, 2, 1}}};

  if (count != 10 && count != 20 && count != 40) {
    throw std::invalid_argument("Supported paylines: 10, 20, 40");
  }

  return {lines.begin(), lines.begin() + count};
}
