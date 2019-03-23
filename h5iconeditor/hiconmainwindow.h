#ifndef HICONMAINWINDOW_H
#define HICONMAINWINDOW_H

#include <QMainWindow>
#include "hicontreewidget.h"
#include <QAction>
#include <QHBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QComboBox>
#include "hiconframe.h"
#include "hiconwidget.h"
#include "hicondocument.h"
#include "hiconmgr.h"
#include "hiconpreview.h"
class HIconMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit HIconMainWindow(HIconMgr *parent = 0);
    ~HIconMainWindow();
public:
    void init();

protected:
    virtual void resizeEvent(QResizeEvent* event);
    void closeEvent(QCloseEvent *event);
private:
    HIconMgr* pIconMgr;
    HIconFrame* pIconFrame;
    HIconWidget* pIconWidget;
    HIconTreeWidget* pIconTreeWidget;
    HIconPreview* pIconPreview;
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
    void drawLine();
    void drawEllipse();
    void drawRectangle();
    void drawArc();
    void drawCircle();
    void drawHexagon();
    void drawPolyline();
    void drawFan();
    void drawText();
    void drawSelection();

    //scaleComboBox
    void scaleChanged(QString strScale);
    void scaleChanged();
    //scene
    void itemInserted(int type);

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

    //
    void Del(const QString &strTemplateName, int nTemplateType, const QString &strUuid);


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

    //原始大小
    //void normalSize();
/*
    //对齐方式--左对齐
    void alignLeft();

    //右对齐
    void alignRight();

    //水平中间对齐
    void alignHCenter();

    //垂直中间对齐
    void alignVCenter();

    //上对齐
    void alignTop();

    //下对齐
    void alignBottom();

    //同等方式--水平同等间隔
    void equivalentHSpace();

    //垂直同等间隔
    void equivalentVSpace();

    //同等宽度
    void equivalentWidth();

    //同等高度
    void equivalentHeight();

    //同等大小
    void equivalentSize();

    //翻转--水平翻转
    void horizontalTurn();

    //垂直翻转
    void verticalTurn();

    //左旋转
    void rotateLeft();

    //右旋转
    void rotateRight();
*/
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
//函数
private:

    void createActions();
    void createStatusBar();
    void createMenuBars();
    void createToolBars();
    void createDockWindows();
    //void updateMenus();



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

    //组合单元
    QAction *groupObjAct;
    QAction *ungroupObjAct;

    //翻转
    QAction *hTurnAct;
    QAction *vTurnAct;
    QAction *rotateLeftAct;
    QAction *rotateRightAct;

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
    QAction* fanAct;
    QAction* textAct;

    //排列单元
    QAction *tileAct;
    QAction *cascadeAct;
    QAction *nextAct;
    QAction *previousAct;

    //关于
    QAction* aboutAct;

};

#endif // HICONMAINWINDOW_H
