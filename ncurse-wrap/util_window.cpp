#include "util_window.h"
#include "ncurses_wrapper.h"
#include "exceptions.h"
#include <algorithm>
#include <climits>
#include <initializer_list>
#include "../resources.h"
#include <utility>
using SCMap = std::pair<std::vector<QString>, std::vector<Color>>;

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

    static SCMap scmap = std::make_pair<std::vector<QString>, std::vector<Color>>(
    {"Black", "Red", "Green", "Yellow", "Blue", "Magenta", "Cyan", "White"},
    {Color(NC::Black, NC::Black),
     Color(NC::Red, NC::Red),
     Color(NC::Green, NC::Green),
     Color(NC::Yellow, NC::Yellow),
     Color(NC::Blue, NC::Blue),
     Color(NC::Magenta, NC::Magenta),
     Color(NC::Cyan, NC::Cyan),
     Color(NC::White, NC::White)});
    auto& keys = scmap.first;
    auto& values = scmap.second;
    if (keys.size() != values.size()) {
        throw FatalError("Resources::parseColor()");
    }
    auto iter = std::find(keys.begin(), keys.end(), colorStr);
    if (iter == keys.end()) {
        throw FatalError("Resources::parseColor()");
    }
    auto diff = iter-keys.begin();
    Color color = *(values.begin()+diff);

    Ncurses::wbkgdset_s(wp, color.getPair());
    Ncurses::wrefresh_s(wp);
}

std::string Window::tl(const char *str) {
    return resource->translator(str);
}

std::string Window::tl(const std::string &str) {
    return resource->translator(str);
}
