#ifndef SONGLIST_WIN_H
#define SONGLIST_WIN_H

#include "./playing_win.h"

class SonglistWin : public PlayingWin
{
public:
    SonglistWin(Resources* res);
    ~SonglistWin();
    Window* handleInput(int ch) override;
    void update() override;
    void draw() override;

private:
    void initSongList();
    NMenu menu;
};

#endif // SONGLIST_WIN_H
