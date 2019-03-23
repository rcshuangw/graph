#ifndef HICONWIDGET_H
#define HICONWIDGET_H

#include <QWidget>

#include "hiconapi.h"
class QTabBar;
class HIconEditorFrame;
class HIconMgr;
class HIconEditorWidget : public QWidget
{
    Q_OBJECT
public:
    HIconEditorWidget();

    void setIconMgr(HIconMgr* iconMgr);

    //新建一个icon图元
    void newIconWidget();

    //删除一个Icon图元
    void delIconWidget();

    //打开一个图元
    void openIconWidget();

    //刷新图元
    void refreshIconWidget();

    QTabBar* getTabBar(){return pTabBar;}

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);
    //HIconFrame* getIconFrame(){return pIconFrame;}
public slots:
    void addShowPattern();
    void delShowPattern();
    void renameShowPattern();
    void patternChanged(int curPatternId);
private:
    HIconMgr* pIconMgr;
    QTabBar* pTabBar;
};

#endif // HICONWIDGET_H
