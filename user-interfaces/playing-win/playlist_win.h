#ifndef SONGLIST_WIN_H
#define SONGLIST_WIN_H

#include "./playing_win.h"

class PlaylistWin : public PlayingWin {
public:
    PlaylistWin(Resources* res);
    PlaylistWin(Resources* res, NMenu const& list);
    ~PlaylistWin();
    Window* handleInput(int ch) override;
    void update() override;
    void draw() override;

protected:
    NMenu list;

private:
    void initSongList();
};

#endif // SONGLIST_WIN_H
