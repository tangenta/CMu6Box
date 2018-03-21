#include "util_window.h"
#include "ncurses_wrapper.h"
#include "exceptions.h"
#include "util_text.h"
#include <algorithm>

#ifndef DEFAULT_BKGD_COLOR
#define DEFAULT_BKGD_COLOR NC::Black
#endif

Window::Window(): bkColor(Color(DEFAULT_BKGD_COLOR)) {
    wp = Ncurses::newwin_s(0, 0, 0, 0);
    setBkgd(bkColor);
}

Window::Window(int rows, int cols, int org_y, int org_x)
    : bkColor(Color(DEFAULT_BKGD_COLOR)) {
    wp = Ncurses::newwin_s(rows, cols, org_y, org_x);
    setBkgd(bkColor);
}

int Window::getRows() {
    return Ncurses::getmaxy_s(wp);
}

int Window::getCols() {
    return Ncurses::getmaxx_s(wp);
}

Color Window::getBkgd() {
    return bkColor;
}

void Window::setBkgd(Color c) {
    bkColor = c;
    // 2 is used for background pair and
    // COLOR_WHITE is a placeholder
    Ncurses::init_pair_s(2, Color(NC::White), c);
    // bkgd() change all the text in the window, while bkgdset() only
    // affects new input texts. So we use bkgdset().
    Ncurses::wbkgdset_s(wp, Ncurses::COLOR_PAIR_s(2));
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

    Ncurses::wmove_s(wp, textR, textC);

    // set color
    // 3 is used for
    Ncurses::init_pair_s(3, text.getColor(), getBkgd());

    Ncurses::wattrset_s(wp, Ncurses::COLOR_PAIR_s(3));

    // set font
    Ncurses::wattron_s(wp, text.getFont());

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
                        objstr + std::string(text.getSize() -
                                             blankCharNum/2 -
                                             objstr.size(), ' ')); break;
    }

    Ncurses::waddstr_s(wp, objstr.c_str());

    // restore the cursor and attribute
    Ncurses::wmove_s(wp, 0, 0);
    Ncurses::wattrset_s(wp, NF::Normal);

    Ncurses::wrefresh_s(wp);
}
