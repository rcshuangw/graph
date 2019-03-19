#ifndef HPOLYLINETOOL_H
#define HPOLYLINETOOL_H
#include "h5drawtool.h"
class H5ICONGUI_EXPORT HPolylineTool: public HDrawTool
{
public:
    HPolylineTool(HDrawManager* manager,DrawShape objShape,const QString& name,const QString& uuid);
    virtual ~HPolylineTool();

public:
    virtual void clear();
    virtual void onEvent(HEvent& event);
    virtual void onMousePress(QMouseEvent* event,QVariant &data);
    virtual void onMouseMove(QMouseEvent* event,QVariant &data);
    virtual void onMouseRelease(QMouseEvent* event,QVariant &data);

private:
    QPointF m_ptStPoint;
    QPointF m_ptCurPoint;

    QPolygonF m_ptPolygons;
};
#endif // HPOLYLINETOOL_H
