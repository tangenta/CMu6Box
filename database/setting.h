#ifndef SETTING_H
#define SETTING_H
#include "../ncurse-wrap/ncurses_wrapper.h"
#include <QJsonDocument>

class Setting {

public:
    enum Language { EN, CN };
    Setting();
    void openSetting();
    void saveCurrentSetting();
    void loadLanguage(Language lan);
    Language getLanguage();
    Attr getTheme();
    std::string tr(std::string const&);
    std::string tr(const char*);
private:
    Language language;
    Attr theme;
    QJsonDocument langDoc;
};

#endif // SETTING_H
