#include "util_statictext.h"

StaticText::StaticText(const std::string &cont,
                       const Position &pos,
                       int width,
                       const Attr &attr,
                       AlignMode mode)
    : Text(cont, pos, width, attr), align(mode) {

    int blankCharNum = width - cont.length();
    blankCharNum = blankCharNum < 0 ? 0 : blankCharNum;

    std::string tstr(blankCharNum, ' ');
    switch (mode) {
        case AlignMode::Right:
            tstr.append(cont); break;
        case AlignMode::Left:
            tstr.insert(0, cont, 0, cont.npos); break;
        case AlignMode::Center:
            tstr.insert(blankCharNum/2, cont, 0, cont.npos); break;
    }

    content = std::string(tstr.begin(), tstr.begin()+width);
    record = content;
}

void StaticText::update() {
    forSoCallMutable();
}

void StaticText::draw(Window *win) {
    forSoCallMutable();

    NWINDOW *wp = win->getNWindow();
    Ncurses::wmove_s(wp, position.getRow(), position.getCol());
    Ncurses::wattron_s(wp, attribute.toBit());
    Ncurses::waddstr_s(wp, content.c_str());
    Ncurses::wattroff_s(wp, attribute.toBit());
}

void StaticText::forSoCallMutable() {
    if (record != content) {
        int blankCharNum = width - content.length();
        blankCharNum = blankCharNum < 0 ? 0 : blankCharNum;

        std::string tstr(blankCharNum, ' ');
        switch (align) {
            case AlignMode::Right:
                tstr.append(content); break;
            case AlignMode::Left:
                tstr.insert(0, content, 0, content.npos); break;
            case AlignMode::Center:
                tstr.insert(blankCharNum/2, content, 0, content.npos); break;
        }

        record = std::string(tstr.begin(), tstr.begin()+width);
        content = record;
    }
}
