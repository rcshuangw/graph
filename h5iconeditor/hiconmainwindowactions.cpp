#include "hiconmainwindow.h"
#include <QMessageBox>
#include "hiconeditormgr.h"
#include "hiconeditordrawtoolmgr.h"
#include "hiconeditorframe.h"
#include "hiconeditorop.h"
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
    if(m_pIconEditorMgr && m_pIconEditorMgr->getIconFrame())
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
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->getIconUndoStack())
        return;
    m_pIconEditorMgr->getIconUndoStack()->undo();
}

//重做
void HIconMainWindow::redo()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->getIconUndoStack())
        return;
    m_pIconEditorMgr->getIconUndoStack()->redo();
}

//剪切
void HIconMainWindow::cut()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->getIconOp())
        return;
    m_pIconEditorMgr->getIconOp()->cut();

}

//复制
void HIconMainWindow::copy()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->getIconOp())
        return;
    m_pIconEditorMgr->getIconOp()->copy();

}

//粘贴
void HIconMainWindow::paste()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->getIconOp())
        return;
    m_pIconEditorMgr->getIconOp()->paste();

}

//删除
void HIconMainWindow::del()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->getIconOp())
        return;
    if(QMessageBox::Cancel == QMessageBox::information(NULL,QStringLiteral("警告"),QStringLiteral("确认删除该图符吗？"),QMessageBox::Ok|QMessageBox::Cancel))
        return;
    m_pIconEditorMgr->getIconOp()->del();
}

//合适宽度
void HIconMainWindow::fitWidth()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->getIconOp() || !m_pIconEditorMgr->getIconFrame())
        return;
    m_pIconEditorMgr->getIconOp()->fitWidth();
}

//合适高度
void HIconMainWindow::fitHeight()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->getIconOp() || !m_pIconEditorMgr->getIconFrame())
        return;
    m_pIconEditorMgr->getIconOp()->fitHeight();
}

void HIconMainWindow::zoomIn()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->getIconFrame())
        return;

    m_pIconEditorMgr->getIconOp()->zoomIn();
}

void HIconMainWindow::zoomOut()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->getIconFrame())
        return;
    m_pIconEditorMgr->getIconOp()->zoomOut();
}



void HIconMainWindow::groupObj()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->getIconOp())
        return;
    m_pIconEditorMgr->getIconOp()->groupObj();
}

//解除组合
void HIconMainWindow::ungroupObj()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->getIconOp())
        return;
    m_pIconEditorMgr->getIconOp()->ungroupObj();
}

//移动到顶层
void HIconMainWindow::bringToTop()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->getIconOp())
        return;
    m_pIconEditorMgr->getIconOp()->bringToTop();
}

//移动到底层
void HIconMainWindow::bringToBottom()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->getIconOp())
        return;
    m_pIconEditorMgr->getIconOp()->bringToBottom();
}

//上移一层
void HIconMainWindow::bringToUp()
{

}

//下移一层
void HIconMainWindow::bringToDown()
{

}

