#include "util_rollingtext.h"

RollingText::RollingText(const std::string &cont,
                         const Position &pos,
                         int width,
                         const Attr &attr)
    : Text(cont, pos, width, attr), running(true) {
    textPos = 0;

    // 若过短则补空格，让其左对齐
    lenOutOfRange = cont.length() - width;
    if (lenOutOfRange < 0) {
        content = cont + std::string(-lenOutOfRange, ' ');
        record = content;
        lenOutOfRange = 0;
    }
}


void RollingText::draw(Window *win) {
    forSoCallMutable();

    const std::string str(content.begin()+textPos, content.begin()+textPos+width);

    NWINDOW *wp = win->getNWindow();
    Ncurses::wmove_s(wp, position.getRow(), position.getCol());
    Ncurses::wattron_s(wp, attribute.toBit());
    Ncurses::waddstr_s(wp, str.c_str());
    Ncurses::wattroff_s(wp, attribute.toBit());
}

void RollingText::update() {
    forSoCallMutable();

    if (running) {
        textPos = (textPos+1) % (lenOutOfRange+1); // something mathematics
    } else {
        textPos = 0;
    }
}

void RollingText::forSoCallMutable() {
    if (content != record) {
        textPos = 0;

        lenOutOfRange = content.length() - width;
        if (lenOutOfRange < 0) {
            record = content + std::string(-lenOutOfRange, ' ');
            content = record;
            lenOutOfRange = 0;
        }
    }
}
