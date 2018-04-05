#include "nccontroller.h"
#include "ncurse-wrap/ncurses_wrapper.h"
#include <string>
#include "ncurse-wrap/exceptions.h"
#include "ncurse-wrap/util_window.h"
#include <sstream>

#ifndef DEFAULT_INTERVAL
#define DEFAULT_INTERVAL 10
#endif

NCController::NCController(QObject *parent)
    : QObject(parent) {
    Ncurses::initscr_s();
    if (Ncurses::has_color_s()) {
        Ncurses::start_color_s();
    }
    Ncurses::nodelay_s(Ncurses::getStdscr(), true);
    Ncurses::keypad_s(Ncurses::getStdscr(), true);
    Ncurses::cbreak_s();
    Ncurses::refresh_s();
}

NCController::~NCController() {
    Ncurses::nodelay_s(Ncurses::getStdscr(), false);
    Ncurses::getch_s();
    for (auto i: winList) {
        delete i;
    }
    Ncurses::endwin_s();
}

void NCController::addWin(Window *win) {
    winList.push_back(win);
}

void NCController::delWin(Window *win) {
    winList.remove(win);
}


void NCController::exec() {
    Ncurses::noecho_s();
    int input;
    while ((input = Ncurses::getch_s()) == -1) {
        Ncurses::napms_s(DEFAULT_INTERVAL);
    }
    if (input == NK::Esc) {
        return;
    } else {
        parseInput(input);
    }
    return exec();
}

void NCController::parseInput(int ch) {
    winList.back()->handleInput(ch);
//    if (ch == NK::Up) {
//        Ncurses::waddstr_s(Ncurses::getStdscr(), "up ");
//    }
//    if (ch == NK::Down) {
//        Ncurses::waddstr_s(Ncurses::getStdscr(), "down ");
//    }
//    if (ch == NK::Right) {
//        Ncurses::waddstr_s(Ncurses::getStdscr(), "right ");
//    }
//    if (ch == NK::Left) {
//        Ncurses::waddstr_s(Ncurses::getStdscr(), "left ");
//    }
//    else {
//        std::stringstream ss;
//        ss << ch;
//        std::string tmp;
//        ss >> tmp;
//        Ncurses::waddstr_s(Ncurses::getStdscr(), tmp.c_str());
//    }
}
