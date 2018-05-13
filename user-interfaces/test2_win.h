#ifndef TEST2_WIN_H
#define TEST2_WIN_H
#include "ncurse-wrap/util_window.h"
#include "ncurse-wrap/util_nmenu.h"
#include "ncurse-wrap/util_nborder.h"
#include "ncurse-wrap/util_ntext.h"
#include "ncurse-wrap/util_nblock.h"

using Test2Menu = NBlock<NMenu, NBorder>;
using Test2Block = NBlock<NText, NBorder>;

class Test2Win: public Window {
public:
    Test2Win();
    Window* handleInput(int ch) override;
    void update() override;
    void draw() override;
private:
    Window* mainInputHandler(int ch);
    Window* subInputHandler(int ch);
    NMenu* initRollingMenu();
    int focus;
    Test2Block playBlock;
    Test2Block songListBlock;
    Test2Block settingBlock;
    NMenu* subMenu;

    Attr defaultAttr;
};

#endif // TEST2_WIN_H
