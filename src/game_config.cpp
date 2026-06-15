#include "../include/game_config.h"
#include <stdexcept>

GameConfig::GameConfig(int paylineCount) {
  paylines = CreatePaylines(paylineCount);
  reels = CreateDefaultReels();
  SetupDefaultPaytable(paytable);
}

std::vector<Reel> GameConfig::CreateDefaultReels() {
  // Retki simboli (visok payout): A, K
  // Česti simboli (nizak payout): Five, Six, Seven, Eight, Nine

  // Reel 1 - najviše niskih simbola
  std::vector<Symbol> reel1Strip = {
      Symbol::Five,  Symbol::Five,  Symbol::Six,   Symbol::Six,  Symbol::Seven,
      Symbol::Seven, Symbol::Eight, Symbol::Eight, Symbol::Nine, Symbol::Nine,
      Symbol::T,     Symbol::T,     Symbol::J,     Symbol::J,    Symbol::Q,
      Symbol::Q,     Symbol::K,     Symbol::A};

  // Reel 2
  std::vector<Symbol> reel2Strip = {
      Symbol::Five,  Symbol::Six,   Symbol::Six,  Symbol::Seven, Symbol::Seven,
      Symbol::Eight, Symbol::Eight, Symbol::Nine, Symbol::Nine,  Symbol::T,
      Symbol::T,     Symbol::J,     Symbol::J,    Symbol::Q,     Symbol::K,
      Symbol::K,     Symbol::A,     Symbol::A};

  // Reel 3 - centralni reel, više visokih simbola
  std::vector<Symbol> reel3Strip = {
      Symbol::Five, Symbol::Six, Symbol::Seven, Symbol::Eight, Symbol::Nine,
      Symbol::Nine, Symbol::T,   Symbol::T,     Symbol::J,     Symbol::J,
      Symbol::Q,    Symbol::Q,   Symbol::K,     Symbol::K,     Symbol::K,
      Symbol::A,    Symbol::A,   Symbol::A};

  // Reel 4
  std::vector<Symbol> reel4Strip = {
      Symbol::Five,  Symbol::Five,  Symbol::Six,  Symbol::Six, Symbol::Seven,
      Symbol::Seven, Symbol::Eight, Symbol::Nine, Symbol::T,   Symbol::T,
      Symbol::J,     Symbol::Q,     Symbol::Q,    Symbol::K,   Symbol::K,
      Symbol::A,     Symbol::A,     Symbol::Wild};

  // Reel 5 - najviše šansi za velike dobitke
  std::vector<Symbol> reel5Strip = {
      Symbol::Five, Symbol::Six,  Symbol::Seven, Symbol::Eight, Symbol::Nine,
      Symbol::T,    Symbol::J,    Symbol::J,     Symbol::Q,     Symbol::Q,
      Symbol::K,    Symbol::K,    Symbol::K,     Symbol::A,     Symbol::A,
      Symbol::A,    Symbol::Wild, Symbol::Wild};

  return {Reel(reel1Strip), Reel(reel2Strip), Reel(reel3Strip),
          Reel(reel4Strip), Reel(reel5Strip)};
}

void GameConfig::SetupDefaultPaytable(PayTable &paytable) {
  // Visoki payouti - retki simboli
  paytable.SetPayout(Symbol::A, 50, 200, 1000); // As - veoma redak
  paytable.SetPayout(Symbol::K, 30, 150, 750);  // Kralj - redak
  paytable.SetPayout(Symbol::Q, 20, 100, 500);  // Damа - srednje redak

  // Srednji payouti
  paytable.SetPayout(Symbol::J, 15, 75, 300); // Žandar
  paytable.SetPayout(Symbol::T, 12, 60, 250); // Desetka

  // Niski payouti - česti simboli
  paytable.SetPayout(Symbol::Nine, 10, 50, 200); // Devetka
  paytable.SetPayout(Symbol::Eight, 8, 40, 150); // Osmica
  paytable.SetPayout(Symbol::Seven, 6, 30, 100); // Sedmica
  paytable.SetPayout(Symbol::Six, 5, 20, 75);    // Šestica
  paytable.SetPayout(Symbol::Five, 4, 15, 50);   // Petica

  // Wild nema payout, samo zamenjuje druge simbole
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
