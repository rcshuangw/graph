#include "hiconmainwindow.h"
#include <QKeySequence>
#include <QRectF>
#include <QRect>
#include <QDockWidget>
#include <QStatusBar>
#include <QInputDialog>
#include <QIntValidator>
#include <QActionGroup>
#include <QMessageBox>
#include <QVariant>
#include <qmath.h>
#include "htempcontainer.h"
#include "hiconeditorop.h"
#include "hiconeditormgr.h"
#include "hiconeditordoc.h"
#include "hiconeditorwidget.h"
#include "hselectedmgr.h"
HIconMainWindow::HIconMainWindow(HIconEditorMgr *parent) : m_pIconEditorMgr(parent)
{
    createActions();
    createMenuBars();
    createToolBars();
    createDockWindows();

    m_pIconEditorWidget = new HIconEditorWidget();

    setCentralWidget(m_pIconEditorWidget);
    setWindowTitle(QStringLiteral("图元编辑器"));
    //setWindowModified(true);

    //pIconDocument = new HIconDocument;
    statusBar()->showMessage("Reday");
    //resize(800,600);
    setWindowState(Qt::WindowMaximized);

    init();
    setUnifiedTitleAndToolBarOnMac(true);
}

HIconMainWindow::~HIconMainWindow()
{

}

void HIconMainWindow::init()
{
    m_pIconEditorFrame = m_pIconEditorMgr->iconEditorFrame();
    connect(m_pIconEditorFrame,SIGNAL(mousePosChanged(const QPoint&,const QPointF&)),this,SLOT(viewMousePosChanged(const QPoint&,const QPointF&)));
    showGridAct->setChecked(m_pIconEditorMgr->getShowGrid());
    showCLineAct->setChecked(m_pIconEditorMgr->getShowCenterLine());
    //改用函数来实现
   // m_pIconEditorMgr->iconEditorFrame()->scaleChangedTo(0.6);
    //QString strScale = QString("%1%").arg(pIconMgr->getIconFrame()->scale()*100);
    //scaleComboBox->setCurrentText(strScale);
}

void HIconMainWindow::createActions()
{

    setIconSize(QSize(32,32));
    //文件项
    //newAct = new QAction(QIcon(":/images/new.png"), QStringLiteral("新建(&N)"), this);
    //newAct->setShortcuts(QKeySequence::New);

    openAct = new QAction(QIcon(":/images/open.png"), QStringLiteral("打开(&O)"), this);
    openAct->setShortcuts(QKeySequence::Open);

    saveAct = new QAction(QIcon(":/images/save.png"), QStringLiteral("保存(&S)"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    connect(saveAct,SIGNAL(triggered(bool)),this,SLOT(save()));

    quitAct = new QAction(QIcon(":/images/close.png"),QStringLiteral("退出(&E)"),this);
    quitAct->setShortcut(QKeySequence::Quit);
    connect(quitAct, &QAction::triggered,this,&QWidget::close);
    // QAction *exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), this, &QWidget::close);

    //编辑项
    undoAct = new QAction(QIcon(":/images/undo.png"),QStringLiteral("撤销(&U)"),this);
    undoAct->setShortcut(QKeySequence(QKeySequence::Undo));
    connect(undoAct,SIGNAL(triggered(bool)),this,SLOT(undo()));

    redoAct = new QAction(QIcon(":/images/redo.png"),QStringLiteral("重做(&R)"),this);
    redoAct->setShortcut(QKeySequence(QKeySequence::Redo));
    connect(redoAct,SIGNAL(triggered(bool)),this,SLOT(redo()));

    cutAct = new QAction(QIcon(":/images/cut.png"), QStringLiteral("剪切(&X)"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    connect(cutAct,SIGNAL(triggered(bool)),this,SLOT(cut()));

    copyAct = new QAction(QIcon(":/images/copy.png"), QStringLiteral("复制(&C)"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    connect(copyAct,SIGNAL(triggered(bool)),this,SLOT(copy()));

    pasteAct = new QAction(QIcon(":/images/paste.png"), QStringLiteral("粘贴(&P)"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    connect(pasteAct,SIGNAL(triggered(bool)),this,SLOT(paste()));

    deleteAct = new QAction(QIcon(":/images/del.png"),QStringLiteral("删除(&D)"),this);
    deleteAct->setShortcut(QKeySequence::Delete);
    connect(deleteAct,SIGNAL(triggered(bool)),this,SLOT(del()));

    //视图项
    showRulerAct = new QAction(QIcon(":/images/ruler.png"), QStringLiteral("标尺(&R)"), this);
    showRulerAct->setCheckable(true);
    showRulerAct->setChecked(true);

    showGridAct = new QAction(QIcon(":/images/grid.png"), QStringLiteral("网格(&G)"), this);
    showGridAct->setCheckable(true);
    showGridAct->setChecked(true);
    connect(showGridAct,SIGNAL(triggered(bool)),this,SLOT(showGrid()));

    showCLineAct = new QAction(QIcon(":/images/center.png"), QStringLiteral("中心线(&C)"), this);
    showCLineAct->setCheckable(true);
    showCLineAct->setChecked(true);
    connect(showCLineAct,SIGNAL(triggered(bool)),this,SLOT(showCenterLine()));

    //缩放项
    fitWidthAct = new QAction(QIcon(":/images/zoom_fit_width.png"), QStringLiteral("合适宽度"), this);
    connect(fitWidthAct,SIGNAL(triggered(bool)),this,SLOT(fitWidth()));
    fitHeightAct = new QAction(QIcon(":/images/zoom_fit_height.png"), QStringLiteral("合适高度"), this);
    connect(fitHeightAct,SIGNAL(triggered(bool)),this,SLOT(fitHeight()));
    zoomInAct = new QAction(QIcon(":/images/zoom_in.png"), QStringLiteral("放大"), this);
    //zoomInAct->setCheckable(true);
    connect(zoomInAct,SIGNAL(triggered(bool)),this,SLOT(zoomIn()));
    zoomOutAct = new QAction(QIcon(":/images/zoom_out.png"), QStringLiteral("缩小"), this);
    //zoomOutAct->setCheckable(true);
    connect(zoomOutAct,SIGNAL(triggered(bool)),this,SLOT(zoomOut()));
    zoomOriAct = new QAction(QIcon(":/images/zoom_original.png"), QStringLiteral("自由缩放"), this);
    //zoomOriAct->setCheckable(true);

    scaleComboBox = new QComboBox(this);
    QIntValidator *validator = new QIntValidator(10,500);
    scaleComboBox->setValidator(validator);
    scaleComboBox->setEditable(true);
    scaleComboBox->addItem(tr("50%"),0.5);
    scaleComboBox->addItem(tr("70%"),0.7);
    scaleComboBox->addItem(tr("100%"),1);
    scaleComboBox->addItem(tr("150%"),1.5);
    connect(scaleComboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(scaleChanged(QString)));
    connect(scaleComboBox->lineEdit(),SIGNAL(editingFinished()),this,SLOT(scaleChanged()));

    toTopAct = new QAction(QIcon(":/images/move_forward.png"),QStringLiteral("置顶"),this);
    connect(toTopAct,SIGNAL(triggered(bool)),this,SLOT(bringToTop()));

    toBottomAct = new QAction(QIcon(":/images/move_backward.png"),QStringLiteral("置底"),this);
    connect(toBottomAct,SIGNAL(triggered(bool)),this,SLOT(bringToBottom()));


    alignLeftAct = new QAction(QIcon(":/images/shape_align_left.png"),QStringLiteral("左对齐"),this);
    connect(alignLeftAct,SIGNAL(triggered(bool)),this,SLOT(alignLeft()));
    alignLeftAct->setEnabled(false);
    alignVCenterAct = new QAction(QIcon(":/images/shape_align_middle.png"),QStringLiteral("纵向居中对齐"),this);
    connect(alignVCenterAct,SIGNAL(triggered(bool)),this,SLOT(alignVCenter()));
    alignRightAct = new QAction(QIcon(":/images/shape_align_right.png"),QStringLiteral("右对齐"),this);
    connect(alignRightAct,SIGNAL(triggered(bool)),this,SLOT(alignRight()));

    alignTopAct = new QAction(QIcon(":/images/shape_align_top.png"),QStringLiteral("上对齐"),this);
    connect(alignTopAct,SIGNAL(triggered(bool)),this,SLOT(alignTop()));
    alignHCenterAct = new QAction(QIcon(":/images/shape_align_center.png"),QStringLiteral("横向居中对齐"),this);
    connect(alignHCenterAct,SIGNAL(triggered(bool)),this,SLOT(alignHCenter()));
    alignBottomAct = new QAction(QIcon(":/images/shape_align_bottom.png"),QStringLiteral("下对齐"),this);;
    connect(alignBottomAct,SIGNAL(triggered(bool)),this,SLOT(alignBottom()));

    //同等单元
   /* QAction *equlHSpaceAct;
    QAction *equlVSpaceAct;
    QAction *equlWidthAct;
    QAction *equlHeightAct;
    QAction *equlSizeAct;
*/
    //组合单元
    groupObjAct = new QAction(QIcon(":/images/group.png"),QStringLiteral("组合"),this);;
    connect(groupObjAct,SIGNAL(triggered(bool)),this,SLOT(groupObj()));
    ungroupObjAct = new QAction(QIcon(":/images/ungroup.png"),QStringLiteral("解除组合"),this);;
    connect(ungroupObjAct,SIGNAL(triggered(bool)),this,SLOT(ungroupObj()));;


    //绘制项
    lineAct = new QAction(QIcon(":/images/line.png"), QStringLiteral("直线"), this);
    lineAct->setCheckable(true);
    lineAct->setData(Line);
    connect(lineAct,SIGNAL(triggered()),this,SLOT(drawTool()));

    rectAct = new QAction(QIcon(":/images/rectangle.png"), QStringLiteral("矩形"), this);
    rectAct->setCheckable(true);
    rectAct->setData(Rectangle);
    connect(rectAct,SIGNAL(triggered()),this,SLOT(drawTool()));

    ellipseAct = new QAction(QIcon(":/images/ellipse.png"), QStringLiteral("椭圆"), this);
    ellipseAct->setCheckable(true);
    ellipseAct->setData(Ellipse);
    connect(ellipseAct,SIGNAL(triggered()),this,SLOT(drawTool()));

    circleAct = new QAction(QIcon(":/images/circle.png"),QStringLiteral("圆"),this);
    circleAct->setCheckable(true);
    circleAct->setData(Circle);
    connect(circleAct,SIGNAL(triggered()),this,SLOT(drawTool()));

    hexagonAct = new QAction(QIcon(":/images/polygon.png"),QStringLiteral("多边形"),this);
    hexagonAct->setCheckable(true);
    hexagonAct->setData(Polygon);
    connect(hexagonAct,SIGNAL(triggered()),this,SLOT(drawTool()));

    polylineAct = new QAction(QIcon(":/images/polyline.png"),QStringLiteral("折线"),this);
    polylineAct->setCheckable(true);
    polylineAct->setData(Polyline);
    connect(polylineAct,SIGNAL(triggered()),this,SLOT(drawTool()));

    arcAct = new QAction(QIcon(":/images/arc.png"), QStringLiteral("弧线"), this);
    arcAct->setCheckable(true);
    arcAct->setData(Arc);
    connect(arcAct,SIGNAL(triggered()),this,SLOT(drawTool()));

    //fanAct = new QAction(QIcon(":/images/pie.png"),QStringLiteral("饼型"),this);
    //fanAct->setCheckable(true);
    //connect(fanAct,SIGNAL(triggered()),this,SLOT(drawFan()));

    textAct = new QAction(QIcon(":/images/text.png"),QStringLiteral("文字"),this);
    textAct->setCheckable(true);
    textAct->setData(Text);
    connect(textAct,SIGNAL(triggered()),this,SLOT(drawTool()));

    selectAct = new QAction(QIcon(":/images/select.png"), QStringLiteral("选择"), this);
    selectAct->setData(Select);
    selectAct->setCheckable(true);
    selectAct->setChecked(true);
    connect(selectAct,SIGNAL(triggered(bool)),this,SLOT(selectTool()));

    QActionGroup * actionGroup = new QActionGroup(this);
    actionGroup->addAction(lineAct);
    actionGroup->addAction(polylineAct);
    actionGroup->addAction(rectAct);
    actionGroup->addAction(ellipseAct);
    actionGroup->addAction(circleAct);
    actionGroup->addAction(hexagonAct);
    actionGroup->addAction(arcAct);
    //actionGroup->addAction(fanAct);
    actionGroup->addAction(textAct);
    actionGroup->addAction(selectAct);


    tileAct = new QAction(tr("&Tile"), this);
    tileAct->setStatusTip(tr("Tile the windows"));


    cascadeAct = new QAction(tr("&Cascade"), this);
    cascadeAct->setStatusTip(tr("Cascade the windows"));


    nextAct = new QAction(tr("Ne&xt"), this);
    nextAct->setShortcuts(QKeySequence::NextChild);
    nextAct->setStatusTip(tr("Move the focus to the next window"));


    previousAct = new QAction(tr("Pre&vious"), this);
    previousAct->setShortcuts(QKeySequence::PreviousChild);
    previousAct->setStatusTip(tr("Move the focus to the previous "
                                 "window"));


    //windowMenuSeparatorAct = new QAction(this);
    //windowMenuSeparatorAct->setSeparator(true);


   // menuBar()->addSeparator();

    //QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

    aboutAct = new QAction(QStringLiteral("关于"), this);
    connect(aboutAct,SIGNAL(triggered()),this,SLOT(about()));
    aboutAct->setStatusTip(tr("Show the application's About box"));

    //QAction *aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    //aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));

 //////////draw Toool/////////////////////
}


void HIconMainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("fileBar"));
    fileToolBar->setIconSize(QSize(32,32));
    //fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(quitAct);


    editToolBar = addToolBar(tr("editBar"));
    editToolBar->setIconSize(QSize(32,32));
    editToolBar->addAction(undoAct);
    editToolBar->addAction(redoAct);
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);
    editToolBar->addAction(deleteAct);

    shapeToolBar = addToolBar(tr("shapeToolBar"));
    shapeToolBar->addAction(toTopAct);
    shapeToolBar->addAction(toBottomAct);

    zoomToolBar = addToolBar(tr("zoomBar"));
    zoomToolBar->setIconSize(QSize(32,32));
    zoomToolBar->addAction(fitWidthAct);
    zoomToolBar->addAction(fitHeightAct);
    zoomToolBar->addAction(zoomInAct);
    zoomToolBar->addAction(zoomOutAct);
    zoomToolBar->addAction(zoomOriAct);
    zoomToolBar->addWidget(scaleComboBox);

    drawToolBar = addToolBar(tr("drawToolBar"));
    drawToolBar->setIconSize(QSize(32,32));
    drawToolBar->addAction(lineAct);
    drawToolBar->addAction(polylineAct);
    drawToolBar->addAction(rectAct);
    drawToolBar->addAction(ellipseAct);
    drawToolBar->addAction(circleAct);
    drawToolBar->addAction(hexagonAct);
    drawToolBar->addAction(arcAct);
    drawToolBar->addAction(fanAct);
    drawToolBar->addAction(textAct);
/*
    shapeToolBar = new QToolBar(tr("shapeToolBar"),this);
    shapeToolBar->setIconSize(QSize(32,32));
    shapeToolBar->addAction(groupObjAct);
    shapeToolBar->addAction(ungroupObjAct);
    shapeToolBar->addAction(alignLeftAct);
    shapeToolBar->addAction(alignVCenterAct);
    shapeToolBar->addAction(alignRightAct);
    shapeToolBar->addAction(alignTopAct);
    shapeToolBar->addAction(alignHCenterAct);
    shapeToolBar->addAction(alignBottomAct);
    shapeToolBar->addAction(toTopAct);
    shapeToolBar->addAction(toBottomAct);
    addToolBar(Qt::BottomToolBarArea,shapeToolBar);
*/



    otherBar = addToolBar(tr("other"));
    otherBar->addAction(selectAct);
    otherBar->addAction(groupObjAct);
    otherBar->addAction(ungroupObjAct);
    //otherBar->addAction(rotateAct);
}

void HIconMainWindow::createMenuBars()
{
    fileMenu = menuBar()->addMenu(QStringLiteral("文件(&F)"));
    //fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

    editMenu = menuBar()->addMenu(QStringLiteral("编辑(&E)"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);


    viewMenu = menuBar()->addMenu(QStringLiteral("视图(&V)"));
    viewMenu->addAction(showRulerAct);
    viewMenu->addAction(showGridAct);
    viewMenu->addAction(showCLineAct);

    toolMenu = menuBar()->addMenu(QStringLiteral("绘制(&W)"));
    toolMenu->addAction(lineAct);
    toolMenu->addAction(polylineAct);
    toolMenu->addAction(rectAct);
    toolMenu->addAction(ellipseAct);
    toolMenu->addAction(hexagonAct);
    toolMenu->addAction(arcAct);
    toolMenu->addAction(fanAct);
    toolMenu->addAction(textAct);

    helpMenu = menuBar()->addMenu(QStringLiteral("帮助(&H)"));
    helpMenu->addAction(aboutAct);
}

void HIconMainWindow::createDockWindows()
{

    QDockWidget* browserIconDock = new QDockWidget(QStringLiteral("图元浏览框"),this);
    browserIconDock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    m_pIconTreeWidget = new HIconTreeWidget(m_pIconEditorMgr);
    m_pIconTreeWidget->setRootIsDecorated(true);
    m_pIconTreeWidget->setSortingEnabled(false);
    browserIconDock->setWidget(m_pIconTreeWidget);
    addDockWidget(Qt::LeftDockWidgetArea,browserIconDock);
    m_pIconTreeWidget->init();

    connect(m_pIconTreeWidget,SIGNAL(IconNew(const QString&,const QString&,const int&)),this,SLOT(New(const QString&,const QString&,const int&)));
    connect(m_pIconTreeWidget,SIGNAL(IconDel(const QString&,const int&,const QString&)),this,SLOT(Del(const QString&,const int&,const QString&)));
    connect(m_pIconTreeWidget,SIGNAL(IconOpen(const QString&,const int&,const QString&)),this,SLOT(Open(const QString&,const int&,const QString&)));

    /*
    QDockWidget* iconPreviewDock = new QDockWidget(QStringLiteral("图元预览框"),this);
    iconPreviewDock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    pIconPreview = new HIconPreview(pIconMgr);
    iconPreviewDock->setWidget(pIconPreview);
    addDockWidget(Qt::RightDockWidgetArea,iconPreviewDock);*/
}

void HIconMainWindow::newFile()
{
    //New(strName);

}

void HIconMainWindow::open()
{

}

void HIconMainWindow::save()
{
    m_pIconEditorMgr->Save(true);
}

void HIconMainWindow::saveAs()
{

}

//关闭
bool HIconMainWindow::close()
{
    QMessageBox mb(QStringLiteral("警告"),QStringLiteral("退出前需要保存所有图符模板吗？"),
            QMessageBox::Information,QMessageBox::Yes | QMessageBox::Default,
            QMessageBox::No,QMessageBox::Cancel | QMessageBox::Escape );
    mb.setButtonText( QMessageBox::Yes, QStringLiteral("是") );
    mb.setButtonText( QMessageBox::No, QStringLiteral("否") );
    mb.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
    switch( mb.exec() ) {
        case QMessageBox::Yes:
            Save();
            return true;
        case QMessageBox::Cancel:
            return false;
    default:
        break;

    }
    return true;
}

//退出
void HIconMainWindow::quit()
{

}


void HIconMainWindow::New(const QString& strTemplateName,const QString& strCatalogName,const int& nCatalogType)
{
    if(!m_pIconEditorMgr && !m_pIconEditorMgr->iconTemplate())
        return;

    HIconTemplate* pTemplate = m_pIconEditorMgr->iconEditorDocument()->findIconTemplateByTemplateName(strTemplateName);
    if(pTemplate)
    {
        QMessageBox::information(this,QStringLiteral("提醒"),QStringLiteral("已经存在相同名字的模板文件，请修改名称"),QMessageBox::Ok);
        return;
    }

    if(m_pIconEditorMgr->iconTemplate()->getModify())
    {
        if(QMessageBox::Ok == QMessageBox::information(NULL,QStringLiteral("提醒"),QStringLiteral("需要保存当前的模板文件吗？"),QMessageBox::Yes|QMessageBox::No))
        {
             Save();
        }
    }

    m_pIconEditorMgr->New(strTemplateName,strCatalogName,nCatalogType);
    m_pIconEditorWidget->setIconEditorMgr(m_pIconEditorMgr);
    m_pIconTreeWidget->addIconTreeWigetItem();
    //pIconPreview->init();

    updateMenu();
}


void HIconMainWindow::Open(const QString &strTemplateName, int nTemplateType, const QString &strUuid)
{
    if(!m_pIconEditorMgr && !m_pIconEditorMgr->iconTemplate())
        return;
    if(m_pIconEditorMgr->iconTemplate()->getModify())
    {
        if(QMessageBox::Ok == QMessageBox::information(NULL,QStringLiteral("提醒"),QStringLiteral("需要保存当前的模板文件吗？"),QMessageBox::Ok|QMessageBox::Cancel))
        {
            Save();
        }
    }

    m_pIconEditorMgr->Open(strTemplateName,nTemplateType,strUuid);
    m_pIconEditorWidget->setIconEditorMgr(m_pIconEditorMgr);
    //pIconPreview->init();

    HIconTemplate *pIconTemplate = m_pIconEditorMgr->iconTemplate();
    QString strTitle = pIconTemplate->getCatalogName() + "/" + pIconTemplate->getSymbol()->getSymolName() + pIconTemplate->getUuid().toString();
    strTitle = QString("%1[*] - %2").arg(strTitle).arg(QStringLiteral("图元编辑器"));
    setWindowTitle(strTitle);
}

void HIconMainWindow::Save()
{
    m_pIconEditorMgr->Save();
}

//
void HIconMainWindow::Del(const QString &strTemplateName, int nTemplateType, const QString &strUuid)
{
    if(!m_pIconEditorWidget || !m_pIconEditorMgr)
        return;
    m_pIconTreeWidget->delIconTreeWidgetItem();
    m_pIconEditorMgr->Del(strTemplateName,nTemplateType,strUuid);
    m_pIconEditorWidget->setIconEditorMgr(0);
    //pIconPreview->init();
}


void HIconMainWindow::about()
{
    HAbout about;
    about.exec();
}

void HIconMainWindow::resizeEvent(QResizeEvent *event)
{
}

void HIconMainWindow::closeEvent(QCloseEvent *event)
{
    if (close()) {
            Save();
            event->accept();
        } else {
            event->ignore();
        }
}

void HIconMainWindow::viewMousePosChanged(const QPoint& pos,const QPointF &logPos)
{
    QString strViewPos = QString("x=%1,y=%2").arg((int)pos.x()).arg((int)pos.y());
    QString strLogicPos =  QString("log:x=%1,y=%2").arg(logPos.x(),0,'f',1).arg(logPos.y(),0,'f',1);
    statusBar()->showMessage(strLogicPos + " " + strViewPos);
}

void HIconMainWindow::scaleChanged(QString strScale)
{
    if(strScale.isEmpty())
        return;
    if(strScale.endsWith("%"))
        strScale = strScale.mid(0,strScale.lastIndexOf("%"));
    bool bOk;
    double newscale = strScale.toDouble(&bOk)/100;
    if(!bOk)
        return;
    pIconMgr->getIconFrame()->scaleChangedTo(newscale);
    strScale = QString("%1%").arg(pIconMgr->getIconFrame()->scale()*100);
    scaleComboBox->blockSignals(true);
    scaleComboBox->lineEdit()->setText(strScale);
    scaleComboBox->blockSignals(false);
}

void HIconMainWindow::scaleChanged()
{
    QString strScale = scaleComboBox->lineEdit()->text();
    if(strScale.isEmpty())
        return;
    scaleChanged(strScale);

}

void HIconMainWindow::itemInserted(int type)
{
    selectAct->setChecked(true);
    emit selectAct->triggered();
    //setCursor(Qt::ArrowCursor);
}

void HIconMainWindow::updateMenu()
{
    updateViewMenu();
    updateFileMenu();
    updateEditMenu();
    updateToolMenu();
}

void HIconMainWindow::updateViewMenu()
{
    showRulerAct->setEnabled(m_pIconEditorMgr);
    showCLineAct->setEnabled(m_pIconEditorMgr);
    showGridAct->setEnabled(m_pIconEditorMgr);
}

void HIconMainWindow::updateFileMenu()
{

}

void HIconMainWindow::updateEditMenu()
{
    undoAct->setEnabled(m_pIconEditorMgr&&m_pIconEditorMgr->iconEditorUndoStack()&&m_pIconEditorMgr->iconEditorUndoStack()->canUndo());
    redoAct->setEnabled(m_pIconEditorMgr&&m_pIconEditorMgr->iconEditorUndoStack()&&m_pIconEditorMgr->iconEditorUndoStack()->canRedo());

    bool b = m_pIconEditorMgr&&m_pIconEditorMgr->selectedMgr()&&m_pIconEditorMgr->selectedMgr()->selectObj();
    cutAct->setEnabled(b&&m_pIconEditorMgr->selectedMgr()->selectObj()->getObjList().size()>0);
    copyAct->setEnabled(b&&m_pIconEditorMgr->selectedMgr()->selectObj()->getObjList().size()>0);
    pasteAct->setEnabled(m_pIconEditorMgr&&m_pIconEditorMgr->iconEditorOp()->isClipboardAvailable());
    deleteAct->setEnabled(b&&m_pIconEditorMgr->selectedMgr()->selectObj()->getObjList().size()>0);

    //editDeleteFromPattern->setEnabled(b&&m_pEditMgr->SelectionMgr()->SelectedObj()->pChild.Size()>0);

    //editSelectAll->setEnabled(m_pEditMgr);
    //editFitView->setEnabled(m_pEditMgr);
    //editOptions->setEnabled(m_pEditMgr);
    //editProperty->setEnabled(b);

    //editCustomProperty->setEnabled(m_pEditMgr);
}

void HIconMainWindow::updateToolMenu()
{
    bool b = m_pIconEditorMgr&&m_pIconEditorMgr->selectedMgr()&&m_pIconEditorMgr->selectedMgr()->selectObj();
    int nSelectObjCount = m_pIconEditorMgr->selectedMgr()->selectObj()->getObjList().size();
    groupObjAct->setEnabled(b&&nSelectObjCount>1);
    if(b&&nSelectObjCount==1&&
        m_pIconEditorMgr->selectedMgr()->selectObj()->getObjList().at(0)->getShapeType()==Group){
            ungroupObjAct->setEnabled(true);
        }
    else{
        ungroupObjAct->setEnabled(false);
    }

    lineAct->setEnabled(m_pIconEditorMgr);
    polylineAct->setEnabled(m_pIconEditorMgr);
    rectAct->setEnabled(m_pIconEditorMgr);
    circleAct->setEnabled(m_pIconEditorMgr);
    ellipseAct->setEnabled(m_pIconEditorMgr);
    hexagonAct->setEnabled(m_pIconEditorMgr);
    arcAct->setEnabled(m_pIconEditorMgr);
    textAct->setEnabled(m_pIconEditorMgr);
}

void HIconMainWindow::updateZoomMenus()
{
    fitWidthAct->setEnabled(m_pIconEditorMgr);
    fitHeightAct->setEnabled(m_pIconEditorMgr);
    zoomInAct->setEnabled(m_pIconEditorMgr);
    zoomOutAct->setEnabled(m_pIconEditorMgr);
    zoomOriAct->setEnabled(m_pIconEditorMgr);
    zoomToolBar->setEnabled(m_pIconEditorMgr);
}
