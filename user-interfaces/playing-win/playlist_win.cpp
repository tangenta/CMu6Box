#include "playlist_win.h"
#include "../../nccontroller.h"
#include "./playing_win.h"
#include "../../ncurse-wrap/util_nblock.h"
#include "../../ncurse-wrap/util_nborder.h"
#include "playlistedit_win.h"

static const Position PLAYING_LIST(4, 55);

PlaylistWin::PlaylistWin(Resources *res) : PlayingWin(res) {
    initSongList();
}

PlaylistWin::PlaylistWin(Resources *res, NMenu const& menu)
    : PlayingWin(res), list(menu) {}

PlaylistWin::~PlaylistWin() {}

Window* PlaylistWin::handleInput(int ch) {
    if (ch == NK::Up) {
        list.moveUp();
    } else if (ch == NK::Down) {
        list.moveDown();
    } else if (ch == NK::Esc) {
        return new PlayingWin(resource);
    } else if (ch == NK::Space) {
        if (resource->player.state() == QMediaPlayer::PlayingState) {
            emit pause();
        } else {
            emit play();
        }
    } else if (ch == NK::Enter) {
        if (!list.isEmpty()) {
            return new PlaylistEditWin(resource, list);
        }
    }
    return this;
}

void PlaylistWin::update() {
    static int counter = 0;
    if (counter++ == 20) {
        counter = 0;
        list.update();
    }
}

void PlaylistWin::draw() {
    this->PlayingWin::draw();

    Window::draw(NText(tl("PLAYING LIST"), normal), PLAYING_LIST + Position(-2, 4));
    Window::draw(list, PLAYING_LIST);
    Window::draw(NText(tl(std::string("available key")) + ": ↑ ↓ Enter Esc Space        ", normal), Position(23, 1));
}

void PlaylistWin::initSongList() {
    list = NMenu(22, 10);
    int i = 0;
    for (const QString& c : resource->playingList) {
        std::string is = std::to_string(++i);
        std::string n = QUrl(c).fileName().toStdString();
        std::size_t p = n.find_last_of('.');
        n = n.substr(0, p);
        list.addItem(NText(is + ". " + n));
    }
    list.setAttr(normal);
    list.setHighlight(highlight);
}
