#ifndef HGRAPHEDITOROP_H
#define HGRAPHEDITOROP_H

#include <QObject>
#include "hiconapi.h"
class HGraphEditorMgr;
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
    bool getbenchMarkPoint(QPointF& pt);
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
    void createIconObj(const QString&,const QString&,int shape,QPointF,QList<HIconGraphicsItem*> &items);
    void ObjCreated(HBaseObj* pObj);
    void addIconObj(HBaseObj* pObj,bool bPaste = false);

private:
    HGraphEditorMgr* m_pGraphEditorMgr;
    Qt::Alignment m_Alignment;
    IconSize m_Equalway;
    IconFlip m_Flipway;
    qreal m_scale;

};

#endif // HGRAPHEDITOROP_H
