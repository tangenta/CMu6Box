QT += core \
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
    user-interfaces/playing_win.cpp \
    ncurse-wrap/util_rollingtext.cpp \
    ncurse-wrap/util_statictext.cpp \
    ncurse-wrap/util_border.cpp \
    ncurse-wrap/util_menu.cpp \
    user-interfaces/testing_win.cpp \
    ncurse-wrap/util_ntext.cpp \
    ncurse-wrap/util_nborder.cpp \
    ncurse-wrap/util_nmenu.cpp \
    user-interfaces/test2_win.cpp \
    resources.cpp

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
    user-interfaces/playing_win.h \
    ncurse-wrap/util_text.h \
    ncurse-wrap/util_position.h \
    ncurse-wrap/util_statictext.h \
    ncurse-wrap/util_rollingtext.h \
    ncurse-wrap/util_border.h \
    ncurse-wrap/util_menu.h \
    ncurse-wrap/block.h \
    user-interfaces/testing_win.h \
    ncurse-wrap/util_ntext.h \
    ncurse-wrap/util_nborder.h \
    ncurse-wrap/util_nmenu.h \
    user-interfaces/test2_win.h \
    ncurse-wrap/util_nblock.h \
    resources.h

LIBS += -lncursesw
