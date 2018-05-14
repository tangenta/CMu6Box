#ifndef RESOURCES_H
#define RESOURCES_H

#include <QObject>
#include <QMediaPlayer>
#include "database/setting.h"

class Resources : public QObject
{
    Q_OBJECT
public:
    explicit Resources(QObject *parent = 0);
    QMediaPlayer player;
    Setting setting;
signals:

public slots:
};

#endif // RESOURCES_H
