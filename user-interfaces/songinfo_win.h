#ifndef SONGINFO_WIN_H
#define SONGINFO_WIN_H
#include "../ncurse-wrap/util_window.h"
#include "../ncurse-wrap/util_dialog.h"
#include "../ncurse-wrap/util_nblock.h"
#include "../ncurse-wrap/util_nborder.h"
#include <QMediaContent>

class SongInfoWin: public Window {
public:
    SongInfoWin(Resources* res, QMediaContent cont);
    ~SongInfoWin();
    Window* handleInput(int ch);
    void update();
    void draw();
private:
    std::string info;
    Dialog dialog;
};

#endif // SONGINFO_WIN_H
