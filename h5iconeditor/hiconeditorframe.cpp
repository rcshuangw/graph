#include "hiconeditorframe.h"
#include <QVBoxLayout>
#include <QByteArray>
#include <QDataStream>
#include <QProcessEnvironment>
#include "hiconeditorscene.h"
#include "hiconeditormgr.h"
#include "hiconeditordrawtoolmgr.h"
#include "hiconeditorselecttool.h"
#include "hiconeditorop.h"
#include "hselectedmgr.h"
HIconEditorFrame::HIconEditorFrame(QWidget * parent, Qt::WindowFlags f )
    :HFrame(parent,f)
{
    m_pIconEditorMgr = NULL;
    m_pView->setInteractive(false);
    m_pView->setDragMode(QGraphicsView::NoDrag);
}

HIconEditorFrame::HIconEditorFrame(HIconEditorMgr* pMgr,QWidget * parent, Qt::WindowFlags f)
:m_pIconEditorMgr(pMgr),HFrame(parent,f)
{
	m_pView->setInteractive(false);
	m_pView->setDragMode(QGraphicsView::NoDrag);

    m_pView->setScene(new HIconEditorScene(m_pIconEditorMgr));
	m_pView->setSceneRect(m_pIconEditorMgr->getLogicRect());
	m_pIconEditorMgr->setIconEditorFrame(this);
}

HIconEditorFrame::~HIconEditorFrame()
{

}

void HIconEditorFrame::drawPath(const QList<Path>& pathList)
{
    if(!m_pView || !m_pView->scene())
        return;
    HIconEditorScene* scene = (HIconEditorScene*)m_pView->scene();

    QList<Path> list;
    for(int i = 0; i< pathList.count();i++)
    {
        Path path = (Path)pathList.at(i);
        if(path.coordType)
        {

        }
        list.append(path);
    }
    scene->drawPath(list);
}

void HIconEditorFrame::endDraw()
{
    if(!m_pView || !m_pView->scene())
        return;
    HIconEditorScene* scene = (HIconEditorScene*)m_pView->scene();
    scene->endDraw();
}

void HIconEditorFrame::objCreated(HBaseObj* obj,bool isPaste)
{
    if(!m_pView || !m_pView->scene())
        return;
    H5GraphicsItem *item = new H5GraphicsItem(obj);
    if(NULL == item) return;
    item->setZValue(obj->zValue());

    if(isPaste)
    {
        obj->setZValue(obj->zValue()+1);
        item->setZValue(obj->zValue());
    }

    HIconEditorScene* scene = (HIconEditorScene*)m_pView->scene();
    scene->addItem(item);
    connect(item,SIGNAL(objSelectChanged(HBaseObj*,bool)),this,SLOT(onObjSelectChanged(HBaseObj*,bool)));
    connect(item,SIGNAL(recalcSelect()),this,SLOT(onRecalcSelect()));

}

void HIconEditorFrame::objRemoved(HBaseObj* obj)
{
    if(!m_pView || !m_pView->scene())
        return;
    HIconEditorScene* scene = (HIconEditorScene*)m_pView->scene();
    if(obj && obj->iconGraphicsItem())
    {
        H5GraphicsItem* item = (H5GraphicsItem*)obj->iconGraphicsItem();
        scene->removeItem(item);
        item->setBaseObj(NULL);
        disconnect(item,SIGNAL(objSelectChanged(HBaseObj*,bool)),this,SLOT(onObjSelectChanged(HBaseObj*,bool)));
        disconnect(item,SIGNAL(recalcSelect()),this,SLOT(onRecalcSelect()));
    }
}

void HIconEditorFrame::onObjSelectChanged(HBaseObj *obj, bool isSelected)
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconEditorOp())
        return;
    m_pIconEditorMgr->iconEditorOp()->onSelectChanged(obj,isSelected);
}

void HIconEditorFrame::onRecalcSelect()
{
    if (!m_pIconEditorMgr && !m_pIconEditorMgr->selectedMgr())
		return;
    m_pIconEditorMgr->selectedMgr()->recalcSelect();
}

void HIconEditorFrame::refreshSelected(const QRectF& rect)
{
    if(!m_pView || !m_pView->scene())
        return;
    HIconEditorScene* scene = (HIconEditorScene*)m_pView->scene();
    if(rect.isNull())
    {
        scene->invalidate(scene->sceneRect(),QGraphicsScene::ForegroundLayer);
    }
    else
    {
        scene->invalidate(rect,QGraphicsScene::ForegroundLayer);
    }
}

void HIconEditorFrame::cursorChanged(const QCursor& cursor)
{
    if(m_pView)
    {
        m_pView->setCursor(cursor);
    }
}

bool HIconEditorFrame::eventFilter(QObject* obj,QEvent* event)
{
    HFrame::eventFilter(obj,event);
    if(obj == m_pView->viewport())
    {
        switch(((QMouseEvent*)event)->type())
        {
        case QEvent::MouseButtonDblClick:
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseMove:
        {
            if(!m_pIconEditorMgr || !m_pView)
                return false;

            QPointF pos = m_pView->mapToScene(((QMouseEvent*)event)->pos());
            HEvent hevent(event,QVariant(pos));
            if(m_pIconEditorMgr->iconEditorOp()->toolType() == ICON_DRAW_TOOL)
                m_pIconEditorMgr->iconEditorDrawToolMgr()->onEvent(hevent);
            else if(m_pIconEditorMgr->iconEditorOp()->toolType() == ICON_SELECT_TOOL)
                m_pIconEditorMgr->iconEditorSelectTool()->onEvent(hevent);

            if(event->type() == QEvent::MouseButtonRelease)
            {
                QMouseEvent* me = (QMouseEvent*)event;
                if(me->button() == Qt::RightButton)
                {
                    if(m_pIconEditorMgr->iconEditorOp()->toolType() == ICON_DRAW_TOOL)
                    {
                        m_pIconEditorMgr->iconEditorOp()->switchSelectTool();
                        return true;
                    }
                }
            }

            return false;
        }
        }
    }
    return false;
}

