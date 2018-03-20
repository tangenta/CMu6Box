#include "window.h"
#include <ncurses.h>
#include "exceptions.h"
#include "text.h"
#include "constants_transform.h"

#ifndef DEFAULT_BKGD_COLOR
#define DEFAULT_BKGD_COLOR NC::Black
#endif

Window::Window() {
    if ((wp = newwin(0,0,0,0)) == NULL) {
        throw FatalError("Window::newwin()");
    }
    setBkgd(Color(DEFAULT_BKGD_COLOR));
}

Window::Window(int rows, int cols, int org_y, int org_x) {
    if (rows < 0 || cols < 0 || org_y < 0 || org_x < 0) {
        throw OutOfRangeError("newwin-negative");
    }
    wp = newwin(rows, cols, org_y, org_x);
    if (wp == NULL) {
        throw FatalError("Window::newwin()");
    }
    setBkgd(Color(DEFAULT_BKGD_COLOR));
}

int Window::getRows() {
    if (getmaxy(wp) == ERR) {
        throw InvalidError("Window::getRows()");
    }
}

int Window::getCols() {
    if (getmaxx(wp) == ERR) {
        throw InvalidError("Window::getCols()");
    }
}

Color Window::getBkgd() {
    return bkColor;
}

void Window::setBkgd(Color c) {
    bkColor = c;
    // 65 is used for background pair and COLOR_WHITE is a placeholder
    if (init_pair(65, COLOR_WHITE, transform(c)) == ERR) {
        throw InvalidError("Window::setBkgd()");
    }
    // bkgd() change all the text in the window, while bkgdset() only
    // affects new input texts. So we use bkgdset().
    wbkgdset(wp, COLOR_PAIR(65));
}

void Window::addText(Text const& text) {
    // move cursor to the position
    int maxRow = getRows();
    int maxCol = getCols();
    int textR = text.getRow();
    int textC = text.getCol();
    if (textR > maxRow || textC > maxCol || textC + text.getSize() > maxCol) {
        throw OutOfRangeError("Window::addText()");
    }
    if (wmove(wp, textR, TextC) == ERR) {
        throw FatalError("Window::addText()");
    }

    // set color
    if (init_pair(66, transform(text.getColor()), text.getBkgd()) == ERR) {
        // 66 is used for text setting
        throw InvalidError("Window::addText()::init_pair()");
    }
    if (wattrset(wp, COLOR_PAIR(66)) == ERR) {
        throw InvalidError("Window::addText()::wattrset()");
    }

    // set font
    if (wattron(wp, transform(text.getFont())) == ERR) {
        throw InvalidError("Window::addText()::wattron()");
    }

    // fill the area with text.getText()
    std::string objstr(text.getText());
    int blankCharNum = text.getSize() - objstr.size();
    switch (text.getAlignMode()) {
        case AlignMode::Right:
            objstr.swap(std::string(blankCharNum, ' ') + objstr); break;
        case AlignMode::Left:
            objstr.swap(objstr + std::string(blankCharNum, ' ')); break;
        case AlignMode::Center:
            objstr.swap(std::string(blankCharNum/2, ' ') +
                        objstr + std::string(text.getSize()-blankCharNum/2, ' ')); break;
    }
    if (waddstr(wp, objstr.c_str()) == ERR) {
        throw InvalidError("Window::addText()::waddstr()");
    }
}
