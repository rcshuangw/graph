#include "hclock.h"
#include <QPaintEvent>
#include <QTime>
#include <QPainter>
#include <QTimer>
HClock::HClock(QWidget *parent, Qt::WindowFlags f):QLabel(parent,f)
{
    m_image[0].load(":/images/color0.bmp","BMP");
    m_image[1].load(":/images/color1.bmp","BMP");
    m_image[2].load(":/images/color2.bmp","BMP");
    m_image[3].load(":/images/color3.bmp","BMP");
    m_image[4].load(":/images/color4.bmp","BMP");
    m_image[5].load(":/images/color5.bmp","BMP");
    m_image[6].load(":/images/color6.bmp","BMP");
    m_image[7].load(":/images/color7.bmp","BMP");
    m_image[8].load(":/images/color8.bmp","BMP");
    m_image[9].load(":/images/color9.bmp","BMP");
    m_image[10].load(":/images/colorblack.bmp","BMP");
    m_image[11].load(":/images/colorline.bmp","BMP");
    m_image[12].load(":/images/colorpoint.bmp","BMP");
    m_pTimer = new QTimer;
    connect(m_pTimer,SIGNAL(timeout()),this,SLOT(update()));
}

HClock::~HClock()
{
    if(m_pTimer)
    {
        m_pTimer->stop();
        delete m_pTimer;
    }
}

void HClock::init()
{
    m_nWidth = width()/8;
    m_nHeight = height();
    m_nBitmapWidth = m_image[0].width();
    m_nBitmapHeight = m_image[0].height();
    m_pTimer->start(1000);
}

void HClock::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QTime time = QTime::currentTime();
    int Hour = time.hour();
    int nHour1 = Hour/10;
    int nHour2 = Hour%10;
    painter.drawImage(QRect(0,0,m_nWidth,m_nHeight),m_image[nHour1]);
    painter.drawImage(QRect(m_nWidth,0,m_nWidth,m_nHeight),m_image[nHour2]);

    //:
    painter.drawImage(QRect(m_nWidth*2,0,m_nWidth,m_nHeight),m_image[12]);

    //分钟
    int Minute = time.minute();
    int Minute1 = Minute/10;
    int Minute2 = Minute%10;
    painter.drawImage(QRect(m_nWidth*3,0,m_nWidth,m_nHeight),m_image[Minute1]);
    painter.drawImage(QRect(m_nWidth*4,0,m_nWidth,m_nHeight),m_image[Minute2]);

    //:
    painter.drawImage(QRect(m_nWidth*5,0,m_nWidth,m_nHeight),m_image[12]);

    //秒
    int Second = time.second();
    int Second1 = Second/10;
    int Second2 = Second%10;
    painter.drawImage(QRect(m_nWidth*6,0,m_nWidth,m_nHeight),m_image[Second1]);
    painter.drawImage(QRect(m_nWidth*7,0,m_nWidth,m_nHeight),m_image[Second2]);
}
