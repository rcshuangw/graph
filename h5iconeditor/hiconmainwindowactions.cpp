#include "hiconmainwindow.h"
#include <QMessageBox>
#include "hiconeditormgr.h"
#include "hiconeditordrawtoolmgr.h"
//显示网格
void HIconMainWindow::showGrid()
{
    bool bcheck = showGridAct->isChecked();
    if(pIconMgr && pIconMgr->getIconFrame())
    {
        pIconMgr->setShowGrid(bcheck);
        if(pIconMgr->getIconFrame()->view())
            pIconMgr->getIconFrame()->view()->resetCachedContent();

    }
}

//显示中心线
void HIconMainWindow::showCenterLine()
{
    bool bcheck = showCLineAct->isChecked();
    if(pIconMgr && pIconMgr->getIconFrame())
    {
        pIconMgr->setShowCenterLine(bcheck);
        if(pIconMgr->getIconFrame()->view())
            pIconMgr->getIconFrame()->view()->resetCachedContent();

    }
}

//draw tool
void HIconMainWindow::drawLine()
{
    pIconMgr->setDrawShape(enumLine);
    pIconMgr->setSelectMode(enumDraw);
    //setCursor(Qt::CrossCursor);
    //m_pIconEditorMgr->iconEditorDrawToolMgr()->selectTool();
}

void HIconMainWindow::drawPolyline()
{
    pIconMgr->setDrawShape(enumPolyline);
    pIconMgr->setSelectMode(enumDraw);
    //setCursor(Qt::CrossCursor);
}

void HIconMainWindow::drawEllipse()
{
    pIconMgr->setDrawShape(enumEllipse);
    pIconMgr->setSelectMode(enumDraw);
    //setCursor(Qt::CrossCursor);
}

void HIconMainWindow::drawRectangle()
{
    pIconMgr->setDrawShape(enumRectangle);
    pIconMgr->setSelectMode(enumDraw);
    //setCursor(Qt::CrossCursor);
}

void HIconMainWindow::drawCircle()
{
    pIconMgr->setDrawShape(enumCircle);
    pIconMgr->setSelectMode(enumDraw);
    //setCursor(Qt::CrossCursor);
}

void HIconMainWindow::drawHexagon()
{
    pIconMgr->setDrawShape(enumPolygon);
    pIconMgr->setSelectMode(enumDraw);
    //setCursor(Qt::CrossCursor);
}

void HIconMainWindow::drawArc()
{
    pIconMgr->setDrawShape(enumArc);
    pIconMgr->setSelectMode(enumDraw);
    //setCursor(Qt::CrossCursor);
}

void HIconMainWindow::drawFan()
{
    pIconMgr->setDrawShape(enumPie);
    pIconMgr->setSelectMode(enumDraw);
    //setCursor(Qt::CrossCursor);
}

void HIconMainWindow::drawText()
{
    pIconMgr->setDrawShape(enumText);
    pIconMgr->setSelectMode(enumDraw);
    //setCursor(Qt::CrossCursor);
}

void HIconMainWindow::drawSelection()
{
    pIconMgr->setDrawShape(enumSelection);
    pIconMgr->setSelectMode(enumDraw);
    //setCursor(Qt::ArrowCursor);
}


//撤销
void HIconMainWindow::undo()
{
    if(!pIconMgr || !pIconMgr->getIconUndoStack())
        return;
    pIconMgr->getIconUndoStack()->undo();
}

//重做
void HIconMainWindow::redo()
{
    if(!pIconMgr || !pIconMgr->getIconUndoStack())
        return;
    pIconMgr->getIconUndoStack()->redo();
}

//剪切
void HIconMainWindow::cut()
{
    if(!pIconMgr || !pIconMgr->getIconOp())
        return;
    pIconMgr->getIconOp()->cut();

}

//复制
void HIconMainWindow::copy()
{
    if(!pIconMgr || !pIconMgr->getIconOp())
        return;
    pIconMgr->getIconOp()->copy();

}

//粘贴
void HIconMainWindow::paste()
{
    if(!pIconMgr || !pIconMgr->getIconOp())
        return;
    pIconMgr->getIconOp()->paste();

}

//删除
void HIconMainWindow::del()
{
    if(!pIconMgr || !pIconMgr->getIconOp())
        return;
    if(QMessageBox::Cancel == QMessageBox::information(NULL,QStringLiteral("警告"),QStringLiteral("确认删除该图符吗？"),QMessageBox::Ok|QMessageBox::Cancel))
        return;
    pIconMgr->getIconOp()->del();
}

//合适宽度
void HIconMainWindow::fitWidth()
{
    if(!pIconMgr || !pIconMgr->getIconOp() || !pIconMgr->getIconFrame())
        return;
    pIconMgr->getIconOp()->fitWidth();
}

//合适高度
void HIconMainWindow::fitHeight()
{
    if(!pIconMgr || !pIconMgr->getIconOp() || !pIconMgr->getIconFrame())
        return;
    pIconMgr->getIconOp()->fitHeight();
}

void HIconMainWindow::zoomIn()
{
    if(!pIconMgr || !pIconMgr->getIconFrame())
        return;

    pIconMgr->getIconOp()->zoomIn();
}

void HIconMainWindow::zoomOut()
{
    if(!pIconMgr || !pIconMgr->getIconFrame())
        return;
    pIconMgr->getIconOp()->zoomOut();
}



void HIconMainWindow::groupObj()
{
    if(!pIconMgr || !pIconMgr->getIconOp())
        return;
    pIconMgr->getIconOp()->groupObj();
}

//解除组合
void HIconMainWindow::ungroupObj()
{
    if(!pIconMgr || !pIconMgr->getIconOp())
        return;
    pIconMgr->getIconOp()->ungroupObj();
}

//移动到顶层
void HIconMainWindow::bringToTop()
{
    if(!pIconMgr || !pIconMgr->getIconOp())
        return;
    pIconMgr->getIconOp()->bringToTop();
}

//移动到底层
void HIconMainWindow::bringToBottom()
{
    if(!pIconMgr || !pIconMgr->getIconOp())
        return;
    pIconMgr->getIconOp()->bringToBottom();
}

//上移一层
void HIconMainWindow::bringToUp()
{

}

//下移一层
void HIconMainWindow::bringToDown()
{

}

