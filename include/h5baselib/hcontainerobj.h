#ifndef HCONTAINEROBJ_H
#define HCONTAINEROBJ_H
#include "hshapeobj.h"
/*
组合形状类：多个简单线条组成的复杂图符，多个复杂图符组成的图形画面等都属于此类
*/
class H5BASELIB_EXPORT HContainerObj : public HShapeObj
{
	Q_OBJECT
public:
	HContainerObj();
	virtual ~HContainerObj();

public:
	//二进制读写
	virtual void readData(int v,QDataStream* data);
	virtual void writeData(int v,QDataStream* data);

	//xml文件读写
	virtual void readXml(int v,QDomElement* data);
	virtual void writeXml(int v,QDomElement* data);

	virtual QString tagName();

	//拷贝克隆
	virtual void copyTo(HBaseObj* obj);
	virtual void clone(HBaseObj* obj);

	QVector<HBaseObj*>& getObjList();

public:
	//新建一个图元元素(按类型)
	HBaseObj* newObj(DrawShape nObjType);
    //HBaseObj* newObj(QString tagName);
public:
    bool objsTransform(double dx,double dy);
	///改变大小
	void resize(double w, double h, bool scale = false);
	void expand(double dx1, double dx2, double dy1, double dy2, qint8 flag = 0);

	void move(double dx, double dy, bool bscale = false);
    //void moveBy(double dx, double dy, bool bscale = false);
public:
    virtual QRectF objsRect(qint8 flag);
    virtual void rePos();
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
	void addObjList(QList<HBaseObj*> objs);
protected:
	QVector<HBaseObj*> m_pObjList;
};

#endif // HSIMPLEOBJ_H
#pragma once
