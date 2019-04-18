#ifndef HGROUPOBJ_H
#define HGROUPOBJ_H
#include "hshapeobj.h"
/*
组合形状类：多个简单线条组成的复杂图符，多个复杂图符组成的图形画面等都属于此类
*/
class H5ICONLIB_EXPORT HComplexObj : public HShapeObj
{
	Q_OBJECT
public:
	HComplexObj();
	virtual ~HComplexObj();

public:
	//二进制读写
	virtual void readData(int v,QDataStream* data);
	virtual void writeData(int v,QDataStream* data);

	//xml文件读写
	virtual void readXml(int v,QDomElement* data);
	virtual void writeXml(int v,QDomElement* data);

	virtual QString TagName();

	//拷贝克隆
	virtual void copyTo(HBaseObj* obj);
	virtual void clone(HBaseObj* obj);

	QVector<HBaseObj*>& getObjList();

public:
	//新建一个图元元素(按类型)
	HBaseObj* newObj(DrawShape nObjType);
	HBaseObj* newObj(QString tagName);
public:
	///改变大小
	void resize(double w, double h, bool scale = false);
	void expand(double dx1, double dx2, double dy1, double dy2, qint8 flag = 0);
	bool transform(double dx,double dy);
	void move(qreal dx, qreal dy, bool bscale = false);
	void moveBy(qreal dx, qreal dy, bool bscale = false);
public:
	virtual QRectF boundingRect(qint8 flag = 0);
	virtual QPainterPath shape(qint8 flag = 0);
public:
	//针对objList的操作 参考QVector类的函数
	void clear();
	void addObj(HBaseObj* obj);
	void removeObj(HBaseObj* obj);
	bool contains(HBaseObj* obj);
	int size();
	HBaseObj* at(int index);

	
protected:
	QVector<HBaseObj*> m_pObjList;
};

#endif // HSIMPLEOBJ_H
#pragma once
