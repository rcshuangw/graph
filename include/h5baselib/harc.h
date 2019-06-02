#ifndef HARC_H
#define HARC_H
#include "hline.h"
class H5BASELIB_EXPORT HArc : public HLine
{
public:
    HArc();

public:
    virtual void readData(int v,QDataStream* data);
    virtual void writeData(int v,QDataStream* data);

    virtual void readXml(int v,QDomElement* data);
    virtual void writeXml(int v,QDomElement* data);

    virtual QString TagName();
    virtual void copyTo(HBaseObj* obj);

public:
    void setStartAngle(int nAngle);
    int startAngle();
    void setSweepLength(int nLength);
    int sweepLength();

public:
    virtual QRectF boundingRect(qint8 flag = 0);
    virtual QPainterPath shape(qint8 flag = 0);
    virtual void paint(QPainter* painter);
private:
    //起始角度
    int m_nStartAngle;
    //逆时针旋转角度
    int m_nSweepLength;//角度
};
#endif // HARC_H
