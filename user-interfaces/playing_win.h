#ifndef PLAYING_WIN_H
#define PLAYING_WIN_H
#include "../ncurse-wrap/util_window.h"

class PlayingWin: public Window {
public:
    PlayingWin();
    Window* handleInput(int ch) override;
private:
    int subwinNo;
    int focus0;
    int focus1;
    int focus2;

    Window* win0(int ch);
    Window* win1(int ch);
    Window* win2(int ch);

    void updateWin0();
    void updateWin1();
    void updateWin2();
};

#endif // PLAYING_WIN_H
