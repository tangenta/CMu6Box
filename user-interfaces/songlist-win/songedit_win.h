#ifndef SONGEDIT_WIN_H
#define SONGEDIT_WIN_H
#include "listsongs_win.h"
#include "../../ncurse-wrap/util_dialog.h"

class SongEditWin: public Listsongs_win {
    Q_OBJECT
public:
    SongEditWin(Resources* res, NMenu const& listnames, NMenu const& songlist);
    ~SongEditWin();
    Window* handleInput(int ch) override;
    void update() override;
    void draw() override;
signals:
    void setCurrentIndex(int);
    void play();
private:
    Window* mainHandleInput(int ch);
    Window* moveToListHandleInput(int ch);
    Window* handleOperation(int index);
    void getCurrentSongInfo();
    NMenu songEditMenu;
    NMenu moveToMenu;
    bool openedMoveToList = false;
};

#endif // SONGEDIT_WIN_H
