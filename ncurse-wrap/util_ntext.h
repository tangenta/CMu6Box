#ifndef UTIL_NTEXT_H
#define UTIL_NTEXT_H

#include <string>
#include "ncurse-wrap/ncurses_wrapper.h"
class NText
{
public:
    NText();
    NText(std::string const& content, Attr const& attribute = Attr());
    std::string getContent() const;
    int getBeginPoint() const;
    int getWidth() const;
    int getHeight() const;
    void setWidth(int wid);
    void setAttr(Attr const& attr);
    void setBeginPoint(int beginPoint);
    Printer toPrinter() const;
private:
    std::string content;
    Attr attribute;
    int beginPoint;
    int width;
};

#endif // UTIL_NTEXT_H
