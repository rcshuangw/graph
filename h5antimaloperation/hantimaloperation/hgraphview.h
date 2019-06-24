#ifndef HONLINEVIEW_H
#define HONLINEVIEW_H

#include <QGraphicsView>
/*
 * 五防系统view基类,又是画面浏览基类
 * 操作票窗口内的view、模板编辑窗口的view都是继承它
*/
class HAntiMalopMgr;
class HGraphView : public QGraphicsView
{
    Q_OBJECT
public:
    HGraphView(QWidget *parent = 0);
    virtual ~HGraphView();

public:
    void setAntiMalopMgr(HAntiMalopMgr* mgr);
    HAntiMalopMgr* antiMalopMgr();

    //目前只刷新界面
    void refresh();

protected:
    bool eventFilter(QObject *o, QEvent *e);

public:
    HAntiMalopMgr* m_pAntiMalopMgr;
};

#endif // HGRAPHEDITORVIEW_H
