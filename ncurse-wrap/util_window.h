#ifndef WINDOW_H
#define WINDOW_H

#include "util_position.h"
#include "ncurses_wrapper.h"
#include "util_nmenu.h"
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

    // utilities
//protected:
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
    void setBackground(Attr const& attr);

    template <typename Drawable>    // Drawable must have defined toPrinter()
    void draw(Drawable const& thing, Position at) {
        Printer printer = thing.toPrinter();
        Ncurses::wmove_s(wp, at.getRow(), at.getCol());
        for (auto& i: printer) {
            Ncurses::wattron_s(wp, i.attr.toBit());
            try {
                Ncurses::waddstr_s(wp, i.content.c_str());
            } catch (FatalError const& e) {
                // bad design signal: depressing bottom-right ERR
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
private:
    NWINDOW* wp;
};

#endif // WINDOW_H
