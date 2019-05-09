#ifndef HICONEDITORDRAWTOOLMGR_H
#define HICONEDITORDRAWTOOLMGR_H
#include "hiconapi.h"
#include "hdrawmanager.h"
/*
 * 图符绘制管理类：主要是针对图符的绘制过程
*/
class HIconEditorMgr;
class HIconEditorDrawToolMgr : public HDrawManager
{
    Q_OBJECT
public:
    HIconEditorDrawToolMgr(HIconEditorMgr* pMgr);
    ~HIconEditorDrawToolMgr();

    void setDrawShape(DrawShape drawShape){curDrawShape = drawShape;}
    DrawShape getDrawShape(){return curDrawShape;}
     void appendObj(HBaseObj* obj);

public:
    DrawShape curDrawShape;//当前绘制对象
    HIconEditorMgr* m_pIconEditorMgr;
};


#endif // HICONSTATE_H
