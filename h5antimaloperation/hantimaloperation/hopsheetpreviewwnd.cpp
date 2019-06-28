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


}

bool HOpSheetPreviewWnd::eventFilter(QObject *watched, QEvent *event)
{
    //创建右键菜单

    if(watched == m_sheetStepTable)
    {
        if(event->type() == QEvent::ContextMenu)
        {
            QMouseEvent* e = static_cast<QMouseEvent*>(event);
            procContextMenu(e);
        }
    }
    return false;
}

void HOpSheetPreviewWnd::procContextMenu(QMouseEvent *event)
{
    QPointF pt = event->pos();

    QMenu* menu = new QMenu;
    QAction* editStepAct = new QAction(QStringLiteral("预演增加一步"));
    QAction* delStepAct = new QAction(QStringLiteral("预演删除一步"));
    menu->addAction(editStepAct);
    menu->addAction(delStepAct);
    menu->popup(pt);
}

//画面传递过来操作票步骤
void HOpSheetPreviewWnd::onOpeartorStepChanged(int nType,OPERATORSHEETSTEP*& step)
{

}
