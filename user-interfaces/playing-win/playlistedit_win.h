#ifndef PLAYLISTEDIT_WIN_H
#define PLAYLISTEDIT_WIN_H
#include "playlist_win.h"

class PlaylistEditWin: public PlaylistWin {
public:
    PlaylistEditWin(Resources* res, int focus);
    ~PlaylistEditWin();
    Window* handleInput(int ch);
    void update();
    void draw();
private:
    void setPlayNext();
    void removeFromList();
    NMenu editOptions;
    int focusItem;
};

#endif // PLAYLISTEDIT_WIN_H
