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

private:
    HGraphFrame* m_pGraphFrame; //画面显示
    HGraphTreeWidget* m_pGraphTreeWidget; //树形
    HAntiMalopMgr* m_pAntiMalpoMgr;
    QSplitter* m_pSplitter;
};

#endif // HONLINEFRAME_H
