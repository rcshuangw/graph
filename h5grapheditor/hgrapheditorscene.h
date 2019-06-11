#ifndef HGRAPHEDITORSCENE_H
#define HGRAPHEDITORSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "hiconapi.h"
#include "hdrawmanager.h"
class HBaseObj;
class HGraphEditorMgr;
class HGraphEditorView;
class HGraphEditorScene : public QGraphicsScene
{
    Q_OBJECT
public:
    HGraphEditorScene(HGraphEditorMgr *mgr);
    ~HGraphEditorScene();

public:
    void clear();
    void setView(QGraphicsView* v);
    QGraphicsView* view();

protected:
    virtual void drawBackground(QPainter *painter, const QRectF &rect);
    virtual void drawForeground(QPainter *painter, const QRectF &rect);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent);

    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dropEvent(QGraphicsSceneDragDropEvent *event);

    //绘制
public:
    void drawPath(const QList<Path>& pathList);
    void endDraw();
    virtual bool eventFilter( QObject *obj, QEvent *event);
    virtual bool event(QEvent *event);
    virtual void showStatusText(QEvent* event);

public slots:
    //virtual void onDrawPath(const QList<Path>& path);
    //virtual void onEndDraw();
    virtual void onCreateObj(HBaseObj* pObj,bool isPaste );
    virtual void onRemoveObj(HBaseObj* pObj);
    virtual void onRefreshSelect(const QRectF& rect);
    virtual void onObjSelectChanged(HBaseObj *obj, bool isSelected);
    void onRecalcSelect();
signals:
    void selectChanged(HBaseObj *obj, bool isSelected);

public:
    QPointF ptStart;
    QPointF prePoint;
    QPointF curPoint;
    bool bLeftShift;
    QList<QPolygonF> oldPolygonF;
    QList<QPolygonF> newPolygonF;

    HGraphEditorMgr* m_pGraphEditorMgr;
    HGraphEditorView* m_pGraphEditorView;
public:
    QList<QGraphicsPathItem*> m_pGraphicsPathItems;
    QList<H5GraphicsItem*> m_dragMoveItems;

};

#endif // HGRAPHEDITORSCENE_H
