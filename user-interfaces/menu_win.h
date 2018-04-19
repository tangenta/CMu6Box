#ifndef MENU_WIN_H
#define MENU_WIN_H

#include "../ncurse-wrap/util_window.h"

class MenuWin: public Window {
public:
    MenuWin();
    Window* handleInput(int ch) override;
    void connector(NCController*) override;
    void update() override;
    void draw() override;
private:
    int focus;
};

#endif // MENU_WIN_H
