#ifndef HCLOCK_H
#define HCLOCK_H
#include "h5mainwindowexport.h"
#include <QLabel>
#include <QImage>
class QPaintEvent;
class QTimer;
class H5MAINWINDOW_EXPORT HClock : public QLabel
{
public:
    HClock(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~HClock();
public:
    void init();
    virtual void paintEvent(QPaintEvent *);

private:
    QImage m_image[13];
    int m_nBitmapWidth;
    int m_nBitmapHeight;
    int m_nWidth;
    int m_nHeight;
    QTimer* m_pTimer;

};

#endif // HCLOCK_H
