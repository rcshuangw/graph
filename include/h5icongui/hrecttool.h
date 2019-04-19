#ifndef HRECTTOOL_H
#define HRECTTOOL_H
#include "h5drawtool.h"

class H5ICONGUI_EXPORT HRectTool: public HDrawTool
{
public:
public:
    HRectTool(HDrawManager* manager,DrawShape objShape,const QString& name,const QString& uuid);
    virtual ~HRectTool();

public:
    virtual void clear();
    virtual void onEvent(HEvent& event);
	virtual void onMousePressEvent(QMouseEvent* event, QVariant &data);
	virtual void onMouseMoveEvent(QMouseEvent* event, QVariant &data);
	virtual void onMouseReleaseEvent(QMouseEvent* event, QVariant &data);

private:
    QPointF m_ptStPoint;
    QPointF m_ptCurPoint;
};

#endif // HRECTTOOL_H
