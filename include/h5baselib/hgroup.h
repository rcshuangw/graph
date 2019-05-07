#ifndef HGROUP_H
#define HGROUP_H
#include "hcontainerobj.h"
/*

*/
class H5BASELIB_EXPORT HGroup : public HContainerObj
{
	Q_OBJECT
public:
    HGroup();
    virtual ~HGroup();
public:
	void move(qreal dx, qreal dy, bool bscale = false);
	void moveBy(qreal dx, qreal dy, bool bscale = false);
public:
    virtual void RePos();
    virtual HPointFList getPointList(qint8 flag /* = 0 */);
	virtual void paint(QPainter* painter);
	virtual QRectF boundingRect(qint8 flag = 0);
	virtual QPainterPath shape(qint8 flag = 0);
};

#endif // HGROUP_H

