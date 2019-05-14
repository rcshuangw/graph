﻿#include "htempcontainer.h"
HTempContainer::HTempContainer()
{
    setShapeType(TempContainer);
}
HTempContainer::~HTempContainer()
{
	clear();
}

void HTempContainer::move(qreal dx, qreal dy, bool scale)
{
	HContainerObj::move(dx, dy, scale);
}

void HTempContainer::moveBy(qreal dx, qreal dy, bool scale)
{
	HContainerObj::moveBy(dx, dy, scale);
}

HPointFList HTempContainer::getPointList(qint8 flag /* = 0 */)
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

QRectF HTempContainer::boundingRect(qint8 flag)
{
	QPointF po(-m_width / 2, -m_height / 2);
	QRectF rectF(po, QSize(m_width, m_height));
	rectF.adjust(-5, -5, 5, 5);
	return rectF;
}

QPainterPath HTempContainer::shape(qint8 flag)
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

void HTempContainer::rePos()
{
    QRectF rectF(0,0,0,0);
    int count = m_pObjList.size();
    if(count < 2) return;
    for (int i = 0; i < count; i++)
    {
        HBaseObj* pObj = m_pObjList.at(i);
        if (!pObj || pObj->isDeleted())
            continue;
        rectF = rectF.united(pObj->getPointList(1).boundingRect().normalized());
    }

    QPointF pt = rectF.center();
    setOX(pt.x());
    setOY(pt.y());
    m_width = rectF.width();
    m_height = rectF.height();
    rotate(0);
    turn(false,false);
}

void HTempContainer::paint(QPainter* painter)
{

}
