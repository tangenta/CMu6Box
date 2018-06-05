#include "playlistedit_win.h"
#include "../../ncurse-wrap/util_nblock.h"
#include "../../ncurse-wrap/util_nborder.h"
#include "../../resources.h"

static const Position editWinPos(6, 54);
static const std::vector<std::string> options =
{"Play", "Play next", "Remove from list"};

PlaylistEditWin::PlaylistEditWin(Resources *res, const NMenu &list)
    : PlaylistWin(res, list), focusItem(list.getFocus()) {
    editOptions = NMenu(22, 3);
    for (auto& i: options) {
        editOptions.addItem(NText("  " + tl(i), normal));
    }
    editOptions.setAttr(normal);
    editOptions.setHighlight(highlight);
}

PlaylistEditWin::~PlaylistEditWin() {}

Window* PlaylistEditWin::handleInput(int ch) {
    if (ch == NK::Esc) {
        return new PlaylistWin(resource, list);
    } else if (ch == NK::Up) {
        editOptions.moveUp();
    } else if (ch == NK::Down) {
        editOptions.moveDown();
    } else if (ch == NK::Enter){
        int localFocus = editOptions.getFocus();
        switch (localFocus) {
        case 0: resource->playlist.setCurrentIndex(focusItem);
                emit play();
                break;
        case 1: setPlayNext(); break; /* play next */
        case 2: removeFromList(); break; /* remove from list */
        }
        return new PlaylistWin(resource, list);
    }
    return this;
}

void PlaylistEditWin::update() {}

void PlaylistEditWin::draw() {
    PlaylistWin::draw();
    NBorder bord('-', ' ', '-', normal);
    bord.fit(editOptions);
    Window::draw(NBlock<NMenu, NBorder>(editOptions, bord), editWinPos);
    Window::draw(NText(tl(std::string("available key")) + ": ↑ ↓ Enter Esc         ", normal), Position(23, 1));
}

void PlaylistEditWin::setPlayNext() {
    int curIndex = resource->playlist.currentIndex();
    if (curIndex != focusItem) {
        resource->playingList.swap(focusItem, curIndex+1);
        resource->playlist.moveMedia(focusItem, curIndex+1);
    }
}

void PlaylistEditWin::removeFromList() {
    resource->playingList.removeAt(focusItem);
    resource->playlist.removeMedia(focusItem);
    PlaylistWin::initSongList();
}
