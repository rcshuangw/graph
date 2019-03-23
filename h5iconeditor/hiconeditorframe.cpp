#include "hiconeditorframe.h"
#include <QVBoxLayout>
#include <QByteArray>
#include <QDataStream>
#include <QProcessEnvironment>
#include "hiconscene.h"
#include "hiconmgr.h"
#include "hiconstate.h"
#include "hicongraphicsitem.h"
#include "hiconcommand.h"

HIconEditorFrame::HIconEditorFrame(QWidget * parent, Qt::WindowFlags f )
    :HFrame(parent,f)
{
    m_pIconMgr = NULL;
    m_pView->setInteractive(false);
    m_pView->setDragMode(QGraphicsView::NoDrag);
}

HIconEditorFrame::HIconEditorFrame(HIconMgr* pMgr,QWidget * parent, Qt::WindowFlags f)
:m_pIconMgr(pMgr),HFrame(parent,f)
{
    m_pView->setScene(new HIconScene(m_pIconMgr));
}

HIconEditorFrame::~HIconEditorFrame()
{

}

void HIconEditorFrame::setIconMgr(HIconMgr *iconmgr)
{
    m_pIconMgr = iconmgr;
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

}

void HIconEditorFrame::cursorChanged(const QCursor& cursor)
{

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






