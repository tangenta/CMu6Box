#include "util_border.h"

void Border::draw(Window *win) {
    std::string line(width, horizontal);
    line[0] = line[line.size()-1] = corner;
    Ncurses::wattron_s(win->getNWindow(), attribute.toBit());

    // draw horizontal
    Ncurses::wmove_s(win->getNWindow(), position.getRow(), position.getCol());
    Ncurses::waddstr_s(win->getNWindow(), line.c_str());
    Ncurses::wmove_s(win->getNWindow(), position.getRow()+height-1, position.getCol());
    Ncurses::waddstr_s(win->getNWindow(), line.c_str());

    // draw vertical
    std::string col(1, vertical);
    for (int i = 0; i != height-2; ++i) {
        Ncurses::wmove_s(win->getNWindow(), position.getRow()+1+i, position.getCol());
        Ncurses::waddstr_s(win->getNWindow(), col.c_str());
        Ncurses::wmove_s(win->getNWindow(), position.getRow()+1+i, position.getCol()+width-1);
        Ncurses::waddstr_s(win->getNWindow(), col.c_str());
    }

    Ncurses::wattroff_s(win->getNWindow(), attribute.toBit());
}


void Border::update() {}
