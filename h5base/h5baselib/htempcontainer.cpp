﻿#include "htempcontainer.h"
HTempContainer::HTempContainer()
{

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

HPointsList HTempContainer::getPointList(qint8 flag /* = 0 */)
{
	QPointF po(-m_width / 2, -m_height / 2);
	QRectF rectF(po, QSize(m_width, m_height));
	HPointsList list;
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