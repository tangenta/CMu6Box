#ifndef RESOURCES_H
#define RESOURCES_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "database/translator.h"
#include "./ncurse-wrap/ncurses_wrapper.h"

class Resources : public QObject
{
    Q_OBJECT
public:
    explicit Resources(QObject *parent = 0);
    void readSetting(QString filename);
    void writeSetting(QString filename);
    Color parseColor(QString const& colorStr);
    Color parseHighlight(QString const& colorStr);
    QMediaPlayer player;
    QMediaPlaylist playlist;
    QList<QMediaContent> contents;

    // setting
    Translator translator;
    QString themeColor;
signals:

public slots:
private:
};

#endif // RESOURCES_H
