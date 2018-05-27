#include "menu_win.h"
#include "../ncurse-wrap/ncurses_wrapper.h"
#include "./playing-win/playing_win.h"
#include "./dir-win/songlist_win.h"
#include "setting_win.h"
#include "../resources.h"
#include "../ncurse-wrap/util_dialog.h"
#include <QFile>
#include <QTextStream>
#include <QDir>

MenuWin::MenuWin(Resources* res) : Window(res), focus(0) {}

MenuWin::~MenuWin() {}

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
            return new PlayingWin(resource);
        } else if (focus == 1) {
            return new Songlist_win(resource);
        }else if (focus == 2) {
            return new SettingWin(resource);
        } else {
            return this;
        }
    } else if (ch == NK::Esc) {
        return nullptr;
    } else {
        return this;
    }
}

void MenuWin::update() {}

void MenuWin::draw() {
    std::vector<NText> vec = {NText(tl("Play")),
                              NText(tl("Song List")),
                              NText(tl("Setting"))};
    std::vector<Position> pos = {Position(5, 5), Position(5, 30), Position(5, 55)};
    NBorder border(20, 10, '-', '|', '+');
    int vecSize = vec.size();
    for (int i = 0; i != vecSize; ++i) {
        NBlock<NText, NBorder> block(vec[i], border, true, true);
        Attr attr = i == focus ? highlight :
                                 normal;
        block.setAttr(attr);
        Window::draw(block, pos[i]);
    }
}
