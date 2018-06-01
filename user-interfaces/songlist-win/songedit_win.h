#ifndef SONGEDIT_WIN_H
#define SONGEDIT_WIN_H
#include "listsongs_win.h"
#include "../../ncurse-wrap/util_dialog.h"

class SongEditWin: public Listsongs_win {
public:
    SongEditWin(Resources* res, NMenu const& listnames, NMenu const& songlist);
    ~SongEditWin();
    Window* handleInput(int ch) override;
    void update() override;
    void draw() override;
private:
    Window* mainHandleInput(int ch);
    Window* moveToListHandleInput(int ch);
    Window* songInfoHandleInput(int ch);
    Window* handleOperation(int index);
    void getCurrentSongInfo();
    NMenu songEditMenu;
    NMenu moveToMenu;
    Dialog songInfoDialog;
    bool openedMoveToList = false;
    bool openedSongInfo = false;
};

#endif // SONGEDIT_WIN_H
