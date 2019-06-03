#ifndef HARCTOOL_H
#define HARCTOOL_H
#include "h5drawtool.h"

class H5BASEGUI_EXPORT HArcTool: public HDrawTool
{
public:
    enum State
    {
        Rect = 0,
        StartAng = 1,
        SweepLen = 2
    };
    HArcTool(HDrawManager* manager,DrawShape objShape,const QString& name,const QString& uuid);
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

    qint8 m_nArcState;
    int m_nStartAngle;//起始角度
    int m_nSweepLength;//旋转角度
};
#endif // HARCTOOL_H
