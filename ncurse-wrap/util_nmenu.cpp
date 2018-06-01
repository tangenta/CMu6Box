#include "util_nmenu.h"

NMenu::NMenu(): width(0), height(0), focus(0), frame(0),
    highlight(Attr(Color(), Font({NF::Bold, NF::Reverse}))) {
}

NMenu::NMenu(int width, int height)
    : width(width), height(height), focus(0), frame(0),
    highlight(Attr(Color(), Font({NF::Bold, NF::Reverse}))) {
}

void NMenu::addItem(NText const& newItem) {
    focus = frame = 0;
    NText item(newItem);
    item.setWidth(width);
    items.push_back(item);
    items[0].setAttr(highlight);
}

void NMenu::removeItemAt(int index) {
    int itemSize = items.size();
    if (index < 0 || index >= itemSize) {
        throw FatalError("NMenu::removeItemAt()");
    }
    focus = frame = 0;
    items.erase(items.begin()+index);
}

void NMenu::removeAll() {
    items.clear();
    focus = frame = 0;
}

int NMenu::size() const {
    return items.size();
}

bool NMenu::isEmpty() const {
    return items.empty();
}

int NMenu::getHeight() const {
    return height;
}

int NMenu::getWidth() const {
    return width;
}

int NMenu::getFocus() const {
    return focus;
}

std::string NMenu::getFocusCont() const {
    if (items.empty()) return "";

    return items.at(focus).getContent();
}

void NMenu::setAttr(Attr const& attr) {
    normal = attr;
    for (auto& i: items) {
        i.setAttr(attr);
    }
}

void NMenu::setHighlight(const Attr& attr) {
    highlight = attr;
    if (!items.empty()) {
        items[focus].setAttr(highlight);
    }
}

void NMenu::moveUp() {
    if (items.empty()) return;
    items[focus].setBeginPoint(0);
    items[focus].setAttr(normal);
    if (focus == frame && focus != 0) {
        frame--;
    }
    focus = (focus == 0) ? focus : focus-1;
    items[focus].setAttr(highlight);
}

void NMenu::moveDown() {
    if (items.empty()) return;
    items[focus].setBeginPoint(0);
    items[focus].setAttr(normal);
    int maxFocus = items.size()-1;
    if (focus == frame+height-1 && focus != maxFocus) {
        frame++;
    }
    focus = (focus == maxFocus) ? maxFocus : focus+1;
    items[focus].setAttr(highlight);
}

void NMenu::update() {
    if (items.empty()) return;
    NText* objText = &items[focus];
    int contentLength = objText->getContent().size();
    if (contentLength-objText->getBeginPoint() <= width) {
        objText->setBeginPoint(0);
    } else {
        objText->setBeginPoint(objText->getBeginPoint()+1);
    }
}

Printer NMenu::toPrinter() const {
    int counter = height;
    Printer printer;
    for (auto i = items.begin()+frame; i != items.end(); ++i) {
        Printer subPrinter = i->toPrinter();
        printer.splice(printer.end(), subPrinter);
        if (--counter == 0) break;
        printer.back().bias = printer.back().bias + Bias(1,0);
    }
    return printer;
}
