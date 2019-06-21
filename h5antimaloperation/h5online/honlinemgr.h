#ifndef HONLINEMGR_H
#define HONLINEMGR_H

#include <QObject>

class HOnlineMgr : public QObject
{
    Q_OBJECT
public:
    explicit HOnlineMgr(QObject *parent = nullptr);

signals:

public slots:
};

#endif // HONLINEMGR_H
