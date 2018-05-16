#include "util_multitext.h"

MultiText::MultiText() : index(0) {}

MultiText::MultiText(const std::vector<std::string> &lists, Attr const& attr)
    : index(0), attr(attr), contents(lists) {}

MultiText::MultiText(const std::initializer_list<std::string> &lists,
                     Attr const& attr): index(0), attr(attr) {
    for (auto &i: lists) contents.push_back(i);
}

Printer MultiText::toPrinter() const {
    if (contents.empty()) return Printer();
    return Printer(1, Printee(contents[index], attr));
}

void MultiText::next() {
    int size = contents.size();
    if (size == 0) return;
    if (index != size-1) index++;
}

void MultiText::prev() {
    if (index != 0) index--;
}

int MultiText::getHeigth() const {
    return 1;
}

int MultiText::getWidth() const {
    // pick the maximum
    int wid = 0;
    for (auto &i: contents) {
        int isize = i.size();
        wid = (wid < isize) ? isize : wid;
    }
    return wid;
}

std::string MultiText::text() const {
    if (contents.empty()) return std::string();
    return contents[index];
}
