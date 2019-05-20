#include "hiconmainwindow.h"
#include <QMessageBox>
#include "hiconeditormgr.h"
#include "hiconeditordrawtoolmgr.h"
#include "hiconeditorframe.h"
#include "hiconeditorop.h"
#include "hselectedmgr.h"
#include "htempcontainer.h"
#include "hiconproperty.h"
//显示网格
void HIconMainWindow::showGrid()
{
    bool bcheck = showGridAct->isChecked();
    if(m_pIconEditorMgr && m_pIconEditorMgr->iconEditorFrame())
    {
        m_pIconEditorMgr->setShowGrid(bcheck);
        if(m_pIconEditorMgr->iconEditorFrame()->view())
            m_pIconEditorMgr->iconEditorFrame()->view()->resetCachedContent();

    }
}

//显示中心线
void HIconMainWindow::showCenterLine()
{
    bool bcheck = showCLineAct->isChecked();
    if(m_pIconEditorMgr && m_pIconEditorMgr->iconEditorFrame())
    {
        m_pIconEditorMgr->setShowCenterLine(bcheck);
        if(m_pIconEditorMgr->iconEditorFrame()->view())
            m_pIconEditorMgr->iconEditorFrame()->view()->resetCachedContent();

    }
}

//draw tool
void HIconMainWindow::drawTool()
{
    QAction* action = qobject_cast<QAction*>(sender());
    if(!action) return;
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconEditorOp())
        return;
    QVariant var = action->data();
    DrawShape shape = static_cast<DrawShape>(var.toInt());
    m_pIconEditorMgr->iconEditorOp()->drawTool(shape);
    if(m_pIconEditorMgr->iconEditorFrame()->view())
        m_pIconEditorMgr->iconEditorFrame()->view()->setInteractive(false);
}

void HIconMainWindow::selectTool()
{
    QAction* action = qobject_cast<QAction*>(sender());
    if(!action) return;
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconEditorOp())
        return;
    QVariant var = action->data();
    SelectMode mode = static_cast<SelectMode>(var.toInt());
    m_pIconEditorMgr->iconEditorOp()->selectTool(mode);
}

//撤销
void HIconMainWindow::undo()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconEditorUndoStack())
        return;
    m_pIconEditorMgr->iconEditorUndoStack()->undo();
    updateEditMenu();
}

//重做
void HIconMainWindow::redo()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconEditorUndoStack())
        return;
    m_pIconEditorMgr->iconEditorUndoStack()->redo();
    updateEditMenu();
}

//剪切
void HIconMainWindow::cut()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconEditorOp())
        return;
    m_pIconEditorMgr->iconEditorOp()->cut();

}

//复制
void HIconMainWindow::copy()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconEditorOp())
        return;
    m_pIconEditorMgr->iconEditorOp()->copy();

}

//粘贴
void HIconMainWindow::paste()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconEditorOp())
        return;
    m_pIconEditorMgr->iconEditorOp()->paste();

}

//删除
void HIconMainWindow::del()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconEditorOp())
        return;
    if(QMessageBox::Cancel == QMessageBox::information(NULL,QStringLiteral("警告"),QStringLiteral("确认删除该图符吗？"),QMessageBox::Ok|QMessageBox::Cancel))
        return;
    m_pIconEditorMgr->iconEditorOp()->del();
}

//合适宽度
void HIconMainWindow::fitWidth()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconEditorOp() || !m_pIconEditorMgr->iconEditorFrame())
        return;
    m_pIconEditorMgr->iconEditorOp()->fitWidth();
}

//合适高度
void HIconMainWindow::fitHeight()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconEditorOp() || !m_pIconEditorMgr->iconEditorFrame())
        return;
    m_pIconEditorMgr->iconEditorOp()->fitHeight();
}

void HIconMainWindow::zoomIn()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconEditorFrame())
        return;

    m_pIconEditorMgr->iconEditorOp()->zoomIn();
}

void HIconMainWindow::zoomOut()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconEditorFrame())
        return;
    m_pIconEditorMgr->iconEditorOp()->zoomOut();
}

void HIconMainWindow::groupObj()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconEditorOp())
        return;
    m_pIconEditorMgr->iconEditorOp()->groupObj();
}

//解除组合
void HIconMainWindow::ungroupObj()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconEditorOp())
        return;
    m_pIconEditorMgr->iconEditorOp()->ungroupObj();
}

//移动到顶层
void HIconMainWindow::bringToTop()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconEditorOp())
        return;
    m_pIconEditorMgr->iconEditorOp()->bringToTop();
}

//移动到底层
void HIconMainWindow::bringToBottom()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconEditorOp())
        return;
    m_pIconEditorMgr->iconEditorOp()->bringToBottom();
}

//上移一层
void HIconMainWindow::bringToUp()
{

}

//下移一层
void HIconMainWindow::bringToDown()
{

}

#include <QDebug>
void HIconMainWindow::onSetAttribute()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconEditorOp())
        return;
    if(m_pIconEditorMgr->iconEditorOp()->toolType() != ICON_SELECT_TOOL)
        return;
    //qDebug()<<"before selectMgr"<<;
    if(m_pIconEditorMgr->selectedMgr())
    {
        QVector<HBaseObj*> objs = m_pIconEditorMgr->selectedMgr()->selectObj()->getObjList();
        if(objs.size() > 1 && objs.size() == 0) return;

       // qDebug()<<"HPropertyDlg"<<;
        HPropertyDlg dlg(objs.at(0));
        dlg.exec();
    }
}

