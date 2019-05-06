#ifndef HICONFRAME_H
#define HICONFRAME_H
#include "hframe.h"
#include "hiconeditorscene.h"
#include <QWidget>
#include <QRectF>
#include <QResizeEvent>
#include "hbaseobj.h"

/*
 * 界面相关类：主要是QGraphicsView的QWidget容器界面类
 * 单个界面
*/

class HIconEditorMgr;
struct Path;
class HIconEditorFrame : public HFrame
{
    Q_OBJECT
public:
    HIconEditorFrame(QWidget * parent = 0, Qt::WindowFlags f = 0 );
    HIconEditorFrame(HIconEditorMgr* pMgr,QWidget * parent = 0, Qt::WindowFlags f = 0 );
    ~HIconEditorFrame();

public:

    //创建Item和绘制相关信息
    void drawPath(const QList<Path>& pathList);
    void endDraw();

    //在widget的scene上创建、删除图符
    void objCreated(HBaseObj* obj,bool isPaste);
    void objRemoved(HBaseObj* obj);

    //刷新选中点、选中框
    void refreshSelected(const QRectF& rect);

    //鼠标的改变
    void cursorChanged(const QCursor& cursor);

public slots:

    //对象选择状态发生改变
    void onObjSelectChanged(HBaseObj* obj,bool isSelected);

    //重新计算选择状态情况下的obj
    void onRecalcSelect();
protected:

    //事件过滤
    virtual bool eventFilter( QObject *obj, QEvent *event);//过滤的对象，过滤的事件

private:
    HIconEditorMgr* m_pIconEditorMgr;

};

#endif // HICONFRAME_H
