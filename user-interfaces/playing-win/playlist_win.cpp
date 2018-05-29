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

PlaylistWin::~PlaylistWin() {}

Window* PlaylistWin::handleInput(int ch) {
    if (ch == NK::Up) {
        menu.moveUp();
    } else if (ch == NK::Down) {
        menu.moveDown();
    } else if (ch == NK::Esc) {
        return new PlayingWin(resource);
    } else if (ch == NK::Space) {
        if (resource->player.state() == QMediaPlayer::PlayingState) {
            emit pause();
        } else {
            emit play();
        }
    } else if (ch == NK::Right || ch == NK::Left) {
        if (!menu.isEmpty()) {
            return new PlaylistEditWin(resource, menu.getFocus());
        }
    } else if (ch == NK::Enter) {
        if (!menu.isEmpty()) {
            resource->playlist.setCurrentIndex(menu.getFocus());
        }
    }
    return this;
}

void PlaylistWin::update() {
    static int counter = 0;
    if (counter++ == 20) {
        counter = 0;
        menu.update();
    }
}

void PlaylistWin::draw() {
    this->PlayingWin::draw();

    Window::draw(NText("PLAYING LIST", normal), PLAYING_LIST + Position(-2, 4));
    Window::draw(menu, PLAYING_LIST);
}

void PlaylistWin::initSongList() {
    menu = NMenu(22, 10);
    int i = 0;
    for (const QString& c : resource->playingList) {
        std::string is = std::to_string(++i);
        std::string n = QUrl(c).fileName().toStdString();
        std::size_t p = n.find_last_of('.');
        n = n.substr(0, p);
        menu.addItem(NText(is + ". " + n));
    }
    menu.setAttr(normal);
    menu.setHighlight(highlight);
}
