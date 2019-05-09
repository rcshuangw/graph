#include "hiconeditorscene.h"
#include <cmath>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QMenu>
#include <QMessageBox>
#include <QDebug>
#include "hiconeditorframe.h"
#include "hiconeditormgr.h"
#include "hselectedmgr.h"
#include "hdrawmanager.h"
HIconEditorScene::HIconEditorScene(HIconEditorMgr* iconMgr)
    :m_pIconEditorMgr(iconMgr)
{

}

void HIconEditorScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if(!m_pIconEditorMgr && !m_pIconEditorMgr->iconEditorFrame())
        return;
    QRectF rectLogic = m_pIconEditorMgr->getLogicRect();
    QRectF finalRect = rectLogic;//rect.intersected(rectLogic);
    painter->save();
    QColor bgclr = QColor(m_pIconEditorMgr->getBackgroundColor());
    painter->fillRect(finalRect,bgclr);


    bool bShowGrid = m_pIconEditorMgr->getShowGrid();
    if(bShowGrid)
    {
        for(qreal x=finalRect.left();x < finalRect.right()+25;x+=25)
            for(qreal y=finalRect.top();y<finalRect.bottom()+25;y+=25)
                painter->drawPoint(x,y);
    }

    bool bShowCenterLine = m_pIconEditorMgr->getShowCenterLine();
    if(bShowCenterLine)
    {
        QPointF p1(rectLogic.left()+5,(rectLogic.topLeft().y()+rectLogic.bottomLeft().y())/2);
        QPointF p2(rectLogic.right()-5,(rectLogic.topLeft().y()+rectLogic.bottomLeft().y())/2);
        QPointF p3((rectLogic.topLeft().x()+rectLogic.topRight().x())/2,rectLogic.top()+5);
        QPointF p4((rectLogic.topLeft().x()+rectLogic.topRight().x())/2,rectLogic.bottom()-5);
        QPen pen(Qt::lightGray);
        pen.setWidth(1);
        painter->setPen(pen);
        painter->drawLine(p1,p2);
        painter->drawLine(p3,p4);
    }
    painter->restore();
}

void HIconEditorScene::drawForeground(QPainter *painter, const QRectF &rect)
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->selectedMgr())
        return;
    QRect rectTemp = QRect(QPoint(),QSize(6,6));
    QRectF selRect = m_pIconEditorMgr->iconEditorFrame()->view()->mapToScene(rectTemp).boundingRect();
    m_pIconEditorMgr->selectedMgr()->paint(painter,rect,selRect);
}


void HIconEditorScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
   
}


void HIconEditorScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
   
}

//绘制
void HIconEditorScene::drawPath(const QList<Path>& pathList)
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

void HIconEditorScene::endDraw()
{
    //绘制结束后绘制路径设为false，既看不到路径item，又防止后续选择上
    for(int i = 0; i < m_pGraphicsPathItems.count();i++)
    {
        QGraphicsPathItem* item = m_pGraphicsPathItems.at(i);
        if(item)
        {
            item->setVisible(false);
        }
    }
}
