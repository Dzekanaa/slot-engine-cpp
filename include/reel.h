#pragma once

#include "symbol.h"
#include <vector>

class Reel {
private:
  std::vector<Symbol> strip;

public:
  Reel() = default;
  explicit Reel(const std::vector<Symbol> &strip);

  Symbol GetSymbol(int index) const;

  int Size() const;
};
