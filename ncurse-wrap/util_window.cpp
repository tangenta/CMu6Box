#include "util_window.h"
#include "ncurses_wrapper.h"
#include "exceptions.h"
#include <algorithm>
#include <climits>

Window::Window() {
    wp = Ncurses::newwin_s(0, 0, 0, 0);
//    Ncurses::init_pair_s(1, NC::White, NC::Black);
//    Ncurses::wbkgdset_s(wp, Ncurses::COLOR_PAIR_s(1));
}

Window::~Window() {
    Ncurses::delwin_s(wp);
}

Window::Window(int rows, int cols, int org_y, int org_x) {
    wp = Ncurses::newwin_s(rows, cols, org_y, org_x);
}

int Window::getRows() {
    return Ncurses::getmaxy_s(wp);
}

int Window::getCols() {
    return Ncurses::getmaxx_s(wp);
}


void Window::addText(std::string const& text) {
    Ncurses::waddstr_s(wp, text.c_str());
    // Ncurses::wrefresh_s(wp);
}

void Window::addText(std::string const& text, Position const& pos,
                     Color const& color, Font const& font, AlignMode mode,
                     int spaceLength) {
    // if the spaceLength is not big enough, set it with text.length()
    if (text.length() > static_cast<size_t>(INT_MAX)) {
        throw InvalidError("addText()::overflow");
    }
    int slen = std::max(spaceLength, static_cast<int>(text.length()));

    // move cursor to the position
    int maxRow = getRows();
    int maxCol = getCols();
    int textR = pos.getRow();
    int textC = pos.getCol();
    if (textR > maxRow || textC > maxCol || textC + slen > maxCol) {
        throw OutOfRangeError("Window::addText()");
    }

    Ncurses::wmove_s(wp, textR, textC);

    // fill the area with text.getText()
    static std::string const invalidEscapeChars = "\a\n\b\f\r\t\v\e";
    for (auto i: text) {
        if (std::count(invalidEscapeChars.begin(),
                       invalidEscapeChars.end(), i) > 0) {
            throw InvalidError("addText()::multilines");
        }
    }

    int blankCharNum = slen - text.length();
    std::string tstr(blankCharNum, ' ');
    switch (mode) {
        case AlignMode::Right:
            tstr.append(text); break;
        case AlignMode::Left:
            tstr.insert(0, text, 0, text.npos); break;
        case AlignMode::Center:
            tstr.insert(blankCharNum/2, text, 0, text.npos); break;
    }

    // set attr
    Ncurses::wattron_s(wp, Ncurses::COLOR_PAIR_s(color.getPair()) | font.toBit());

    Ncurses::waddstr_s(wp, tstr.c_str());

    Ncurses::wattroff_s(wp, Ncurses::COLOR_PAIR_s(color.getPair()) | font.toBit());

    // // restore the cursor and attribute
    // Ncurses::wmove_s(wp, 0, 0);
    // Ncurses::wrefresh_s(wp);
}

void Window::addBorder(Position const& topLeft,
                       Position const& bottomRight,
                       Color const& color,
                       char horizontal,
                       char vertical,
                       char corner) {
    int width = bottomRight.getCol()-topLeft.getCol()-1;
    int height = bottomRight.getRow()-topLeft.getRow()-1;
    if (width < 0 || height < 0) {
        throw InvalidError("addBorder()::overflow");
    }
    std::string line(width+2, horizontal);
    line[0] = line[line.size()-1] = corner;
    Ncurses::wattron_s(wp, Ncurses::COLOR_PAIR_s(color.getPair()));

    // draw horizontal
    Ncurses::wmove_s(wp, topLeft.getRow(), topLeft.getCol());
    Ncurses::waddstr_s(wp, line.c_str());
    Ncurses::wmove_s(wp, bottomRight.getRow(), topLeft.getCol());
    Ncurses::waddstr_s(wp, line.c_str());

    // draw vertical
    std::string col(1, vertical);
    for (int i = 0; i != height; ++i) {
        Ncurses::wmove_s(wp, topLeft.getRow()+1+i, topLeft.getCol());
        Ncurses::waddstr_s(wp, col.c_str());
        Ncurses::wmove_s(wp, topLeft.getRow()+1+i, bottomRight.getCol());
        Ncurses::waddstr_s(wp, col.c_str());
    }

    Ncurses::wattroff_s(wp, Ncurses::COLOR_PAIR_s(color.getPair()));
    // Ncurses::wrefresh_s(wp);
}
