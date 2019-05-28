﻿#ifndef HPOLYLINE_H
#define HPOLYLINE_H
#include "hlineobj.h"
//折线
class H5BASELIB_EXPORT HPolyline : public HLineObj
{
public:
    HPolyline();
    virtual ~HPolyline();

    //二进制读写
    virtual void readData(int v,QDataStream* data);
    virtual void writeData(int v,QDataStream* data);

    //xml文件读写
    virtual void readXml(int v,QDomElement* dom);
    virtual void writeXml(int v,QDomElement* dom);

    virtual QString tagName();
    //拷贝克隆
    virtual void copyTo(HBaseObj* obj);

public:
    virtual bool setPointList(QPolygonF& list, qint8 flag = 1);
    virtual QPolygonF getPointList(qint8 flag = 0);

    virtual void resize(double w, double h, bool scale);
    virtual QRectF boundingRect(qint8 flag = 0);
    virtual QPainterPath shape(qint8 flag = 0);
    virtual void paint(QPainter* painter);

protected:
    HPointFList pylist;
};

#endif // HPOLYLINE_H
