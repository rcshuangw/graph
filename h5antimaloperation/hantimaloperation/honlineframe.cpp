#include "honlineframe.h"
#include <QSplitter>
#include <QToolBar>
#include <QDockWidget>
#include "hgraphframe.h"
#include "hgraphtreewidget.h"
HOnlineFrame::HOnlineFrame(HAntiMalopMgr *mgr,HFrame* parent)
    :m_pAntiMalpoMgr(mgr),HFrame(parent)
{
    crateToolBar();
    initOnlineFrame();
}

HOnlineFrame::~HOnlineFrame()
{

}

void HOnlineFrame::crateToolBar()
{
    QToolBar* bar = new QToolBar(this);
    QAction* actOpen = new QAction(QIcon(":/images/open.png"),QStringLiteral("Open"));
    QAction* actPrint = new QAction(QIcon(":/images/print.png"),QStringLiteral("Print"));
    bar->addAction(actOpen);
    bar->addAction(actPrint);
    bar->addSeparator();
    QAction* actZoomIn = new QAction(QIcon(":/images/zoom_in.png"),QStringLiteral("Print"));
    QAction* actZoomOut = new QAction(QIcon(":/images/zoom_out.png"),QStringLiteral("Print"));
    QAction* actZoom = new QAction(QIcon(":/images/zoom.png"),QStringLiteral("Print"));
    bar->addAction(actZoomIn);
    bar->addAction(actZoomOut);
    bar->addAction(actZoom);
    bar->addSeparator();
    QAction* actSelect = new QAction(QIcon(":/images/select.png"),QStringLiteral("Select"));
    QAction* actHand = new QAction(QIcon(":/images/hand_select.png"),QStringLiteral("Hand"));
    bar->addAction(actSelect);
    bar->addAction(actHand);

    QHBoxLayout* boxLayout = new QHBoxLayout;
    boxLayout->setContentsMargins(6,2,6,2);
    boxLayout->addWidget(bar);
    centerLayout->addLayout(boxLayout);
}

void HOnlineFrame::initOnlineFrame()
{
    m_pSplitter = new QSplitter(this);
    QDockWidget* dock = new QDockWidget(this);
    m_pGraphTreeWidget = new HGraphTreeWidget(m_pAntiMalpoMgr);
    dock->setWidget(m_pGraphTreeWidget);
    m_pSplitter->addWidget(dock);
    //创建信号

    //右边
    HGraphFrame* graphFrame = new HGraphFrame(m_pAntiMalpoMgr);
    m_pSplitter->addWidget(graphFrame);
    //创建信号

    m_pSplitter->setStretchFactor(0,3);
    m_pSplitter->setStretchFactor(1,7);
    centerLayout->addWidget(m_pSplitter);
}
