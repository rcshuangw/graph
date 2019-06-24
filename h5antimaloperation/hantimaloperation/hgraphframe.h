#ifndef HONLINEFRAME1_H
#define HONLINEFRAME1_H
#include "hframe.h"
class HGraphView;
class HAntiMalopMgr;
class HGraphFrame : public HFrame
{
    Q_OBJECT

public:
    HGraphFrame(HAntiMalopMgr* mgr,HFrame *parent = 0);
    ~HGraphFrame();

public:
    void crateToolBar();//创建工具栏
    void initGraphFrame();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
private:
    HGraphView* m_pGraphView;
    HAntiMalopMgr* m_pAntiMalpoMgr;
};

#endif // HONLINEFRAME1_H
