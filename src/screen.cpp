#include "../include/screen.h"

Screen::Screen(const std::vector<std::vector<Symbol>> &columns)
    : columns(columns) {}

Symbol Screen::GetSymbol(int reel, int row) const { return columns[reel][row]; }

int Screen::Rows() const { return static_cast<int>(columns[0].size()); }

int Screen::Columns() const { return static_cast<int>(columns.size()); }
