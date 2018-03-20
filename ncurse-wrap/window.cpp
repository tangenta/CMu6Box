#include "window.h"
#include <ncurses.h>
#include "exceptions.h"
#include "text.h"
#include "constants.h"


#ifndef DEFAULT_BKGD_COLOR
#define DEFAULT_BKGD_COLOR NC::Black
#endif

Window::Window(): bkColor(Color(DEFAULT_BKGD_COLOR)) {
    if ((wp = newwin(0,0,0,0)) == NULL) {
        throw FatalError("Window::newwin()");
    }
    setBkgd(bkColor);
}

Window::Window(int rows, int cols, int org_y, int org_x)
    : bkColor(Color(DEFAULT_BKGD_COLOR)) {
    if (rows < 0 || cols < 0 || org_y < 0 || org_x < 0) {
        throw OutOfRangeError("newwin-negative");
    }
    wp = newwin(rows, cols, org_y, org_x);
    if (wp == NULL) {
        throw FatalError("Window::newwin()");
    }
    setBkgd(bkColor);
}

int Window::getRows() {
    WINDOW* wwp = static_cast<WINDOW*>(wp);
    int rows;
    if ((rows = getmaxy(wwp)) == ERR) {
        throw InvalidError("Window::getRows()");
    }
    return rows;
}

int Window::getCols() {
    WINDOW* wwp = static_cast<WINDOW*>(wp);
    int cols;
    if ((cols = getmaxx(wwp)) == ERR) {
        throw InvalidError("Window::getCols()");
    }
    return cols;
}

Color Window::getBkgd() {
    return bkColor;
}

void Window::setBkgd(Color c) {
    bkColor = c;
    // 1 is used for background pair and COLOR_WHITE is a placeholder
    if (init_pair(1, COLOR_WHITE, /*transform(c)*/COLOR_BLACK) == ERR) {
        throw InvalidError("Window::setBkgd()");
    }
    // bkgd() change all the text in the window, while bkgdset() only
    // affects new input texts. So we use bkgdset().
    WINDOW* wwp = static_cast<WINDOW*>(wp);
    wbkgdset(wwp, COLOR_PAIR(1));
}

void Window::addText(Text const& text) {
    WINDOW* wwp = static_cast<WINDOW*>(wp);

    // move cursor to the position
    int maxRow = getRows();
    int maxCol = getCols();
    int textR = text.getRow();
    int textC = text.getCol();
    if (textR > maxRow || textC > maxCol || textC + text.getSize() > maxCol) {
        throw OutOfRangeError("Window::addText()");
    }
    if (wmove(wwp, textR, textC) == ERR) {
        throw FatalError("Window::addText()");
    }

    // set color
    if (init_pair(2, text.getColor().getNC(), getBkgd().getNC()) == ERR) {
        // 2 is used for text setting
        throw InvalidError("Window::addText()::init_pair()");
    }
    if (wattrset(wwp, COLOR_PAIR(2)) == ERR) {
        throw InvalidError("Window::addText()::wattrset()");
    }

    // set font
    if (wattron(wwp, text.getFont().getNF()) == ERR) {
        throw InvalidError("Window::addText()::wattron()");
    }

    // fill the area with text.getText()
    std::string objstr(text.getText());
    for (auto i: objstr) {
        if (i == '\n' || i == '\t') {
            throw InvalidError("addText()::multilines");
        }
    }
    int blankCharNum = text.getSize() - objstr.size();
    switch (text.getAlignMode()) {
        case AlignMode::Right:
            objstr.assign(std::string(blankCharNum, ' ') + objstr); break;
        case AlignMode::Left:
            objstr.assign(objstr + std::string(blankCharNum, ' ')); break;
        case AlignMode::Center:
            objstr.assign(std::string(blankCharNum/2, ' ') +
                        objstr + std::string(text.getSize()-blankCharNum/2, ' ')); break;
    }
    if (waddstr(wwp, objstr.c_str()) == ERR) {
        throw InvalidError("Window::addText()::waddstr()");
    }
    if (wrefresh(wwp) == ERR) {
        throw InvalidError("Window::addText()::wrefresh()");
    }
    if (wmove(wwp, 0, 0) == ERR) {
        throw InvalidError("Window::addText()::wrefresh()");
    }
}
