#include "hgrapheditormainwindow.h"
#include "ui_grapheditormainwindow.h"
#include "hiconapi.h"
#include "hgrapheditormgr.h"
#include "hgrapheditordoc.h"
#include "hgrapheditorview.h"
#include "hgrapheditorop.h"
#include "hgrapheditordrawtoolmgr.h"
#include "hiconhelper.h"
#include "hiconproperty.h"
#include "hdigitalpage.h"
#include "hanaloguepage.h"
#include "hrelaypage.h"
#include "hselectedmgr.h"
#include "htempcontainer.h"
#include "hiconobj.h"
#include <QComboBox>
//文件部分
void HGraphEditorMainWindow::actionNew_clicked()
{

}

void HGraphEditorMainWindow::actionOpen_clicked()
{
    //打开所有的
}

void HGraphEditorMainWindow::actionSave_clicked()
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorDoc())
        return;
    m_pGraphEditorMgr->graphEditorDoc()->saveAllGraph();
}

void HGraphEditorMainWindow::actionSaveAs_clicked()
{

}

void HGraphEditorMainWindow::actionPrint_clicked()
{

}

void HGraphEditorMainWindow::actionExit_clicked()
{
    //退出之前需要将curGrpah拷贝到对应的graph里面 然后delete curGraph
}

//编辑部分
void HGraphEditorMainWindow::acitonUndo_clicked()
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorStack())
        return;
    m_pGraphEditorMgr->graphEditorStack()->undo();
}

void HGraphEditorMainWindow::actionRedo_clicked()
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorStack())
        return;
    m_pGraphEditorMgr->graphEditorStack()->redo();
}

void HGraphEditorMainWindow::actionCut_clicked()
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
        return;
    m_pGraphEditorMgr->graphEditorOp()->cut();
}

void HGraphEditorMainWindow::actionCopy_clicked()
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorView())
        return;
    m_pGraphEditorMgr->graphEditorOp()->copy();
}

void HGraphEditorMainWindow::actionPaste_clicked()
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorView())
        return;
    m_pGraphEditorMgr->graphEditorOp()->paste();
}

void HGraphEditorMainWindow::actionDelete_clicked()
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorView())
        return;
    m_pGraphEditorMgr->graphEditorOp()->del();
}

//置顶置底
void HGraphEditorMainWindow::actionTop_clicked()
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
        return;
    m_pGraphEditorMgr->graphEditorOp()->bringToTop();
}

void HGraphEditorMainWindow::actionBottom_clicked()
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
        return;
    m_pGraphEditorMgr->graphEditorOp()->bringToBottom();
}

//属性
void HGraphEditorMainWindow::actionAttribute_clicked()
{

}

//排列
void HGraphEditorMainWindow::actionAlignTop_clicked()
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
        return;
    m_pGraphEditorMgr->graphEditorOp()->alignTop();
}

void HGraphEditorMainWindow::actionAlignHCenter_clicked()
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
        return;
    m_pGraphEditorMgr->graphEditorOp()->alignHCenter();
}

void HGraphEditorMainWindow::actionAlignBottom_clicked()
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
        return;
    m_pGraphEditorMgr->graphEditorOp()->alignBottom();
}

void HGraphEditorMainWindow::actionAlignLeft_clicked()
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
        return;
    m_pGraphEditorMgr->graphEditorOp()->alignLeft();
}

void HGraphEditorMainWindow::actionAlignVCenter_clicked()
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
        return;
    m_pGraphEditorMgr->graphEditorOp()->alignVCenter();
}

void HGraphEditorMainWindow::actionAlignRight_clicked()
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
        return;
    m_pGraphEditorMgr->graphEditorOp()->alignRight();
}

//旋转
void HGraphEditorMainWindow::actionRotate_clicked()
{

}

void HGraphEditorMainWindow::actionFlipLeft_clicked()
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
        return;
    m_pGraphEditorMgr->graphEditorOp()->flipLeft90();
}

void HGraphEditorMainWindow::actionFlipRight_clicked()
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
        return;
    m_pGraphEditorMgr->graphEditorOp()->flipRight90();
}

void HGraphEditorMainWindow::actionFlipHorizon_clicked()
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
        return;
    m_pGraphEditorMgr->graphEditorOp()->flipHorizon();
}

void HGraphEditorMainWindow::actionFlipVertical_clicked()
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
        return;
    m_pGraphEditorMgr->graphEditorOp()->flipVertical();
}

 //字体部分
 void HGraphEditorMainWindow::fontBox_clicked(int nIndex)
 {
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp() || nIndex == (int)-1)
         return;
     QString strFamily = m_pLineStyleBox->currentText();
     m_pGraphEditorMgr->graphEditorOp()->setFontFamily(strFamily);

 }

 void HGraphEditorMainWindow::fontSizeBox_clicked(int nIndex)
 {
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp() || nIndex == (int)-1)
         return;
     int nSize = m_pFontSizeBox->currentData().toInt();
     m_pGraphEditorMgr->graphEditorOp()->setFontSize(nSize);
 }

 void HGraphEditorMainWindow::actionBold_clicked(bool bchecked)
 {
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp() )
         return;
     bool b = ui->actionBold->isChecked();
     m_pGraphEditorMgr->graphEditorOp()->setBold(bchecked);
 }

 void HGraphEditorMainWindow::actionItalic_clicked(bool bchecked)
 {
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
         return;
     bool b = ui->actionItalic->isChecked();
     m_pGraphEditorMgr->graphEditorOp()->setItalic(bchecked);
 }

 void HGraphEditorMainWindow::actionTextUnder_clicked(bool bchecked)
 {
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp() )
         return;
     bool b = ui->actionTextUnder->isChecked();
     m_pGraphEditorMgr->graphEditorOp()->setUnderline(bchecked);
 }

 //颜色部分
 void HGraphEditorMainWindow::actionPenColor_clicked()
 {
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
         return;
     QColor color = m_pGraphEditorMgr->graphEditorOp()->getPenColor();
     QIcon icon = ui->actionPenColor->icon();
     icon = HIconHelper::Instance()->createPenorBrushColorIcon(icon,color);
     ui->actionPenColor->setIcon(icon);
 }

 void HGraphEditorMainWindow::actionFillColor_clicked()
 {
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
         return;
     QColor color = m_pGraphEditorMgr->graphEditorOp()->getFillColor();
     QIcon icon = ui->actionFillColor->icon();
     icon = HIconHelper::Instance()->createPenorBrushColorIcon(icon,color);
     ui->actionFillColor->setIcon(icon);
 }

 void HGraphEditorMainWindow::actionBackPicture_clicked()
 {

 }

 void HGraphEditorMainWindow::lineStyleBox_clicked(int nIndex)
 {
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp() || nIndex == (int)-1)
         return;
     int nLineStyle = m_pLineStyleBox->currentData().toInt();
     m_pGraphEditorMgr->graphEditorOp()->setLineStyle(nLineStyle);
 }

 void HGraphEditorMainWindow::lineWidthBox_clicked(int nIndex)
 {
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp() || nIndex == (int)-1)
         return;
     int nLineWidth = m_pLineWidthBox->currentData().toInt();
     m_pGraphEditorMgr->graphEditorOp()->setLineWidth(nLineWidth);
 }

 void HGraphEditorMainWindow::fillBrushBox_clicked(int nIndex)
 {
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp() || nIndex == (int)-1)
         return;
     int nFillStyle = m_pFillBrushBox->currentData().toInt();
     m_pGraphEditorMgr->graphEditorOp()->setFillBrush(nFillStyle);
 }

 //组合
 void HGraphEditorMainWindow::actionGroup_clicked()
 {
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
         return;
     m_pGraphEditorMgr->graphEditorOp()->groupObj();
 }

 void HGraphEditorMainWindow::actionUnGroup_clicked()
 {
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
         return;
     m_pGraphEditorMgr->graphEditorOp()->ungroupObj();
 }

 //缩放
 void HGraphEditorMainWindow::actionZoomin_clicked()
 {
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
         return;
     m_pGraphEditorMgr->graphEditorOp()->zoomIn();
 }

 void HGraphEditorMainWindow::actionZoomout_clicked()
 {
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
         return;
     m_pGraphEditorMgr->graphEditorOp()->zoomOut();
 }

 void HGraphEditorMainWindow::actionZoom_clicked()
 {
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
         return;
     m_pGraphEditorMgr->graphEditorOp()->zoom();
 }

 void HGraphEditorMainWindow::actionZoomSame_clicked()
 {
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
         return;
     m_pGraphEditorMgr->graphEditorOp()->zoomSame();
 }

 //等比
 void HGraphEditorMainWindow::actionSameWidth_clicked()
 {
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
         return;
     m_pGraphEditorMgr->graphEditorOp()->sizeEqualWidth();
 }

 void HGraphEditorMainWindow::actionSameHeight_clicked()
 {
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
         return;
     m_pGraphEditorMgr->graphEditorOp()->sizeEqualHeight();
 }

 void HGraphEditorMainWindow::actionSame_clicked()
 {
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
         return;
     m_pGraphEditorMgr->graphEditorOp()->sizeEqualComplete();
 }

 void HGraphEditorMainWindow::actionHSameSpace_clicked()
 {
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
         return;
     m_pGraphEditorMgr->graphEditorOp()->sizeHEqualSpace();
 }

 void HGraphEditorMainWindow::actionVSameSpace_clicked()
 {
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
         return;
     m_pGraphEditorMgr->graphEditorOp()->sizeVEqualSpace();
 }

 //关于
 void HGraphEditorMainWindow::about()
 {

 }

 //draw tool
 void HGraphEditorMainWindow::drawTool()
 {
     QAction* action = qobject_cast<QAction*>(sender());
     if(!action) return;
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
         return;
     QVariant var = action->data();
     DrawShape shape = static_cast<DrawShape>(var.toInt());
     m_pGraphEditorMgr->graphEditorOp()->drawTool(shape);
     if(m_pGraphEditorMgr->graphEditorView())
         m_pGraphEditorMgr->graphEditorView()->setInteractive(false);
     m_pGraphEditorMgr->graphEditorOp()->onEndDraw();
 }

 void HGraphEditorMainWindow::selectTool()
 {
     QAction* action = qobject_cast<QAction*>(sender());
     if(!action) return;
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
         return;
     QVariant var = action->data();
     SelectMode mode = static_cast<SelectMode>(var.toInt());
     m_pGraphEditorMgr->graphEditorOp()->selectTool(mode);
     m_pGraphEditorMgr->graphEditorOp()->onEndDraw();
 }

 void HGraphEditorMainWindow::handTool()
 {

 }

 void HGraphEditorMainWindow::onAttributeChanged()
 {
     if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorOp())
         return;
     if(m_pGraphEditorMgr->graphEditorOp()->toolType() != ICON_SELECT_TOOL)
         return;
     //qDebug()<<"before selectMgr"<<;
     if(m_pGraphEditorMgr->selectedMgr())
     {
         QVector<HBaseObj*> objs = m_pGraphEditorMgr->selectedMgr()->selectObj()->getObjList();
         if(objs.size() > 1 || objs.size() == 0) return;
         HBaseObj *obj = objs.at(0);
         if(obj->getShapeType() == Icon)
         {
             HIconObj* icon = (HIconObj*)obj;
             int nPointType = icon->getObjType();
             if(nPointType == TEMPLATE_TYPE_DIGITAL)
             {
                 HDigitalPage dlg(icon);
                 if(dlg.exec() == QDialog::Accepted)
                 {
                     QRectF rectF = objs.at(0)->boundingRect(1);
                     m_pGraphEditorMgr->graphEditorOp()->onRefreshSelect(rectF);
                     m_pGraphEditorMgr->selectedMgr()->clear();
                     objs.at(0)->iconGraphicsItem()->setSelected(true);
                     objs.at(0)->iconGraphicsItem()->setPos(objs.at(0)->pos());
                     m_pGraphEditorMgr->selectedMgr()->recalcSelect();
                 }
             }
             else if(nPointType == TEMPLATE_TYPE_ANALOGUE)
             {
                 HAnaloguePage dlg(icon);
                 if(dlg.exec() == QDialog::Accepted)
                 {
                     QRectF rectF = objs.at(0)->boundingRect(1);
                     m_pGraphEditorMgr->graphEditorOp()->onRefreshSelect(rectF);
                     m_pGraphEditorMgr->selectedMgr()->clear();
                     objs.at(0)->iconGraphicsItem()->setSelected(true);
                     objs.at(0)->iconGraphicsItem()->setPos(objs.at(0)->pos());
                     m_pGraphEditorMgr->selectedMgr()->recalcSelect();
                 }
             }
             else if(nPointType == TEMPLATE_TYPE_RELAY || nPointType == TEMPLATE_TYPE_CONTROL)
             {
                 HRelayPage dlg(icon);
                 if(dlg.exec() == QDialog::Accepted)
                 {
                     QRectF rectF = objs.at(0)->boundingRect(1);
                     m_pGraphEditorMgr->graphEditorOp()->onRefreshSelect(rectF);
                     m_pGraphEditorMgr->selectedMgr()->clear();
                     objs.at(0)->iconGraphicsItem()->setSelected(true);
                     objs.at(0)->iconGraphicsItem()->setPos(objs.at(0)->pos());
                     m_pGraphEditorMgr->selectedMgr()->recalcSelect();
                 }
             }
         }
         else
         {
             HPropertyDlg dlg(objs.at(0));
             if(dlg.exec() == QDialog::Accepted)
             {
                 QRectF rectF = objs.at(0)->boundingRect(1);
                 m_pGraphEditorMgr->graphEditorOp()->onRefreshSelect(rectF);
                 m_pGraphEditorMgr->selectedMgr()->clear();
                 objs.at(0)->iconGraphicsItem()->setSelected(true);
                 objs.at(0)->iconGraphicsItem()->setPos(objs.at(0)->pos());
                 m_pGraphEditorMgr->selectedMgr()->recalcSelect();
             }
         }
     }
 }
