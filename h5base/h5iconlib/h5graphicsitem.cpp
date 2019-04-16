#include "h5graphicsitem.h"
#include "hbaseobj.h"
H5GraphicsItem::H5GraphicsItem(HBaseObj* obj,QGraphicsItem* parent):m_pBaseObj(obj),QGraphicsObject(parent)
{
    if(m_pBaseObj)
    {
        //setPos(m_pBaseObj->pos());
        setZValue(m_pBaseObj->zValue());
        m_pBaseObj->setIconGraphicsItem(this);
    }
    setFlag(QGraphicsItem::ItemIsMovable,true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges,true);
}

H5GraphicsItem::~H5GraphicsItem()
{

}

QRectF H5GraphicsItem::boundingRect() const
{
    if(m_pBaseObj && !m_pBaseObj->isDeleted() && m_pBaseObj->isVisible())
        return m_pBaseObj->boundingRect().adjusted(-5,-5,5,5);
    return QRectF();
}

void H5GraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!isVisible())
        return;
    if(m_pBaseObj && !m_pBaseObj->isDeleted() && m_pBaseObj->isVisible())
        return m_pBaseObj->paint(painter);
}


bool H5GraphicsItem::contains(const QPointF &point) const
{
    return false;
}

QPainterPath H5GraphicsItem::shape() const
{
    if(m_pBaseObj && !m_pBaseObj->isDeleted() && m_pBaseObj->isVisible())
        return m_pBaseObj->shape();
    return QPainterPath();
}

int H5GraphicsItem::type() const
{
    return QGraphicsItem::type();
}

QVariant H5GraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(m_pBaseObj && !m_pBaseObj->isDeleted())
    {
        if(change == QGraphicsItem::ItemSelectedChange && m_pBaseObj->isVisible())
            emit objSelectChanged(m_pBaseObj,value.toBool());
        else if(change == QGraphicsItem::ItemPositionHasChanged)
        {
            QPointF pt = this->pos();
            m_pBaseObj->move(pt.x(),pt.y());
            emit recalcSelect();
        }
    }
    return QGraphicsItem::itemChange(change,value);
}

