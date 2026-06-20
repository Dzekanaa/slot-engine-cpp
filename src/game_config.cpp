#include "../include/game_config.h"
#include <stdexcept>

namespace SlotEngine {

GameConfig::GameConfig(int paylineCount) {
  paylines = CreatePaylines(paylineCount);
  reels = CreateDefaultReels();
  SetupDefaultPaytable(paytable);
}

void GameConfig::SetupDefaultPaytable(PayTable &paytable) {
  // Scatter payout (bilo gde na ekranu)
  paytable.SetPayout(Symbol::Scatter, 1, 5, 25);
  // Visoki payouti - retki simboli
  paytable.SetPayout(Symbol::A, 5, 20, 100);
  paytable.SetPayout(Symbol::K, 3, 15, 75);
  paytable.SetPayout(Symbol::Q, 2, 10, 50);
  // Srednji payouti
  paytable.SetPayout(Symbol::J, 2, 8, 30);
  paytable.SetPayout(Symbol::Ten, 1, 6, 25);
  // Niski payouti - česti simboli
  paytable.SetPayout(Symbol::Nine, 1, 5, 20);
  paytable.SetPayout(Symbol::Eight, 1, 4, 15);
  paytable.SetPayout(Symbol::Seven, 1, 3, 10);
  paytable.SetPayout(Symbol::Six, 1, 2, 8);
  paytable.SetPayout(Symbol::Five, 1, 2, 5);
}

std::vector<Reel> GameConfig::CreateDefaultReels() {
  // Reel 1
  std::vector<Symbol> reel1Strip = {
      Symbol::Five,  Symbol::Five,  Symbol::Six,    Symbol::Six,
      Symbol::Seven, Symbol::Seven, Symbol::Eight,  Symbol::Eight,
      Symbol::Nine,  Symbol::Nine,  Symbol::Ten,    Symbol::Ten,
      Symbol::J,     Symbol::J,     Symbol::Q,      Symbol::Q,
      Symbol::K,     Symbol::A,     Symbol::Scatter};

  // Reel 2
  std::vector<Symbol> reel2Strip = {
      Symbol::Five,  Symbol::Six,   Symbol::Six,  Symbol::Seven,  Symbol::Seven,
      Symbol::Eight, Symbol::Eight, Symbol::Nine, Symbol::Nine,   Symbol::Ten,
      Symbol::Ten,   Symbol::J,     Symbol::J,    Symbol::Q,      Symbol::K,
      Symbol::K,     Symbol::A,     Symbol::A,    Symbol::Scatter};

  // Reel 3 - centralni reel, više šansi za scatter
  std::vector<Symbol> reel3Strip = {
      Symbol::Five, Symbol::Six,  Symbol::Seven,   Symbol::Eight,
      Symbol::Nine, Symbol::Nine, Symbol::Ten,     Symbol::Ten,
      Symbol::J,    Symbol::J,    Symbol::Q,       Symbol::Q,
      Symbol::K,    Symbol::K,    Symbol::K,       Symbol::A,
      Symbol::A,    Symbol::A,    Symbol::Scatter, Symbol::Scatter};

  // Reel 4
  std::vector<Symbol> reel4Strip = {
      Symbol::Five,  Symbol::Five,  Symbol::Six,  Symbol::Six,    Symbol::Seven,
      Symbol::Seven, Symbol::Eight, Symbol::Nine, Symbol::Ten,    Symbol::Ten,
      Symbol::J,     Symbol::Q,     Symbol::Q,    Symbol::K,      Symbol::K,
      Symbol::A,     Symbol::A,     Symbol::Wild, Symbol::Scatter};

  // Reel 5
  std::vector<Symbol> reel5Strip = {
      Symbol::Five, Symbol::Six,  Symbol::Seven, Symbol::Eight,  Symbol::Nine,
      Symbol::Ten,  Symbol::J,    Symbol::J,     Symbol::Q,      Symbol::Q,
      Symbol::K,    Symbol::K,    Symbol::K,     Symbol::A,      Symbol::A,
      Symbol::A,    Symbol::Wild, Symbol::Wild,  Symbol::Scatter};

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

GameConfig GameConfig::CreateClassicConfig() {
  return GameConfig(20); // 20 paylines
}

GameConfig GameConfig::CreateHighVolatilityConfig() {
  GameConfig config(20);
  // Veći payouti za retke simbole, manji za česte
  config.paytable.SetPayout(Symbol::A, 100, 500, 2500);
  config.paytable.SetPayout(Symbol::K, 60, 300, 1500);
  return config;
}

GameConfig GameConfig::CreateLowVolatilityConfig() {
  GameConfig config(20);
  // Manje razlike između payouta
  config.paytable.SetPayout(Symbol::A, 30, 100, 400);
  config.paytable.SetPayout(Symbol::K, 25, 80, 300);
  return config;
}

} // namespace SlotEngine
