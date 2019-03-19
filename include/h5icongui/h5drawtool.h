#ifndef H5DRAWTOOL_H
#define H5DRAWTOOL_H
#include "h5iconguiexport.h"
#include "h5event.h"
#include "h5iconlib/hbaseobj.h"

class HDrawManager; //绘制管理
class H5ICONGUI_EXPORT HDrawTool
{
public:
    HDrawTool(HDrawManager* manager,DrawShape drawShape,const QString& name,const QString& uuid);
    virtual ~HDrawTool();

public:
    virtual void clear();
    virtual void onEvent(HEvent& event);

    virtual void onMousePress(QMouseEvent* event,QVariant &data) = 0;
    virtual void onMouseMove(QMouseEvent* event,QVariant &data) = 0;
    virtual void onMouseRelease(QMouseEvent* event,QVariant &data) = 0;
public:
    DrawShape drawShape() {return m_edrawShape;}
    QString objTypeName(){ return m_strObjName;}
    QString templateUuid() {return m_strObjUuid;}
    HDrawManager* drawManager(){return m_pDrawManager;}

protected:
    HDrawManager* m_pDrawManager;
    DrawShape m_edrawShape;
    QString m_strObjName;
    QString m_strObjUuid;
};

