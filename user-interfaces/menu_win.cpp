#include "menu_win.h"
#include "../ncurse-wrap/ncurses_wrapper.h"
#include "playing_win.h"
#include "testing_win.h"
#include "test2_win.h"

MenuWin::MenuWin() : focus(0) {}

Window* MenuWin::handleInput(int ch) {

    if (ch == NK::Left) {
        if (--focus < 0)
            focus += 3;
        return this;

    } else if (ch == NK::Right) {
        focus = (focus + 1) % 3;
        return this;    

    } else if (ch == NK::Enter) {
        if (focus == 0) {
            return new PlayingWin;
        } else {
            return this;
        }

    } else if (ch == NK::Esc) {
        return nullptr;

    } else {
        return this;
    }

    
}

void MenuWin::connector(NCController*) {}

void MenuWin::update() {}

void MenuWin::draw() {
    Color playColor(NC::White);
    Color songListColor(NC::White);
    Color settingColor(NC::White);
    switch (focus) {
    case 0: playColor = Color(NC::Cyan); break;
    case 1: songListColor = Color(NC::Cyan); break;
    case 2: settingColor = Color(NC::Cyan); break;
    }

    addBlock(Position(5, 5), Position(15,25), {"Play"}, playColor, Font({NF::Bold}));
    addBlock(Position(5, 30), Position(15,50), {"Song List"}, songListColor, Font({NF::Bold}));
    addBlock(Position(5, 55), Position(15,75), {"Setting"}, settingColor, Font({NF::Bold}));
}
