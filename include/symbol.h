#pragma once

#include <string>

enum class Symbol {
  Wild,
  Scatter,
  A,
  K,
  Q,
  J,
  Ten,
  Nine,
  Eight,
  Seven,
  Six,
  Five
};

inline std::string SymbolToString(Symbol s) {
  switch (s) {
  case Symbol::Wild:
    return "W";
  case Symbol::Scatter:
    return "S";
  case Symbol::A:
    return "A";
  case Symbol::K:
    return "K";
  case Symbol::Q:
    return "Q";
  case Symbol::J:
    return "J";
  case Symbol::Ten:
    return "10";
  case Symbol::Nine:
    return "9";
  case Symbol::Eight:
    return "8";
  case Symbol::Seven:
    return "7";
  case Symbol::Six:
    return "6";
  case Symbol::Five:
    return "5";
  }

  return "?";
};
