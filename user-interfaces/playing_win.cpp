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

static const int maxVolume = 8;
static const Position volumePos(4, 6);
static const Position playingIconPos(6, 36);

PlayingWin::PlayingWin(Resources* res)
    : Window(res), border(Position(0,0), 79, 24),
      volumeBorder(volumePos, 3, maxVolume+2),
      volume(2), playing(false) {
    connect(this, SIGNAL(play()), &resource->player, SLOT(play()));
    connect(this, SIGNAL(pause()), &resource->player, SLOT(pause()));
    connect(this, SIGNAL(setVolume(int)), &resource->player, SLOT(setVolume(int)));
}

PlayingWin::~PlayingWin() {}

Window* PlayingWin::handleInput(int ch) {
    if (ch == NK::Enter) {
        playing = !playing;
        if (playing) {
            emit play();
        } else {
            emit pause();
        }
        return this;
    } else if (ch == NK::Esc) {
        return new MenuWin(resource);
    } else if (ch == NK::Up) {
        if (volume < maxVolume) {
            volume++;
            emit setVolume(100*volume/maxVolume);
        }
    } else if (ch == NK::Down) {
        if (volume > 0) {
            volume--;
            emit setVolume(100*volume/maxVolume);
        }
    }
    return this;
}

void PlayingWin::update() {
}

void PlayingWin::draw() {
    drawVolume();
    drawPlayingIcon();
    border.draw(this);
}

void PlayingWin::drawVolume() {
    int row = volumePos.getRow();
    int col = volumePos.getCol();
    addText("VOL", Position(row-1, col));
    row++;
    col++;
    for (int i = 0; i != maxVolume; ++i) {
        std::string volStr = (maxVolume-i <= volume) ? "#" : " ";
        addText(volStr, Position(row+i, col));
    }
    volumeBorder.draw(this);

}

void PlayingWin::drawPlayingIcon() {
    int row = playingIconPos.getRow();
    int col = playingIconPos.getCol();
    for (size_t i = 0; i != playIcon.size(); ++i) {
        if (playing) {
            addText(pauseIcon[i], Position(row+i, col));
        } else {
            addText(playIcon[i], Position(row+i, col));
        }
    }

}
