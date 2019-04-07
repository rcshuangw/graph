#ifndef HARCTOOL_H
#define HARCTOOL_H
#include "h5drawtool.h"
class H5ICONGUI_EXPORT HArcTool: public HDrawTool
{
public:
    HArcTool(HToolManager* manager,DrawShape objShape,const QString& name,const QString& uuid);
    virtual ~HArcTool();

public:
    virtual void clear();
    virtual void onEvent(HEvent& event);
	virtual void onMousePressEvent(QMouseEvent* event, QVariant &data);
	virtual void onMouseMoveEvent(QMouseEvent* event, QVariant &data);
	virtual void onMouseReleaseEvent(QMouseEvent* event, QVariant &data);

private:
    QPointF m_ptStPoint;
    QPointF m_ptCurPoint;

    int startAngle;//起始角度
    int spanAngle;//旋转角度
};
#endif // HARCTOOL_H
