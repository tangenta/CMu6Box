#ifndef SETTING_WIN_H
#define SETTING_WIN_H
#include "../ncurse-wrap/util_window.h"
#include <vector>
#include "../ncurse-wrap/util_multitext.h"
#include "../ncurse-wrap/util_dialog.h"
class SettingWin: public Window {
public:
    SettingWin(Resources* res);
    Window* handleInput(int ch) override;
    void update() override;
    void draw() override;
private:
    void validateSetting();
    std::vector<NText> labels;
    int focus;
    MultiText langBox;
    MultiText theme;
    bool aboutShow;
    Dialog aboutPage;
};

#endif // SETTING_WIN_H
