#include "hsystool.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QToolButton>
#include <QPushButton>
#include <QMenu>
#include "hclock.h"
HSysTool::HSysTool(QWidget* parent) :
    QFrame(parent,Qt::FramelessWindowHint|Qt::X11BypassWindowManagerHint|Qt::WindowStaysOnTopHint)
{
    //int win_width = QApplication::desktop()->screenGeometry(-1).width();		//屏幕宽度
    m_nWidth = 100;																	//工具条宽度，与屏幕等宽
    //int win_height= QApplication::desktop()->screenGeometry(-1).height();		//屏幕高度
    m_nHeight = 36;
    setStyleSheet("background-color:black;");//#1D5D91
    m_pStartBtn = new QToolButton(this);
    m_pOnlineBtn = new QPushButton(this);
    m_pPreviewBtn = new QPushButton(this);
    m_pTypicalBtn = new QPushButton(this);

    m_pClock = new HClock(this);
}

HSysTool::~HSysTool()
{
    if(m_pClock)
        delete m_pClock;
}

void HSysTool::init()
{
    int nX,nY;
    nX = 0;
    nY = win_height - m_nHeight;
    setGeometry(nX,nY,win_width,m_nHeight);
    setLineWidth(1);
    setMidLineWidth(0);
    setFrameShape(QFrame::Box);
    setFrameShadow(QFrame::Sunken);

    m_pStartBtn->setGeometry(QRect(2,3,40,m_nHeight-5));
    m_pStartBtn->setIconSize(QSize(24,24));
    m_pStartBtn->setIcon(QIcon(":/images/start2.png"));
    //m_pStartBtn->setStyleSheet("background-color: transparent;color: #0000FF;");
    m_pStartBtn->setArrowType(Qt::NoArrow);
    m_pStartBtn->setCursor(QCursor(Qt::PointingHandCursor));
    m_pStartBtn->setToolTip(tr("Start"));
    m_pStartBtn->setStyleSheet("\
        QToolButton::menu-indicator{\
        image: none;\
    }");

    m_pStartBtn->setPopupMode(QToolButton::InstantPopup);
    createMenu();

    int left_start = m_pStartBtn->width();
    QString strBtnSheet = "QPushButton {border: 1px solid #555;padding: 4px;min-width: 65px;min-height: 12px;} \
            QPushButton{background-color: transparent;border-style: outset;border-width:1px; \
            border-radius:3px;border-color: beige;font: bold 18px;padding:1px;color: #FFFFFF;} \
            #QPushButton:hover {background-color: #999;}  \
            QPushButton:pressed { background-color: #676767;} \
            QPushButton:disabled {color: #333333;}";
    left_start += 10;
    m_pOnlineBtn->setGeometry(QRect(left_start,3,100,m_nHeight-5));
    m_pOnlineBtn->setText(QStringLiteral("主接线图"));
    m_pOnlineBtn->setToolTip("online");
    m_pOnlineBtn->setStyleSheet(strBtnSheet);

    left_start += m_pOnlineBtn->width();
    left_start += 4;
    m_pPreviewBtn->setGeometry(QRect(left_start,3,100,m_nHeight-5));
    m_pPreviewBtn->setText(QStringLiteral("操作票预演"));
    m_pPreviewBtn->setToolTip("preview");
    m_pPreviewBtn->setStyleSheet(strBtnSheet);

    left_start += m_pPreviewBtn->width();
    left_start += 4;
    m_pTypicalBtn->setGeometry(QRect(left_start,3,100,m_nHeight-5));
    m_pTypicalBtn->setText(QStringLiteral("典型票编辑"));
    m_pTypicalBtn->setToolTip("preview");
    m_pTypicalBtn->setStyleSheet(strBtnSheet);

    //

    m_pClock->setGeometry(QRect(win_width-200,3,140,m_nHeight-5));
    m_pClock->init();
}

void HSysTool::createMenu()
{
    QString strMenu = "QMenu { background-color: white; border: 1px solid white;} \
        QMenu::item {background-color: transparent;padding:6px 12px;margin:0px 8px;border-bottom:1px solid #DBDBDB;} \
        QMenu::item:selected { background-color: #2dabf9;}";

    QMenu* menu = new QMenu();
    QMenu* funMenu = menu->addMenu(QStringLiteral("功能应用"));
    QMenu* confMenu = menu->addMenu(QStringLiteral("配置工具"));
    QMenu* connMenu = menu->addMenu(QStringLiteral("网络监视"));
    menu->setStyleSheet(strMenu);
    funMenu->addAction(QStringLiteral("管理工作票"));
    funMenu->addAction(QStringLiteral("管理操作票"));
    funMenu->addAction(QStringLiteral("打印设置"));
    confMenu->addAction(QStringLiteral("数据库编辑"));
    confMenu->addAction(QStringLiteral("画面编辑"));
    confMenu->addAction(QStringLiteral("权限编辑"));
    confMenu->addAction(QStringLiteral("系统设置"));
    connMenu->addAction(QStringLiteral("电脑钥匙报文监视"));
    connMenu->addAction(QStringLiteral("网络通讯报文监视"));
    connMenu->addAction(QStringLiteral("插件通讯报文监视"));
    //menu->addSeparator();
    menu->addAction(QStringLiteral("显示任务栏"));
    menu->addAction(QStringLiteral("隐藏任务栏"));

    //menu->addSeparator();
    menu->addAction(QStringLiteral("退出"));

    m_pStartBtn->setMenu(menu);
}
