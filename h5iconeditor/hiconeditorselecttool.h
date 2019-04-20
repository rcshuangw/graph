#ifndef HSELECTTOOL_H
#define HSELECTTOOL_H
#include <QObject>
#include "hiconapi.h"
#include "../include/h5icongui/h5event.h"
class HIconEditorMgr;
class HIconEditorSelectTool : public QObject
{
	Q_OBJECT
public:
	HIconEditorSelectTool(HIconEditorMgr* mgr, DrawShape objShape, const QString& name, const QString& uuid);
	virtual ~HIconEditorSelectTool();

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
