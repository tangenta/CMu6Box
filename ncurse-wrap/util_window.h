#ifndef WINDOW_H
#define WINDOW_H

#include "util_position.h"
#include "ncurses_wrapper.h"
#include "util_nmenu.h"
#include "../database/translator.h"
#include <QObject>

class Resources;
class NCController;

class Window: public QObject {
    Q_OBJECT
public:
    friend class NCController;
    Window(Resources* res);
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

    void clearScreen();
    std::string getInput(int row, int col, int length);

    void setBackground(QString const& colorStr);

    template <typename Drawable>    // Drawable must have defined toPrinter()
    void draw(Drawable const& thing, Position at) {
        Printer printer = thing.toPrinter();
        Ncurses::wmove_s(wp, at.getRow(), at.getCol());
        for (auto& i: printer) {
            Ncurses::wattron_s(wp, i.attr.toBit());
            try {
                Ncurses::waddstr_s(wp, i.content.c_str());
            } catch (FatalError const& e) {
                // Fixme: bad design, suppressing bottom-right ERR
                if (at.getRow() != 24) throw e;
            }
            Ncurses::wattroff_s(wp, i.attr.toBit());
            at = at + i.bias;
            Ncurses::wmove_s(wp, at.getRow(), at.getCol());
        }
        Ncurses::wmove_s(wp, 0, 0);
    }

    // update
    virtual Window* handleInput(int ch) = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
protected:
    Resources* resource;
    Attr highlight;
    Attr normal;
    std::string tl(std::string const& str);
    std::string tl(const char* str);

private:
    NWINDOW* wp;
};

#endif // WINDOW_H
