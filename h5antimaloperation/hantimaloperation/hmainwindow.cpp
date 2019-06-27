#include "hmainwindow.h"
//#include "ui_mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include "honlineframe.h"
#include "hopsheetrunwidget.h"
#include "hantimalopmgr.h"
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)//,
   // ui(new Ui::MainWindow)
{    
    int win_width = QApplication::desktop()->screenGeometry(-1).width();		//屏幕宽度
    resize(win_width,600);
    int win_height= height();//QApplication::desktop()->screenGeometry(-1).height();

    HAntiMalopMgr* mgr = new HAntiMalopMgr;
    m_pSysTool = new HSysTool(this);
    m_pSysTool->win_width = win_width;
    m_pSysTool->win_height = win_height;
    m_pSysTool->init();
    m_pClient = new HClient(this);
    m_pClient->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_pClient->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    //setCentralWidget(m_pClient);

    setWindowTitle(tr("MDI"));
    //setUnifiedTitleAndToolBarOnMac(true);
    m_pClient->setGeometry(0,0,win_width,win_height - m_pSysTool->m_nHeight);

   // HOnlineFrame* frame = new HOnlineFrame(mgr);
    //m_pClient->addSubWindow(frame);

    HOpSheetRunWidget* runWidget = new HOpSheetRunWidget(mgr);
    m_pClient->addSubWindow(runWidget);
    runWidget->showMaximized();
}

MainWindow::~MainWindow()
{
    if(m_pClient)
        delete m_pClient;
    if(m_pSysTool)
        delete m_pSysTool;
}
