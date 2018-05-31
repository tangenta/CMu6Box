#ifndef PLAYING_WIN_H
#define PLAYING_WIN_H
#include "../../ncurse-wrap/util_window.h"
#include <vector>
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

protected:
private:
    void drawProgressBar();
    void drawVolume();
    void drawPlayingIcon();
    void drawSongName();
    void drawPlayMode();
    int volume;
    std::vector<std::string> playIcon = {" *    ",
                                         " ***  ",
                                         " **** ",
                                         " ***  ",
                                         " *    "};

    std::vector<std::string> pauseIcon ={" # # ",
                                         " # # ",
                                         " # # ",
                                         " # # ",
                                         " # # "};
};

#endif // PLAYING_WIN_H
