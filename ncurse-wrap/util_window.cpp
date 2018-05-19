#include "util_window.h"
#include "ncurses_wrapper.h"
#include "exceptions.h"
#include <algorithm>
#include <climits>
#include <initializer_list>
#include "../resources.h"
#include <utility>

Window::Window(Resources* res): QObject() {
    wp = Ncurses::newwin_s(0, 0, 0, 0);
    resource = res;
    setBackground(res->themeColor);
}

Window::~Window() {
    Ncurses::delwin_s(wp);
}

Window::Window(int rows, int cols, int org_y, int org_x) {
    wp = Ncurses::newwin_s(rows, cols, org_y, org_x);
}

int Window::getRows() const {
    return Ncurses::getmaxy_s(wp);
}

int Window::getCols() const {
    return Ncurses::getmaxx_s(wp);
}

NWINDOW* Window::getNWindow() const {
    return wp;
}

void Window::clearScreen() {
    Ncurses::werase_s(this->wp);
}

void Window::setBackground(QString const& colorStr) {
    Color color = resource->parseColor(colorStr);
    Ncurses::wbkgdset_s(wp, color.getPair());
}

std::string Window::tl(const char *str) {
    return resource->translator(str);
}

std::string Window::tl(const std::string &str) {
    return resource->translator(str);
}
