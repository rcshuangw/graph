#include "hiconeditorframe.h"
#include <QVBoxLayout>
#include <QByteArray>
#include <QDataStream>
#include <QProcessEnvironment>
#include "hiconeditorscene.h"
#include "hiconeditormgr.h"
#include "hicondrawtoolmanager.h"
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

    }

    HIconEditorScene* scene = (HIconEditorScene*)m_pView->scene();
    scene->addItem(item);
    connect(item,SIGNAL(objSelectChanged(HBaseObj*,bool)),this,SLOT(objSelectChanged(HBaseObj*,bool)));
    connect(item,SIGNAL(recalcSelect()),this,SLOT(recalcSelect()));

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
        disconnect(item,SIGNAL(objSelectChanged(HBaseObj*,bool)),this,SLOT(objSelectChanged(HBaseObj*,bool)));
        disconnect(item,SIGNAL(recalcSelect()),this,SLOT(recalcSelect()));
    }
}

void HIconEditorFrame::objSelectChanged(HBaseObj *obj, bool isSelected)
{
    if(!m_pIconEditorMgr)
        return;
    //选择selectManager
    //m_pEditMgr->m_pSelectionMgr->SelectChanged(obj,isSelected);
    //m_pEditMgr->m_pSelectionMgr->RecalcSelect();
}

void HIconEditorFrame::recalcSelect()
{
	if (!m_pIconEditorMgr && !m_pIconEditorMgr->iconEditorOp())
		return;
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
