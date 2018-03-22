#ifndef NCURSES_WRAPPER_H
#define NCURSES_WRAPPER_H

#include <initializer_list>

// Ncurses Color value
struct NC {
    static short Black;
    static short Red;
    static short Green;
    static short Yellow;
    static short Blue;
    static short Magenta;
    static short Cyan;
    static short White;
};

// Ncurses Font value
struct NF {
    static unsigned long Normal;
    static unsigned long Standout;
    static unsigned long Underline;
    static unsigned long Reverse;
    static unsigned long Blink;
    static unsigned long Dim;
    static unsigned long Bold;
    static unsigned long AltCharSet;
};

class NWINDOW {};

enum class AlignMode {
    Center,
    Left,
    Right,
};

class Color {
public:
    Color();
    Color(short);
    Color(short, short);
    int getPair() const { return clrPair; }
private:
    int clrPair;
};

class Font {
public:
    Font() = delete;
    // Font(unsigned long f): ifont(f) {}
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
    static int getch_s();
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
};




#endif // NCURSES_WRAPPER_H
