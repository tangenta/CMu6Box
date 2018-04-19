#include "playing_win.h"
#include "menu_win.h"
#include "../ncurse-wrap/util_rollingtext.h"
#include "../ncurse-wrap/util_statictext.h"
#include "../ncurse-wrap/util_border.h"
#include "../ncurse-wrap/ncurses_wrapper.h"
#include "../ncurse-wrap/util_menu.h"
#include "../nccontroller.h"
#include <algorithm>
#include <string>

PlayingWin::PlayingWin()
    :text(std::make_shared<StaticText>("play", Position(11,1),
                                       80, Attr(), AlignMode::Center)), playing(false) {}

PlayingWin::~PlayingWin() {}

Window* PlayingWin::handleInput(int ch) {
    if (ch == NK::Enter) {
        std::string displayStr(playing ? "pause" : "play");
        playing = !playing;
        text->content = displayStr;
        if (playing) {
            emit play();
        } else {
            emit pause();
        }
        return this;
    } else if (ch == NK::Esc) {
        return new MenuWin;
    } else {
        return this;
    }
}

void PlayingWin::connector(NCController *nc) {
    connect(this, SIGNAL(play()), nc, SIGNAL(play()));
    connect(this, SIGNAL(pause()), nc, SIGNAL(pause()));
}

void PlayingWin::update() {
    text->update();
}

void PlayingWin::draw() {
    text->draw(this);
}
