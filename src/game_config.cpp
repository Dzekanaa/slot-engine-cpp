#include "../include/game_config.h"
#include <stdexcept>

namespace SlotEngine {

GameConfig::GameConfig(int paylineCount) {
  paylines = CreatePaylines(paylineCount);
  reels = CreateDefaultReels();
  SetupDefaultPaytable(paytable);
}

void GameConfig::SetupDefaultPaytable(PayTable &paytable) {
  // Scatter payout
  paytable.SetPayout(Symbol::Scatter, 1, 5, 25);

  // High symbols
  paytable.SetPayout(Symbol::A, 4, 14, 70);
  paytable.SetPayout(Symbol::K, 3, 11, 53);
  paytable.SetPayout(Symbol::Q, 2, 7, 35);

  // Medium symbols
  paytable.SetPayout(Symbol::J, 2, 6, 21);
  paytable.SetPayout(Symbol::Ten, 1, 4, 18);

  // Low symbols
  paytable.SetPayout(Symbol::Nine, 1, 4, 14);
  paytable.SetPayout(Symbol::Eight, 1, 3, 11);
  paytable.SetPayout(Symbol::Seven, 1, 2, 7);
  paytable.SetPayout(Symbol::Six, 1, 1, 6);
  paytable.SetPayout(Symbol::Five, 1, 1, 4);
}

std::vector<Reel> GameConfig::CreateDefaultReels() {
  // Reel 1 (40)
  std::vector<Symbol> reel1Strip = {
      Symbol::Five,  Symbol::Five,  Symbol::Five,    Symbol::Six,
      Symbol::Six,   Symbol::Six,   Symbol::Seven,   Symbol::Seven,
      Symbol::Seven, Symbol::Eight, Symbol::Eight,   Symbol::Eight,
      Symbol::Nine,  Symbol::Nine,  Symbol::Nine,    Symbol::Nine,
      Symbol::Ten,   Symbol::Ten,   Symbol::Ten,     Symbol::Ten,
      Symbol::J,     Symbol::J,     Symbol::J,       Symbol::J,
      Symbol::Q,     Symbol::Q,     Symbol::Q,       Symbol::Q,
      Symbol::K,     Symbol::K,     Symbol::K,       Symbol::A,
      Symbol::A,     Symbol::A,     Symbol::Five,    Symbol::Six,
      Symbol::Seven, Symbol::Eight, Symbol::Scatter, Symbol::Nine};

  // Reel 2 (40)
  std::vector<Symbol> reel2Strip = {
      Symbol::Five,  Symbol::Five,  Symbol::Five,    Symbol::Six,
      Symbol::Six,   Symbol::Six,   Symbol::Seven,   Symbol::Seven,
      Symbol::Seven, Symbol::Eight, Symbol::Eight,   Symbol::Eight,
      Symbol::Nine,  Symbol::Nine,  Symbol::Nine,    Symbol::Nine,
      Symbol::Ten,   Symbol::Ten,   Symbol::Ten,     Symbol::Ten,
      Symbol::J,     Symbol::J,     Symbol::J,       Symbol::J,
      Symbol::Q,     Symbol::Q,     Symbol::Q,       Symbol::K,
      Symbol::K,     Symbol::K,     Symbol::A,       Symbol::A,
      Symbol::A,     Symbol::Five,  Symbol::Six,     Symbol::Seven,
      Symbol::Eight, Symbol::Nine,  Symbol::Scatter, Symbol::Wild};

  // Reel 3 (40)
  std::vector<Symbol> reel3Strip = {
      Symbol::Five,  Symbol::Five,  Symbol::Five,    Symbol::Six,
      Symbol::Six,   Symbol::Six,   Symbol::Seven,   Symbol::Seven,
      Symbol::Seven, Symbol::Eight, Symbol::Eight,   Symbol::Eight,
      Symbol::Nine,  Symbol::Nine,  Symbol::Nine,    Symbol::Ten,
      Symbol::Ten,   Symbol::Ten,   Symbol::J,       Symbol::J,
      Symbol::J,     Symbol::Q,     Symbol::Q,       Symbol::Q,
      Symbol::K,     Symbol::K,     Symbol::K,       Symbol::K,
      Symbol::A,     Symbol::A,     Symbol::A,       Symbol::A,
      Symbol::Five,  Symbol::Six,   Symbol::Seven,   Symbol::Eight,
      Symbol::Nine,  Symbol::Wild,  Symbol::Scatter, Symbol::Scatter,
      Symbol::Wild};

  // Reel 4 (40)
  std::vector<Symbol> reel4Strip = {
      Symbol::Five,  Symbol::Five,    Symbol::Five,  Symbol::Six,
      Symbol::Six,   Symbol::Six,     Symbol::Seven, Symbol::Seven,
      Symbol::Seven, Symbol::Eight,   Symbol::Eight, Symbol::Eight,
      Symbol::Nine,  Symbol::Nine,    Symbol::Nine,  Symbol::Ten,
      Symbol::Ten,   Symbol::Ten,     Symbol::J,     Symbol::J,
      Symbol::J,     Symbol::Q,       Symbol::Q,     Symbol::Q,
      Symbol::K,     Symbol::K,       Symbol::K,     Symbol::A,
      Symbol::A,     Symbol::A,       Symbol::Five,  Symbol::Six,
      Symbol::Seven, Symbol::Eight,   Symbol::Nine,  Symbol::Wild,
      Symbol::Wild,  Symbol::Scatter, Symbol::Ten,   Symbol::J};

  // Reel 5 (40)
  std::vector<Symbol> reel5Strip = {
      Symbol::Five,  Symbol::Five,    Symbol::Five,  Symbol::Six,
      Symbol::Six,   Symbol::Six,     Symbol::Seven, Symbol::Seven,
      Symbol::Seven, Symbol::Eight,   Symbol::Eight, Symbol::Eight,
      Symbol::Nine,  Symbol::Nine,    Symbol::Nine,  Symbol::Ten,
      Symbol::Ten,   Symbol::Ten,     Symbol::J,     Symbol::J,
      Symbol::J,     Symbol::Q,       Symbol::Q,     Symbol::Q,
      Symbol::K,     Symbol::K,       Symbol::K,     Symbol::A,
      Symbol::A,     Symbol::A,       Symbol::Five,  Symbol::Six,
      Symbol::Seven, Symbol::Eight,   Symbol::Nine,  Symbol::Wild,
      Symbol::Wild,  Symbol::Scatter, Symbol::Q,     Symbol::K};

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

// TODO : change how the high and low volitality config works
GameConfig GameConfig::CreateHighVolatilityConfig() {
  GameConfig config(20);
  config.paytable.SetPayout(Symbol::A, 10, 50, 250);
  config.paytable.SetPayout(Symbol::K, 6, 30, 150);
  return config;
}

GameConfig GameConfig::CreateLowVolatilityConfig() {
  GameConfig config(20);
  config.paytable.SetPayout(Symbol::A, 3, 10, 40);
  config.paytable.SetPayout(Symbol::K, 2, 8, 30);
  return config;
}

} // namespace SlotEngine
