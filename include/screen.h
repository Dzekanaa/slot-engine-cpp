#pragma once

#include "symbol.h"
#include <vector>

class Screen {
private:
  std::vector<std::vector<Symbol>> columns;

public:
  Screen() = default;
  explicit Screen(const std::vector<std::vector<Symbol>> &columns);

  Symbol GetSymbol(int reel, int row) const;
  int Rows() const;
  int Columns() const;
};
