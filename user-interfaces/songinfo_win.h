#ifndef SONGINFO_WIN_H
#define SONGINFO_WIN_H
#include "../ncurse-wrap/util_window.h"
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
};

#endif // SONGINFO_WIN_H
