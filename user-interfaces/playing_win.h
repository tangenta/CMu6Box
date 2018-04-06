#ifndef PLAYING_WIN_H
#define PLAYING_WIN_H
#include "../ncurse-wrap/util_window.h"

class PlayingWin: public Window {
public:
    PlayingWin();
    Window* handleInput(int ch) override;
};

#endif // PLAYING_WIN_H
