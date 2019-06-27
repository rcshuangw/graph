#ifndef HONLINEFRAME1_H
#define HONLINEFRAME1_H
#include "hbaseframe.h"
class HGraphView;
class HAntiMalopMgr;
class HIconObj;
class HGraphFrame : public HBaseFrame
{
    Q_OBJECT

public:
    HGraphFrame(HAntiMalopMgr* mgr,HBaseFrame *parent = 0);
    ~HGraphFrame();
public:
    void openGraph();
public:
    virtual bool onMousePressEvent(QObject *obj, QEvent *event);
    virtual bool onMouseMoveEvent(QObject *obj, QEvent *event);
    virtual bool onMouseReleaseEvent(QObject *obj, QEvent *event);
    virtual bool onMouseDoubleClickEvent(QObject *obj, QEvent *event);
    virtual bool onKeyPressEvent(QObject *obj, QEvent *event);
    virtual bool onWheelEvent(QObject *obj, QEvent *event);
    virtual bool onContextMenuEvent(QObject *obj, QEvent *event);
protected:
    //bool eventFilter(QObject *obj, QEvent *event);

signals:
signals:
    //nType--预演步骤、编辑步骤
    void opeartorStepChanged(int nType,OPERATORSHEETSTEP*& step);
public:
    HGraphView* m_pGraphView;
    HIconObj* m_pCurControlBtn; //当前操作的控制点
    HIconObj* m_pMovedCtrlBtn;//移动的控制点
protected:
    int m_nDatabaseID;
    quint8 m_btGraphType;

};

#endif // HONLINEFRAME1_H
