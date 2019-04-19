#ifndef HICONSELECTMANAGER_H
#define HICONSELECTMANAGER_H
#include <QObject>
#include <QPainter>
/*
管理选中的图元
*/
class HBaseObj;
class HSelectManager : public QObject
{
    Q_OBJECT
public:
    HSelectManager();
    ~HSelectManager();

public:
    void draw(QPainter* painter,const QRectF& rect,const QRectF &selectRect = QRectF());
    void addObj(HBaseObj* obj);
    void removeObj(HBaseObj* obj);
    void setSelectObj(QList<HBaseObj*> objs);
    void selectChanged(HBaseObj* obj,bool isSelect);
    void clear();
    bool isSelected(HBaseObj* obj);
    int isOnPoint(const QPointF& point,QPointF& selectPoint);
    bool isOnObj(const QPointF& point);//在point点上是否选中obj
    void recalcSelect();

private:
    void calcPoints();

signals:
	void refreshSelect(const QRect& rect);
};

#endif // HICONSELECTMANAGER_H
