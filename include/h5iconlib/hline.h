#ifndef HLINE_H
#define HLINE_H
/*
obj���Ǽ̳�HBaseObj ���Ǳ�������̳�
*/
#include "hlineobj.h"
///////////////////////////////////////////HRectangleObj///////////////////////////////////////////
class H5ICONLIB_EXPORT HLine : public HLineObj
{
public:
	HLine();
	virtual ~HLine();

	//�����ƶ�д
	virtual void readData(QDataStream* data);
	virtual void writeData(QDataStream* data);

	//xml�ļ���д
	virtual void readXml(QDomElement* data);
	virtual void writeXml(QDomElement* data);

	virtual QString TagName();

	//������¡
	virtual void copyTo(HBaseObj* obj);
	virtual void clone(HBaseObj* obj);

///////////////////////////////////////////////////////��������/////////////////////////////
//�ı��С
	virtual void resize(double w, double h, bool scale);

public:
	///��������
	virtual bool setPointList(QPolygonF& list, qint8 flag = 1);
	virtual QPolygonF getPointList(qint8 flag = 0) = 0;

public:
	virtual QRectF boundingRect(qint8 flag = 0);
	virtual QPainterPath shape(qint8 flag = 0);
	virtual void paint(QPainter* painter) = 0;

protected:
	QPointF ptHeadPoint;
	QPointF ptTailPoint;
};

#endif // HLINEOBJ_H
#pragma once
