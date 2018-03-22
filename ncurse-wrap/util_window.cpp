#include "util_window.h"
#include "ncurses_wrapper.h"
#include "exceptions.h"
#include <algorithm>
#include <climits>

Window::Window(): bkColor(Color()) {
    wp = Ncurses::newwin_s(0, 0, 0, 0);
    setBkgd(bkColor);
}

Window::Window(int rows, int cols, int org_y, int org_x)
    : bkColor(Color()) {
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
    // bkgd() change all the text in the window, while bkgdset() only
    // affects new input texts. So we use bkgdset().
    Ncurses::wbkgdset_s(wp, Ncurses::COLOR_PAIR_s(c.getPair()));
}

void Window::addText(std::string const& text) {
    Ncurses::waddstr_s(wp, text.c_str());
    Ncurses::wrefresh_s(wp);    
}

void Window::addText(std::string const& text, Position const& pos,
                     Color const& color, Font const& font, AlignMode mode,
                     int spaceLength) {
    // if the spaceLength is not big enough, set it with text.size()
    if (text.size() > static_cast<size_t>(INT_MAX)) {
        throw InvalidError("addText()::overflow");
    }
    spaceLength = std::max(spaceLength, static_cast<int>(text.size()));

    // move cursor to the position
    int maxRow = getRows();
    int maxCol = getCols();
    int textR = pos.getRow();
    int textC = pos.getCol();
    if (textR > maxRow || textC > maxCol || textC + spaceLength > maxCol) {
        throw OutOfRangeError("Window::addText()");
    }

    Ncurses::wmove_s(wp, textR, textC);

    // fill the area with text.getText()
    std::string objstr(text);
    for (auto i: objstr) {
        if (i == '\n' || i == '\t') {
            throw InvalidError("addText()::multilines");
        }
    }

    int blankCharNum = spaceLength - objstr.size();
    switch (mode) {
        case AlignMode::Right:
            objstr.assign(std::string(blankCharNum, ' ') + objstr); break;
        case AlignMode::Left:
            objstr.assign(objstr + std::string(blankCharNum, ' ')); break;
        case AlignMode::Center:
            objstr.assign(std::string(blankCharNum/2, ' ') +
                        objstr + std::string(spaceLength -
                                             blankCharNum/2 -
                                             objstr.size(), ' ')); break;
    }

    // set attr
    Ncurses::wattron_s(wp, Ncurses::COLOR_PAIR_s(color.getPair()) | font.toBit());

    Ncurses::waddstr_s(wp, objstr.c_str());

    Ncurses::wattroff_s(wp, Ncurses::COLOR_PAIR_s(color.getPair()) | font.toBit());

    // // restore the cursor and attribute
    // Ncurses::wmove_s(wp, 0, 0);
    Ncurses::wrefresh_s(wp);
}
