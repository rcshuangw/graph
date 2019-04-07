#ifndef HPOLYLINETOOL_H
#define HPOLYLINETOOL_H
#include "h5drawtool.h"
class H5ICONGUI_EXPORT HPolylineTool: public HDrawTool
{
public:
    HPolylineTool(HToolManager* manager,DrawShape objShape,const QString& name,const QString& uuid);
    virtual ~HPolylineTool();

public:
    virtual void clear();
    virtual void onEvent(HEvent& event);
	virtual void onMousePressEvent(QMouseEvent* event, QVariant &data);
	virtual void onMouseMoveEvent(QMouseEvent* event, QVariant &data);
	virtual void onMouseReleaseEvent(QMouseEvent* event, QVariant &data);

private:
    QPointF m_ptStPoint;
    QPointF m_ptCurPoint;

    QPolygonF m_ptPolygons;
};
#endif // HPOLYLINETOOL_H
