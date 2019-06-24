#include "hgraphframe.h"
#include "hgraphview.h"
#include "hantimalopmgr.h"
HGraphFrame::HGraphFrame(HAntiMalopMgr* mgr,HFrame *parent) :
    m_pAntiMalpoMgr(mgr),HFrame(parent)
{
    //设置左右比例
    //ui->splitter->setStretchFactor(0,3);
    //ui->splitter->setStretchFactor(1,7);
    initGraphFrame();
}

HGraphFrame::~HGraphFrame()
{
}

void HGraphFrame::initGraphFrame()
{
    //m_pGraphView = new HGraphView(ui->widget);
    //m_pGraphView->setResizeAnchor(QGraphicsView::AnchorViewCenter);
}

bool HGraphFrame::eventFilter(QObject *obj, QEvent *event)
{
    return false;
}
