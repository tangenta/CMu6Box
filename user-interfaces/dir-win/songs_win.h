#ifndef SONGS_WIN_H
#define SONGS_WIN_H
#include "songlist_win.h"

class Songs_win : public Songlist_win {
public:
    Songs_win(Resources* res, NMenu const& listnames, NMenu const& songlist);
    ~Songs_win();
    Window* handleInput(int ch) override;
    void update() override;
    void draw() override;

private:
    void _initMenusAttr();
};

#endif // SONGS_WIN_H
