#include "util_menu.h"
#include <algorithm>
#include <cassert>

Menu::Menu(std::initializer_list<std::string> strList,
           const Position &pos,
           int width,
           int height,
           const Attr &hl,
           const Attr &other)
    : position(pos), width(width), height(height),
      highlight(hl), other(other), focus(0), item(0),
      itemLength(strList.size()) {

    if (width < 0 || height < 0) {
        throw OutOfRangeError("Menu()::overflow");
    }

    for (int i = 0; i < itemLength; ++i) {
        texts.push_back(RollingText(*(strList.begin()+i),
                                    Position(pos.getRow()+i, pos.getCol()),
                                    width, other));
    }
}


void Menu::down() {
    if (focus < height-1 && item < itemLength-1) {
        focus++;
        item++;
    } else if (focus == height-1 && item < itemLength-1) {
        item++;
        rollDown();
    } else {
        // 到底
    }
}

void Menu::up() {
    if (focus > 0 && item > 0) {
        focus--;
        item--;
    } else if (focus == 0 && item > 0) {
        item--;
        rollUp();
    } else {
        // 到顶
    }
}

void Menu::draw(Window *win) {
    const int n = item - focus;
    const int len = std::min(height, itemLength);
    for (int i = 0; i < len; i++) {
        if (i == focus) {
            texts.at(n+i).attribute = highlight;
            texts.at(n+i).draw(win);
        } else {
            texts.at(n+i).attribute = other;
            texts.at(n+i).draw(win);
        }
    }
}

void Menu::update() {
    const int n = item - focus;
    const int len = std::min(height, itemLength);
    for (int i = 0; i < len; i++) {
        if (i == focus) {
            texts.at(n+i).enable(true);
            texts.at(n+i).update();
        } else {
            texts.at(n+i).enable(false);
            texts.at(n+i).update();
        }
    }
}

void Menu::rollDown() {
    for (auto & i : texts) {
        i.position = Position(i.position.getRow()-1, i.position.getCol());
    }
}

void Menu::rollUp() {
    for (auto & i : texts) {
        i.position = Position(i.position.getRow()+1, i.position.getCol());
    }
}
