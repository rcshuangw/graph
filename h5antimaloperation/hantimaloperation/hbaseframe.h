#ifndef HBASEFRAME_H
#define HBASEFRAME_H
#include <QScrollArea>
class HAntiMalopMgr;
class HGraphView;
class HGraphScene;
//图形界面基类
class HBaseFrame : public QScrollArea
{
public:
    HBaseFrame(HAntiMalopMgr *mgr,QScrollArea* parent = 0);
    ~HBaseFrame();
public:
    void init();
    void reset();
private:
    HGraphView* m_pGraphView;
    HGraphScene *m_pGraphScene;
    HAntiMalopMgr* m_pAntiMalpoMgr;
};

#endif // HBASEFRAME_H
