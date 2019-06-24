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
#include "hdrawmanager.h"
class HBaseObj;
class HGraph;
class HGraphFrame;
class HAntiMalopMgr;
class HGraphView;
class HGraphScene : public QGraphicsScene
{
    Q_OBJECT
public:
    HGraphScene(HAntiMalopMgr* mgr);
    ~HGraphScene();
public:
    void setView(QGraphicsView* v);
    QGraphicsView* view();
protected:
    virtual void drawBackground(QPainter *painter, const QRectF &rect);
    virtual void drawForeground(QPainter *painter, const QRectF &rect);

    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dropEvent(QGraphicsSceneDragDropEvent *event);

    //绘制
public:
    void drawPath(const QList<Path>& pathList);
    void endDraw();
    void onCreateObj(HBaseObj* pObj,bool isPaste=false );
    void onRemoveObj(HBaseObj* pObj);

public:
    QList<QGraphicsPathItem*> m_pGraphicsPathItems;
    HGraph* m_pGraph;
    HAntiMalopMgr* m_pAntiMalopMgr;
    HGraphView* m_pGraphView;
public:

};

#endif // HONLINESCENE_H
