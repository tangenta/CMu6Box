#include "ncurses_wrapper.h"
#include <ncurses.h>
#include "exceptions.h"

// for convenient
inline WINDOW* RC(NWINDOW* ptr) {
    return reinterpret_cast<WINDOW*>(ptr);
}

Font::Font(std::initializer_list<unsigned long> fl) {
    unsigned long t = 0;
    for (auto i : fl) {
        t |= i;
    }
    ifont = t;
};


void Ncurses::initscr_s() {
    if (initscr() == NULL) {
        throw FatalError("initscr()");
    }
}

bool Ncurses::has_color_s() {
    // it seems silly but actually not
    return has_colors() == TRUE ? true : false;
}

void Ncurses::start_color_s() {
    if (start_color() == ERR) {
        throw InvalidError("start_color()");
    }
}

void Ncurses::refresh_s() {
    if (refresh() == ERR) {
        throw FatalError("refresh()::ERR");
    }
}

int Ncurses::getch_s() {
    int ret = getch();
    if (ret == ERR) {
        throw InvalidError("getch()::ERR");
    }
    return ret;
}

NWINDOW* Ncurses::newwin_s(int rows, int cols, int org_y, int org_x) {
    if (rows < 0 || cols < 0 || org_y < 0 || org_x < 0) {
        throw OutOfRangeError("newwin()::negative");
    }
    WINDOW* ret;
    if ((ret = newwin(rows, cols, org_y, org_x)) == NULL) {
        throw FatalError("newwin()::NULL");
    }
    return reinterpret_cast<NWINDOW*>(ret);
}

void Ncurses::delwin_s(NWINDOW* wp) {
    if (delwin(RC(wp)) == ERR) {
        throw FatalError("delwin()::ERR");
    }
}

void Ncurses::endwin_s() {
    if (endwin() == ERR) {
        throw FatalError("endwin()::ERR");
    }
}

int Ncurses::getmaxy_s(NWINDOW* wp) {
    int ret = getmaxy(RC(wp));
    if (ret == ERR) {
        throw FatalError("getmaxy()::ERR");
    }
    return ret;
}

int Ncurses::getmaxx_s(NWINDOW* wp) {
    int ret = getmaxx(RC(wp));
    if (ret == ERR) {
        throw FatalError("getmaxx()::ERR");
    }
    return ret;
}

void Ncurses::init_pair_s(short pair, short fg, short bg) {
    if (init_pair(pair, fg, bg) == ERR) {
        throw InvalidError("init_pair()::ERR");
    }
}

int Ncurses::COLOR_PAIR_s(int pair) {
    int ret = COLOR_PAIR(pair);
    if (ret == ERR) {
        throw InvalidError("COLOR_PAIR()::ERR");
    }
    return ret;
}

void Ncurses::wbkgdset_s(NWINDOW* wp, int colorPair) {
    wbkgdset(RC(wp), colorPair);
}

void Ncurses::wmove_s(NWINDOW* wp, int row, int col) {
    if (row < 0 || col < 0) {
        throw OutOfRangeError("wmove()::negative");
    }
    if (wmove(RC(wp), row, col) == ERR) {
        throw FatalError("wmove()::ERR");
    }
}

void Ncurses::wattrset_s(NWINDOW* wp, unsigned long colorPair) {
    if (wattrset(RC(wp), colorPair) == ERR) {
        throw InvalidError("wattrset()::ERR");
    }
}

void Ncurses::wattron_s(NWINDOW* wp, unsigned long attr) {
    if (wattron(RC(wp), attr) == ERR) {
        throw InvalidError("wattron()::ERR");
    }
}

void Ncurses::wattroff_s(NWINDOW* wp, unsigned long attr) {
    if (wattroff(RC(wp), attr) == ERR) {
        throw InvalidError("wattron()::ERR");
    }
}

void Ncurses::waddstr_s(NWINDOW* wp, char const* str) {
    if (waddstr(RC(wp), str) == ERR) {
        throw OutOfRangeError("waddstr()::ERR");  // should this be OutOfRange or Fatal?
    }
}

void Ncurses::wrefresh_s(NWINDOW* wp) {
    if (wrefresh(RC(wp)) == ERR) {
        throw FatalError("wrefresh()::ERR");
    }
}


short NC::Black = COLOR_BLACK;
short NC::Red = COLOR_RED;
short NC::Green = COLOR_GREEN;
short NC::Yellow = COLOR_YELLOW;
short NC::Blue = COLOR_BLUE;
short NC::Magenta = COLOR_MAGENTA;
short NC::Cyan = COLOR_CYAN;
short NC::White = COLOR_WHITE;

unsigned long NF::Normal = A_NORMAL;
unsigned long NF::Standout = A_STANDOUT;
unsigned long NF::Underline = A_UNDERLINE;
unsigned long NF::Reverse = A_REVERSE;
unsigned long NF::Blink = A_BLINK;
unsigned long NF::Dim = A_DIM;
unsigned long NF::Bold = A_BOLD;
unsigned long NF::AltCharSet = A_ALTCHARSET;
