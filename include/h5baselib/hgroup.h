#ifndef HGROUP_H
#define HGROUP_H
#include "hcontainerobj.h"
class HTempContainer;
/*

*/
class H5BASELIB_EXPORT HGroup : public HContainerObj
{
	Q_OBJECT
public:
    HGroup();
    virtual ~HGroup();
public:
    void makeTempContainer(HTempContainer* tc);
	void move(double dx, double dy, bool bscale = false);
	void moveBy(double dx, double dy, bool bscale = false);
public:
    virtual void RePos();
    virtual HPointFList getPointList(qint8 flag /* = 0 */);
	virtual void paint(QPainter* painter);
	virtual QRectF boundingRect(qint8 flag = 0);
	virtual QPainterPath shape(qint8 flag = 0);
};

#endif // HGROUP_H

