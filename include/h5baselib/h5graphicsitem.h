#ifndef H5GRAPHICSITEM_H
#define H5GRAPHICSITEM_H
#include <QGraphicsObject>
#include "h5baselibexport.h"
class HBaseObj;
class H5BASELIB_EXPORT H5GraphicsItem : public QGraphicsObject
{
	Q_OBJECT
public:
    H5GraphicsItem(HBaseObj* obj,QGraphicsItem* parent = 0);
    virtual ~H5GraphicsItem();
public:
    virtual QRectF boundingRect() const;
    virtual bool contains(const QPointF &point) const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    virtual QPainterPath shape() const;
    virtual int type() const;

public:
    void setBaseObj(HBaseObj* obj) {m_pBaseObj = obj;}
    HBaseObj* baseObj() {return m_pBaseObj;}

protected:
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

signals:
    void objSelectChanged(HBaseObj* obj,bool isSelected);
    void recalcSelect();

private:
    HBaseObj* m_pBaseObj;
};

#endif // H5ICONITEM_H
