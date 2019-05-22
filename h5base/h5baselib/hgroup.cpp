#include "hgroup.h"
HGroup::HGroup()
{
    m_eDrawShape = Group;
}
HGroup::~HGroup()
{
	clear();
}

void HGroup::move(double dx, double dy, bool scale)
{
	HContainerObj::move(dx, dy, scale);
}

void HGroup::moveBy(double dx, double dy, bool scale)
{
	HContainerObj::moveBy(dx, dy, scale);
}

HPointFList HGroup::getPointList(qint8 flag /* = 0 */)
{
	QPointF po(-m_width / 2, -m_height / 2);
	QRectF rectF(po, QSize(m_width, m_height));
    HPointFList list;
	list.append(rectF.topLeft());
	list.append(rectF.topRight());
	list.append(rectF.bottomRight());
	list.append(rectF.bottomLeft());
	maps(list, flag);
	return list;
}

QRectF HGroup::boundingRect(qint8 flag)
{
    return getPointList(flag).boundingRect();
}

QPainterPath HGroup::shape(qint8 flag)
{
	QPainterPath path;
    path.addPolygon(getPointList(0));
	return path;
}

void HGroup::RePos()
{
    QRectF rectF = boundingRect(1);
    QPointF pt = rectF.center();
    setOX(pt.x());
    setOY(pt.y());
    m_width = rectF.width();
    m_height = rectF.height();
    rotate(0);
    turn(false,false);
}

void HGroup::paint(QPainter* painter)
{
    if (!painter)
        return;
    painter->save();
    HShapeObj::setPainter(painter);

    //先要根据zvalue
    for (int i = 0; i < getObjList().count(); i++)
    {
        HBaseObj* pObj = (HBaseObj*)(getObjList().at(i));
        if (pObj)
        {
            pObj->paint(painter);
        }
    }
    painter->restore();
}
