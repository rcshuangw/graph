#include "htempcontainer.h"
#include "hgroup.h"
HTempContainer::HTempContainer()
{
    setShapeType(TempContainer);
}
HTempContainer::~HTempContainer()
{
//	clear();
}

void HTempContainer::move(double dx, double dy, bool scale)
{
	HContainerObj::move(dx, dy, scale);
}

void HTempContainer::moveBy(double dx, double dy, bool scale)
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
    if(0 == flag)
        return rectF;
    rectF.translate(getOX(),getOY());
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
    QRectF rectF = objsRect(1);

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

void HTempContainer::makeGroup(HGroup *group)
{
    if(!group)
        return;
    group->m_width = m_width;
    group->m_height = m_height;
    group->setOX(getOX());
    group->setOY(getOY());
    int sz = getObjList().size();
    for(int i = 0; i < sz;i++)
    {
        HBaseObj* pObj = getObjList().at(i);
        if(!pObj) continue;
        pObj->resetParent(group);
    }
    getObjList().clear();
}
