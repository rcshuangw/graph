#ifndef HGROUPOBJ_H
#define HGROUPOBJ_H
#include "hshapeobj.h"
/*
组合形状类：继承形状类，子类画面类、图元类等等
记录多个简单图元的组合的形状类
注意此类必须是图元组合形状的类
*/
class H5ICONLIB_EXPORT HGroupObj : public HShapeObj
{
	Q_OBJECT
public:
	HGroupObj();
	virtual ~HGroupObj();

public:
	//二进制读写
	virtual void readData(QDataStream* data);
	virtual void writeData(QDataStream* data);

	//xml文件读写
	virtual void readXml(QDomElement* data);
	virtual void writeXml(QDomElement* data);

	virtual QString TagName();

	//拷贝克隆
	virtual void copyTo(HBaseObj* obj);
	virtual void clone(HBaseObj* obj);

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

	QVector<HBaseObj*>& getObjList();
protected:
	QVector<HBaseObj*> m_pObjList;
};

#endif // HSIMPLEOBJ_H
#pragma once
