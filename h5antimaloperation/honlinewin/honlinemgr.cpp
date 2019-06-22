#include "honlinemgr.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QScrollBar>
#include "honlineview.h"
#include "honlinescene.h"
#include "honlinedoc.h"

#include "hgraph.h"
HOnlineMgr::HOnlineMgr(QObject *parent) : QObject(parent),m_logicRectF(-500,-500,1000,1000)
{
    m_pOnlineDoc = new HOnlineDoc(this);
    Q_ASSERT(m_pOnlineDoc);

    m_pOnlineOp = new HOnlineOp(this);
    m_pSelectedMgr = new HSelectedMgr;

    m_pOnlineScene = new HOnlineScene(this);
    m_pOnlineView = NULL;

    int width = qApp->desktop()->screen()->width();
    int height = qApp->desktop()->screen()->height();
    m_logicRectF.setX(0-(width-2)/2);
    m_logicRectF.setY(0-(height-100)/2);
    m_logicRectF.setWidth(width-2);
    m_logicRectF.setHeight(height-100);
}

HOnlineScene* HOnlineMgr::onlineScene()
{

}

HOnlineView* HOnlineMgr::onlineView()
{

}

HOnlineDoc* HOnlineMgr::onlineDoc()
{

}

HOnlineOp* HOnlineMgr::onlineOp()
{

}

HSelectedMgr* HOnlineMgr::selectedMgr()
{

}

void HOnlineMgr::setGraphEditorView(HOnlineView* view)
{
    if(view)
    {
        m_pOnlineView = view;
        m_pOnlineView->setScene(m_pOnlineScene);
        m_pOnlineScene->setView(m_pOnlineView);
        QRectF rectF(m_logicRectF);
        m_pOnlineScene->setSceneRect(rectF);

        QScrollBar* pBar = m_pOnlineView->horizontalScrollBar();
        if(pBar && pBar->isHidden() == false)
        {
            pBar->setSliderPosition(pBar->minimum());
        }
        pBar = m_pOnlineView->verticalScrollBar();
        if(pBar && pBar->isHidden() == false)
        {
            pBar->setSliderPosition(pBar->minimum());
        }

        if(m_pOnlineDoc->getCurGraph())
        {
           m_pOnlineDoc->getCurGraph()->m_width = m_logicRectF.width();
           m_pOnlineDoc->getCurGraph()->m_height = m_logicRectF.height();
        }
    }
}

void HOnlineMgr::loadGraphs()
{
    if(!m_pOnlineDoc)
        return;
    m_pOnlineDoc->loadAllGraph();
}

bool HOnlineMgr::Open(const QString& graphName,int id)
{
    if(!m_pOnlineDoc)
        return false;
    if(!m_pOnlineDoc->openGraph(graphName,id))
        return false;

    int width = m_pOnlineDoc->getCurGraph()->m_width;
    int height = m_pOnlineDoc->getCurGraph()->m_height;
    QRectF newLogicRectF = QRectF(QPointF(0-width/2,0-height/2),QSizeF(width,height));
    if(!m_pOnlineScene || !m_pOnlineView)
        return;
    m_pOnlineScene->setSceneRect(newLogicRectF);
    if(m_pOnlineView)
    {
        QScrollBar* pBar = m_pOnlineView->horizontalScrollBar();
        if(pBar && pBar->isHidden() == false)
        {
            pBar->setSliderPosition(pBar->minimum());
        }
        pBar = m_pOnlineView->verticalScrollBar();
        if(pBar && pBar->isHidden() == false)
        {
            pBar->setSliderPosition(pBar->minimum());
        }
    }
    refreshView();


    if(!m_pOnlineDoc->getCurGraph())
        return false;
    for(int i = 0; i < m_pOnlineDoc->getCurGraph()->size();i++)
    {
        HBaseObj* obj = (HBaseObj*)m_pOnlineDoc->getCurGraph()->at(i);
        m_pOnlineScene->onCreateObj(obj);
    }
}

void HOnlineMgr::reset()
{
    m_pSelectedMgr->clear();
    for(int i = 0; i < m_pOnlineScene->views().count();i++)
        m_pOnlineScene->views().at(i)->setScene(0);

    delete m_pOnlineScene;
    m_pOnlineScene = NULL;
    m_pOnlineScene =  new HOnlineScene(this);

    //初始化scene
    setGraphEditorView(m_pOnlineView);
}

void HOnlineMgr::setLogicRect(const QRectF& rect)
{
    m_logicRectF = rect;
}

QRectF HOnlineMgr::getLogicRect()
{
    return m_logicRectF;
}

void HOnlineMgr::refreshView()
{

}