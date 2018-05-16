#ifndef RESOURCES_H
#define RESOURCES_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class Resources : public QObject
{
    Q_OBJECT
public:
    explicit Resources(QObject *parent = 0);
    QMediaPlayer player;
    QMediaPlaylist playlist;
    QList<QMediaContent> contents;
signals:

public slots:
};

#endif // RESOURCES_H
