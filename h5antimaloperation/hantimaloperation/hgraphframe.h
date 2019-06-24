#ifndef HONLINEFRAME1_H
#define HONLINEFRAME1_H
#include "hbaseframe.h"
class HGraphView;
class HAntiMalopMgr;
class HGraphFrame : public HBaseFrame
{
    Q_OBJECT

public:
    HGraphFrame(HAntiMalopMgr* mgr,HBaseFrame *parent = 0);
    ~HGraphFrame();

public:
    void crateToolBar();//创建工具栏
    void initGraphFrame();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
private:
    HGraphView* m_pGraphView;
};

#endif // HONLINEFRAME1_H
