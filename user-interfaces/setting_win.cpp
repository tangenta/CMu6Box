#include "setting_win.h"
#include "menu_win.h"
#include "../resources.h"

SettingWin::SettingWin(Resources* res): Window(res) {
    auto& s = resource->setting;
    languageLabel = NText(s.tr("language"));
    themeLabel = NText(s.tr("theme"));
    aboutLabel = NText(s.tr("about"));
}

Window* SettingWin::handleInput(int ch) {
    if (ch == NK::Esc) {
        resource->setting.saveCurrentSetting();
        return new MenuWin(resource);
    }
    return this;
}

void SettingWin::update() {

}

void SettingWin::draw() {
    Window::draw(languageLabel, Position(4, 15));
    Window::draw(themeLabel, Position(6, 15));
    Window::draw(aboutLabel, Position(8, 15));
}
