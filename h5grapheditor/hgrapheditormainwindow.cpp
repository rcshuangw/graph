#include "hgrapheditormainwindow.h"
#include "ui_grapheditormainwindow.h"
#include "hgrapheditormgr.h"
#include "hgrapheditorop.h"
#include "hgrapheditorview.h"
#include "hgrapheditordoc.h"
#include "hgrapheditorscene.h"
#include "hgraphtreewidget.h"
#include "hicontabwidget.h"
#include "hiconvieweditor.h"
#include "hfonthelper.h"
#include "hiconhelper.h"
#include "hselectedmgr.h"
#include "htempcontainer.h"
#include <QLineEdit>
#include <QFileInfo>
#include <QComboBox>
#include <QMessageBox>
#include <QDir>
#include <QDebug>
HGraphEditorMainWindow::HGraphEditorMainWindow(HGraphEditorMgr *pMgr,QWidget *parent)
:QMainWindow (parent),
ui(new Ui::GraphEditorMainWindow),m_pGraphEditorMgr(pMgr)
{
    ui->setupUi(this);

    initMainWindow();
    createToolBars();
    createStatusBar();
    createActions();
    createDockWidget();
    showMaximized();
    setWindowTitle(QStringLiteral("测试界面"));
    onUpdateBaseAction();
}

HGraphEditorMainWindow::~HGraphEditorMainWindow()
{
    delete ui;
}

void HGraphEditorMainWindow::createActions()
{
    m_pAlignGroup = new QActionGroup(this);
    m_pEqualGroup = new QActionGroup(this);
    m_pDivideGroup = new QActionGroup(this);
    m_pFlipGroup = new QActionGroup(this);
    m_pEditAndBringGroup = new QActionGroup(this);
    //m_pEditAndBringGroup->setEnabled(false);
    //文件部分
    connect(ui->actionNew_N,SIGNAL(triggered(bool)),this,SLOT(actionNew_clicked()));
    connect(ui->actionOpen_O,SIGNAL(triggered(bool)),this,SLOT(actionOpen_clicked()));
    connect(ui->actionSave_S,SIGNAL(triggered(bool)),this,SLOT(actionSave_clicked()));
    connect(ui->actionSave_As,SIGNAL(triggered(bool)),this,SLOT(actionSaveAs_clicked()));
    connect(ui->actionPrint_P,SIGNAL(triggered(bool)),this,SLOT(actionPrint_clicked()));
    connect(ui->actionExit_E,SIGNAL(triggered(bool)),this,SLOT(actionExit_clicked()));

    //undo redo部分
    connect(ui->actionUndo_U,SIGNAL(triggered(bool)),this,SLOT(acitonUndo_clicked()));
    connect(ui->actionRedo_R,SIGNAL(triggered(bool)),this,SLOT(actionRedo_clicked()));

    //编辑部分
    connect(ui->actionCut_X,SIGNAL(triggered(bool)),this,SLOT(actionCut_clicked()));
    connect(ui->actionCopy_C,SIGNAL(triggered(bool)),this,SLOT(actionCopy_clicked()));
    connect(ui->actionPaste_V,SIGNAL(triggered(bool)),this,SLOT(actionPaste_clicked()));
    connect(ui->actionDelete,SIGNAL(triggered(bool)),this,SLOT(actionDelete_clicked()));
    m_pEditAndBringGroup->addAction(ui->actionCut_X);
    m_pEditAndBringGroup->addAction(ui->actionCopy_C);
    m_pEditAndBringGroup->addAction(ui->actionPaste_V);
    //ui->actionPaste_V->setEnabled(true);
    m_pEditAndBringGroup->addAction(ui->actionDelete);

    //置顶置底
    connect(ui->actionTop_T,SIGNAL(triggered(bool)),this,SLOT(actionTop_clicked()));
    connect(ui->actionBottom_B,SIGNAL(triggered(bool)),this,SLOT(actionBottom_clicked()));
    m_pEditAndBringGroup->addAction(ui->actionTop_T);
    m_pEditAndBringGroup->addAction(ui->actionBottom_B);

    //属性
    connect(ui->actionAttribute,SIGNAL(triggered(bool)),this,SLOT(actionAttribute_clicked()));

    //排列
    connect(ui->actionAlignTop,SIGNAL(triggered(bool)),this,SLOT(actionAlignTop_clicked()));
    connect(ui->actionAlignHCenter,SIGNAL(triggered(bool)),this,SLOT(actionAlignHCenter_clicked()));
    connect(ui->actionAlignBottom,SIGNAL(triggered(bool)),this,SLOT(actionAlignBottom_clicked()));
    connect(ui->actionAlignLeft,SIGNAL(triggered(bool)),this,SLOT(actionAlignLeft_clicked()));
    connect(ui->actionAlignVCenter,SIGNAL(triggered(bool)),this,SLOT(actionAlignVCenter_clicked()));
    connect(ui->actionAlignRight,SIGNAL(triggered(bool)),this,SLOT(actionAlignRight_clicked()));
    m_pAlignGroup->addAction(ui->actionAlignTop);
    m_pAlignGroup->addAction(ui->actionAlignHCenter);
    m_pAlignGroup->addAction(ui->actionAlignBottom);
    m_pAlignGroup->addAction(ui->actionAlignLeft);
    m_pAlignGroup->addAction(ui->actionAlignVCenter);
    m_pAlignGroup->addAction(ui->actionAlignRight);
    //m_pAlignGroup->setEnabled(true);

    //旋转
    connect(ui->actionRotate,SIGNAL(triggered(bool)),this,SLOT(actionRotate_clicked()));
    connect(ui->actionFilpLeft,SIGNAL(triggered(bool)),this,SLOT(actionFlipLeft_clicked()));
    connect(ui->actionFlipRight,SIGNAL(triggered(bool)),this,SLOT(actionFlipRight_clicked()));
    connect(ui->actionFlipHorizon,SIGNAL(triggered(bool)),this,SLOT(actionFlipHorizon_clicked()));
    connect(ui->actionFlipHorizon,SIGNAL(triggered(bool)),this,SLOT(actionFlipVertical_clicked()));
    m_pFlipGroup->addAction(ui->actionRotate);
    m_pFlipGroup->addAction(ui->actionFilpLeft);
    m_pFlipGroup->addAction(ui->actionFlipRight);
    m_pFlipGroup->addAction(ui->actionFlipHorizon);
    m_pFlipGroup->addAction(ui->actionFlipVertical);
    //m_pFlipGroup->setEnabled(true);

    //字体部分的actions()
    connect(m_pFontBox,SIGNAL(currentIndexChanged(int)),this,SLOT(fontBox_clicked(int)));
    connect(m_pFontSizeBox,SIGNAL(currentIndexChanged(int)),this,SLOT(fontSizeBox_clicked(int)));
    connect(ui->actionBold,SIGNAL(triggered(bool)),this,SLOT(actionBold_clicked(bool)));
    connect(ui->actionItalic,SIGNAL(triggered(bool)),this,SLOT(actionItalic_clicked(bool)));
    connect(ui->actionTextUnder,SIGNAL(triggered(bool)),this,SLOT(actionTextUnder_clicked(bool)));

    //颜色部分
    connect(ui->actionPenColor,SIGNAL(triggered(bool)),this,SLOT(actionPenColor_clicked()));
    connect(ui->actionFillColor,SIGNAL(triggered(bool)),this,SLOT(actionFillColor_clicked()));
    connect(ui->actionBackPicture,SIGNAL(triggered(bool)),this,SLOT(actionBackPicture_clicked()));

    //组合
    connect(ui->actionGroup,SIGNAL(triggered(bool)),this,SLOT(actionGroup_clicked()));
    connect(ui->actionUngroup,SIGNAL(triggered(bool)),this,SLOT(actionUnGroup_clicked()));


    //选择,工具
    ui->actionSelect->setData(None);
    connect(ui->actionSelect,SIGNAL(triggered(bool)),this,SLOT(selectTool()));
    ui->actionHand_H->setCheckable(true);
    connect(ui->actionHand_H,SIGNAL(triggered(bool)),this,SLOT(handTool()));

    //工具
    ui->actionText->setCheckable(true);
    ui->actionText->setData(Text);
    connect(ui->actionText,SIGNAL(triggered(bool)),this,SLOT(drawTool()));
    ui->actionLine->setCheckable(true);
    ui->actionLine->setData(Line);
    connect(ui->actionLine,SIGNAL(triggered(bool)),this,SLOT(drawTool()));
    ui->actionRectangle->setCheckable(true);
    ui->actionRectangle->setData(Rectangle);
    connect(ui->actionRectangle,SIGNAL(triggered(bool)),this,SLOT(drawTool()));
    ui->actionPolyline->setCheckable(true);
    ui->actionPolyline->setData(Polyline);
    connect(ui->actionPolyline,SIGNAL(triggered(bool)),this,SLOT(drawTool()));
    ui->actionPolygon->setCheckable(true);
    ui->actionPolygon->setData(Polygon);
    connect(ui->actionPolygon,SIGNAL(triggered(bool)),this,SLOT(drawTool()));
    ui->actionEllipse->setCheckable(true);
    ui->actionEllipse->setData(Ellipse);
    connect(ui->actionEllipse,SIGNAL(triggered(bool)),this,SLOT(drawTool()));
    ui->actionCircle->setCheckable(true);
    ui->actionCircle->setData(Circle);
    connect(ui->actionCircle,SIGNAL(triggered(bool)),this,SLOT(drawTool()));
    ui->actionArc->setCheckable(true);
    ui->actionArc->setData(Arc);
    connect(ui->actionArc,SIGNAL(triggered(bool)),this,SLOT(drawTool()));
    QActionGroup * actionGroup = new QActionGroup(this);
    actionGroup->addAction(ui->actionText);
    actionGroup->addAction(ui->actionLine);
    actionGroup->addAction(ui->actionRectangle);
    actionGroup->addAction(ui->actionPolyline);
    actionGroup->addAction(ui->actionPolygon);
    actionGroup->addAction(ui->actionEllipse);
    actionGroup->addAction(ui->actionCircle);
    actionGroup->addAction(ui->actionArc);
    actionGroup->addAction(ui->actionSelect);
    actionGroup->addAction(ui->actionHand_H);

    //平移


    //缩放
    connect(ui->actionZoomin,SIGNAL(triggered(bool)),this,SLOT(actionZoomin_clicked()));
    connect(ui->actionZoomout,SIGNAL(triggered(bool)),this,SLOT(actionZoomout_clicked()));
    connect(ui->actionZoom,SIGNAL(triggered(bool)),this,SLOT(actionZoom_clicked()));
    connect(ui->actionZoomSame,SIGNAL(triggered(bool)),this,SLOT(actionZoomSame_clicked()));


    //等比
    connect(ui->actionSameWidth,SIGNAL(triggered(bool)),this,SLOT(actionSameWidth_clicked()));
    connect(ui->actionSameHeight,SIGNAL(triggered(bool)),this,SLOT(actionSameHeight_clicked()));
    connect(ui->actionSame,SIGNAL(triggered(bool)),this,SLOT(actionSame_clicked()));
    m_pEqualGroup->addAction(ui->actionSameWidth);
    m_pEqualGroup->addAction(ui->actionSameHeight);
    m_pEqualGroup->addAction(ui->actionSame);
    //m_pEqualGroup->setEnabled(false);
    connect(ui->actionHSameSpace,SIGNAL(triggered(bool)),this,SLOT(actionHSameSpace_clicked()));
    connect(ui->actionVSameSpace,SIGNAL(triggered(bool)),this,SLOT(actionVSameSpace_clicked()));
    m_pDivideGroup->addAction(ui->actionHSameSpace);
    m_pDivideGroup->addAction(ui->actionVSameSpace);
    //m_pDivideGroup->setEnabled(true);

    //关于
    connect(ui->actionAbout_A,SIGNAL(triggered(bool)),this,SLOT(about()));
}

void HGraphEditorMainWindow::createToolBars()
{
   //字体 默认的字体都是可以Bold italic
   m_pFontBox = new QComboBox(ui->fontBar);
   HFontHelper::Instance()->initFontFamilyComboBox(m_pFontBox);
   m_pFontBox->setCurrentIndex(0);
   ui->fontBar->insertWidget(ui->actionBold,m_pFontBox);

   //大小
   m_pFontSizeBox = new QComboBox(ui->fontBar);
   HFontHelper::Instance()->initFontSizeComboBox(m_pFontSizeBox,m_pFontBox->currentText());
   ui->fontBar->insertWidget(ui->actionBold,m_pFontSizeBox);

   //最后插入文本编辑框
   m_pTextEdit = new QLineEdit(ui->fontBar);
   ui->fontBar->addWidget(m_pTextEdit);

   //插入线型、线宽、填充方式
   m_pLineStyleBox = new QComboBox(ui->attrBar);
   HIconHelper::Instance()->InitPenStyleComboBox(m_pLineStyleBox);
   m_pLineStyleBox->setCurrentIndex(0);
   ui->attrBar->insertWidget(ui->actionBackPicture,m_pLineStyleBox);
   connect(m_pLineStyleBox,SIGNAL(currentIndexChanged(int)),this,SLOT(lineStyleBox_clicked(int)));

   m_pLineWidthBox = new QComboBox(ui->attrBar);
   HIconHelper::Instance()->InitPenWidthComboBox(m_pLineWidthBox);
   m_pLineWidthBox->setCurrentIndex(0);
   ui->attrBar->addWidget(m_pLineWidthBox);
   connect(m_pLineWidthBox,SIGNAL(currentIndexChanged(int)),this,SLOT(lineWidthBox_clicked(int)));

   m_pFillBrushBox = new QComboBox(ui->attrBar);
   HIconHelper::Instance()->InitBrushStyleComboBox(m_pFillBrushBox);
   ui->attrBar->addWidget(m_pFillBrushBox);
   connect(m_pFillBrushBox,SIGNAL(currentIndexChanged(int)),this,SLOT(fillBrushBox_clicked(int)));
}

void HGraphEditorMainWindow::createFontBar()
{

}

void HGraphEditorMainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void HGraphEditorMainWindow::createDockWidget()
{
    m_pIconTabWidget = new HIconTabWidget(m_pGraphEditorMgr);
    //connect(pIconTabWidget,SIGNAL(iconSelected(const QString&,const QString&,const QString&,int)),SLOT(iconTemplateSelected(const QString&,const QString&,const QString&,int)));
    ui->resDockWidget->setWidget(m_pIconTabWidget);
    //ui->resDockWidget->setMaximumWidth(10);

    m_pGraphTreeWidget = new HGraphTreeWidget(m_pGraphEditorMgr);
    ui->fileDockWidget->setWidget(m_pGraphTreeWidget);
    connect(m_pGraphTreeWidget,SIGNAL(graphNew(const QString&)),this,SLOT(New(const QString&)));//新建
    connect(m_pGraphTreeWidget,SIGNAL(graphOpen(const QString&,const int)),this,SLOT(Open(const QString&,const int)));//打开
    connect(m_pGraphTreeWidget,SIGNAL(graphDel(const QString&,const int )),this,SLOT(Del(const QString&,const int)));//删除
    connect(m_pGraphTreeWidget,SIGNAL(graphImport(const QString&)),this,SLOT(ImportFile(const QString&)));
    connect(m_pGraphTreeWidget,SIGNAL(graphImportPath(const QString&)),this,SLOT(ImportGraphFolder(const QString&)));
}

void HGraphEditorMainWindow::initGraphEditorMgr()
{

}

void HGraphEditorMainWindow::initMainWindow()
{
    m_pGraphEditorView = new HGraphEditorView(ui->centralWidget);
    m_pGraphEditorView->setObjectName(QStringLiteral("画图系统"));
    m_pGraphEditorView->setFrameShape(QFrame::NoFrame);
    m_pGraphEditorView->setFrameShadow(QFrame::Plain);
    m_pGraphEditorView->setLineWidth(0);


    ui->gridLayout->addWidget(m_pGraphEditorView,0,1,1,1);
    m_pGraphEditorMgr->setGraphEditorView(m_pGraphEditorView);
    connect(m_pGraphEditorMgr->graphEditorScene(),SIGNAL(itemInserted(int)),this,SLOT(itemInserted(int)));
    connect(m_pGraphEditorMgr->graphEditorScene(),SIGNAL(selectItemChanged(int)),this,SLOT(selectItemChanged(int)));
    connect(m_pGraphEditorMgr->graphEditorScene(),SIGNAL(mousePosChanged(const QPointF&)),this,SLOT(viewMousePosChanged(const QPointF&)));

    connect(m_pGraphEditorMgr->graphEditorOp(),SIGNAL(setSelectTool()),this,SLOT(onSelectTool()));
    connect(m_pGraphEditorMgr->graphEditorOp(),SIGNAL(attributeChanged()),this,SLOT(onAttributeChanged()));
    connect(m_pGraphEditorMgr->graphEditorOp(),SIGNAL(selectChanged()),this,SLOT(onSelectChanged()));
    connect(m_pGraphEditorMgr->graphEditorOp(),SIGNAL(updateBaseAction()),this,SLOT(onUpdateBaseAction()));
    connect(m_pGraphEditorMgr->graphEditorOp(),SIGNAL(updateStatus(const QString&)),this,SLOT(onUpdateStatus(const QString&)));

}

void HGraphEditorMainWindow::New(const QString& graphName)
{
    //主要要先保存，然后删除当前的，然后新建graph对象(mgr->doc)，然后树新增
    if(!m_pGraphEditorMgr)
        return;
    bool bfind = m_pGraphEditorMgr->findGraphByName(graphName);
    if(bfind)
    {
        QMessageBox::information(this,QStringLiteral("提醒"),QStringLiteral("已经存在相同名字的图形文件，请修改名称"),QMessageBox::Ok);
        return;
    }

    //如果有修改的
    if(m_pGraphEditorMgr->isGraphModify())
    {
        if(QMessageBox::Ok == QMessageBox::information(NULL,QStringLiteral("提醒"),QStringLiteral("需要保存当前的画面文件吗？"),QMessageBox::Yes|QMessageBox::No))
        {

             //Save();
        }
    }

    //view 或者 scene里面要清除掉所有内容
    m_pGraphEditorMgr->reset();
    m_pGraphEditorMgr->New(graphName);
    m_pGraphTreeWidget->addGraphTreeWidgetItem();
    onUpdateBaseAction();
    ui->actionSelect->trigger();
}

void HGraphEditorMainWindow::Open(const QString& name,const int id)
{
    //主要要先保存，然后删除当前的，然后新建graph对象(mgr->doc)，然后树新增
    if(!m_pGraphEditorMgr)
        return;

    //如果有修改的
    if(m_pGraphEditorMgr->isGraphModify())
    {
        if(QMessageBox::Yes == QMessageBox::information(NULL,QStringLiteral("提醒"),QStringLiteral("需要保存当前的画面文件吗？"),QMessageBox::Yes|QMessageBox::No))
        {

             m_pGraphEditorMgr->Save();
        }
    }

    //先删除原来的，在打开文件，最后显示
    //Reset();
    m_pGraphEditorMgr->reset();
    m_pGraphEditorMgr->Open(name,id);
    onUpdateBaseAction();
    ui->actionSelect->trigger();
}

void HGraphEditorMainWindow::ImportFile(const QString& name)
{
    if(!m_pGraphEditorMgr)
        return;
    //对文件进行判断
    QFileInfo fileInfo(name);
    QString strName = fileInfo.completeSuffix();
    if(strName.compare("grf") != 0)
    {
        if(QMessageBox::Ok == QMessageBox::information(NULL,QStringLiteral("警告"),QStringLiteral("画面后缀为grf,请修改"),QMessageBox::Yes))
        {
             return;
        }
    }
    int graphID = m_pGraphEditorMgr->ImportFile(name);
    if((int)-1 == graphID)
    {
        //提示导入失败
        return;
    }
    if(m_pGraphEditorMgr->isGraphModify())
    {
        if(QMessageBox::Ok == QMessageBox::information(NULL,QStringLiteral("提醒"),QStringLiteral("需要保存当前的画面文件吗？"),QMessageBox::Yes|QMessageBox::No))
        {
             //Save();
        }
    }
    //通知属性控件刷新
    m_pGraphEditorMgr->Open("",graphID);
    m_pGraphTreeWidget->addGraphTreeWidgetItem();
    m_pGraphEditorMgr->refreshView();
    onUpdateBaseAction();
}


void HGraphEditorMainWindow::ImportGraphFolder(const QString& path)
{
    //判断文件个数是否过多
    QDir graphsDir(path);
    QFileInfoList graphFolderList = graphsDir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
    if(graphFolderList.count() > 1 || graphFolderList.count() == 0)
    {

    }
    foreach(QFileInfo info,graphFolderList)
    {
    }

    QString strName = QFileInfo(graphFolderList[0]).fileName();
    ImportFile(path + "/" + strName);
}

void HGraphEditorMainWindow::Del(const QString& graphName,const int graphID)
{
    if(!m_pGraphEditorMgr)
        return;
    if(QMessageBox::No == QMessageBox::information(NULL,QStringLiteral("提醒"),QStringLiteral("确定需要删除该画面吗？"),QMessageBox::Yes|QMessageBox::No))
    {
        return;
    }
    m_pGraphEditorMgr->reset();
    m_pGraphEditorMgr->Del(graphName,graphID);
    m_pGraphTreeWidget->delGraphTreeWidgetItem();
    m_pGraphEditorMgr->refreshView();
    onUpdateBaseAction();

}

void HGraphEditorMainWindow::itemInserted(int type)
{
    //ui->actionSelect->setChecked(true);
    //emit ui->actionSelect->triggered();
}

void HGraphEditorMainWindow::selectItemChanged(int nSelectMode)
{

}

void HGraphEditorMainWindow::viewMousePosChanged(const QPointF &logPos)
{

    //QString strViewPos = QString("x=%1,y=%2").arg((int)pos.x()).arg((int)pos.y());
    QString strLogicPos =  QString("log:x=%1,y=%2").arg(logPos.x(),0,'f',1).arg(logPos.y(),0,'f',1);
    statusBar()->showMessage(strLogicPos );
}

//刷新菜单工具栏状态
void HGraphEditorMainWindow::onUpdateBaseAction()
{
    //还要判断当前是否已经打开graph
    bool bMgr = m_pGraphEditorMgr->graphEditorDoc()->m_bGraphValid;
    //if(m_pGraphEditorMgr)
    //    bMgr = true;
    //undo redo
    ui->actionRedo_R->setEnabled(bMgr&&m_pGraphEditorMgr->graphEditorStack()&&m_pGraphEditorMgr->graphEditorStack()->canUndo());
    ui->actionUndo_U->setEnabled(bMgr&&m_pGraphEditorMgr->graphEditorStack()&&m_pGraphEditorMgr->graphEditorStack()->canRedo());

    //cut copy paste del
    bool bselectObj = bMgr&&m_pGraphEditorMgr->selectedMgr()&&m_pGraphEditorMgr->selectedMgr()->selectObj();
    int nSelectObjCount = m_pGraphEditorMgr->selectedMgr()->selectObj()->getObjList().size();
    bool b = bselectObj && nSelectObjCount > 0;
    ui->actionCopy_C->setEnabled(bselectObj&&nSelectObjCount>0);
    ui->actionCut_X->setEnabled(bselectObj&&nSelectObjCount>0);
    ui->actionPaste_V->setEnabled(m_pGraphEditorMgr&&m_pGraphEditorMgr->graphEditorOp()->isClipboardAvailable());
    ui->actionDelete->setEnabled(bselectObj&&nSelectObjCount>0);

    //bringtotop bringtobottom
    ui->actionTop_T->setEnabled(bselectObj&&nSelectObjCount==1);
    ui->actionBottom_B->setEnabled(bselectObj&&nSelectObjCount==1);

    //group ungroup
    ui->actionGroup->setEnabled(bselectObj&&nSelectObjCount>1);
    if(bselectObj&&nSelectObjCount==1&&
        m_pGraphEditorMgr->selectedMgr()->selectObj()->getObjList().at(0)->getShapeType()==Group){
            ui->actionUngroup->setEnabled(true);
        }
    else{
        ui->actionUngroup->setEnabled(false);
    }

    //draw obj
    ui->actionLine->setEnabled(bMgr);
    ui->actionRectangle->setEnabled(bMgr);
    ui->actionPolyline->setEnabled(bMgr);
    ui->actionPolygon->setEnabled(bMgr);
    ui->actionEllipse->setEnabled(bMgr);
    ui->actionCircle->setEnabled(bMgr);
    ui->actionArc->setEnabled(bMgr);
    ui->actionText->setEnabled(bMgr);

    //zoom
    ui->actionZoom->setEnabled(bMgr);
    ui->actionZoomin->setEnabled(bMgr);
    ui->actionZoomout->setEnabled(bMgr);
    ui->actionZoomSame->setEnabled(bMgr);

    //align
    ui->actionAlignLeft->setEnabled(bselectObj&&nSelectObjCount>0);
    ui->actionAlignRight->setEnabled(bselectObj&&nSelectObjCount>0);
    ui->actionAlignHCenter->setEnabled(bselectObj&&nSelectObjCount>0);
    ui->actionAlignTop->setEnabled(bselectObj&&nSelectObjCount>0);
    ui->actionAlignBottom->setEnabled(bselectObj&&nSelectObjCount>0);
    ui->actionAlignVCenter->setEnabled(bselectObj&&nSelectObjCount>0);

    //same
    ui->actionSame->setEnabled(bselectObj&&nSelectObjCount>1);
    ui->actionSameHeight->setEnabled(bselectObj&&nSelectObjCount>1);
    ui->actionSameWidth->setEnabled(bselectObj&&nSelectObjCount>1);

    //等分
    ui->actionHSameSpace->setEnabled(bselectObj&&nSelectObjCount>2);
    ui->actionVSameSpace->setEnabled(bselectObj&&nSelectObjCount>2);
}

void HGraphEditorMainWindow::onUpdateStatus(const QString &showText)
{
    statusBar()->showMessage(showText);
}

void HGraphEditorMainWindow::onSelectTool()
{
    ui->actionSelect->trigger();
}

void HGraphEditorMainWindow::onSelectChanged()
{

}
