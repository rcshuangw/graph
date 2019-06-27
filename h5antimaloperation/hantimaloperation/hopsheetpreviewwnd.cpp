#include "hopsheetpreviewwnd.h"
#include "hopsheetbasewnd.h"
#include <QWidget>
#include <QToolBar>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QEvent>
#include <QMenu>
#include <QTableWidgetItem>
#include <QHeaderView>
HOpSheetPreviewWnd::HOpSheetPreviewWnd(QWidget *parent):HOpSheetBaseWnd(0,parent)
{
    createActions();
}

void HOpSheetPreviewWnd::createActions()
{
    //QToolBar* bar = new QToolBar(this);
    //bar->setIconSize(QSize(32,32));
    m_fileOpenAct = new QAction(QIcon(":/images/FileOpen.png"),QStringLiteral("打开操作票"));
    m_fileSaveAct = new QAction(QIcon(":/images/FileSave.png"),QStringLiteral("关闭操作票"));
    m_filePrintAct = new QAction(QIcon(":/images/FilePrint.png"),QStringLiteral("打印操作票"));
    m_toExecuteAct = new QAction(QIcon(":/images/ToExecute.png"),QStringLiteral("转预演/执行操作票"));
    m_fileAbolishAct = new QAction(QIcon(":/images/Abolish.png"),QStringLiteral("作废操作票"));
    m_fileCloseAct = new QAction(QIcon(":/images/FileClose.png"),QStringLiteral("关闭操作票"));
    m_toolBar->addAction(m_fileOpenAct);
    m_toolBar->addAction(m_fileSaveAct);
    m_toolBar->addAction(m_filePrintAct);
    m_toolBar->addAction(m_toExecuteAct);
    m_toolBar->addAction(m_fileAbolishAct);
    m_toolBar->addAction(m_fileCloseAct);

    //创建Table内容

    m_sheetStepTable->setColumnCount(4);
    QTableWidgetItem *item = new QTableWidgetItem();
    m_sheetStepTable->setHorizontalHeaderItem(0, item);
    item->setText(QStringLiteral("步骤"));
    QTableWidgetItem *item1 = new QTableWidgetItem();
    m_sheetStepTable->setHorizontalHeaderItem(1, item1);
    item1->setText(QStringLiteral("操作内容"));
    QTableWidgetItem *item2 = new QTableWidgetItem();
    m_sheetStepTable->setHorizontalHeaderItem(2, item2);
    item2->setText(QStringLiteral("操作时间"));
    QTableWidgetItem *item3 = new QTableWidgetItem();
    m_sheetStepTable->setHorizontalHeaderItem(3, item3);
    item3->setText(QStringLiteral("备注"));


    m_sheetStepTable->setColumnWidth(0,60);
   /* m_sheetStepTable->setColumnWidth(1,600);*/
    m_sheetStepTable->setColumnWidth(2,150);
    m_sheetStepTable->setColumnWidth(3,100);
    m_sheetStepTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    m_sheetStepTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    m_sheetStepTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    m_sheetStepTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
   // m_sheetStepTable->horizontalHeader()->setStretchLastSection(true);//
    m_sheetStepTable->setObjectName(QStringLiteral("sheetStepTable"));
}

bool HOpSheetPreviewWnd::eventFilter(QObject *watched, QEvent *event)
{
    /*
    if(watched == m_sheetStepTable)
    {
        if(event->type() == QEvent::ContextMenu)
        {

        }
    }*/
    return false;
}

void HOpSheetPreviewWnd::procContextMenu(QMouseEvent *event)
{
    QPointF pt = event->pos();

    QMenu* menu = new QMenu;
    //QAction*
}
