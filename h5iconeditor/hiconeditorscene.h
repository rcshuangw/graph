#ifndef HICONSCENE_H
#define HICONSCENE_H

#include <QGraphicsScene>
class HIconEditorFrame;
class HIconEditorMgr;
class HBaseObj;
class HIconEditorScene : public QGraphicsScene
{
    Q_OBJECT
public:
    HIconEditorScene(HIconEditorMgr* iconMgr);

public:
    void drawPath(const QList<Path>& pathList);
    void endDraw();

public:
    bool getItemAt(const QPointF& pos);
    void setItemProperty(QGraphicsItem *item);
    void setItemCursor(QGraphicsSceneMouseEvent *mouseEvent);
    HIconGraphicsItem* addItemByIconObj(HBaseObj* pObj);
    void refreshItemByPatternId(int nPatternId);
    void clearItemByPatternId(int nPatternId);
    void setItemVisible(int nPatternId);
    void calcSelectedItem(const QRectF& rectF);
    int pointInRect(QPointF& pointF);
    void prepareMoveItem(QGraphicsSceneMouseEvent *mouseEvent);
    void prepareRezieItem(QGraphicsSceneMouseEvent *mouseEvent);
    void addNewIconCommand(HBaseObj* pObj);
    void getIconGraphicsItemPointList(HIconGraphicsItem* item,QList<QPolygonF>& pfList);

protected:
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    //virtual void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent);
    //virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void drawBackground(QPainter *painter, const QRectF &rect);
    virtual void keyPressEvent(QKeyEvent *event);

signals:
    void itemInserted(int type);
    void itemSelected(QGraphicsItem* item);
public slots:
    void cutItem();
    void copyItem();
    void delItem();
    void pasteItem();
    void showProperty();
private:
    int nSelectMode;
    bool bLeftShift;
    QPointF prePoint;
    QPointF curPoint;
    QList<QPolygonF> oldPolygonF;
    QList<QPolygonF> newPolygonF;

    HIconEditorMgr* pIconMgr;
    /*HIconLineItem* line;
    HIconRectangleItem* rectangle;
    HIconEllipseItem* ellipse;
    HIconCircleItem* circle;
    HIconPolygonItem* polygon;
    HIconPolylineItem* polyline;
    HIconArcItem* arc;
    HIconPieItem* pie;
    HIconTextItem* text;
    HIconSelectionItem* select;
    HIconItemGroup* group;*/
};

#endif // HGRAPHICSSCENE_H
