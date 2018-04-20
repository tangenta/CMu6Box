#include "util_rollingtext.h"

RollingText::RollingText(const std::string &cont,
                         const Position &pos,
                         int width,
                         const Attr &attr)
    : Text(cont, pos, width, attr), running(true) {
    updateContentRecord();
}


void RollingText::draw(Window *win) {
    if (content != record) updateContentRecord();

    const std::string str(content.begin()+textPos, content.begin()+textPos+width);

    NWINDOW *wp = win->getNWindow();
    Ncurses::wmove_s(wp, position.getRow(), position.getCol());
    Ncurses::wattron_s(wp, attribute.toBit());
    Ncurses::waddstr_s(wp, str.c_str());
    Ncurses::wattroff_s(wp, attribute.toBit());
}

void RollingText::update() {
    if (content != record) updateContentRecord();
    if (running) {
        textPos = (textPos+1) % (lenOutOfRange+1); // something mathematics
    } else {
        textPos = 0;
    }
}

void RollingText::updateContentRecord() {
    textPos = 0;
    lenOutOfRange = content.length() - width;
    if (lenOutOfRange < 0) {
        content += std::string(-lenOutOfRange, ' ');
        lenOutOfRange = 0;
    }

    record = content;
}
