#ifndef MENU_WIN_H
#define MENU_WIN_H

#include "../ncurse-wrap/util_window.h"

class Dialog;
class MenuWin: public Window {
public:
    MenuWin(Resources* res);
    ~MenuWin();
    Window* handleInput(int ch) override;
    void update() override;
    void draw() override;
private:
    int focus;
    Window* msgHandleInput(int ch);
};

#endif // MENU_WIN_H
