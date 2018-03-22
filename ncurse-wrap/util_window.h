#ifndef WINDOW_H
#define WINDOW_H

#include "uitl_position.h"
#include "ncurses_wrapper.h"

class Window {
    friend class NCController;
public:
    Window();
    Window(int rows, int cols, int org_x, int org_y);
    Window(Window const&) = delete;
    Window(Window &&) = delete;
    Window& operator=(Window const&) = delete;
    Window& operator=(Window &&) = delete;

    // getter
    int getRows();
    int getCols();
    Color getBkgd();

    // setter
    void setBkgd(Color);

    //void addText(std::string const&, Position const&, int size, Color const&, Font const&, AlignMode);
    void addText(std::string const&);
    void addText(std::string const&, Position const&,
                 Color const& = Color(NC::White),
                 Font const& = Font({NF::Normal}),
                 AlignMode = AlignMode::Left, int = -1);

    // debug
    NWINDOW* getWp() { return wp; }
private:
    Color bkColor;
    NWINDOW* wp;
};

#endif // WINDOW_H
