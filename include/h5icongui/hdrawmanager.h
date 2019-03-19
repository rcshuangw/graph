#ifndef HDRAWMANAGER_H
#define HDRAWMANAGER_H

#include <QList>
#include "h5iconlib/hbaseobj.h"
#include "h5event.h"
class HDrawTool;
class HDrawManager
{
public:
    HDrawManager();
    ~HDrawManager();
public:
    virtual void onEvent(HEvent& e);

    virtual void selectTool(DrawShape shape,const QString& catalogName,const QString& uuid);
    virtual void appendBaseObj(HBaseObj* obj) = 0;

    bool findTool(DrawShape shape,const QString& catalogName,const QString& uuid);


public:
    int m_nCurdrawShape;
    HDrawTool *m_pDrawTool;
    QList<HDrawTool*> m_drawToolList;
};

#endif
