%{CurrentProject:Path} QT += core \
      multimedia
QT -= gui

CONFIG += c++11

TARGET = Myplayer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    nccontroller.cpp \
    ncurse-wrap/ncurses_wrapper.cpp \
    ncurse-wrap/util_window.cpp \
    user-interfaces/menu_win.cpp \
    user-interfaces/playing-win/playing_win.cpp \
    ncurse-wrap/util_ntext.cpp \
    ncurse-wrap/util_nborder.cpp \
    ncurse-wrap/util_nmenu.cpp \
    resources.cpp \
    user-interfaces/setting_win.cpp \
    ncurse-wrap/util_dialog.cpp \
    database/translator.cpp \
    ncurse-wrap/util_multitext.cpp \
    user-interfaces/songlist-win/dir_win.cpp \
    user-interfaces/playing-win/playlist_win.cpp \
    user-interfaces/songlist-win/listedit_win.cpp \
    user-interfaces/songlist-win/listname_win.cpp \
    user-interfaces/songlist-win/listsongs_win.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    nccontroller.h \
    ncurse-wrap/exceptions.h \
    ncurse-wrap/ncurses_wrapper.h \
    ncurse-wrap/util_window.h \
    user-interfaces/menu_win.h \
    user-interfaces/playing-win/playing_win.h \
    ncurse-wrap/util_position.h \
    ncurse-wrap/util_ntext.h \
    ncurse-wrap/util_nborder.h \
    ncurse-wrap/util_nmenu.h \
    ncurse-wrap/util_nblock.h \
    resources.h \
    user-interfaces/setting_win.h \
    ncurse-wrap/util_dialog.h \
    database/translator.h \
    ncurse-wrap/util_multitext.h \
    user-interfaces/songlist-win/dir_win.h \
    user-interfaces/playing-win/playlist_win.h \
    user-interfaces/songlist-win/listedit_win.h \
    user-interfaces/songlist-win/listname_win.h \
    user-interfaces/songlist-win/listsongs_win.h

LIBS += -lncursesw
