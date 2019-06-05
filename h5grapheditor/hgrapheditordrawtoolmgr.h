#ifndef HGRAPHEDITORDRAWTOOLMGR_H
#define HGRAPHEDITORDRAWTOOLMGR_H
#include "hiconapi.h"
#include "hdrawmanager.h"
/*
 * 图符绘制管理类：主要是针对图符的绘制过程
*/
class HGraphEditorMgr;
class HGraphEditorDrawToolMgr : public HDrawManager
{
    Q_OBJECT
public:
    HGraphEditorDrawToolMgr(HGraphEditorMgr* pMgr);
    ~HGraphEditorDrawToolMgr();

    void setDrawShape(DrawShape drawShape){curDrawShape = drawShape;}
    DrawShape getDrawShape(){return curDrawShape;}
    void appendObj(HBaseObj* obj);

public:
    DrawShape curDrawShape;//当前绘制对象
    HGraphEditorMgr* m_pGraphEditorMgr;
};


#endif // HGRAPHEDITORDRAWTOOLMGR_H
