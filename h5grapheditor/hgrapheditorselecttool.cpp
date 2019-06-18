#include "hgrapheditorselecttool.h"
#include <QWidget>
#include <QMenu>
#include <QMouseEvent>
#include "hgrapheditormgr.h"
#include "hgrapheditorop.h"
#include "h5event.h"
#include "htempcontainer.h"
#include "hselectedmgr.h"
#include "hgrapheditorview.h"
#include "hgraphcommand.h"
#include "hdrawhelper.h"
HGraphEditorSelectTool::HGraphEditorSelectTool(HGraphEditorMgr* manager)
    :m_pGraphEditorMgr(manager),m_bIsSelectPoint(false)
{
    m_nSelPointIndex = -1;
    m_SelectMode = None;
    m_SelectWidget = new QWidget;
    m_SelectWidget->setPalette(QPalette(Qt::blue));
    m_SelectWidget->setWindowFlags(Qt::FramelessWindowHint);
    m_SelectWidget->setMouseTracking(false);
    m_SelectWidget->hide();
    m_SelectWidget->installEventFilter(this);

    m_bMoveGrab = false;
    //m_pDrawHelper = new HDrawHelper;
}

HGraphEditorSelectTool::~HGraphEditorSelectTool()
{

}

void HGraphEditorSelectTool::setSelectMode(SelectMode mode)
{
    if(None == mode)
    {
        HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
        if(tempContainer && tempContainer->getObjList().size() == 0)
        {
            m_SelectMode = None;
        }
        else
            m_SelectMode = Select;
        m_pGraphEditorMgr->graphEditorView()->setInteractive(true);
        m_pGraphEditorMgr->graphEditorView()->setDragMode(QGraphicsView::RubberBandDrag);
    }
    else
    {
        m_SelectMode = mode;
        m_pGraphEditorMgr->graphEditorView()->setInteractive(false);
        m_pGraphEditorMgr->graphEditorView()->setDragMode(QGraphicsView::NoDrag);
    }
}

SelectMode HGraphEditorSelectTool::selectMode()
{
    return m_SelectMode;
}

void HGraphEditorSelectTool::clear()
{

}

bool HGraphEditorSelectTool::eventFilter(QObject *obj, QEvent *ev)
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorView())
        return false;
    if(obj == m_SelectWidget)
    {
        switch(ev->type())
        {
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseMove:
        {
            m_bIsSelectPoint = true;
            QPoint gp = ((QMouseEvent*)ev)->globalPos();
            QPoint vp = m_pGraphEditorMgr->graphEditorView()->viewport()->mapFromGlobal(gp);
            QPointF fp = m_pGraphEditorMgr->graphEditorView()->mapToScene(vp);
            QMouseEvent e(ev->type(),vp,gp,((QMouseEvent*)ev)->button(),((QMouseEvent*)ev)->buttons(),((QMouseEvent*)ev)->modifiers());
            HEvent he(&e,QVariant(fp));
            //onEvent(he);
            if ( ev->type() == QEvent::MouseMove )
            {
                QVariant data( fp );
                onMouseMoveEvent( &e, data );
            }
            else
            {
                onEvent(he);
                if ( ev->type() == QEvent::MouseButtonPress&&e.button()==Qt::LeftButton )
                {
                    m_bMoveGrab = true;
                }
                else if( ev->type() == QEvent::MouseButtonRelease )
                {
                    m_bMoveGrab = false;
                }
            }
            return true;
        }
            break;
        }
    }
    return false;
}

void HGraphEditorSelectTool::onEvent(HEvent& e)
{
    if(e.event()->type() == QEvent::MouseButtonPress)
    {
        onMousePressEvent((QMouseEvent*)e.event(),e.m_data);
    }
    else if(e.event()->type() == QEvent::MouseMove)
    {
        if(!m_bMoveGrab)
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
void HGraphEditorSelectTool::onMousePressEvent(QMouseEvent* event, QVariant &data)
{
    if(!event || !m_pGraphEditorMgr || !m_pGraphEditorMgr->selectedMgr())
        return;
    m_ptCurPoint = m_ptOriPoint = m_ptStPoint = data.toPointF();
    if(None == m_SelectMode)
    {
        if(m_pGraphEditorMgr->graphEditorView()->scene()->mouseGrabberItem()){
            m_SelectMode = Select;
        }
    }

}

void HGraphEditorSelectTool::onMouseMoveEvent(QMouseEvent* event, QVariant &data)
{
    if(!event || !m_pGraphEditorMgr || !m_pGraphEditorMgr->selectedMgr() || !m_pGraphEditorMgr->selectedMgr()->selectObj())
        return;
    m_ptStPoint = m_ptCurPoint;
    m_ptCurPoint = data.toPointF();
    if(event->buttons() == Qt::NoButton)
    {
        QPointF selPoint;
        //是否选择在四角或者中间
        m_nSelPointIndex = m_pGraphEditorMgr->selectedMgr()->isOnPoint(m_ptCurPoint,selPoint);
        if(m_nSelPointIndex < 0)
        {
            m_bIsSelectPoint = false;
            if(m_pGraphEditorMgr->selectedMgr()->isOnObj(m_ptCurPoint))
            {
                m_pGraphEditorMgr->graphEditorView()->setCursor(Qt::SizeAllCursor);
            }
            else
                m_pGraphEditorMgr->graphEditorView()->setCursor(cursor());
            m_SelectWidget->hide();
        }
        else
        {
            m_bIsSelectPoint = true;
            if(!m_SelectWidget->parent())
            {
                m_SelectWidget->setParent(m_pGraphEditorMgr->graphEditorView()->viewport());
            }
            m_SelectWidget->resize(6,6);
            QPoint pt = m_pGraphEditorMgr->graphEditorView()->mapFromScene(selPoint);
            m_SelectWidget->move(pt.x() - 6/2,pt.y() - 6/2);
            if(0)
            {

            }
            else
            {
                HDrawHelper* pDrawHelper = HDrawHelper::Instance();
                if(pDrawHelper)
                {
                    m_SelectWidget->setCursor(pDrawHelper->cursor(m_nSelPointIndex));
                }
            }
            m_SelectWidget->show();

            if(0)
            {

            }
            else
            {
                //保存原来的点
                m_vlOldPoints.clear();
                HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
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
            HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
            if(!tempContainer) return;
            if(!m_pGraphEditorMgr->graphEditorView()->scene()->mouseGrabberItem())
            {
                if(m_SelectMode == Select)
                    m_SelectMode = None;
            }
            else
                m_SelectMode = Select;


            if(Select == m_SelectMode)
            {
                double dx = m_ptCurPoint.x() - m_ptStPoint.x();
                double dy = m_ptCurPoint.y() - m_ptStPoint.y();
                tempContainer->moveBy(dx,dy);
            }
        }
    }
    else
    {
        if(event->buttons()&Qt::LeftButton)
        {
            HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
            if(!tempContainer) return;
            if(!tempContainer || tempContainer->getObjList().size() <= 0)
                return;
            if(0)
            {

            }
            else
            {
                HDrawHelper* pDrawHelper = HDrawHelper::Instance();
                if(pDrawHelper)
                {
                    pDrawHelper->movePoint(m_nSelPointIndex,m_ptCurPoint);
                }
            }
            m_pGraphEditorMgr->selectedMgr()->recalcSelect();
        }
    }
}

void HGraphEditorSelectTool::onMouseReleaseEvent(QMouseEvent* event, QVariant &data)
{
    if(!event || !m_pGraphEditorMgr || !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
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
            m_pGraphEditorMgr->selectedMgr()->recalcSelect();
            if(tempContainer)
            {
                QList<HBaseObj*> objs;
                QList<HPointFList> points;
                for(int i = 0; i < tempContainer->getObjList().size();i++)
                {
                    HBaseObj* pObj = tempContainer->getObjList().at(i);
                    if(pObj){
                        pObj->setModify(true);
                        objs.append(pObj);
                        points.append(pObj->getPointList(1));
                    }
                }

                HGraphResizeCommand* reizeCommand = new HGraphResizeCommand(m_pGraphEditorMgr,objs,m_vlOldPoints,points);
                m_pGraphEditorMgr->graphEditorStack()->push(reizeCommand);
            }
        }
    }
    else
    {
        if(None == m_SelectMode)
        {
            if(tempContainer && tempContainer->getObjList().size() > 0)
            {
                m_SelectMode = Select;
            }
        }
        else if(Select == m_SelectMode)
        {
            if(tempContainer && tempContainer->getObjList().count() == 0)
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
                    {
                        pObj->setModify(true);
                        objs.append(pObj);
                    }
                }
                double dx = m_ptCurPoint.x() - m_ptOriPoint.x();
                double dy = m_ptCurPoint.y() - m_ptOriPoint.y();
                if(qFuzzyCompare(dx,0) && qFuzzyCompare(dy,0))
                    return;
                HGraphMoveCommand* moveCommand = new HGraphMoveCommand(m_pGraphEditorMgr,objs,dx,dy);
                m_pGraphEditorMgr->graphEditorStack()->push(moveCommand);
            }
        }
    }
}

void HGraphEditorSelectTool::onMouseDoubleClickEvent(QMouseEvent* event, QVariant &data)
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
        return;
    m_pGraphEditorMgr->graphEditorOp()->setObjAttribute();
}

void HGraphEditorSelectTool::onContextMenuEvent(QContextMenuEvent *event, QVariant &data)
{
    if(!event || !m_pGraphEditorMgr || !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(!tempContainer || tempContainer->getObjList().size() == 0)
        return;
    QMenu menu;
    if(tempContainer->getObjList().size()>=1)
    {
        //menu.addAction(QIcon(":/images/cut.png"),QStringLiteral("剪切"),m_pIconEditorMgr->iconEditorOp(),SLOT(cut()));
        //menu.addAction(QIcon(":/images/copy.png"),QStringLiteral("复制"),m_pIconEditorMgr->iconEditorOp(),SLOT(copy()));
        //menu.addAction(QIcon(":/images/del.png"),QStringLiteral("删除"),m_pIconEditorMgr->iconEditorOp(),SLOT(del()));
        //menu.addAction(QIcon(":/images/attribute.png"),QStringLiteral("属性"),m_pIconEditorMgr->iconEditorOp(),SLOT(setObjAttribute()));
    }
    if(m_pGraphEditorMgr->graphEditorOp()->isClipboardAvailable())
    {
        //menu.addAction(QIcon(":/images/paste.png"),QStringLiteral("粘贴"),m_pIconEditorMgr->iconEditorOp(),SLOT(paste()));
    }
    menu.exec(event->globalPos());
}

void HGraphEditorSelectTool::onKeyPressEvent(QKeyEvent *event, QVariant& data)
{
    if(!event || !m_pGraphEditorMgr || !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
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
    QList<HBaseObj*> objs;
    if(tempContainer->getObjList().size() == 1)
    {
        HBaseObj* pObj = tempContainer->getObjList().at(0);
        if(pObj)
        {
            pObj->setModify(true);
            pObj->moveBy(ndx,ndy);
            pObj->iconGraphicsItem()->setPos(pObj->pos(1));
            objs.append(pObj);
        }
    }
    else
    {
        tempContainer->moveBy(ndx,ndy);
        for(int i = 0; i < tempContainer->getObjList().size();i++)
        {
            HBaseObj* pObj = tempContainer->getObjList().at(i);
            if(pObj)
            {
                pObj->setModify(true);
                pObj->moveBy(ndx,ndy);
                pObj->iconGraphicsItem()->setPos(pObj->pos(1));
                objs.append(pObj);
            }
        }

    }
    HGraphMoveCommand* moveCommand = new HGraphMoveCommand(m_pGraphEditorMgr,objs,ndx,ndy);
    m_pGraphEditorMgr->graphEditorStack()->push(moveCommand);
}

QCursor HGraphEditorSelectTool::cursor()
{
    return QCursor();
}

void HGraphEditorSelectTool::onSelectChanged()
{

}
