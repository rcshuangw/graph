#ifndef HSELECTEDMGR_H
#define HSELECTEDMGR_H
#include <QObject>
#include <QPainter>
#include "h5iconguiexport.h"
#include "hbaseobj.h"
/*
管理选中的图元
*/
class HBaseObj;
class HTempContainer;
class HDrawHelper;
class H5BASEGUI_EXPORT HSelectedMgr : public QObject
{
    Q_OBJECT
public:
	HSelectedMgr();
    ~HSelectedMgr();

public:
    void paint(QPainter* painter,const QRectF& rect,const QRectF &selectRect = QRectF());
    void addObj(HBaseObj* obj);
    void removeObj(HBaseObj* obj);
    void setSelectObj(QList<HBaseObj*> objs);
    void selectChanged(HBaseObj* obj,bool isSelect);
    void clear();
    bool isSelected(HBaseObj* obj);
    int isOnPoint(const QPointF& point,QPointF& selectPoint);
    bool isOnObj(const QPointF& point);//在point点上是否选中obj
    void refreshObjs();
    void recalcSelect();
    HTempContainer* selectObj() {return m_pTempContainer;}

private:
    void calcPoints();

signals:
	void refreshSelect(const QRectF& rect);
private:
    //HDrawHelper* m_pDrawHelper;
	HTempContainer* m_pTempContainer;
	HPointFList m_selectedPoints;//图元四周的点，供选择使用
	QRectF m_SelectBounding;


};

#endif // HICONSELECTMANAGER_H
