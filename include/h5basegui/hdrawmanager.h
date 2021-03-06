#ifndef HDRAWMANAGER_H
#define HDRAWMANAGER_H

#include <QList>
#include "hbaseobj.h"
#include "h5event.h"
struct Path
{
    QPainterPath painterPath;
    QPen pen;
    QBrush brush;
    bool coordType; //false 逻辑坐标 true 设备坐标
};

//界面上绘制的基本属性
struct DrawAttribute
{
    QFont font;
    QPen drawPen;
    QPen textPen;
    QBrush brush;
};
/*
 * 绘制工具管理类
*/
class HDrawTool;
class H5BASEGUI_EXPORT HDrawManager : public QObject
{
    Q_OBJECT
public:
	HDrawManager();
    ~HDrawManager();
public:
    virtual void onEvent(HEvent& e);
    virtual void selectTool(DrawShape shape,const QString& catalogName=QString(),const QString& uuid = QString());
    virtual void appendObj(HBaseObj* obj) = 0;
    virtual QCursor cursor() const;
public:
    bool findTool(DrawShape shape,const QString& catalogName = QString(),const QString& uuid = QString());
    void onDrawPath(const QList<Path> &pathList);
    void onEndDraw();

signals:
    void drawPath(const QList<Path> &pathList);
    void endDraw();

public:
    DrawAttribute m_vDrawAttribute;
protected:
    int m_nCurdrawShape;
    HDrawTool *m_pDrawTool;
    QList<HDrawTool*> m_drawToolList;
};

#endif
