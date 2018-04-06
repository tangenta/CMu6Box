#ifndef NCURSES_WRAPPER_H
#define NCURSES_WRAPPER_H

#include <initializer_list>

// Ncurses Color value
struct NC {
    static short const Black;
    static short const Red;
    static short const Green;
    static short const Yellow;
    static short const Blue;
    static short const Magenta;
    static short const Cyan;
    static short const White;
};

// Ncurses Font value
struct NF {
    static unsigned long const Normal;
    static unsigned long const Standout;
    static unsigned long const Underline;
    static unsigned long const Reverse;
    static unsigned long const Blink;
    static unsigned long const Dim;
    static unsigned long const Bold;
    static unsigned long const AltCharSet;
};

// Ncurses Key value
struct NK {
    static int const Up;
    static int const Down;
    static int const Left;
    static int const Right;
    static int const Esc;
    static int const Enter;
};

class NWINDOW {};

enum class AlignMode {
    Center,
    Left,
    Right,
};

class Color {
public:
    Color(short = NC::White, short = NC::Black);
    int getPair() const { return clrPair; }
private:
    int clrPair;
};

class Font {
public:
    Font() = delete;
    Font(std::initializer_list<unsigned long> fl);
    unsigned long toBit() const { return ifont; }
private:
    unsigned long ifont;
};

struct Ncurses {
    static void initscr_s();
    static bool has_color_s();
    static void start_color_s();
    static void refresh_s();
    static int getch_s();   // if getch() returns an ERR, getch_s() returns -1
    static NWINDOW* newwin_s(int, int, int, int);
    static void delwin_s(NWINDOW*);
    static void endwin_s();
    static int getmaxy_s(NWINDOW*);
    static int getmaxx_s(NWINDOW*);
    static void init_pair_s(short, short, short);
    static int COLOR_PAIR_s(int);
    static void wbkgdset_s(NWINDOW*, int);
    static void wmove_s(NWINDOW*, int, int);
    static void wattrset_s(NWINDOW*, unsigned long);
    static void wattron_s(NWINDOW*, unsigned long);
    static void wattroff_s(NWINDOW*, unsigned long);
    static void waddstr_s(NWINDOW*, const char*);
    static void wrefresh_s(NWINDOW*);
    static void echo_s();
    static void noecho_s();
    static void nodelay_s(NWINDOW*, bool);
    static void napms_s(int ms);
    static void keypad_s(NWINDOW*, bool);
    static void cbreak_s();
    static void nocbreak_s();
    // extended functions
    static NWINDOW* getStdscr();
};




#endif // NCURSES_WRAPPER_H
