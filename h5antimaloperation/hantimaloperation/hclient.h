#ifndef HCLIENT_H
#define HCLIENT_H
#include "h5mainwindowexport.h"
#include <QMdiArea>

class H5MAINWINDOW_EXPORT HClient : public QMdiArea
{
    Q_OBJECT
public:
    explicit HClient(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // HCLIENT_H
