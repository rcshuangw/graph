#include "hiconeditorscene.h"
#include "hiconeditorframe.h"
#include <cmath>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QMenu>
#include <QMessageBox>
#include <QDebug>
HIconEditorScene::HIconEditorScene(HIconEditorMgr* iconMgr)
    :m_pIconEditorMgr(iconMgr)
{

}

void HIconEditorScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if(!m_pIconEditorMgr && !m_pIconEditorMgr->getIconFrame())
        return;
    QRectF rectLogic = m_pIconEditorMgr->getLogicRect();
    QRectF finalRect = rectLogic;//rect.intersected(rectLogic);
    painter->save();
    QColor bgclr = QColor(m_pIconEditorMgr->getBackgroundColor());
    painter->fillRect(finalRect,bgclr);


    bool bShowGrid = pIconMgr->getShowGrid();
    if(bShowGrid)
    {
        for(qreal x=finalRect.left();x < finalRect.right()+25;x+=25)
            for(qreal y=finalRect.top();y<finalRect.bottom()+25;y+=25)
                painter->drawPoint(x,y);
    }

    bool bShowCenterLine = pIconMgr->getShowCenterLine();
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

}

void HIconEditorScene::endDraw()
{

}
