#ifndef HSELECTTOOL_H
#define HSELECTTOOL_H
#include <QObject>
#include "hiconapi.h"
#include "h5event.h"
class HIconEditorMgr;
class HIconEditorSelectToolMgr : public HDrawManager
{
	Q_OBJECT
public:
    HIconEditorSelectToolMgr(HIconEditorMgr* mgr, DrawShape objShape, const QString& name, const QString& uuid);
    virtual ~HIconEditorSelectToolMgr();

public:
	virtual void clear();
	virtual void onEvent(HEvent& event);
	virtual void onMousePress(QMouseEvent* event, QVariant &data);
	virtual void onMouseMove(QMouseEvent* event, QVariant &data);
	virtual void onMouseRelease(QMouseEvent* event, QVariant &data);

	virtual void onMouseDoubleClickEvent(QMouseEvent* event, QVariant &data);
	virtual void onContextMenuEvent(QContextMenuEvent *event, QVariant &data);//ÓÒ¼ü

	virtual void onKeyPressEvent(QKeyEvent *event, QVariant& data);
	virtual QCursor cursor();

signals:
    void refreshSelect(const QRectF& rect);
public slots:
	void onSelectChanged();

private:
	QPointF m_ptStPoint;
	QPointF m_ptCurPoint;
}; 
#endif
