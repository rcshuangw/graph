#include "hgroup.h"
#include "htempcontainer.h"
HGroup::HGroup()
{
    m_eDrawShape = Group;
}
HGroup::~HGroup()
{
//	clear();
}

QString HGroup::tagName()
{
    return "Group";
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

void HGroup::makeTempContainer(HTempContainer* tc)
{
    QTransform trans;
    QPointF pt = pos(1);
    trans.translate(pt.x(),pt.y());
    if(isHorizonTurn())
        trans.scale(-1,1);
    if(isVerticalTurn())
        trans.scale(1,-1);
    trans.rotate(rotateAngle());
    trans.translate(-pt.x(),-pt.y());

    if(!tc) return;
    tc->m_width = m_width;
    tc->m_height = m_height;
    tc->setOX(getOX());
    tc->setOY(getOY());
    int sz = getObjList().size();
    for(int i = 0; i < sz;i++)
    {
        HBaseObj* pObj = getObjList().at(i);
        if(!pObj) continue;
        if(isHorizonTurn())
            pObj->turn(!pObj->isHorizonTurn(),pObj->isVerticalTurn());
        if(isVerticalTurn())
            pObj->turn(pObj->isHorizonTurn(),!pObj->isVerticalTurn());
        pObj->rotate(rotateAngle()*((isHorizonTurn()+isValidBkImagePath())==1?-1:1));
        QPointF objPt = pObj->pos(1);
        objPt = trans.map(objPt);
        pObj->move(objPt.x(),objPt.y());
        pObj->setParent(0);
        tc->getObjList().append(pObj);
    }
    getObjList().clear();
}
