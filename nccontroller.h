#ifndef NCCONTROLLER_H
#define NCCONTROLLER_H

#include <QObject>

class NCController : public QObject
{
    Q_OBJECT
public:
    explicit NCController(QObject *parent = 0);

signals:

public slots:
};

#endif // NCCONTROLLER_H