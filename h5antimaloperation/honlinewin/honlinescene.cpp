#include "honlinescene.h"
#include "honlinedoc.h"
#include "hiconapi.h"
#include "hiconsymbol.h"
#include "hgraph.h"
#include "honlinemgr.h"
HOnlineScene::HOnlineScene(HOnlineMgr *mgr)
    :m_pOnlineMgr(mgr)
{
    //setSceneRect(m_pOnlineMgr->getLogicRect());
}

HOnlineScene::~HOnlineScene()
{

}


void HOnlineScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if(NULL == m_pOnlineMgr)
        return;
    painter->save();
    painter->setBrush(backgroundBrush());
    QGraphicsScene::drawBackground(painter,rect);

    HGraph* pGraph = m_pOnlineMgr->onlineDoc()->getCurGraph();
    QColor clr;
    if(pGraph)
    {
        clr = QColor(pGraph->getFillColor());
    }
    else
    {
        clr = QColor(Qt::darkGray);
    }
    QRectF rectF = m_pOnlineMgr->getLogicRect();
    painter->fillRect(rectF,clr);
    painter->restore();
}

void HOnlineScene::drawForeground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawForeground(painter,rect);
}


void HOnlineScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    QPointF point = event->scenePos();
    if(!m_pOnlineMgr || !m_pOnlineMgr->onlineOp())
        return;
    if(event->mimeData()->hasFormat("DragIcon"))
    {
        ptStart = point;
        QByteArray itemData = event->mimeData()->data("DragIcon");//数组
        QDataStream dataStream(&itemData,QIODevice::ReadOnly);//读数据到数组的流
        //uuid,name,type ==> uuid,红绿灯,遥信
        QString strUuid,strTypeName;
        int nShapeType = 0;
        dataStream>>strUuid>>strTypeName>>nShapeType; //读入数据到数组

        //

        event->setDropAction(Qt::MoveAction);
        event->accept();

    }
    else
        event->ignore();
}

void HOnlineScene::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{

}

void HOnlineScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if(!m_pOnlineMgr || !m_pOnlineMgr->onlineDoc() || !m_pOnlineMgr->onlineDoc()->getCurGraph())
        return;
    QPointF pointF = event->scenePos();
    if(event->mimeData()->hasFormat("DragIcon"))
    {
       //

        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
        event->ignore();
}

void HOnlineScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if(!m_pOnlineMgr || !m_pOnlineMgr->onlineDoc() || !m_pOnlineMgr->onlineDoc()->getCurGraph())
        return;
    if(event->mimeData()->hasFormat("DragIcon"))
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
        event->ignore();
}

void HOnlineScene::onCreateObj(HBaseObj* obj,bool isPaste )
{
    if(!m_pOnlineMgr || !m_pOnlineMgr->onlineView())
        return;
    obj->setModify(true);
    H5GraphicsItem *item = new H5GraphicsItem(obj);
    if(NULL == item) return;
    item->setZValue(obj->zValue());

    if(isPaste)
    {
        obj->setZValue(obj->zValue()+1);
        item->setZValue(obj->zValue());
    }

    addItem(item);
    connect(item,SIGNAL(objSelectChanged(HBaseObj*,bool)),this,SLOT(onObjSelectChanged(HBaseObj*,bool)));
    connect(item,SIGNAL(recalcSelect()),this,SLOT(onRecalcSelect()));
}

void HOnlineScene::onRemoveObj(HBaseObj* obj)
{
    if(!m_pOnlineMgr || !m_pOnlineMgr->onlineView())
        return;
    if(obj && obj->iconGraphicsItem())
    {
        H5GraphicsItem* item = (H5GraphicsItem*)obj->iconGraphicsItem();
        removeItem(item);
        item->setBaseObj(NULL);
        disconnect(item,SIGNAL(objSelectChanged(HBaseObj*,bool)),this,SLOT(onObjSelectChanged(HBaseObj*,bool)));
        disconnect(item,SIGNAL(recalcSelect()),this,SLOT(onRecalcSelect()));
    }
}

//绘制
void HOnlineScene::drawPath(const QList<Path>& pathList)
{
    for(int i = 0;i < pathList.count();i++)
    {
        Path path = pathList.at(i);
        QGraphicsPathItem* item;
        //之前存在路径item直接拿出来用
        if(i < m_pGraphicsPathItems.count())
        {
            item = m_pGraphicsPathItems.at(i);
        }
        else
        {
            item = new QGraphicsPathItem;
            m_pGraphicsPathItems.append(item);
            addItem(item);
        }
        item->setVisible(true);
        item->setPen(path.pen);
        item->setBrush(path.brush);
        item->setPath(path.painterPath);
    }

    //多余的部分隐藏依赖
    for(int i = pathList.count(); i < m_pGraphicsPathItems.count();i++)
    {
        QGraphicsPathItem* item = m_pGraphicsPathItems.at(i);
        if(item)
        {
            item->setVisible(false);
        }
    }
}

void HOnlineScene::endDraw()
{
    for(int i = 0; i < m_pGraphicsPathItems.count();i++)
    {
        QGraphicsPathItem* item = m_pGraphicsPathItems.at(i);
        if(item)
        {
            item->setVisible(false);
        }
    }
}
