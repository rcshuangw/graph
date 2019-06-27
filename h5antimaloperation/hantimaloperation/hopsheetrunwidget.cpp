#include "hopsheetrunwidget.h"
//左:浏览框、预演框、执行框
//右:previewgraphframe 预演画面
#include <QSplitter>
#include <QTabWidget>
#include "hantimalopmgr.h"
#include "hopsheetpreviewwnd.h"
#include "hpreviewgraphframe.h"
HOpSheetRunWidget::HOpSheetRunWidget(HAntiMalopMgr *mgr,HFrame* parent) : m_pAntiMalpoMgr(mgr) ,HFrame(parent)
{
    createOpSheetRunWidget();
}

HOpSheetRunWidget::~HOpSheetRunWidget()
{

}

void HOpSheetRunWidget::createOpSheetRunWidget()
{
    QSplitter *splitter = new QSplitter(this);

    //left
    m_pRunWndTab = new QTabWidget(this);
    m_pOpSheetPreviewWnd = new HOpSheetPreviewWnd;
    m_pRunWndTab->addTab(m_pOpSheetPreviewWnd,QStringLiteral("预演窗"));
    splitter->addWidget(m_pRunWndTab);

    //right
    m_pPreviewGraphFrame = new HPreviewGraphFrame(0,m_pAntiMalpoMgr);
    splitter->addWidget(m_pPreviewGraphFrame);


    splitter->setStretchFactor(0,3);
    splitter->setStretchFactor(1,7);
    centerLayout->addWidget(splitter);
}
