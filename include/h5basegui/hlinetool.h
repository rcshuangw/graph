#ifndef HLINETOOL_H
#define HLINETOOL_H
#include "h5drawtool.h"
class H5BASEGUI_EXPORT HLineTool: public HDrawTool
{
public:
    HLineTool(HDrawManager* manager,DrawShape objShape,const QString& name,const QString& uuid);
    virtual ~HLineTool();

public:
    virtual void clear();
    virtual void onEvent(HEvent& event);
	virtual void onMousePressEvent(QMouseEvent* event, QVariant &data);
	virtual void onMouseMoveEvent(QMouseEvent* event, QVariant &data);
	virtual void onMouseReleaseEvent(QMouseEvent* event, QVariant &data);

private:
    QPointF m_ptStPoint;
    QPointF m_ptCurPoint;
	bool m_bDrawStart;
};
#endif // HLINETOOL_H
