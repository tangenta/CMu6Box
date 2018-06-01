#include "playing_win.h"
#include "../menu_win.h"
#include "../../ncurse-wrap/ncurses_wrapper.h"
#include "../../ncurse-wrap/util_nmenu.h"
#include "../../nccontroller.h"
#include "../../ncurse-wrap/util_nblock.h"
#include "../../ncurse-wrap/util_nborder.h"
#include "./playlist_win.h"
#include <string>
#include <QDateTime>

static const int maxVolume = 13;
static const int maxProgress = 40;
static const Position volumePos(4, 4);
static const Position playingIconPos(6, 36);
static const Position progressBar(18, 13);
static const Position songName(13, 30);
static const Position playBackModePos(15, 30);
static const std::vector<std::string> playBackMode =
{"Current Item Once", "Current Item In Loop", "Sequential", "Loop", "Random"};


PlayingWin::PlayingWin(Resources* res)
    : Window(res), volume(resource->player.volume()) {
    connect(this, SIGNAL(play()), &resource->player, SLOT(play()));
    connect(this, SIGNAL(pause()), &resource->player, SLOT(pause()));
    connect(this, SIGNAL(setVolume(int)), &resource->player, SLOT(setVolume(int)));
    connect(this, SIGNAL(next()), &resource->playlist, SLOT(next()));
    connect(this, SIGNAL(previous()), &resource->playlist, SLOT(previous()));
}

PlayingWin::~PlayingWin() {}

Window* PlayingWin::handleInput(int ch) {
    if (ch == NK::Space) {
        if (resource->player.state() == QMediaPlayer::PlayingState) {
            emit pause();
        } else {
            emit play();
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
    } else if (ch == NK::Tab) {
        int mode = resource->playlist.playbackMode();
        mode = mode == 4 ? 0 : mode+1;
        resource->playlist.setPlaybackMode(static_cast<QMediaPlaylist::PlaybackMode>(mode));
    } else if (ch == NK::Enter) {
        return new PlaylistWin(resource);
    }
    return this;
}

void PlayingWin::update() {
}

void PlayingWin::draw() {
    drawProgressBar();
    drawVolume();
    drawSongName();
    drawPlayingIcon();
    drawPlayMode();
    Window::draw(NText(tl(std::string("available key")) + ": ← → ↑ ↓ Enter Esc Space", normal), Position(23, 1));
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

    if (resource->player.state() == QMediaPlayer::PlayingState) {
        for (size_t i = 0; i != playIcon.size(); ++i) {
            Window::draw(NText(pauseIcon[i], normal), Position(row+i, col));
        }
    } else {
        for (size_t i = 0; i != playIcon.size(); ++i) {
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
    m.addItem(NText(n, normal));
    m.setAttr(normal);
    m.setHighlight(normal);
    Window::draw(m, songName);
}

void PlayingWin::drawPlayMode() {
    NText mode(tl("Mode")+": "+tl(playBackMode[resource->playlist.playbackMode()]), normal);
    Window::draw(mode, playBackModePos);
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

