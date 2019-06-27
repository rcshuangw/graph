#include "hopsheetrunwidget.h"
//左:浏览框、预演框、执行框
//右:previewgraphframe 预演画面
#include <QSplitter>
#include <QTabWidget>
#include <QToolBar>
#include <QTabBar>
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
    QString strTabSheet = " QTabBar {background-color: #C2C7CB; }\
            QTabBar::tab {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, \
                     stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3); \
             border: 1px solid darkkhaki; border-bottom-color: #C2C7CB; border-top-left-radius: 4px;\
             border-top-right-radius: 4px; min-width: 8ex;padding: 2px;} \
             QTabBar::tab:hover { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, \
             stop: 0 #fafafa, stop: 0.4 #f4f4f4,stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);} \
             QTabBar::tab:selected {border-color: #9B9B9B;border-bottom-color: #C2C7CB;} \
             QTabBar::tab:!selected {margin-top: 2px; }";
    QString strTabWidgetSheet = "QTabWidget::pane { border-top: 2px solid #C2C7CB;}QTabWidget::tab-bar {left: 5px;}";
    m_pRunWndTab = new QTabWidget(this);
    m_pOpSheetPreviewWnd = new HOpSheetPreviewWnd;
    QFont font;
    font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));//宋体
    font.setPointSize(12);
    font.setBold(true);
    m_pRunWndTab->addTab(m_pOpSheetPreviewWnd,QStringLiteral("预演窗"));
    m_pRunWndTab->setFont(font);
    m_pRunWndTab->tabBar()->setStyleSheet(strTabSheet);
    m_pRunWndTab->setStyleSheet(strTabWidgetSheet);
    splitter->addWidget(m_pRunWndTab);

    //right
    //右边
    QWidget* widget = new QWidget(this);
    QVBoxLayout* rightLayout = new QVBoxLayout(widget);
    rightLayout->setContentsMargins(0,0,0,0);
    rightLayout->setSpacing(0);
    QToolBar* toolBar = new QToolBar(widget);
    toolBar->setIconSize(QSize(32,32));
    rightLayout->addWidget(toolBar);
    QAction* startPreview = new QAction(QIcon(":/images/preview_start.png"),QStringLiteral("开始预演"));
    QAction* stopPreview = new QAction(QIcon(":/images/preview_stop.png"),QStringLiteral("结束预演"));
    QAction* cancelPreview = new QAction(QIcon(":/images/preview_cancel.png"),QStringLiteral("取消预演"));
    toolBar->addAction(startPreview);
    toolBar->addAction(stopPreview);
    toolBar->addAction(cancelPreview);
    rightLayout->addWidget(toolBar);

    QString strToolBarSheet = "QToolBar { \
                              background-color: #C2C7CB;}border-width: 2px;border-color: darkkhaki; \
                              QToolButton {border:1px solid yellow; }";
    toolBar->setStyleSheet(strToolBarSheet);

    m_pPreviewGraphFrame = new HPreviewGraphFrame(0,m_pAntiMalpoMgr);
    rightLayout->addWidget(m_pPreviewGraphFrame);
    splitter->addWidget(widget);


    splitter->setStretchFactor(0,2);
    splitter->setStretchFactor(1,8);
    centerLayout->addWidget(splitter);
}

void HOpSheetRunWidget::createActions()
{
    //画面传递操作票信息
    connect(m_pPreviewGraphFrame,SIGNAL(opeartorStepChanged(int,OPERATORSHEETSTEP*&)),m_pOpSheetPreviewWnd,SLOT(onOpeartorStepChanged(int,OPERATORSHEETSTEP*&)));
}
