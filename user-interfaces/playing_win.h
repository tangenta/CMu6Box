#ifndef PLAYING_WIN_H
#define PLAYING_WIN_H
#include "../ncurse-wrap/util_window.h"
#include "../ncurse-wrap/util_rollingtext.h"
#include "../ncurse-wrap/util_statictext.h"
#include "../ncurse-wrap/util_border.h"
#include "../ncurse-wrap/util_text.h"
#include "../ncurse-wrap/util_menu.h"
#include "../ncurse-wrap/block.h"
#include <vector>
#include <memory>

class PlayingWin: public Window {
public:
    PlayingWin();
    Window* handleInput(int ch) override;
    void update() override;
    void draw() override;


private:
    size_t subwin;

    void initSubwin0();
    Window* handleInputSubwin0(int ch);
    void updateSubwin0();
    void drawSubwin0();
    int focusSubwin0;
    std::shared_ptr<std::vector<Block<Border, StaticText>>> objSubwin0;

    void initSubwin1();
    Window* handleInputSubwin1(int ch);
    void updateSubwin1();
    void drawSubwin1();
    int focusSubwin1;
    std::shared_ptr<Block<Border, Menu>> objSubwin1;
};

#endif // PLAYING_WIN_H
