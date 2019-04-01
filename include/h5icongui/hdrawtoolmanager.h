#ifndef HDRAWMANAGER_H
#define HDRAWMANAGER_H

#include <QList>
#include "h5iconlib/hbaseobj.h"
#include "h5event.h"
struct Path
{
    QPainterPath painterPath;
    QPen pen;
    QBrush brush;
    bool coordType; //false 逻辑坐标 true 设备坐标
};

/*
 * 绘制工具管理类
*/
class HDrawTool;
class HDrawManager : public QObject
{
    Q_OBJECT
public:
    HDrawManager();
    ~HDrawManager();
public:
    virtual void onEvent(HEvent& e);

    virtual void selectTool(DrawShape shape,const QString& catalogName,const QString& uuid);
    virtual void appendObj(HBaseObj* obj) = 0;

public:
    bool findTool(DrawShape shape,const QString& catalogName,const QString& uuid);

    void onDrawPath(const QList<Path> &pathList);
    void onEndDraw();

signals:
    void drawPath(const QList<Path> &pathList);
    void endDraw();
public:
    int m_nCurdrawShape;
    HDrawTool *m_pDrawTool;
    QList<HDrawTool*> m_drawToolList;
};

#endif
