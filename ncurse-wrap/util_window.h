#ifndef WINDOW_H
#define WINDOW_H

#include "util_position.h"
#include "ncurses_wrapper.h"
#include <QObject>

class Window {
public:
    friend class NCController;
    Window();
    virtual ~Window();
    Window(int rows, int cols, int org_x, int org_y);
    Window(Window const&) = delete;
    Window(Window &&) = delete;
    Window& operator=(Window const&) = delete;
    Window& operator=(Window &&) = delete;

    // getter
    int getRows() const;
    int getCols() const;
    NWINDOW* getNWindow() const;

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
    
    void addBlock(Position const& topLeft,
                  Position const& bottomRight,
                  std::initializer_list<std::string> textList,
                  Color const& = Color(NC::White),
                  Font const& = Font({NF::Normal}),
                  char horizontal = '-',
                  char vertical = '|',
                  char corner = '+');

    void clearScreen();

    void fillBlank(Position const& topLeft,
                   Position const& bottomRight);

    // update
    virtual Window* handleInput(int ch) = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

private:
    NWINDOW* wp;
};

#endif // WINDOW_H
