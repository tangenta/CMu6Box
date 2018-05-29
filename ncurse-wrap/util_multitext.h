#ifndef UTIL_MULTITEXT_H
#define UTIL_MULTITEXT_H
#include <initializer_list>
#include <string>
#include <vector>
#include "ncurses_wrapper.h"
/*
 * In MultiText, several strings share the same space.
 *  They can be interchanged with next() and prev().
 */
class MultiText
{
public:
    MultiText();
    MultiText(std::vector<std::string> const& lists, Attr const& attr = Attr());
    MultiText(std::initializer_list<std::string> const& lists, Attr const& attr = Attr());
    Printer toPrinter() const;
    void next();
    void prev();
    void setIndex(int i);
    void setAttr(Attr const& aAttr);
    int getHeigth() const;
    int getWidth() const;
    std::string text() const;   // return current text
private:
    int index;
    Attr attr;
    std::vector<std::string> contents;
};

#endif // UTIL_MULTITEXT_H
