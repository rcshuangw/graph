#ifndef HSELECTTOOL_H
#define HSELECTTOOL_H
#include "h5drawtool.h"
class H5ICONGUI_EXPORT HSelectTool : public HDrawTool
{
	Q_OBJECT
public:
	HSelectTool(HToolManager* manager, DrawShape objShape, const QString& name, const QString& uuid);
	virtual ~HSelectTool();

public:
	virtual void clear();
	virtual void onEvent(HEvent& event);
	virtual void onMousePress(QMouseEvent* event, QVariant &data);
	virtual void onMouseMove(QMouseEvent* event, QVariant &data);
	virtual void onMouseRelease(QMouseEvent* event, QVariant &data);

	virtual void onMouseDoubleClickEvent(QMouseEvent* event, QVariant &data);
	virtual void onContextMenuEvent(QContextMenuEvent *event, QVariant &data);//ср╪Э

	virtual void onKeyPressEvent(QKeyEvent *event, QVariant& data);
	virtual QCursor cursor();

public slots:
	void onSelectChanged();

private:
	QPointF m_ptStPoint;
	QPointF m_ptCurPoint;
}; 
#endif
