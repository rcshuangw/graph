#ifndef HGRAPHEDITOROP_H
#define HGRAPHEDITOROP_H

#include <QObject>
#include "hiconapi.h"
#include "hdrawmanager.h"
#define ICON_DRAW_TOOL   0x01
#define ICON_SELECT_TOOL 0x02
class HGraphEditorMgr;
class HBaseObj;
class HGraphEditorOp : public QObject
{
    Q_OBJECT
public:
    HGraphEditorOp(HGraphEditorMgr* mgr);
    ~HGraphEditorOp();
public:
    void setGraphicsView();

    void cut();
    void copy();
    void paste();
    void del();
    QString getClipboardFile();
    bool isClipboardAvailable();

    void bringToTop();
    void bringToBottom();

    void groupObj();
    void ungroupObj();
public:
    void alignLeft();
    void alignRight();
    void alignHCenter();
    void alignTop();
    void alignBottom();
    void alignVCenter();
    void alignAlgorithm();
public: //等宽
    void sizeEqualWidth();
    void sizeEqualHeight();
    void sizeEqualComplete();
    void sizeHEqualSpace();
    void sizeVEqualSpace();
    bool getbenchMarkSize(QPointF& pt);
    void equalAlgorithm();
public: //旋转
    void flipLeft90();
    void flipRight90();
    void flipHorizon();
    void flipVertical();
    void flipAlgorithm();
public:
    void zoomIn();
    void zoomOut();
    void zoom();
    void zoomSame();
    void setupMatrix();
public:
    int toolType() {return m_nToolType;}
    void drawTool(DrawShape drawShape);
    void selectTool(SelectMode select);
    void switchSelectTool();

public:
    void createIconObj(const QString&,const QString&,int shape,QPointF,QList<H5GraphicsItem*> &items);
    void ObjCreated(HBaseObj* pObj,bool bPaste = false);
    void addIconObj(HBaseObj* pObj,bool bPaste = false);

    void objSelectChanged(HBaseObj *obj, bool isSelected);
    void onUpdateStatus(const QString& text);
public slots:
    void onDrawPath(const QList<Path>& path);
    void onEndDraw();
signals:
    void setSelectTool();
    void updateStatus(const QString& text);
    void updateBaseAction(HBaseObj* obj);
private:
    HGraphEditorMgr* m_pGraphEditorMgr;
    Qt::Alignment m_Alignment;
    IconSize m_Equalway;
    IconFlip m_Flipway;
    qreal m_scale;
    int m_nToolType;

};

#endif // HGRAPHEDITOROP_H
