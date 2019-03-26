#ifndef HICONFRAME_H
#define HICONFRAME_H
#include "hframe.h"
#include "hiconscene.h"
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
    void objCreated(HBaseObj* obj,bool isPaste);
    void objRemoved(HBaseObj* obj);


    //刷新选中点、选中框
    void refreshSelected(const QRectF& rect);

    //鼠标的改变
    void cursorChanged(const QCursor& cursor);

public:

    void setIconMgr(HIconEditorMgr* iconmgr);

    //设置scene的逻辑区域
    void setLogicRect(QRectF& rectF);

    //获取scene的区域
    QRectF getLogicRect();

    //获取frame里面的scene对象
    HIconScene* getIconScene();

    //设置显示方案对象的显示和隐藏功能
    void setItemVisible(int nPatternId);

    //获取item
    HIconGraphicsItem* getIconGraphicsItemByObj(HBaseObj* pObj);

//////////////////////////////////////////////以下为pattern的操作//////////////////////////////////////////
    //在pattern获取Item对象
    HIconGraphicsItem* addItemByIconObj(HBaseObj* pObj);

    //增加scene的显示方案
    void refreshSceneByPatternId(int nPatternId);

    //删除scene的显示方案
    void clearSceneByPatternId(int nPatternId);


public slots:
    void objSelectChanged(HBaseObj* obj,bool isSelected);
    void recalcSelect();
protected:

    //事件过滤
   // virtual bool eventFilter( QObject *obj, QEvent *event);//过滤的对象，过滤的事件

private:
    QRectF m_sceneRect;
    HIconEditorMgr* m_pIconEditorMgr;

};

#endif // HICONFRAME_H
