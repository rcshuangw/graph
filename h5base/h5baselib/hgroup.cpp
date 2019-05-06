#include "hgroup.h"
HGroup::HGroup()
{

}
HGroup::~HGroup()
{
	clear();
}

void HGroup::move(qreal dx, qreal dy, bool scale)
{
	HContainerObj::move(dx, dy, scale);
}

void HGroup::moveBy(qreal dx, qreal dy, bool scale)
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
	QPointF po(-m_width / 2, -m_height / 2);
	QRectF rectF(po, QSize(m_width, m_height));
	rectF.adjust(-5, -5, 5, 5);
	return rectF;
}

QPainterPath HGroup::shape(qint8 flag)
{
	QPainterPath path;
	int count = m_pObjList.size();
	for (int i = 0; i < count; i++)
	{
		HBaseObj* pObj = m_pObjList.at(i);
		if (!pObj || pObj->isDeleted())
			continue;
		path.addPath(pObj->shape());
	}
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

