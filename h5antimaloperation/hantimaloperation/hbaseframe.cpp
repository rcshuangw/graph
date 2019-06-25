#include "hbaseframe.h"
#include <QHBoxLayout>
#include "hantimalopmgr.h"
#include "hgraphview.h"
#include "hgraphscene.h"
HBaseFrame::HBaseFrame(HAntiMalopMgr *mgr,QScrollArea* parent):m_pAntiMalpoMgr(mgr),QScrollArea(parent)
{
    init();
}

HBaseFrame::~HBaseFrame()
{

}

void HBaseFrame::init()
{
    m_pGraphView = new HGraphView;
    m_pGraphView->setInteractive(false);
    m_pGraphView->setDragMode(QGraphicsView::NoDrag);

    m_pGraphScene = new HGraphScene(m_pAntiMalpoMgr);
    m_pGraphView->setScene(m_pGraphScene);
    m_pGraphView->setSceneRect(m_pAntiMalpoMgr->getLogicRect());

    QHBoxLayout* layout = new QHBoxLayout;
    layout->setContentsMargins(2,2,2,2);
    layout->addWidget(m_pGraphView);
    setLayout(layout);
}

void HBaseFrame::reset()
{
    if(m_pGraphScene){
        delete m_pGraphScene;
        m_pGraphScene = NULL;
    }
    m_pGraphScene = new HGraphScene(m_pAntiMalpoMgr);
    m_pGraphView->setScene(m_pGraphScene);
    m_pGraphView->setSceneRect(m_pAntiMalpoMgr->getLogicRect());
}
