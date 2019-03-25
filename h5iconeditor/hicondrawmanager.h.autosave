#ifndef HICONSTATE_H
#define HICONSTATE_H
#include <QObject>
#include <QPainterPath>
#include "hiconapi.h"
#include "hbaseobj.h"
#include "hiconeditormgr.h"
#include "hdrawmanager.h"
class HIconEditorMgr;
class HIconDrawManager : HDrawManager
{
    Q_OBJECT
public:
    HIconDrawManager(HIconEditorMgr* pMgr);
    ~HIconDrawManager();

    void setDrawShape(DrawShape drawShape){curDrawShape = drawShape;}
    DrawShape getDrawShape(){return curDrawShape;}
     void appendObj(HBaseObj* obj);

public:
    DrawShape curDrawShape;//当前绘制对象
    HIconEditorMgr* pIconMgr;
};


#endif // HICONSTATE_H
