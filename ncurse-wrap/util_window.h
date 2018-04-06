#ifndef WINDOW_H
#define WINDOW_H

#include "uitl_position.h"
#include "ncurses_wrapper.h"

class Window {
    friend class NCController;
public:
    Window();
    virtual ~Window();
    Window(int rows, int cols, int org_x, int org_y);
    Window(Window const&) = delete;
    Window(Window &&) = delete;
    Window& operator=(Window const&) = delete;
    Window& operator=(Window &&) = delete;

    // getter
    int getRows();
    int getCols();

    // utilities
    void addText(std::string const&);
    void addText(std::string const&, Position const&,
                 Color const& = Color(NC::White),
                 Font const& = Font({NF::Normal}),
                 AlignMode = AlignMode::Left, int = -1);
    void addBorder(Position const& topLeft,
                   Position const& bottomRight,
                   Color const& = Color(NC::White),
                   char horizontal = '-',
                   char vertical = '|',
                   char corner = '+');

    // update
    virtual Window* handleInput(int ch) = 0;
private:
    NWINDOW* wp;
};

#endif // WINDOW_H
