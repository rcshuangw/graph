﻿#ifndef HMAKEICON_H
#define HMAKEICON_H
#include "h5baselibexport.h"
#include "hiconapi.h"
#include <QVector>
class HBaseObj;
class HIconTemplate;
class HGraph;
class H5BASELIB_EXPORT HMakeIcon
{
protected:
    HMakeIcon();
public:
    static HMakeIcon* m_pInstance;
    static HMakeIcon* Instance();
    static void Exstance();
    virtual ~HMakeIcon();
public:
    void setGraph(HGraph* graph);
    HGraph* getGraph();
    HBaseObj* newObj(DrawShape nObjType,const QString& arg = QString::null, HBaseObj* parent=0);
    void addObjID(int id);
    void clear();
private:
    int getObjID();
    bool findObjID(int nObjID);


private:
    QVector<int> m_nIdList;
    HGraph* m_pGraph;
};

#endif // HMAKEICON_H
