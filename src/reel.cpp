#include "../include/reel.h"

Reel::Reel(const std::vector<Symbol> &strip) : strip(strip) {}

Symbol Reel::GetSymbol(int index) const { return strip[index % strip.size()]; }

int Reel::Size() const { return static_cast<int>(strip.size()); }
