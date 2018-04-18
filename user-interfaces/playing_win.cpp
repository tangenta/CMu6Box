#include "playing_win.h"
#include "menu_win.h"
#include "../ncurse-wrap/util_rollingtext.h"
#include "../ncurse-wrap/util_statictext.h"
#include "../ncurse-wrap/util_border.h"
#include "../ncurse-wrap/ncurses_wrapper.h"
#include "../ncurse-wrap/util_menu.h"
#include <algorithm>
#include <string>

PlayingWin::PlayingWin()
    : text(StaticText("play", Position(11,1),
                      80, Attr(), AlignMode::Center)), playing(false) {

}


Window* PlayingWin::handleInput(int ch) {

}

void PlayingWin::update() {

}

void PlayingWin::draw() {
    text.draw(this);
}
