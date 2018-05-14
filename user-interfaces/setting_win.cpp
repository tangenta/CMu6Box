#include "setting_win.h"
#include "menu_win.h"
#include "../resources.h"

SettingWin::SettingWin(Resources* res): Window(res) {
    auto& tr = resource->tf;
    languageLabel = NText(tr["language"]);
    themeLabel = NText(tr["theme"]);
    aboutLabel = NText(tr["about"]);
}

Window* SettingWin::handleInput(int ch) {
    if (ch == NK::Esc) {
        return new MenuWin(resource);
    }
    return this;
}

void SettingWin::update() {

}

void SettingWin::draw() {
//    Window::draw(NText(resource->tf["language"]), Position(4, 15));
    Window::draw(languageLabel, Position(4, 15));
    Window::draw(themeLabel, Position(6, 15));
    Window::draw(aboutLabel, Position(8, 15));
}
