#ifndef MENU_WIN_H
#define MENU_WIN_H

#include "../ncurse-wrap/util_window.h"

class MenuWin: public Window {
public:
    MenuWin();
    void handleInput(int ch) override;
private:
    int focus;
    void updateFocus();
};

#endif // MENU_WIN_H
