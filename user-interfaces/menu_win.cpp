#include "menu_win.h"
#include "../ncurse-wrap/ncurses_wrapper.h"
#include "playing_win.h"

MenuWin::MenuWin()
{
    addText("Play", Position(10, 6),
                   Color(NC::Blue), Font({NF::Bold}), AlignMode::Center, 19);
    addText("Song List", Position(10, 31),
                   Color(NC::White), Font({NF::Bold}), AlignMode::Center, 19);
    addText("Setting", Position(10, 56),
                   Color(NC::White), Font({NF::Bold}), AlignMode::Center, 19);
    addBorder(Position(5, 5), Position(15,25));
    addBorder(Position(5, 30), Position(15,50));
    addBorder(Position(5, 55), Position(15,75));
    focus = 0;
}

Window* MenuWin::handleInput(int ch) {
    if (ch == NK::Left) {
        if (--focus < 0) focus += 3;
        updateFocus();
    } else if (ch == NK::Right) {
        focus = (focus+1) % 3;
        updateFocus();
    } else if (ch == NK::Enter) {
        if (focus == 0) {
            return new PlayingWin;
        }
    }
    return nullptr;
}

void MenuWin::updateFocus() {
    Color playColor(NC::White);
    Color songListColor(NC::White);
    Color settingColor(NC::White);
    switch (focus) {
    case 0: playColor = Color(NC::Blue); break;
    case 1: songListColor = Color(NC::Blue); break;
    case 2: settingColor = Color(NC::Blue); break;
    }
    addText("Play", Position(10, 6),
                   playColor, Font({NF::Bold}), AlignMode::Center, 19);
    addText("Song List", Position(10, 31),
                   songListColor, Font({NF::Bold}), AlignMode::Center, 19);
    addText("Setting", Position(10, 56),
                   settingColor, Font({NF::Bold}), AlignMode::Center, 19);
}
