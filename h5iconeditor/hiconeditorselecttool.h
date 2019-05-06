﻿#ifndef HSELECTTOOL_H
#define HSELECTTOOL_H
#include <QObject>
#include "hiconapi.h"
#include "h5event.h"
#include "hbaseobj.h"
class HIconEditorMgr;
class HDrawHelper;
class HIconEditorSelectToolMgr : public QObject
{
	Q_OBJECT
public:
    HIconEditorSelectToolMgr(HIconEditorMgr* mgr);
    virtual ~HIconEditorSelectToolMgr();

public:
	virtual void clear();
	virtual void onEvent(HEvent& event);
    virtual void onMousePressEvent(QMouseEvent* event, QVariant &data);
    virtual void onMouseMoveEvent(QMouseEvent* event, QVariant &data);
    virtual void onMouseReleaseEvent(QMouseEvent* event, QVariant &data);

	virtual void onMouseDoubleClickEvent(QMouseEvent* event, QVariant &data);
	virtual void onContextMenuEvent(QContextMenuEvent *event, QVariant &data);//ÓÒ¼ü

	virtual void onKeyPressEvent(QKeyEvent *event, QVariant& data);
	virtual QCursor cursor();
public:
    bool eventFilter(QObject *obj, QEvent *ev);
signals:
    void refreshSelect(const QRectF& rect);
public slots:
	void onSelectChanged();

private:
    QWidget* m_SelectWidget;
    bool m_bIsSelectPoint;
    SELECTMODE m_SelectMode;


    QList<HPointFList> m_vlOldPoints;
    int m_nSelPointIndex;
    QPointF m_ptOriPoint;
	QPointF m_ptStPoint;
	QPointF m_ptCurPoint;
    HIconEditorMgr* m_pIconEditorMgr;
    HDrawHelper* m_pDrawHelper;
}; 
#endif
