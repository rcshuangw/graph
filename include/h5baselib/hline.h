#ifndef HLINE_H
#define HLINE_H
/*
obj都是继承HBaseObj 都是被其他类继承
*/
#include "hlineobj.h"
///////////////////////////////////////////HRectangleObj///////////////////////////////////////////
class H5BASELIB_EXPORT HLine : public HLineObj
{
public:
	HLine();
	virtual ~HLine();

	//二进制读写
	virtual void readData(QDataStream* data);
	virtual void writeData(QDataStream* data);

	//xml文件读写
	virtual void readXml(QDomElement* data);
	virtual void writeXml(QDomElement* data);

	virtual QString tagName();

	//拷贝克隆
	virtual void copyTo(HBaseObj* obj);
	virtual void clone(HBaseObj* obj);

///////////////////////////////////////////////////////操作属性/////////////////////////////
//改变大小
	virtual void resize(double w, double h, bool scale);

public:
	virtual bool setPointList(QPolygonF& list, qint8 flag = 1);
	virtual QPolygonF getPointList(qint8 flag = 0);
public:
	virtual QRectF boundingRect(qint8 flag = 0);
	virtual QPainterPath shape(qint8 flag = 0);
	virtual void paint(QPainter* painter);

protected:
	QPointF ptHeadPoint;
	QPointF ptTailPoint;
};

#endif // HLINEOBJ_H
#pragma once
