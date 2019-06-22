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
class HBaseObj;
class HGraph;
class HOnlineFrame;
class HOnlineMgr;
class HOnlineScene : public QGraphicsScene
{
    Q_OBJECT
public:
    HOnlineScene(HOnlineMgr* mgr);
    ~HOnlineScene();
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
    HOnlineMgr* m_pOnlineMgr;
public:

};

#endif // HONLINESCENE_H
