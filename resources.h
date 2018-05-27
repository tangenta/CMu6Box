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

    // play
    QMediaPlayer player;
    QMediaPlaylist playlist;
    QList<QMediaContent> playingList;


    // songlist
    void readSonglist(QString filename);
    void writeSonglist(QString filename);

    QList<QString> songlistNames;
    QList<QStringList> songlists;


    // setting
    void readSetting(QString filename);
    void writeSetting(QString filename);
    Color parseColor(QString const& colorStr);
    Color parseHighlight(QString const& colorStr);

    Translator translator;
    QString themeColor;
signals:

public slots:
private:
};

#endif // RESOURCES_H
