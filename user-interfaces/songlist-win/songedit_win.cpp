#include "songedit_win.h"
#include "../../resources.h"
#include "../playing-win/playing_win.h"
#include "../../ncurse-wrap/util_nblock.h"
#include "../../ncurse-wrap/util_nborder.h"

static const std::vector<std::string> editOper = {
    "Play",
    "Sort list",
    "Remove song",
    "Move to..",
};

static const Position songEditMenuPos(4, 62);
static const Position moveToMenuPos(3, 44);
static const Position songInfoDialogPos(4, 26);

SongEditWin::SongEditWin(Resources* res, NMenu const& listnames, NMenu const& songlist)
    : Listsongs_win(res, listnames, songlist) {
    songEditMenu = NMenu(18, 5);
    for (auto const& i: editOper) {
        songEditMenu.addItem(NText(tl(i)));
    }
    songEditMenu.setAttr(normal);
    songEditMenu.setHighlight(highlight);
    moveToMenu = NMenu(14, 10);
    for (auto const& listname: resource->songlistNames) {
        moveToMenu.addItem(NText(listname.toStdString()));
    }
    moveToMenu.setAttr(normal);
    moveToMenu.setHighlight(highlight);
    connect(this, SIGNAL(play()), &resource->player, SLOT(play()));
    connect(this, SIGNAL(setCurrentIndex(int)), &resource->playlist, SLOT(setCurrentIndex(int)));
}

SongEditWin::~SongEditWin() {}

Window* SongEditWin::handleInput(int ch) {
    if (openedMoveToList) {
        return moveToListHandleInput(ch);
    }

    return mainHandleInput(ch);
}

void SongEditWin::update() {

}

void SongEditWin::draw() {
    Listsongs_win::draw();
    Window::draw(songEditMenu, songEditMenuPos);
    NBorder tmpBorder('-', '|', '+');
    tmpBorder.fit(moveToMenu);

    if (openedMoveToList) {
        Window::draw(NBlock<NMenu, NBorder>(moveToMenu, tmpBorder), moveToMenuPos);
    }

    if (openedMoveToList) {
        Window::draw(NText(tl(std::string("available key")) + ": ↑ ↓ Enter Esc    ", normal), Position(23, 1));
    } else {
        Window::draw(NText(tl(std::string("available key")) + ": ↑ ↓ Enter Esc    ", normal), Position(23, 1));
    }
}

/*---------handleInput------------*/

Window* SongEditWin::mainHandleInput(int ch) {
    if (ch == NK::Up) {
        songEditMenu.moveUp();
    } else if (ch == NK::Down) {
        songEditMenu.moveDown();
    } else if (ch == NK::Esc) {
        return new Listsongs_win(resource, _listnames, _songlist);
    } else if (ch == NK::Enter) {
        if (!songEditMenu.isEmpty()) {
            return handleOperation(songEditMenu.getFocus());
        }
    }
    return this;
}

Window* SongEditWin::moveToListHandleInput(int ch) {
    if (ch == NK::Up) {
        moveToMenu.moveUp();
    } else if (ch == NK::Down) {
        moveToMenu.moveDown();
    } else if (ch == NK::Esc) {
        openedMoveToList = false;
    } else if (ch == NK::Enter) {  // move to..
        QStringList& sourceSongList = resource->songlists[_listnames.getFocus()];
        QStringList& objSonglist = resource->songlists[moveToMenu.getFocus()];
        int songIndex = _songlist.getFocus();
        objSonglist.push_back(sourceSongList.at(songIndex));
        sourceSongList.removeAt(songIndex);
        _fill_list(_listnames.getFocus());
        openedMoveToList = false;
        return new Listsongs_win(resource, _listnames, _songlist);
    }
    return this;
}


Window* SongEditWin::handleOperation(int index) {
    QStringList& playingList = resource->playingList;
    QStringList& objSongList = resource->songlists[_listnames.getFocus()];
    QString const& song = objSongList.at(_songlist.getFocus());
    switch(index) {
    case 0:  /* Play */
        int songIndexInPlaylist;
        if ((songIndexInPlaylist = playingList.indexOf(song)) == -1) {  //not found
            songIndexInPlaylist = playingList.size();
            playingList.push_back(song);
            resource->refreshPlayinglist();
        }
        emit setCurrentIndex(songIndexInPlaylist);
        emit play();
        return new PlayingWin(resource);
    case 1: /* Sort List */
        std::sort(objSongList.begin(), objSongList.end());
        _fill_list(_listnames.getFocus());
        return new Listsongs_win(resource, _listnames, _songlist);
    case 2: /* Remove Song */
        objSongList.removeAt(_songlist.getFocus());
        _fill_list(_listnames.getFocus());
        return new Listsongs_win(resource, _listnames, _songlist);
    case 3: /* Move to.. */
        openedMoveToList = true;
        return this;
    }
    return new Listsongs_win(resource, _listnames, _songlist);
}

void SongEditWin::getCurrentSongInfo() {
    // TODO: get song information
    QString infoStr;
    infoStr += tl("Information").c_str() + QString(":\n\n");
    infoStr += QString("Name: ") + _songlist.getFocusCont().c_str();
}
