#ifndef CONSTANTS_TRANSFORM_H
#define CONSTANTS_TRANSFORM_H

#include "constants.h"
#include <ncurses.h>

short transform(Color c) {
    switch (c.getNC()) {
    case NC::Black: return COLOR_BLACK;
    case NC::Red: return COLOR_RED;
    case NC::Green: return COLOR_GREEN;
    case NC::Yellow: return COLOR_YELLOW;
    case NC::Blue: return COLOR_BLUE;
    case NC::Magenta: return COLOR_MAGENTA;
    case NC::Cyan: return COLOR_CYAN;
    case NC::White: return COLOR_WHITE;
    }
}

chtype transform(Font f) {
    switch (f.getNF()) {
    case NF::Normal: return A_NORMAL;
    case NF::Standout: return A_STANDOUT;
    case NF::Underline: return A_UNDERLINE;
    case NF::Reverse: return A_REVERSE;
    case NF::Blink: return A_BLINK;
    case NF::Dim: return A_DIM;
    case NF::Bold: return A_BOLD;
    case NF::AltCharSet: return A_ALTCHARSET;
    }
}

#endif
