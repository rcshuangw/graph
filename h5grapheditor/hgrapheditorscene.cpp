#include "hgrapheditorscene.h"
#include "hgrapheditormgr.h"
#include "hgrapheditordoc.h"
#include "hiconapi.h"
#include "hiconsymbol.h"
#include "hgraph.h"
#include "hgrapheditorview.h"
#include <QMimeData>
#include <QDebug>

HGraphEditorScene::HGraphEditorScene(HGraphEditorMgr *mgr)
    :pGraphEditorMgr(mgr)
{

}

void HGraphEditorScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if(NULL == pGraphEditorMgr)
        return;
    painter->save();
    painter->setBrush(backgroundBrush());
    QGraphicsScene::drawBackground(painter,rect);

    HGraph* pGraph = pGraphEditorMgr->graphEditorDoc()->getCurGraph();
    QColor clr;
    if(pGraph)
    {
        clr = QColor(pGraph->getFillColor());
    }
    else
    {
        clr = QColor(Qt::darkGray);
    }
    QRectF rectF = pGraphEditorMgr->getLogicRect();
    painter->fillRect(rectF,clr);
    painter->restore();
}

void HGraphEditorScene::drawForeground(QPainter *painter, const QRectF &rect)
{

}

void HGraphEditorScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button() != Qt::LeftButton)
        return;
    if(!pGraphEditorMgr)
        return;

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void HGraphEditorScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if(!pGraphEditorMgr->graphEditorDoc() || !pGraphEditorMgr->graphEditorDoc()->getCurGraph())
        return;

    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void HGraphEditorScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    m_dragMoveItems.clear();
    QPointF point = event->scenePos();
    if(!pGraphEditorMgr || !pGraphEditorMgr->graphEditorDoc() || !pGraphEditorMgr->graphEditorDoc()->getCurGraph())
        return;
    if(event->mimeData()->hasFormat("DragIcon"))
    {
        ptStart = point;
        QByteArray itemData = event->mimeData()->data("DragIcon");//数组
        QDataStream dataStream(&itemData,QIODevice::ReadOnly);//读数据到数组的流
        //uuid,name,type uuid,红绿灯,遥信
        QString strUuid,strTypeName;
        int nShapeType = 0;
        dataStream>>strUuid>>strTypeName>>nShapeType; //读入数据到数组
        pGraphEditorMgr->createIconObj(strTypeName,strUuid,nShapeType,point,dragMoveItems);
        event->setDropAction(Qt::MoveAction);
        event->accept();

    }
    else
        event->ignore();

}

void HGraphEditorScene::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{

}

void HGraphEditorScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if(!pGraphEditorMgr || !pGraphEditorMgr->graphEditorDoc() || !pGraphEditorMgr->graphEditorDoc()->getCurGraph())
        return;
    QPointF pointF = event->scenePos();
    if(event->mimeData()->hasFormat("DragIcon"))
    {

        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
        event->ignore();
}

void HGraphEditorScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if(!pGraphEditorMgr || !pGraphEditorMgr->graphEditorDoc() || !pGraphEditorMgr->graphEditorDoc()->getCurGraph())
        return;
    if(event->mimeData()->hasFormat("DragIcon"))
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
        event->ignore();
}


//绘制
void HGraphEditorScene::drawPath(const QList<Path>& pathList)
{

}

void HGraphEditorScene::endDraw()
{

}

bool HGraphEditorScene::event(QEvent *event)
{

}

void HGraphEditorScene::showStatusText(QEvent* event)
{

}

void HGraphEditorScene::onDrawPath(const QList<Path>& path)
{

}

void HGraphEditorScene::onEndDraw()
{

}

void HGraphEditorScene::onCreateObj(HBaseObj* pObj,bool isPaste )
{

}

void HGraphEditorScene::onRefreshSelect(const QRectF& rect)
{

}

void HGraphEditorScene::onSelectChanged(HBaseObj *obj, bool isSelected)
{

}

void HGraphEditorScene::onRecalcSelect()
{

}

void HGraphEditorScene::setView(QGraphicsView* v)
{

}

QGraphicsView* HGraphEditorScene::view()
{

}
