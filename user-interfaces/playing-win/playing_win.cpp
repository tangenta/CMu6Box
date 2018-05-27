#include "playing_win.h"
#include "../menu_win.h"
#include "../../ncurse-wrap/ncurses_wrapper.h"
#include "../../ncurse-wrap/util_nmenu.h"
#include "../../nccontroller.h"
#include "./songlist_win.h"
#include <string>
#include <QDateTime>

static const int maxVolume = 13;
static const int maxProgress = 40;
static const Position volumePos(4, 4);
static const Position playingIconPos(6, 36);
static const Position progressBar(18, 13);
static const Position songName(13, 30);

bool PlayingWin::playing = false;
int PlayingWin::volume = 40;

PlayingWin::PlayingWin(Resources* res)
    : Window(res) {
    connect(this, SIGNAL(play()), &resource->player, SLOT(play()));
    connect(this, SIGNAL(pause()), &resource->player, SLOT(pause()));
    connect(this, SIGNAL(setVolume(int)), &resource->player, SLOT(setVolume(int)));
    connect(this, SIGNAL(next()), &resource->playlist, SLOT(next()));
    connect(this, SIGNAL(previous()), &resource->playlist, SLOT(previous()));
}

PlayingWin::~PlayingWin() {}

Window* PlayingWin::handleInput(int ch) {
    if (ch == ' ') {
        playing = !playing;
        if (playing) {
            emit play();
        } else {
            emit pause();
        }
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
        return new SonglistWin(resource);
    }
    return this;
}

void PlayingWin::update() {}

void PlayingWin::draw() {
    drawProgressBar();
    drawVolume();
    drawSongName();
    drawPlayingIcon();
}

void PlayingWin::drawVolume() {
    int row = volumePos.getRow();
    int col = volumePos.getCol();
    Window::draw(NText(std::string("VOL"), normal), Position(row-1, col));
    Window::draw(NBorder(3, maxVolume+2, '-', '|', '+', normal), volumePos);
    row++;
    col++;

    for (int i = 0; i != maxVolume; ++i) {
        std::string volStr = (maxVolume-i <= volume/100.0*maxVolume) ? "#" : " ";
        Window::draw(NText(volStr, normal), Position(row+i, col));
    }

    std::string n = std::to_string(volume);
    n.insert(n.begin(), 3-n.size(), ' ');
    Window::draw(NText(n, normal), Position(row+maxVolume+1, col-1));
}

void PlayingWin::drawPlayingIcon() {
    int row = playingIconPos.getRow();
    int col = playingIconPos.getCol();
    for (size_t i = 0; i != playIcon.size(); ++i) {
        if (playing) {
            Window::draw(NText(pauseIcon[i], normal), Position(row+i, col));
        } else {
            Window::draw(NText(playIcon[i], normal), Position(row+i, col));
        }
    }
}

void PlayingWin::drawSongName() {
    std::string n = resource->player.currentMedia().canonicalUrl().fileName().toStdString();
    std::size_t p = n.find_last_of('.');
    n = n.substr(0, p);

    // TODO:
    NMenu m(24, 1);
    m.addItem(n);
    m.setAttr(normal);
    m.setHighlight(normal);
    Window::draw(m, songName);
}

void PlayingWin::drawProgressBar() {
    qint64 dura = resource->player.duration();
    qint64 pos = resource->player.position();
    std::string posS = QDateTime::fromTime_t(pos/1000).toUTC().toString("mm:ss").toStdString();
    std::string durS = QDateTime::fromTime_t(dura/1000).toUTC().toString("mm:ss").toStdString();

    int progress = (double)pos / dura * maxProgress;

    // two border
    Window::draw(NText(std::string("|"), normal), progressBar);
    Window::draw(NText(std::string("|"), normal),
                 Position(progressBar.getRow(), progressBar.getCol()+maxProgress));

    // progress
    Window::draw(NText(std::string(progress, '>'), normal),
                 Position(progressBar.getRow(), progressBar.getCol()+1));

    // time
    Window::draw(NText(posS + " / ", normal),
                 Position(progressBar.getRow(), progressBar.getCol()+maxProgress+2));
    Window::draw(NText(durS, normal),
                 Position(progressBar.getRow(), progressBar.getCol()+maxProgress+10));
}

