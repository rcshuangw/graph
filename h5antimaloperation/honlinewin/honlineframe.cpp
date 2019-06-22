#include "honlineframe.h"
#include "ui_onlineframe.h"
#include "honlineview.h"
#include "honlinemgr.h"
HOnlineFrame::HOnlineFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::onlineframe)
{
    ui->setupUi(this);
    //设置左右比例
    ui->splitter->setStretchFactor(0,3);
    ui->splitter->setStretchFactor(1,7);
    initOnlineFrame();
}

HOnlineFrame::~HOnlineFrame()
{
    delete ui;
}

void HOnlineFrame::initOnlineFrame()
{
    m_pOnlineView = new HOnlineView(ui->widget);
    m_pOnlineView->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    m_pOnlineMgr = new HOnlineMgr;
    m_pOnlineMgr->setGraphEditorView(m_pOnlineView);
    m_pOnlineView->setOnlineMgr(m_pOnlineMgr);
}

bool HOnlineFrame::eventFilter(QObject *obj, QEvent *event)
{

}
