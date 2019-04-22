#ifndef HTEMPGROUP_H
#define HTEMPGROUP_H
#include "hcontainerobj.h"
/*

*/
class H5BASELIB_EXPORT HTempContainer : public HContainerObj
{
	Q_OBJECT
public:
	HTempContainer();
	virtual ~HTempContainer();
public:
	void move(qreal dx, qreal dy, bool bscale = false);
	void moveBy(qreal dx, qreal dy, bool bscale = false);
public:
	virtual HPointsList getPointList(qint8 flag /* = 0 */);
	virtual void paint(QPainter* painter);
	virtual QRectF boundingRect(qint8 flag = 0);
	virtual QPainterPath shape(qint8 flag = 0);
};

#endif // HSIMPLEOBJ_H
#pragma once
#pragma once
