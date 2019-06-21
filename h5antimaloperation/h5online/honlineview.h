#ifndef HONLINEVIEW_H
#define HONLINEVIEW_H

#include <QGraphicsView>
/*
 * 五防系统view基类,又是画面浏览基类
 * 操作票窗口内的view、模板编辑窗口的view都是继承它
*/
class HGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    HGraphicsView(QWidget *parent = Q_NULLPTR);

public:
    //目前只刷新界面
    void refresh();
};

#endif // HGRAPHEDITORVIEW_H
