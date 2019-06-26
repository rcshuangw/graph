#include "hgraphframe.h"
#include <QScrollBar>
#include "hgraphview.h"
#include "hantimalopmgr.h"
#include "hantimalopdoc.h"
#include "hgraphview.h"
#include "hgraphscene.h"
#include "hgraph.h"
HGraphFrame::HGraphFrame(HAntiMalopMgr* mgr,HBaseFrame *parent) :
    HBaseFrame(mgr,parent)
{
}

HGraphFrame::~HGraphFrame()
{
}

void HGraphFrame::openGraph()
{
    if(!m_pAntiMalpoMgr || !m_pAntiMalpoMgr->antiMalopDoc())
        return;
    reset();
    int width = m_pAntiMalpoMgr->antiMalopDoc()->getCurGraph()->m_width;
    int height = m_pAntiMalpoMgr->antiMalopDoc()->getCurGraph()->m_height;
    QRectF newLogicRectF = QRectF(QPointF(0-width/2,0-height/2),QSizeF(width,height));
    if(!m_pGraphScene || !m_pGraphView)
        return;
    m_pGraphScene->setSceneRect(newLogicRectF);
    if(m_pGraphView)
    {
        QScrollBar* pBar = m_pGraphView->horizontalScrollBar();
        if(pBar && pBar->isHidden() == false)
        {
            pBar->setSliderPosition(pBar->minimum());
        }
        pBar = m_pGraphView->verticalScrollBar();
        if(pBar && pBar->isHidden() == false)
        {
            pBar->setSliderPosition(pBar->minimum());
        }
    }
    m_pGraphView->refresh();


    if(!m_pAntiMalpoMgr->antiMalopDoc()->getCurGraph())
        return false;
    for(int i = 0; i < m_pAntiMalpoMgr->antiMalopDoc()->getCurGraph()->size();i++)
    {
        HBaseObj* obj = (HBaseObj*)m_pAntiMalpoMgr->antiMalopDoc()->getCurGraph()->at(i);
        m_pGraphScene->onCreateObj(obj);
    }
}

/*
bool HGraphFrame::eventFilter(QObject *obj, QEvent *event)
{
    QEvent::Type type = event->type();
    if(obj != m_pGraphView->viewport())
        return false;
    switch(type)
    {
    case QEvent::MouseButtonPress:
        return onMousePressEvent(obj,event);
        break;
    case QEvent::MouseMove:
        return onMouseMoveEvent(obj,event);
        break;
    case QEvent::MouseButtonRelease:
        return onMouseReleaseEvent(obj,event);
        break;
    case QEvent::ContextMenu:
        return onContextMenuEvent(obj,event);
        break;
    case QEvent::KeyPress:
        return onKeyPressEvent(obj,event);
        break;
    case QEvent::Wheel:
        return onWheelEvent(obj,event);
        break;
    }
    return false;
}*/

bool HGraphFrame::onMousePressEvent(QObject *obj, QEvent *event)
{
    //处理2种情况 1是控制点，2是牌
    QMouseEvent* e = static_cast<QMouseEvent*>(event);
    QPointF pos = m_pGraphView->mapToScene(e->pos());
    QGraphicsScene* scene = m_pGraphView->scene();
    if(!scene) return false;

    //记录下按下的点 后面牌、控制点可以可能要拖动

}

bool HGraphFrame::onMouseMoveEvent(QObject *obj, QEvent *event)
{
    //主要是移动鼠标到牌或者控制点上要有颜色过渡效果
    //牌的移动等操作
}

bool HGraphFrame::onMouseReleaseEvent(QObject *obj, QEvent *event)
{
    //按到牌或者控制点上后的操作要在这里处理
}

bool HGraphFrame::onMouseDoubleClickEvent(QObject *obj, QEvent *event)
{

}

bool HGraphFrame::onKeyPressEvent(QObject *obj, QEvent *event)
{

}

bool HGraphFrame::onWheelEvent(QObject *obj, QEvent *event)
{

}

bool HGraphFrame::onContextMenuEvent(QObject *obj, QEvent *event)
{
    //右键效果 1.按到遥信遥测等图元上 2.按到普通图元、控制点上 3.按到后面的画面层上
}
