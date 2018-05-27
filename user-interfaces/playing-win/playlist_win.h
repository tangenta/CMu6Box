#ifndef SONGLIST_WIN_H
#define SONGLIST_WIN_H

#include "./playing_win.h"

class PlaylistWin : public PlayingWin {
public:
    PlaylistWin(Resources* res);
    ~PlaylistWin();
    Window* handleInput(int ch) override;
    void update() override;
    void draw() override;

private:
    void initSongList();
    NMenu menu;
};

#endif // SONGLIST_WIN_H
