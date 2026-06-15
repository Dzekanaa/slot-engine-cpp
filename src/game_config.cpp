#include "../include/game_config.h"
#include <stdexcept>

GameConfig::GameConfig(int paylineCount) {
  paylines = CreatePaylines(paylineCount);
  reels = CreateDefaultReels();
  SetupDefaultPaytable(paytable);
}

// U SetupDefaultPaytable metodi dodaj:
void GameConfig::SetupDefaultPaytable(PayTable &paytable) {
  // Scatter payout (bilo gde na ekranu)
  paytable.SetPayout(Symbol::Scatter, 10, 50, 250); // 3, 4 ili 5 scatter-a

  // Visoki payouti - retki simboli
  paytable.SetPayout(Symbol::A, 50, 200, 1000);
  paytable.SetPayout(Symbol::K, 30, 150, 750);
  paytable.SetPayout(Symbol::Q, 20, 100, 500);

  // Srednji payouti
  paytable.SetPayout(Symbol::J, 15, 75, 300);
  paytable.SetPayout(Symbol::Ten, 12, 60, 250);

  // Niski payouti - česti simboli
  paytable.SetPayout(Symbol::Nine, 10, 50, 200);
  paytable.SetPayout(Symbol::Eight, 8, 40, 150);
  paytable.SetPayout(Symbol::Seven, 6, 30, 100);
  paytable.SetPayout(Symbol::Six, 5, 20, 75);
  paytable.SetPayout(Symbol::Five, 4, 15, 50);

  // Wild nema payout
}

// U CreateDefaultReels metodi dodaj Scatter na neke pozicije:
std::vector<Reel> GameConfig::CreateDefaultReels() {
  // Reel 1
  std::vector<Symbol> reel1Strip = {
      Symbol::Five,  Symbol::Five,  Symbol::Six,    Symbol::Six,
      Symbol::Seven, Symbol::Seven, Symbol::Eight,  Symbol::Eight,
      Symbol::Nine,  Symbol::Nine,  Symbol::Ten,    Symbol::Ten,
      Symbol::J,     Symbol::J,     Symbol::Q,      Symbol::Q,
      Symbol::K,     Symbol::A,     Symbol::Scatter // Dodaj Scatter
  };

  // Reel 2
  std::vector<Symbol> reel2Strip =
      {
          Symbol::Five,  Symbol::Six,   Symbol::Six,    Symbol::Seven,
          Symbol::Seven, Symbol::Eight, Symbol::Eight,  Symbol::Nine,
          Symbol::Nine,  Symbol::Ten,   Symbol::Ten,    Symbol::J,
          Symbol::J,     Symbol::Q,     Symbol::K,      Symbol::K,
          Symbol::A,     Symbol::A,     Symbol::Scatter // Dodaj Scatter
      };

  // Reel 3 - centralni reel, više šansi za scatter
  std::vector<Symbol> reel3Strip = {
      Symbol::Five,    Symbol::Six,    Symbol::Seven,
      Symbol::Eight,   Symbol::Nine,   Symbol::Nine,
      Symbol::Ten,     Symbol::Ten,    Symbol::J,
      Symbol::J,       Symbol::Q,      Symbol::Q,
      Symbol::K,       Symbol::K,      Symbol::K,
      Symbol::A,       Symbol::A,      Symbol::A,
      Symbol::Scatter, Symbol::Scatter // Dva scatter-a
  };

  // Reel 4
  std::vector<Symbol> reel4Strip =
      {
          Symbol::Five,  Symbol::Five,  Symbol::Six,    Symbol::Six,
          Symbol::Seven, Symbol::Seven, Symbol::Eight,  Symbol::Nine,
          Symbol::Ten,   Symbol::Ten,   Symbol::J,      Symbol::Q,
          Symbol::Q,     Symbol::K,     Symbol::K,      Symbol::A,
          Symbol::A,     Symbol::Wild,  Symbol::Scatter // Dodaj Scatter
      };

  // Reel 5
  std::vector<Symbol> reel5Strip =
      {
          Symbol::Five, Symbol::Six,  Symbol::Seven,  Symbol::Eight,
          Symbol::Nine, Symbol::Ten,  Symbol::J,      Symbol::J,
          Symbol::Q,    Symbol::Q,    Symbol::K,      Symbol::K,
          Symbol::K,    Symbol::A,    Symbol::A,      Symbol::A,
          Symbol::Wild, Symbol::Wild, Symbol::Scatter // Dodaj Scatter
      };

  return {Reel(reel1Strip), Reel(reel2Strip), Reel(reel3Strip),
          Reel(reel4Strip), Reel(reel5Strip)};
}

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
