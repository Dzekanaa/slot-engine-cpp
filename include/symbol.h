#pragma once
#include <string>

namespace SlotEngine {

/**
 * @brief Represents all possible symbols that can appear on the slot reels.
 *
 * This enumeration defines the complete set of symbols used by the slot engine,
 * including special symbols such as Wild and Scatter, as well as regular
 * paying symbols ranked from A to Five.
 */
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
/**
 * @brief Converts a slot symbol to its string representation.
 *
 * Returns a short textual representation of the given sumbol that can be used
 * for displaying reels, debugging, logging, or printing game result.
 *
 * @param s the Symbol to convert.
 * @return String representation of the symbol (e.g. "W", "S", "A", "10").
 */
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
  default:
    return "?";
  }
}

} // namespace SlotEngine
