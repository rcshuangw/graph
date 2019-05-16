#ifndef HSELECTTOOL_H
#define HSELECTTOOL_H
#include <QObject>
#include "hdrawmanager.h"
#include "hiconapi.h"
#include "h5event.h"
#include "hbaseobj.h"
class HIconEditorMgr;
class HDrawHelper;
class HIconEditorSelectTool : public QObject
{
	Q_OBJECT
public:
    HIconEditorSelectTool(HIconEditorMgr* mgr);
    virtual ~HIconEditorSelectTool();
public:
    void setSelectMode(SelectMode mode);
    SelectMode selectMode();
public:
	virtual void clear();
	virtual void onEvent(HEvent& event);
    virtual void onMousePressEvent(QMouseEvent* event, QVariant &data);
    virtual void onMouseMoveEvent(QMouseEvent* event, QVariant &data);
    virtual void onMouseReleaseEvent(QMouseEvent* event, QVariant &data);

	virtual void onMouseDoubleClickEvent(QMouseEvent* event, QVariant &data);
    virtual void onContextMenuEvent(QContextMenuEvent *event, QVariant &data);

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
    SelectMode m_SelectMode;


    QList<HPointFList> m_vlOldPoints;
    int m_nSelPointIndex;
    QPointF m_ptOriPoint;
	QPointF m_ptStPoint;
	QPointF m_ptCurPoint;
    HIconEditorMgr* m_pIconEditorMgr;
    ///是否在选中点上移动
        bool m_bMoveGrab;
}; 
#endif
