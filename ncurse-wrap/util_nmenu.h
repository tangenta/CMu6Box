#ifndef UTIL_NMENU_H
#define UTIL_NMENU_H

#include "ncurse-wrap/util_ntext.h"
#include <vector>
class NMenu
{
public:
    NMenu();
    NMenu(int width, int height);

    void addItem(NText const& newItem);
    void removeItemAt(int index);

    int getHeight() const;
    int getWidth() const;
    int getFocus() const;
    std::string getFocusCont() const;
    void removeAll();
    void setAttr(Attr const& attr);
    void setHighlight(Attr const& attr);
    void moveUp();
    void moveDown();
    void update();
    Printer toPrinter() const;
private:
    int width;
    int height;
    std::vector<NText> items;
    int focus;
    int frame;
    Attr normal;
    Attr highlight;
};

#endif // UTIL_NMENU_H
