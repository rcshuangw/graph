#ifndef HGROUPOBJ_H
#define HGROUPOBJ_H
#include "hshapeobj.h"
/*
�����״�ࣺ�̳���״�࣬���໭���ࡢͼԪ��ȵ�
��¼�����ͼԪ����ϵ���״��
ע����������ͼԪ�����״����
*/
class H5ICONLIB_EXPORT HGroupObj : public HShapeObj
{
	Q_OBJECT
public:
	HGroupObj();
	virtual ~HGroupObj();

public:
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

	QVector<HBaseObj*>& getObjList();
protected:
	QVector<HBaseObj*> m_pObjList;
};

#endif // HSIMPLEOBJ_H
#pragma once
