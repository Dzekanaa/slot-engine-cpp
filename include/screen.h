#pragma once
#include "symbol.h"
#include <vector>

namespace SlotEngine {

class Screen {
private:
  std::vector<std::vector<Symbol>> columns;

public:
  Screen(const std::vector<std::vector<Symbol>> &columns);

  Symbol GetSymbol(int reel, int row) const;
  int Rows() const;
  int Columns() const;
};

} // namespace SlotEngine
