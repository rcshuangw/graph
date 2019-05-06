﻿#include "hiconeditorselecttool.h"
#include <QWidget>
#include <QMouseEvent>
#include "hiconeditormgr.h"
#include "hiconeditorframe.h"
#include "h5event.h"
#include "htempcontainer.h"
#include "hselectedmgr.h"
#include "hiconcommand.h"
#include "hdrawhelper.h"
HIconEditorSelectToolMgr::HIconEditorSelectToolMgr(HIconEditorMgr* manager)
    :m_pIconEditorMgr(manager),m_bIsSelectPoint(false)
{
    m_SelectMode = None;
    m_SelectWidget = new QWidget;
    m_SelectWidget->setPalette(QPalette(Qt::blue));
    m_SelectWidget->setWindowFlags(Qt::FramelessWindowHint);
    m_SelectWidget->setMouseTracking(false);
    m_SelectWidget->hide();
    m_SelectWidget->installEventFilter(this);

    m_pDrawHelper = new HDrawHelper;
}

HIconEditorSelectToolMgr::~HIconEditorSelectToolMgr()
{
    if(m_pDrawHelper)
    {
        delete m_pDrawHelper;
        m_pDrawHelper = NULL;
    }
}

void HIconEditorSelectToolMgr::clear()
{

}

bool HIconEditorSelectToolMgr::eventFilter(QObject *obj, QEvent *ev)
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconEditorFrame() || !m_pIconEditorMgr->iconEditorFrame()->view())
        return false;
    if(obj == m_SelectWidget)
    {
        switch(ev->type())
        {
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseMove:
        {
            QPoint gp = ((QMouseEvent*)ev)->globalPos();
            QPoint vp = m_pIconEditorMgr->iconEditorFrame()->view()->viewport()->mapFromGlobal(gp);
            QPointF fp = m_pIconEditorMgr->iconEditorFrame()->view()->mapToScene(vp);
            QMouseEvent e(ev->type(),vp,gp,((QMouseEvent*)ev)->button(),((QMouseEvent*)ev)->buttons(),((QMouseEvent*)ev)->modifiers());
            HEvent he(&e,QVariant(fp));
            onEvent(he);
        }
            break;
        }
    }
}

void HIconEditorSelectToolMgr::onEvent(HEvent& e)
{
    if(e.event()->type() == QEvent::MouseButtonPress)
    {
        onMousePressEvent((QMouseEvent*)e.event(),e.m_data);
    }
    else if(e.event()->type() == QEvent::MouseMove)
    {
        onMouseMoveEvent((QMouseEvent*)e.event(), e.m_data);
    }
    else if(e.event()->type() == QEvent::MouseButtonRelease)
    {
        onMouseReleaseEvent((QMouseEvent*)e.event(), e.m_data);
    }
    else if(e.event()->type() == QEvent::KeyPress)
    {
        onKeyPressEvent((QKeyEvent*)e.event(),e.m_data);
    }
    else if(e.event()->type() == QEvent::MouseButtonDblClick)
    {
        onMouseDoubleClickEvent((QMouseEvent*)e.event(), e.m_data);
    }
    else if(e.event()->type() == QEvent::ContextMenu)
    {
        onContextMenuEvent((QContextMenuEvent*)e.event(), e.m_data);
    }
}

//鼠标左键
void HIconEditorSelectToolMgr::onMousePressEvent(QMouseEvent* event, QVariant &data)
{
    if(!event || !m_pIconEditorMgr || !m_pIconEditorMgr->selectedMgr())
        return;
    m_ptCurPoint = m_ptOriPoint = m_ptStPoint = data.toPointF();
    if(None == m_SelectMode)
    {
        if(m_pIconEditorMgr->iconEditorFrame()->view()->scene()->mouseGrabberItem()){
            m_SelectMode = Select;
        }
    }

}

void HIconEditorSelectToolMgr::onMouseMoveEvent(QMouseEvent* event, QVariant &data)
{
    if(!event || !m_pIconEditorMgr || !m_pIconEditorMgr->selectedMgr() || !m_pIconEditorMgr->selectedMgr()->selectObj())
        return;
    m_ptStPoint = m_ptCurPoint;
    m_ptCurPoint = data.toPointF();
    if(event->buttons() == Qt::NoButton)
    {
        QPointF selPoint;
        m_nSelPointIndex = m_pIconEditorMgr->selectedMgr()->isOnPoint(m_ptCurPoint,selPoint);
        if(m_nSelPointIndex < 0)
        {
            m_bIsSelectPoint = false;
            if(m_pIconEditorMgr->selectedMgr()->isOnObj(m_ptCurPoint))
            {
                m_pIconEditorMgr->iconEditorFrame()->view()->setCursor(Qt::SizeAllCursor);
            }
            else
                m_pIconEditorMgr->iconEditorFrame()->view()->setCursor(cursor());
            m_SelectWidget->hide();
        }
        else
        {
            m_bIsSelectPoint = true;
            if(!m_SelectWidget->parent())
            {
                m_SelectWidget->setParent(m_pIconEditorMgr->iconEditorFrame()->view()->viewport());
            }
            m_SelectWidget->resize(6,6);
            QPoint pt = m_pIconEditorMgr->iconEditorFrame()->view()->mapFromScene(selPoint);
            m_SelectWidget->move(pt.x() - 6/2,pt.y() - 6/2);
            if(0)
            {

            }
            else
            {
                if(m_pDrawHelper)
                {
                    m_SelectWidget->setCursor(m_pDrawHelper->cursor(m_nSelPointIndex));
                }
            }
            m_SelectWidget->show();

            if(0)
            {

            }
            else
            {
                m_vlOldPoints.clear();
                HTempContainer* tempContainer = m_pIconEditorMgr->selectedMgr()->selectObj();
                for(int i = 0; i < tempContainer->getObjList().size();i++)
                {
                    HBaseObj* pObj = tempContainer->getObjList().at(i);
                    if(pObj)
                    {
                        m_vlOldPoints.append(pObj->getPointList(1));
                    }
                }
            }
        }
    }

    //当左键点击,没有点到四角点
    if(!m_bIsSelectPoint)
    {
        if(event->buttons()&Qt::LeftButton)
        {
            HTempContainer* tempContainer = m_pIconEditorMgr->selectedMgr()->selectObj();
            if(!tempContainer) return;
            if(!m_pIconEditorMgr->iconEditorFrame()->view()->scene()->mouseGrabberItem())
            {
                if(m_SelectMode == Select)
                    m_SelectMode = None;
            }
            else
                m_SelectMode = Select;

            if(Select == m_SelectMode)
            {
                qreal dx = m_ptCurPoint.x() - m_ptStPoint.x();
                qreal dy = m_ptCurPoint.y() - m_ptStPoint.y();
                tempContainer->moveBy(dx,dy);
            }
        }
    }
    else
    {
        if(event->buttons()&Qt::LeftButton)
        {
            HTempContainer* tempContainer = m_pIconEditorMgr->selectedMgr()->selectObj();
            if(!tempContainer) return;
            if(!tempContainer || !tempContainer->getObjList().size() <= 0)
                return;
            if(0)
            {

            }
            else
            {
                if(m_pDrawHelper)
                {
                    //m_pDrawHelper->
                }
            }
        }
    }
}

void HIconEditorSelectToolMgr::onMouseReleaseEvent(QMouseEvent* event, QVariant &data)
{
    if(!event || !m_pIconEditorMgr || !m_pIconEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pIconEditorMgr->selectedMgr()->selectObj();
    m_ptStPoint = m_ptCurPoint;
    m_ptCurPoint = data.toPointF();

    //选中四周的点
    if(m_bIsSelectPoint)
    {
        if(0)
        {

        }
        else
        {
            m_pIconEditorMgr->selectedMgr()->recalcSelect();
            if(tempContainer)
            {
                QList<HBaseObj*> objs;
                QList<HPointFList> points;
                for(int i = 0; i < tempContainer->getObjList().size();i++)
                {
                    HBaseObj* pObj = tempContainer->getObjList().at(i);
                    if(pObj){
                        objs.append(pObj);
                        points.append(pObj->getPointList());
                    }
                }

                HResizeIconCommand* reizeCommand = new HResizeIconCommand(m_pIconEditorMgr,objs,m_vlOldPoints,points);
                m_pIconEditorMgr->iconEditorUndoStack()->push(reizeCommand);
            }
        }
    }
    else
    {
        if(None == m_SelectMode)
        {
            if(tempContainer && tempContainer->getObjList().count() > 0)
            {
                m_SelectMode = Select;
            }
        }
        else if(Select == m_SelectMode)
        {
            if(tempContainer && tempContainer->getObjList().count() > 0)
            {
                m_SelectMode = None;
            }
            else if(tempContainer)
            {
                QList<HBaseObj*> objs;
                for(int i = 0; i < tempContainer->getObjList().size();i++)
                {
                    HBaseObj* pObj = tempContainer->getObjList().at(i);
                    if(pObj)
                        objs.append(pObj);
                }
                qreal dx = m_ptCurPoint.x() - m_ptOriPoint.x();
                qreal dy = m_ptCurPoint.y() - m_ptOriPoint.y();
                if(qFuzzyCompare(dx,0) && qFuzzyCompare(dy,0))
                    return;
                HMoveIconCommand* moveCommand = new HMoveIconCommand(m_pIconEditorMgr,objs,dx,dy);
                m_pIconEditorMgr->iconEditorUndoStack()->push(moveCommand);
            }
        }
    }
}

void HIconEditorSelectToolMgr::onMouseDoubleClickEvent(QMouseEvent* event, QVariant &data)
{

}

void HIconEditorSelectToolMgr::onContextMenuEvent(QContextMenuEvent *event, QVariant &data)
{

}

void HIconEditorSelectToolMgr::onKeyPressEvent(QKeyEvent *event, QVariant& data)
{
    if(!event || !m_pIconEditorMgr || !m_pIconEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pIconEditorMgr->selectedMgr()->selectObj();
    if(!tempContainer || tempContainer->getObjList().size() == 0)
        return;
    int nStep = 5;
    if(event->modifiers() == Qt::ShiftModifier)
    {
        nStep = 1;
    }
    int ndx = 0;
    int ndy = 0;
    switch(event->key())
    {
    case Qt::Key_Up:
    {
        ndx = 0;
        ndy = -nStep;
        break;
    }
    case Qt::Key_Down:
    {
        ndx = 0;
        ndy = nStep;
        break;
    }
    case Qt::Key_Left:
    {
        ndx = -nStep;
        ndy = 0;
        break;
    }
    case Qt::Key_Right:
    {
        ndx = nStep;
        ndy = 0;
        break;
    }
    }

    if(ndx == 0 && ndy == 0)
        return;

    HMoveIconCommand* moveCommand = new HMoveIconCommand(m_pIconEditorMgr,objs,dx,dy);
    m_pIconEditorMgr->iconEditorUndoStack()->push(moveCommand);
}

QCursor HIconEditorSelectToolMgr::cursor()
{

}
