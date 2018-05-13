#ifndef MENU_WIN_H
#define MENU_WIN_H

#include "../ncurse-wrap/util_window.h"
#include "../ncurse-wrap/block.h"
#include "../ncurse-wrap/util_statictext.h"

class MenuWin: public Window {
public:
    MenuWin(Resources* res);
    Window* handleInput(int ch) override;
    void update() override;
    void draw() override;
private:
    int focus;
};

#endif // MENU_WIN_H
