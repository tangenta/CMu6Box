#ifndef SONGINFO_WIN_H
#define SONGINFO_WIN_H
#include "../ncurse-wrap/util_window.h"

class SongInfoWin: public Window {
public:
    SongInfoWin(Resources* res);
    ~SongInfoWin();
    Window* handleInput(int ch);
    void update();
    void draw();
};

#endif // SONGINFO_WIN_H
