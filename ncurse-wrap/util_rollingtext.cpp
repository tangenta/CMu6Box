#include "util_rollingtext.h"

RollingText::RollingText(const std::string &cont,
                         const Position &pos,
                         int width,
                         const Attr &attr)
    : Text(cont, pos, width, attr) {
    textPos = 0;

    // 若过短则补空格，让其左对齐
    lenOutOfRange = cont.length() - width;
    if (lenOutOfRange < 0) {
        content = cont + std::string(-lenOutOfRange, ' ');
        lenOutOfRange = 0;
    }
}


void RollingText::draw(Window *win) {
    const std::string str(content.begin()+textPos, content.begin()+textPos+width);

    NWINDOW *wp = win->getNWindow();
    Ncurses::wmove_s(wp, position.getRow(), position.getCol());
    Ncurses::wattron_s(wp, attribute.toBit());
    Ncurses::waddstr_s(wp, str.c_str());
    Ncurses::wattroff_s(wp, attribute.toBit());
}

void RollingText::update() {
    textPos = (textPos+1) % (lenOutOfRange+1); // something mathematics
}
