#ifndef HICONWIDGET_H
#define HICONWIDGET_H

#include <QWidget>
#include "hiconapi.h"
/*
 * 绘制图符窗口类：存放QIconEditorFrame和QTabBar
 * QIconEditorFrame类是真正的窗口绘制类
*/
class QTabBar;
class HIconEditorFrame;
class HIconEditorMgr;

class HIconEditorWidget : public QWidget
{
    Q_OBJECT
public:
    HIconEditorWidget();

    void setIconEditorMgr(HIconEditorMgr* iconMgr);

    //刷新图元
    void refreshIconWidget();

    QTabBar* getTabBar(){return pTabBar;}
public:
    void clear();
    void refresh();
protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);
    //HIconFrame* getIconFrame(){return pIconFrame;}
public slots:
    void addShowPattern();
    void delShowPattern();
    void renameShowPattern();
    void patternChanged(int curPatternId);
private:
    HIconEditorMgr* m_pIconEditorMgr;
    QTabBar* m_pTabBar;
};

#endif // HICONWIDGET_H
