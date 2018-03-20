#ifndef WINDOW_H
#define WINDOW_H

#include "constants.h"
#include "text.h"

struct WINDOW;
//class NCController;

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

    void addText(Text const&);
private:
    WINDOW* wp;
    Color bkColor;
};

#endif // WINDOW_H
