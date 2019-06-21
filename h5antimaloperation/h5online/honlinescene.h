#ifndef HONLINESCENE_H
#define HONLINESCENE_H
/*
 * 五防系统场景基类，又是画面浏览scene类
 * 操作票scene,模板票编辑secne的基类
*/
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
class HIconLineItem;
class HIconRectItem;
class HIconEllipseItem;
class HIconCircleItem;
class HIconPolygonItem;
class HIconPolylineItem;
class HIconArcItem;
class HIconPieItem;
class HIconTextItem;
class HIconComplexItem;
class HIconSelectionItem;
class HIconGraphicsItem;
class HIconItemGroup;
class HBaseObj;
class HWfSystemMgr;
class HGraph;
class HGraphFrame;
class HGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    HGraphicsScene(HGraphFrame* parent = 0);
public:
    void setItemCursor(QGraphicsSceneMouseEvent *mouseEvent);
    void setItemProperty(QGraphicsItem* item);
    void setGraph(HGraph* graph);
public:
    virtual void openGraphicsSceneItems();
    virtual void delGraphicsSceneItems();
    virtual void addGraphicsIconItem(HBaseObj* pObj,bool del = false);//obj->item
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent);
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *contextMenuEvent);
    virtual void drawBackground(QPainter *painter, const QRectF &rect);
signals:
    void itemInserted(int);
    void mousePosChanged(QPointF logPos);

public:
    HGraph* m_pGraph;
    HGraphFrame* m_pOnlineWindow;
public:
    HIconLineItem* line;
    HIconRectItem* rectangle;
    HIconEllipseItem* ellipse;
    HIconCircleItem* circle;
    HIconPolygonItem* polygon;
    HIconPolylineItem* polyline;
    HIconArcItem* arc;
    HIconPieItem* pie;
    HIconTextItem* text;
    HIconSelectionItem* select;
    HIconItemGroup* group;
    HIconComplexItem* complex;

public:
    QList<HIconGraphicsItem*> dragMoveItems;
};

#endif // HONLINESCENE_H
