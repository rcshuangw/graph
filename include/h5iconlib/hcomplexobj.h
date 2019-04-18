#ifndef HGROUPOBJ_H
#define HGROUPOBJ_H
#include "hshapeobj.h"
/*
�����״�ࣺ�����������ɵĸ���ͼ�����������ͼ����ɵ�ͼ�λ���ȶ����ڴ���
*/
class H5ICONLIB_EXPORT HComplexObj : public HShapeObj
{
	Q_OBJECT
public:
	HComplexObj();
	virtual ~HComplexObj();

public:
	//�����ƶ�д
	virtual void readData(int v,QDataStream* data);
	virtual void writeData(int v,QDataStream* data);

	//xml�ļ���д
	virtual void readXml(int v,QDomElement* data);
	virtual void writeXml(int v,QDomElement* data);

	virtual QString TagName();

	//������¡
	virtual void copyTo(HBaseObj* obj);
	virtual void clone(HBaseObj* obj);

	QVector<HBaseObj*>& getObjList();

public:
	//�½�һ��ͼԪԪ��(������)
	HBaseObj* newObj(DrawShape nObjType);
	HBaseObj* newObj(QString tagName);
public:
	///�ı��С
	void resize(double w, double h, bool scale = false);
	void expand(double dx1, double dx2, double dy1, double dy2, qint8 flag = 0);
	bool transform(double dx,double dy);
	void move(qreal dx, qreal dy, bool bscale = false);
	void moveBy(qreal dx, qreal dy, bool bscale = false);
public:
	virtual QRectF boundingRect(qint8 flag = 0);
	virtual QPainterPath shape(qint8 flag = 0);
public:
	//���objList�Ĳ��� �ο�QVector��ĺ���
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
