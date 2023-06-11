#pragma once

#include <ostream>

enum ColorCode {
    FG_RED      = 31,
    FG_GREEN    = 32,
    FG_BLUE     = 34,
    FG_DEFAULT  = 39,
    BG_RED      = 41,
    BG_GREEN    = 42,
    BG_BLUE     = 44,
    BG_DEFAULT  = 49
};

class ColorMod {
    ColorCode code;
public:
    ColorMod(ColorCode pCode) : code(pCode) {}
    friend std::ostream&
    operator<<(std::ostream& os, const ColorMod& mod) {
        return os << "\033[" << mod.code << "m";
    }
};