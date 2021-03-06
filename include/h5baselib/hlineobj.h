﻿#ifndef HLINEOBJ_H
#define HLINEOBJ_H
/*
obj都是继承HBaseObj 都是被其他类继承
*/
#include "hshapeobj.h"
#include "h5baselibexport.h"
///////////////////////////////////////////HRectangleObj///////////////////////////////////////////
class H5BASELIB_EXPORT HLineObj : public HBaseObj
{
public:
	HLineObj();
	virtual ~HLineObj();

	//二进制读写
    virtual void readData(int v,QDataStream* data);
    virtual void writeData(int v,QDataStream* data);

	//xml文件读写
    virtual void readXml(int v,QDomElement* data);
    virtual void writeXml(int v,QDomElement* data);

	virtual QString tagName();

	//拷贝克隆
	virtual void copyTo(HBaseObj* obj);
public:
	void setStartArrowType(quint8 start);
	quint8 getStartArrowType();

	void setEndArrowType(quint8 end);
	quint8 getEndArrowType();

	void setArrowWidth(quint8 width);
	quint8 getArrowWidth();

	void setArrowHeight(quint8 height);
	quint8 getArrowHeight();

	virtual QPainterPath getArrowPath(HPointFList& points,bool head);
	virtual void getBoundingRect(HPointFList& points,QPointF &ptStart,QPointF& ptEnd,double width);

	///////////////////////////////////////////////////////操作属性/////////////////////////////
	//改变大小
	virtual void resize(double w, double h, bool scale);
	virtual void move(double dx, double dy, bool bscale = false);
	virtual void moveBy(double dx, double dy, bool bscale = false);

public:
	///绝对坐标
	virtual bool setPointList(QPolygonF& list, qint8 flag = 1);
	//获得线条的矩形边框
public:
	//virtual QRectF boundingRect(qint8 flag = 0);
	//virtual QPainterPath shape(qint8 flag = 0) = 0;
	//virtual void paint(QPainter* painter) = 0;
	//virtual bool contains(const QPointF &point) const;
protected:
	quint8 m_nArrowStart;//箭头的类型
	quint8 m_nArrowEnd;//箭尾的类型
	quint8 m_nArrowWidth;
	quint8 m_nArrowHeight;
};

#endif // HLINEOBJ_H
