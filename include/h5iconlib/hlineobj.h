#ifndef HLINEOBJ_H
#define HLINEOBJ_H
/*
obj���Ǽ̳�HBaseObj ���Ǳ�������̳�
*/
#include "hshapeobj.h"
///////////////////////////////////////////HRectangleObj///////////////////////////////////////////
class H5ICONLIB_EXPORT HLineObj : public HBaseObj
{
public:
	HLineObj();
	virtual ~HLineObj();

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
	void setStartArrowType(quint8 start);
	quint8 getStartArrowType();

	void setEndArrowType(quint8 end);
	quint8 getEndArrowType();

	void setArrowWidth(quint8 width);
	quint8 getArrowWidth();

	void setArrowHeight(quint8 height);
	quint8 getArrowHeight();

	virtual QPainterPath getArrowPath(HPointsList& points,bool head);
	virtual void getBoundingRect(HPointsList& points,QPointF &ptStart,QPointF& ptEnd,double width);

	///////////////////////////////////////////////////////��������/////////////////////////////
	//�ı��С
	virtual void resize(double w, double h, bool scale);
	virtual void move(qreal dx, qreal dy, bool bscale = false);
	virtual void moveBy(qreal dx, qreal dy, bool bscale = false);

public:
	///��������
	virtual bool setPointList(QPolygonF& list, qint8 flag = 1);
	//��������ľ��α߿�
public:
	//virtual QRectF boundingRect(qint8 flag = 0);
	//virtual QPainterPath shape(qint8 flag = 0) = 0;
	//virtual void paint(QPainter* painter) = 0;
	//virtual bool contains(const QPointF &point) const;
protected:
	quint8 m_nArrowStart;//��ͷ������
	quint8 m_nArrowEnd;//��β������
	quint8 m_nArrowWidth;
	quint8 m_nArrowHeight;
};

#endif // HLINEOBJ_H
