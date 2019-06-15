#ifndef HMAKEICON_H
#define HMAKEICON_H
#include "h5baselibexport.h"
#include "hiconapi.h"
#include <QVector>
#include <QUuid>
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
    HBaseObj* newObj(DrawShape nObjType,const QUuid& uuid,const QString& arg = QString::null, HBaseObj* parent=0);
private:
    HGraph* m_pGraph;
};

#endif // HMAKEICON_H
