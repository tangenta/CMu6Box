#include "ncurses_wrapper.h"
#include <ncurses.h>
#include "exceptions.h"
#include <map>
#include <utility>

// for convenient
inline WINDOW* RC(NWINDOW* ptr) {
    return reinterpret_cast<WINDOW*>(ptr);
}

static int colorPair = 1;
static std::map<std::pair<short, short>, int> colorPairMap;

Color::Color(short fg, short bg) {
    auto key = std::make_pair(fg, bg);
    if (colorPairMap.find(key) != colorPairMap.end()) {  // previous color pair is found
        clrPair = colorPairMap.at(key);
        return;
    }
    colorPairMap[key] = colorPair;
    this->clrPair = colorPair;
    Ncurses::init_pair_s(colorPair++, fg, bg);
    if (colorPair >= 256) {
        throw InvalidError("Color()::colorPairOverflow");
    }
}

Font::Font(std::initializer_list<unsigned long> fl) {
    unsigned long t = 0;
    for (auto i : fl) {
        t |= i;
    }
    ifont = t;
}


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
        return -1;
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
        throw FatalError("waddstr()::ERR");
    }
}

void Ncurses::wrefresh_s(NWINDOW* wp) {
    if (wrefresh(RC(wp)) == ERR) {
        throw FatalError("wrefresh()::ERR");
    }
}

void Ncurses::echo_s() {
    if (echo() == ERR) {
        throw FatalError("echo()::ERR");
    }
}

void Ncurses::noecho_s() {
    if (noecho() == ERR) {
        throw FatalError("unecho()::ERR");
    }
}

void Ncurses::nodelay_s(NWINDOW* wp, bool flag) {
    int res = flag ? nodelay(RC(wp), true)
                   : nodelay(RC(wp), false);
    if (res == ERR) {
        throw FatalError("nodelay()::ERR");
    }
}

void Ncurses::napms_s(int ms) {
    if (ms < 0) {
        throw FatalError("napms()::negative");
    }
    napms(ms);
}

void Ncurses::keypad_s(NWINDOW* wp, bool flag) {
    int res = flag ? keypad(RC(wp), true)
                   : keypad(RC(wp), false);
    if (res == ERR) {
        throw FatalError("keypad()::ERR");
    }
}

void Ncurses::cbreak_s() {
    if (cbreak() == ERR) {
        throw FatalError("cbreak()::ERR");
    }
}

void Ncurses::nocbreak_s() {
    if (nocbreak() == ERR) {
        throw FatalError("nocbreak()::ERR");
    }
}

NWINDOW* Ncurses::getStdscr() {
    return reinterpret_cast<NWINDOW*>(stdscr);
}

short const NC::Black = COLOR_BLACK;
short const NC::Red = COLOR_RED;
short const NC::Green = COLOR_GREEN;
short const NC::Yellow = COLOR_YELLOW;
short const NC::Blue = COLOR_BLUE;
short const NC::Magenta = COLOR_MAGENTA;
short const NC::Cyan = COLOR_CYAN;
short const NC::White = COLOR_WHITE;

unsigned long const NF::Normal = A_NORMAL;
unsigned long const NF::Standout = A_STANDOUT;
unsigned long const NF::Underline = A_UNDERLINE;
unsigned long const NF::Reverse = A_REVERSE;
unsigned long const NF::Blink = A_BLINK;
unsigned long const NF::Dim = A_DIM;
unsigned long const NF::Bold = A_BOLD;
unsigned long const NF::AltCharSet = A_ALTCHARSET;

int const NK::Up = KEY_UP;
int const NK::Down = KEY_DOWN;
int const NK::Right = KEY_RIGHT;
int const NK::Left = KEY_LEFT;
int const NK::Esc = 27;
int const NK::Enter = 10;   // KEY_ENTER doesn't work?
