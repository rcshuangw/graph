#include "hgrapheditorscene.h"
#include "hgrapheditormgr.h"
#include "hgrapheditordoc.h"
#include "hgrapheditorview.h"
#include "hgrapheditorop.h"
#include "h5graphicsitem.h"
#include "hiconapi.h"
#include "hgraph.h"
#include "hselectedmgr.h"
#include <QMimeData>
#include <QDebug>

HGraphEditorScene::HGraphEditorScene(HGraphEditorMgr *mgr)
    :m_pGraphEditorMgr(mgr)
{
    setSceneRect(m_pGraphEditorMgr->getLogicRect());
}

HGraphEditorScene::~HGraphEditorScene()
{

}

void HGraphEditorScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if(NULL == m_pGraphEditorMgr)
        return;
    painter->save();
    painter->setBrush(backgroundBrush());
    QGraphicsScene::drawBackground(painter,rect);

    HGraph* pGraph = m_pGraphEditorMgr->graphEditorDoc()->getCurGraph();
    QColor clr;
    if(pGraph)
    {
        clr = QColor(pGraph->getFillColorName());
    }
    else
    {
        clr = QColor(Qt::darkGray);
    }
    QRectF rectF = m_pGraphEditorMgr->getLogicRect();
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
    if(!m_pGraphEditorMgr)
        return;

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void HGraphEditorScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if(!m_pGraphEditorMgr->graphEditorDoc() || !m_pGraphEditorMgr->graphEditorDoc()->getCurGraph())
        return;

    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void HGraphEditorScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    m_dragMoveItems.clear();
    QPointF point = event->scenePos();
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
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
        m_pGraphEditorMgr->graphEditorOp()->createIconObj(strTypeName,strUuid,nShapeType,point,m_dragMoveItems);
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
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorDoc() || !m_pGraphEditorMgr->graphEditorDoc()->getCurGraph())
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
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorDoc() || !m_pGraphEditorMgr->graphEditorDoc()->getCurGraph())
        return;
    if(event->mimeData()->hasFormat("DragIcon"))
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
        event->ignore();
}

bool HGraphEditorScene::event(QEvent *event)
{
    return false;
}

bool HGraphEditorScene::eventFilter(QObject *obj, QEvent *event)
{
    static bool bRight = false;
    if(obj == m_pGraphEditorView->viewport())
    {
        switch(((QMouseEvent*)event)->type())
        {
        case QEvent::MouseButtonDblClick:
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseMove:
        {
            if(!m_pGraphEditorMgr || !m_pGraphEditorView)
                return false;

            QPointF pos = m_pGraphEditorView->mapToScene(((QMouseEvent*)event)->pos());
            HEvent hevent(event,QVariant(pos));
            //if(m_pIconEditorMgr->iconEditorOp()->toolType() == ICON_DRAW_TOOL)
            //    m_pIconEditorMgr->iconEditorDrawToolMgr()->onEvent(hevent);
            //else if(m_pIconEditorMgr->iconEditorOp()->toolType() == ICON_SELECT_TOOL)
            //    m_pIconEditorMgr->iconEditorSelectTool()->onEvent(hevent);

            if(event->type() == QEvent::MouseButtonRelease)
            {
                QMouseEvent* me = (QMouseEvent*)event;
                if(me->button() == Qt::RightButton)
                {
                    //if(m_pIconEditorMgr->iconEditorOp()->toolType() == ICON_DRAW_TOOL)
                    {
                        //m_pIconEditorMgr->iconEditorOp()->switchSelectTool();
                        bRight = true;
                        return true;
                    }
                }
            }
            if(event->type() == QEvent::MouseMove)
            {
                showStatusText(event);
            }
            return false;
        }
        case QEvent::ContextMenu:
        {
            if(bRight)
            {
                bRight = false;
                return true;
            }
            HEvent hevent(event,QVariant());
            //m_pIconEditorMgr->iconEditorSelectTool()->onEvent(hevent);
            return false;
        }
        }
    }
    else if(obj == m_pGraphEditorView){
            switch(event->type()){
            case QEvent::KeyPress:
            case QEvent::KeyRelease:
                {
                    if(!m_pGraphEditorMgr)
                    {
                        return false;
                    }
                    HEvent hevent(event,QVariant());
                    //m_pIconEditorMgr->iconEditorSelectTool()->onEvent(hevent);
                    return false;
                }
            default:
                {
                    return false;
                }
            }
        }
    return false;
}

void HGraphEditorScene::showStatusText(QEvent* event)
{
    if(!event) return;
    QMouseEvent* e = dynamic_cast<QMouseEvent*>(event);
    QPointF pt = m_pGraphEditorView->mapToScene(e->pos());
    QString strText = QStringLiteral("坐标:(") + QString::number(pt.x(),'f',0) + QString::number(pt.y(),'f',0) +  ")";
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->graphEditorOp())
        return;
    m_pGraphEditorMgr->graphEditorOp()->updateStatus(strText);
}

void HGraphEditorScene::onDrawPath(const QList<Path>& pathList)
{
    if(!m_pGraphEditorView )
        return;

    QList<Path> list;
    for(int i = 0; i< pathList.count();i++)
    {
        Path path = (Path)pathList.at(i);
        if(path.coordType)
        {

        }
        list.append(path);
    }
    drawPath(list);
}

void HGraphEditorScene::onEndDraw()
{
    if(!m_pGraphEditorView)
        return;
    endDraw();
}

void HGraphEditorScene::onCreateObj(HBaseObj* obj,bool isPaste )
{
    if(!m_pGraphEditorView)
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

void HGraphEditorScene::onRefreshSelect(const QRectF& rect)
{
    invalidate(rect,QGraphicsScene::ForegroundLayer);
}

void HGraphEditorScene::onObjSelectChanged(HBaseObj *obj, bool isSelected)
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
        return;
    m_pGraphEditorMgr->graphEditorOp()->objSelectChanged(obj,isSelected);
}

void HGraphEditorScene::onRecalcSelect()
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->selectedMgr())
        return;
    m_pGraphEditorMgr->selectedMgr()->recalcSelect();
}

void HGraphEditorScene::setView(QGraphicsView* v)
{
    m_pGraphEditorView = dynamic_cast<HGraphEditorView*>(v);
}

QGraphicsView* HGraphEditorScene::view()
{
    return m_pGraphEditorView;
}

//绘制
void HGraphEditorScene::drawPath(const QList<Path>& pathList)
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

void HGraphEditorScene::endDraw()
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
