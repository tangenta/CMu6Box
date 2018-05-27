#include "playlist_win.h"
#include "../../nccontroller.h"
#include "./playing_win.h"

static const Position songList(4, 56);

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

void PlaylistWin::update() {
    static int counter = 0;
    if (counter++ == 20) {
        counter = 0;
        menu.update();
    }
}

void PlaylistWin::draw() {
    this->PlayingWin::draw();
    Window::draw(menu, songList);
}

void PlaylistWin::initSongList() {
    menu = NMenu(22, 10);
    int i = 0;
    for (const QMediaContent& c : resource->playingList) {
        std::string is = std::to_string(++i);
        std::string n = c.canonicalUrl().fileName().toStdString();
        std::size_t p = n.find_last_of('.');
        n = n.substr(0, p);
        menu.addItem(NText(is + ". " + n));
    }
    menu.setAttr(normal);
    menu.setHighlight(highlight);
}
