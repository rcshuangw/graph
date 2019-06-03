#ifndef HGRAPHEDITOROP_H
#define HGRAPHEDITOROP_H

#include <QObject>
#include "hiconapi.h"
class HGraphEditorMgr;
class HBaseObj;
class HGraphEditorOp
{
public:
    HGraphEditorOp(HGraphEditorMgr* mgr);
    ~HGraphEditorOp();
public:
    void cut();
    void copy();
    void paste();
    void del();
    QString getClipboardFile();

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
    void onDrawPath(const QList<Path>& path);
    void onEndDraw();
    void drawTool(DrawShape drawShape);
    void selectTool(SelectMode select);
    void switchSelectTool();

public:
    void createIconObj(const QString&,const QString&,int shape,QPointF,QList<HIconGraphicsItem*> &items);
    void ObjCreated(HBaseObj* pObj,bool bPaste = false);
    void addIconObj(HBaseObj* pObj,bool bPaste = false);

    void objSelectChanged(HBaseObj *obj, bool isSelected);
    void onUpdateStatus(const QString& text);
public slots:

signals:
    void updateStatus(const QString& text);
    void updateBaseAction(HBaseObj* obj);
private:
    HGraphEditorMgr* m_pGraphEditorMgr;
    Qt::Alignment m_Alignment;
    IconSize m_Equalway;
    IconFlip m_Flipway;
    qreal m_scale;

};

#endif // HGRAPHEDITOROP_H
