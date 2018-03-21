#include "nccontroller.h"
#include "ncurse-wrap/ncurses_wrapper.h"
#include <string>
#include "ncurse-wrap/exceptions.h"
#include "ncurse-wrap/util_window.h"

#ifndef DEFAULT_INTERVAL
#define DEFAULT_INTERVAL 10
#endif

NCController::NCController(QObject *parent)
    : QObject(parent) {
    Ncurses::initscr_s();
    if (Ncurses::has_color_s()) {
        Ncurses::start_color_s();
    }

    Ncurses::refresh_s();
}

NCController::~NCController() {
    Ncurses::getch_s();
    for (auto i: winList) {
        Ncurses::delwin_s(i->wp);
        delete i;
    }
    Ncurses::endwin_s();
}

Window* NCController::newwin() {
    Window* ret = new Window();
    winList.push_back(ret);
    return ret;
}

Window* NCController::newwin(int rows, int cols, int org_y, int org_x) {
    Window* ret = new Window(rows, cols, org_y, org_x);
    winList.push_back(ret);
    return ret;
}

void NCController::delwin(Window* wp) {
    Ncurses::delwin_s(wp->wp);
    winList.remove(wp);
    delete wp;
}

void NCController::exec() {
    Ncurses::noecho_s();
    Ncurses::nodelay_s(Ncurses::getStdscr(), true);
    Ncurses::keypad_s(Ncurses::getStdscr(), true);
    int input;
    while ((input = Ncurses::getch_s()) == -1) {
        Ncurses::napms_s(DEFAULT_INTERVAL);
    }
    if (input == 'q') {
        return;
    } else {
        parseInput(input);
    }
    return exec();
}

void NCController::parseInput(int ch) {
    if (ch == NK::Up) {
        Ncurses::waddstr_s(Ncurses::getStdscr(), "up ");
    }
    if (ch == NK::Down) {
        Ncurses::waddstr_s(Ncurses::getStdscr(), "down ");
    }
    if (ch == NK::Right) {
        Ncurses::waddstr_s(Ncurses::getStdscr(), "right ");
    }
    if (ch == NK::Left) {
        Ncurses::waddstr_s(Ncurses::getStdscr(), "left ");
    }
}
