#include "songs_win.h"
#include "../menu_win.h"

Songs_win::Songs_win(Resources* res, NMenu const& listnames, NMenu const& songlist)
    : Songlist_win(res, listnames, songlist) {
    _initMenusAttr();
}

Songs_win::~Songs_win() {}

Window* Songs_win::handleInput(int ch) {
    if (ch == NK::Down) {
        _songlist.moveDown();
    } else if (ch == NK::Up) {
        _songlist.moveUp();
    } else if (ch == NK::Left) {
        return new Songlist_win(resource, _listnames, _songlist);
    } else if (ch == NK::Esc) {
        return new MenuWin(resource);
    }
    return this;
}

void Songs_win::update() {
    static int counter = 0;
    if (counter++ == 20) {
        counter = 0;
        _songlist.update();
    }
}
void Songs_win::draw() {
    Songlist_win::draw();

    // title
    static const Position LIST_NAME(4, 4);
    static const Position SONG_LIST(4, 20);
    Window::draw(NText("  SONGLIST"), LIST_NAME + Position(-2, 1));
    Window::draw(NText("> CONTENT"), SONG_LIST + Position(-2, 12));
}

void Songs_win::_initMenusAttr() {
    _listnames.setAttr(normal);
    _listnames.setHighlight(normal);
    _songlist.setAttr(normal);
    _songlist.setHighlight(highlight);
}
