﻿#ifndef HICONMAINWINDOW_H
#define HICONMAINWINDOW_H

#include <QMainWindow>
#include "hicontreewidget.h"
#include <QAction>
#include <QHBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QComboBox>

class HIconEditorFrame;
class HIconEditorMgr;
class HIconTreeWidget;
class HIconEditorWidget;
class HIconEditorPreview;
class HIconMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit HIconMainWindow(HIconEditorMgr *parent = 0);
    ~HIconMainWindow();
public:
    void init();

protected:
    virtual void resizeEvent(QResizeEvent* event);
    void closeEvent(QCloseEvent *event);
private:
    HIconEditorMgr* m_pIconEditorMgr;
    HIconEditorFrame* m_pIconEditorFrame;
    HIconEditorWidget* m_pIconEditorWidget;
    HIconTreeWidget* m_pIconTreeWidget;
    HIconEditorPreview* m_pIconEditorPreview;
signals:



private slots:
    void newFile();
    void open();
    void save();
    void saveAs();

    //opera
    void showGrid();
    void showCenterLine();

    //draw tool
    void drawTool();
    void selectTool();

    //scaleComboBox
    void scaleChanged(QString strScale);
    void scaleChanged();
    //scene
    void itemInserted(int type);

    //
    /*  QMenu *windowMenu;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *toolMenu;
    QMenu* helpMenu;
*/
    void updateMenu();
    void updateViewMenu();
    void updateFileMenu();
    void updateEditMenu();
    void updateToolMenu();
#ifndef QT_NO_CLIPBOARD
    //void cut();
    //void copy();
    //void paste();
#endif
    void about();

public slots:

    //关闭
    bool close();

    //退出
    void quit();

    //保存 true 文件 false 库
    //void save();

    //新建对象
    void New(const QString& strTemplateName,const QString& strCatalogName,const int& nCatalogType);

    //打开 save falg = true
    void Open(const QString &strTemplateName, int nTemplateType, const QString &strUuid);

    void Del(const QString &strTemplateName, int nTemplateType, const QString &strUuid);

    void Rename(const QString& strTemplateName,const int& nTemplateType, const QString &strUuid);

    void Save();

    //撤销
    void undo();

    //重做
    void redo();

    //剪切
    void cut();

    //复制
    void copy();

    //粘贴
    void paste();

    //删除
    void del();

    //合适宽度
    void fitWidth();

    //合适高度
    void fitHeight();

    //放大
    void zoomIn();

    //缩小
    void zoomOut();

    //组合
    void groupObj();

    //解除组合
    void ungroupObj();

    //移动到顶层
    void bringToTop();

    //移动到底层
    void bringToBottom();

    //上移一层
    void bringToUp();

    //下移一层
    void bringToDown();

    //其他槽函数
    void viewMousePosChanged(const QPoint&,const QPointF &);
    void onSelectTool();

    void onSetAttribute();

    void onSelectChanged();
//函数
private:
    void createActions();
    void createStatusBar();
    void createMenuBars();
    void createToolBars();
    void createDockWindows();
    void updateZoomMenus();
//菜单的项
private:

    QMenu *windowMenu;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *toolMenu;
    QMenu* helpMenu;


    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *zoomToolBar;
    QToolBar *drawToolBar;
    QToolBar *shapeToolBar;
    QToolBar *otherBar;

    //文件单元
    QAction *newAct;
    QAction *saveAct;
    QAction *openAct;
    QAction *closeAct;
    QAction *quitAct;

    //撤销单元
    QAction *undoAct;
    QAction *redoAct;

    //编辑单元
#ifndef QT_NO_CLIPBOARD
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *deleteAct;
#endif

    //标尺单元
    QAction *showRulerAct;
    QAction *showGridAct;
    QAction *showCLineAct;

    //缩放单元
    QAction *fitWidthAct;
    QAction *fitHeightAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *zoomOriAct;
    QComboBox *scaleComboBox;

    //其他单元
    QAction *selectAct;
    QAction *rotateAct;
/*
    //对其单元
    QAction *alignLeftAct;
    QAction *alignRightAct;
    QAction *alignHCenterAct;
    QAction *alignVCenterAct;
    QAction *alignTopAct;
    QAction *alignBottomAct;

    //同等单元
    QAction *equlHSpaceAct;
    QAction *equlVSpaceAct;
    QAction *equlWidthAct;
    QAction *equlHeightAct;
    QAction *equlSizeAct;

    //翻转
    QAction *hTurnAct;
    QAction *vTurnAct;
    QAction *rotateLeftAct;
    QAction *rotateRightAct;
*/
    //组合单元
    QAction *groupObjAct;
    QAction *ungroupObjAct;



    //移动
    QAction *toTopAct;
    QAction *toBottomAct;
    QAction *toUpAct;
    QAction *toDownAct;

    //draw Tool
    QAction* lineAct;
    QAction* ellipseAct;
    QAction* rectAct;
    QAction* arcAct;
    QAction* circleAct;
    QAction* hexagonAct;
    QAction* polylineAct;
    //QAction* fanAct;
    QAction* textAct;

    //其他
    QAction *selectAllAct;
    QAction *deleteAllAct;
    QAction *AttributeAct;
    QAction *pageAttrAct;

    //关于
    QAction* aboutAct;

};

#endif // HICONMAINWINDOW_H
