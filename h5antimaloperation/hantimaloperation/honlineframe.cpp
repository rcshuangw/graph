#include "honlineframe.h"
#include <QSplitter>
#include <QToolBar>
#include <QDockWidget>
#include <QEvent>
#include <QMouseEvent>
#include "hgraphframe.h"
#include "hgraphtreewidget.h"
#include "hgraphview.h"
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
    m_actOpen = new QAction(QIcon(":/images/open.png"),QStringLiteral("Open"));
    m_actPrint = new QAction(QIcon(":/images/print.png"),QStringLiteral("Print"));
    bar->addAction(m_actOpen);
    bar->addAction(m_actPrint);
    bar->addSeparator();
    m_actZoomIn = new QAction(QIcon(":/images/zoom_in.png"),QStringLiteral("Print"));
    m_actZoomOut = new QAction(QIcon(":/images/zoom_out.png"),QStringLiteral("Print"));
    m_actZoom = new QAction(QIcon(":/images/zoom.png"),QStringLiteral("Print"));
    bar->addAction(m_actZoomIn);
    bar->addAction(m_actZoomOut);
    bar->addAction(m_actZoom);
    bar->addSeparator();
    m_actSelect = new QAction(QIcon(":/images/select.png"),QStringLiteral("Select"));
    m_actHand = new QAction(QIcon(":/images/hand_select.png"),QStringLiteral("Hand"));
    bar->addAction(m_actSelect);
    bar->addAction(m_actHand);

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
    m_pGraphFrame = new HGraphFrame(m_pAntiMalpoMgr);
    m_pSplitter->addWidget(m_pGraphFrame);
    //创建信号

    m_pSplitter->setStretchFactor(0,3);
    m_pSplitter->setStretchFactor(1,7);
    centerLayout->addWidget(m_pSplitter);
}

bool HOnlineFrame::eventFilter(QObject *obj, QEvent *event)
{
    QEvent::Type type = event->type();
    switch(type)
    {
    case QEvent::MouseButtonPress:
        return onMousePressEvent(obj,event);
        break;
    }
    return false;
}

bool HOnlineFrame::onMousePressEvent(QObject *obj, QEvent *event)
{
    if(m_actHand->isChecked())
        return false;
    if(obj != m_pGraphFrame->m_pGraphView->viewport())
        return false;
    QMouseEvent* e = static_cast<QMouseEvent*>(event);
    if(e->buttons()& Qt::LeftButton)
    {
        //处理手型
        //处理牌函数

        //获取对象
        //处理对象的按下操作
        m_pGraphFrame->onMousePressEvent(obj,event);
    }
    return false;
}
