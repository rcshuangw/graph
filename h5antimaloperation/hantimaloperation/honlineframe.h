#ifndef HONLINEFRAME_H
#define HONLINEFRAME_H
#include "hframe.h"
class QSplitter;
class HGraphTreeWidget;
class HGraphFrame;
class HAntiMalopMgr;
class HOnlineFrame:public HFrame
{
public:
    HOnlineFrame(HAntiMalopMgr *mgr,HFrame* parent = 0);
    ~HOnlineFrame();
public:
    void crateToolBar();//创建工具栏
    void initOnlineFrame();
public:
    virtual bool onMousePressEvent(QObject *obj, QEvent *event);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
private:
    HGraphFrame* m_pGraphFrame; //画面显示
    HGraphTreeWidget* m_pGraphTreeWidget; //树形
    HAntiMalopMgr* m_pAntiMalpoMgr;
    QSplitter* m_pSplitter;
    QAction* m_actOpen;
    QAction* m_actPrint;
    QAction* m_actZoomIn;
    QAction* m_actZoomOut;
    QAction* m_actZoom;
    QAction* m_actSelect;
    QAction* m_actHand;
};

#endif // HONLINEFRAME_H
