#include "playlistedit_win.h"
#include "../../ncurse-wrap/util_nblock.h"
#include "../../ncurse-wrap/util_nborder.h"
#include "../../resources.h"

static const Position editWinPos(6, 54);
static const std::vector<std::string> options =
{"play next", "remove from list", "song info", "source song list"};

PlaylistEditWin::PlaylistEditWin(Resources* res, int focus)
    : PlaylistWin(res), focusItem(focus) {
    editOptions = NMenu(22, 4);
    for (auto& i: options) {
        editOptions.addItem(NText(">>  " + i, normal));
    }
    editOptions.setAttr(normal);
    editOptions.setHighlight(highlight);
}

PlaylistEditWin::~PlaylistEditWin() {}

Window* PlaylistEditWin::handleInput(int ch) {
    if (ch == NK::Esc) {
        return new PlaylistWin(resource);
    } else if (ch == NK::Up) {
        editOptions.moveUp();
    } else if (ch == NK::Down) {
        editOptions.moveDown();
    } else if (ch == NK::Enter){
        int localFocus = editOptions.getFocus();
        switch (localFocus) {
        case 0: setPlayNext(); break; /* play next */
        case 1: removeFromList(); break; /* remove from list */
        case 2: break; /* song info */
        case 3: break; /* source song list */
        }
        return new PlaylistWin(resource);
    }
    return this;
}

void PlaylistEditWin::update() {}

void PlaylistEditWin::draw() {
    PlaylistWin::draw();
    NBorder bord('=', '*', '#', normal);
    bord.fit(editOptions);
    Window::draw(NBlock<NMenu, NBorder>(editOptions, bord), editWinPos);
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
}



