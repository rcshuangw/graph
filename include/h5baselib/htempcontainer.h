#ifndef HTEMPCONTAINER_H
#define HTEMPCONTAINER_H
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
	void move(double dx, double dy, bool bscale = false);
	void moveBy(double dx, double dy, bool bscale = false);
public:
    virtual void rePos();
	virtual HPointFList getPointList(qint8 flag /* = 0 */);
    virtual void paint(QPainter* painter);
	virtual QRectF boundingRect(qint8 flag = 0);
	virtual QPainterPath shape(qint8 flag = 0);
};

#endif // HTEMPCONTAINER_H

