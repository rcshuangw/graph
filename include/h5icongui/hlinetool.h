#ifndef HLINETOOL_H
#define HLINETOOL_H
#include "h5drawtool.h"
class H5ICONGUI_EXPORT HLineTool: public HDrawTool
{
public:
    HLineTool(HDrawManager* manager,DrawShape objShape,const QString& name,const QString& uuid);
    virtual ~HLineTool();

public:
    virtual void clear();
    virtual void onEvent(HEvent& event);
    virtual void onMousePress(QMouseEvent* event,QVariant &data);
    virtual void onMouseMove(QMouseEvent* event,QVariant &data);
    virtual void onMouseRelease(QMouseEvent* event,QVariant &data);

private:
    QPointF m_ptStPoint;
    QPointF m_ptCurPoint;
};
#endif // HLINETOOL_H
