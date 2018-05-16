#ifndef PLAYING_WIN_H
#define PLAYING_WIN_H
#include "../ncurse-wrap/util_window.h"
#include "../ncurse-wrap/util_rollingtext.h"
#include "../ncurse-wrap/util_statictext.h"
#include "../ncurse-wrap/util_border.h"
#include "../ncurse-wrap/util_text.h"
#include "../ncurse-wrap/util_menu.h"
#include "../ncurse-wrap/util_nmenu.h"
#include "../ncurse-wrap/block.h"
#include <vector>
#include <memory>
#include <QObject>

class PlayingWin: public Window {
    Q_OBJECT
public:
    PlayingWin(Resources* res);
    ~PlayingWin();
    Window* handleInput(int ch) override;
    void update() override;
    void draw() override;
signals:
    void play();
    void pause();
    void setVolume(int);
    void next();
    void previous();
public slots:
private:
    Window* _handleInput0(int);
    Window* _handleInput1(int);
    size_t winFocus;
    void drawProgressBar();
    void drawVolume();
    void drawPlayingIcon();
    void drawSongName();
    void initSongList();
    static int volume;
    static bool playing;
    NMenu menu;
    std::vector<std::string> playIcon = {" #    ",
                                         " ###  ",
                                         " #### ",
                                         " ###  ",
                                         " #    "};
    std::vector<std::string> pauseIcon ={" # # ",
                                         " # # ",
                                         " # # ",
                                         " # # ",
                                         " # # "};
};

#endif // PLAYING_WIN_H
