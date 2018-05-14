#ifndef MENU_WIN_H
#define MENU_WIN_H

#include "../ncurse-wrap/util_window.h"
#include "../ncurse-wrap/util_statictext.h"
#include "../ncurse-wrap/util_nblock.h"
#include "../ncurse-wrap/util_nborder.h"

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
    NBlock<Dialog, NBorder>* msg;
};

#endif // MENU_WIN_H
