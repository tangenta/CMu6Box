#include "playing_win.h"
#include "menu_win.h"
#include "../ncurse-wrap/util_rollingtext.h"
#include "../ncurse-wrap/util_statictext.h"
#include "../ncurse-wrap/util_border.h"
#include "../ncurse-wrap/util_nborder.h"
#include "../ncurse-wrap/ncurses_wrapper.h"
#include "../ncurse-wrap/util_menu.h"
#include "../ncurse-wrap/util_nmenu.h"
#include "../nccontroller.h"
#include <algorithm>
#include <string>
#include <QDateTime>

static const int maxVolume = 13;
static const int maxProgress = 40;
static const Position volumePos(4, 4);
static const Position playingIconPos(6, 36);
static const Position progressBar(18, 13);
static const Position songName(13, 30);
static const Position songList(4, 56);

bool PlayingWin::playing = false;
int PlayingWin::volume = 40;

PlayingWin::PlayingWin(Resources* res)
    : Window(res), winFocus(0) {
    connect(this, SIGNAL(play()), &resource->player, SLOT(play()));
    connect(this, SIGNAL(pause()), &resource->player, SLOT(pause()));
    connect(this, SIGNAL(setVolume(int)), &resource->player, SLOT(setVolume(int)));
    connect(this, SIGNAL(next()), &resource->playlist, SLOT(next()));
    connect(this, SIGNAL(previous()), &resource->playlist, SLOT(previous()));
    draw();
    initSongList();
}

PlayingWin::~PlayingWin() {}

Window* PlayingWin::handleInput(int ch) {
    if (winFocus == 0) {
        return _handleInput0(ch);
    } else if (winFocus == 1) {
        return _handleInput1(ch);
    }
    return this;
}

Window* PlayingWin::_handleInput0(int ch) {
    if (ch == ' ') {
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
        if (volume < 100) {
            volume += 2;
            emit setVolume(volume);
        }
    } else if (ch == NK::Down) {
        if (volume > 0) {
            volume -= 2;
            emit setVolume(volume);
        }
    } else if (ch == NK::Left) {
        emit previous();
    } else if (ch == NK::Right) {
        emit next();
    } else if (ch == NK::Enter) {
        winFocus = 1;
    }
    return this;
}

Window* PlayingWin::_handleInput1(int ch) {
    if (ch == NK::Up) {
        menu.moveUp();
    } else if (ch == NK::Down) {
        menu.moveDown();
    } else if (ch == NK::Esc) {
        winFocus = 0;
    } else if (ch == ' ') {
        playing = !playing;
        if (playing) {
            emit play();
        } else {
            emit pause();
        }
    } else if (ch == NK::Enter) {
        resource->playlist.setCurrentIndex(menu.getFocus());
    }
    return this;
}

void PlayingWin::update() {
    static int counter = 0;
    if (counter++ == 20) {
        counter = 0;
        menu.update();
    }
}

void PlayingWin::draw() {
    clearScreen();
    if (winFocus == 0) {
        drawProgressBar();
        drawVolume();
        drawSongName();
        drawPlayingIcon();
    } else if (winFocus == 1) {
        drawProgressBar();
        drawVolume();
        drawSongName();
        drawPlayingIcon();
        Window::draw(menu, songList);
    }
}

void PlayingWin::drawVolume() {
    int row = volumePos.getRow();
    int col = volumePos.getCol();
    Window::draw(NText(std::string("VOL")), Position(row-1, col));
    Window::draw(NBorder(3, maxVolume+2, '-', '|', '+'), volumePos);
    row++;
    col++;

    for (int i = 0; i != maxVolume; ++i) {
        std::string volStr = (maxVolume-i <= volume/100.0*maxVolume) ? "#" : " ";
        Window::draw(NText(volStr), Position(row+i, col));
    }

    std::string n = std::to_string(volume);
    n.insert(n.begin(), 3-n.size(), ' ');
    Window::draw(NText(n), Position(row+maxVolume+1, col-1));
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

void PlayingWin::drawSongName() {
    std::string n = resource->player.currentMedia().canonicalUrl().fileName().toStdString();
    std::size_t p = n.find_last_of('.');
    n = n.substr(0, p);

    NMenu m(24, 1);
    m.setHighlight(Attr());
    m.addItem(n);
    Window::draw(m, songName);
}

void PlayingWin::drawProgressBar() {
    qint64 dura = resource->player.duration();
    qint64 pos = resource->player.position();
    std::string posS = QDateTime::fromTime_t(pos/1000).toUTC().toString("mm:ss").toStdString();
    std::string durS = QDateTime::fromTime_t(dura/1000).toUTC().toString("mm:ss").toStdString();

    int progress = (double)pos / dura * maxProgress;

    // two border
    Window::draw(NText(std::string("|")), progressBar);
    Window::draw(NText(std::string("|")),
                 Position(progressBar.getRow(), progressBar.getCol()+maxProgress));

    // progress
    Window::draw(NText(std::string(progress, '>')),
                 Position(progressBar.getRow(), progressBar.getCol()+1));

    // time
    Window::draw(NText(posS + " / "),
                 Position(progressBar.getRow(), progressBar.getCol()+maxProgress+2));
    Window::draw(NText(durS),
                 Position(progressBar.getRow(), progressBar.getCol()+maxProgress+10));
}

void PlayingWin::initSongList() {
    menu = NMenu(22, 10);
    int i = 0;
    for (const QMediaContent& c : resource->contents) {
        std::string is = std::to_string(++i);
        std::string n = c.canonicalUrl().fileName().toStdString();
        std::size_t p = n.find_last_of('.');
        n = n.substr(0, p);
        menu.addItem(NText(is + ". " + n));
    }
}
