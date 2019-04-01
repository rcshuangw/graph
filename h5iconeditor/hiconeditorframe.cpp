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

HIconEditorFrame::HIconEditorFrame(HIconMgr* pMgr,QWidget * parent, Qt::WindowFlags f)
:m_pIconEditorMgr(pMgr),HFrame(parent,f)
{
    m_pView->setScene(new HIconScene(m_pIconEditorMgr));
}

HIconEditorFrame::~HIconEditorFrame()
{

}

void HIconEditorFrame::setIconMgr(HIconMgr *iconmgr)
{
    m_pIconEditorMgr = iconmgr;
}

void HIconEditorFrame::setLogicRect(QRectF &rectF)
{
    if(rectF == m_sceneRect)
        return;
    m_sceneRect = rectF;
    if(m_pView)
    {
        m_pView->setSceneRect(rectF);
        int f_width = width();
        int f_height = height();
        resize(f_width-1,f_height);
        resize(f_width,f_height);
    }
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
    item->setZValue(obj->getStackOrder());

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
    if(obj && obj->getIconGraphicsItem())
    {
        H5GraphicsItem* item = (H5GraphicsItem*)obj->getIconGraphicsItem();
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

}

QRectF HIconEditorFrame::getLogicRect()
{
    return m_sceneRect;
}

HIconScene* HIconEditorFrame::getIconScene()
{
    if(m_pView)
        return (HIconScene*)m_pView->scene();
    return NULL;
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

void HIconEditorFrame::setItemVisible(int nPatternId)
{
    HIconScene* pIconScene = getIconScene();
    if(!m_pIconMgr && !pIconScene)
        return;
    pIconScene->setItemVisible(nPatternId);
}

//粘贴
HIconGraphicsItem* HIconEditorFrame::addItemByIconObj(HBaseObj* pObj)
{
    HIconScene* pIconScene = getIconScene();
    if(!m_pIconMgr && !pIconScene)
        return NULL;
    return pIconScene->addItemByIconObj(pObj);
}

//切换nPattern
void HIconEditorFrame::refreshSceneByPatternId(int nPatternId)
{
    HIconScene* pIconScene = getIconScene();
    if(!m_pIconMgr && !pIconScene)
        return;
    pIconScene->refreshItemByPatternId(nPatternId);

}

void HIconEditorFrame::clearSceneByPatternId(int nPatternId)
{
    HIconScene* pIconScene = getIconScene();
    if(!m_pIconMgr && !pIconScene)
        return;
    pIconScene->clearItemByPatternId(nPatternId);
}

HIconGraphicsItem* HIconEditorFrame::getIconGraphicsItemByObj(HBaseObj *pObj)
{
    if(!pObj || !getIconScene()) return NULL;
    QList<QGraphicsItem*> items = getIconScene()->items();
    foreach (QGraphicsItem *item1, items)
    {
        HIconGraphicsItem* item = qgraphicsitem_cast<HIconGraphicsItem*>(item1);
        if(!item) continue;
        if(pObj->getShapeType() != item->type()) continue;
        HBaseObj* obj = item->getItemObj();
        if(obj->getObjID() == pObj->getObjID())
            return item;
    }
    return NULL;
}






