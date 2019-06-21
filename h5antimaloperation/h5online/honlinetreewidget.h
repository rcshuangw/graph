#ifndef HONLINETREEWIDGET_H
#define HONLINETREEWIDGET_H
//左边的树结构
#include <QTreeWidget>
#include <QTreeWidgetItem>

class HWfSystemMgr;
class QContextMenuEvent;
class HOnlineTreeWidgetItem:public QTreeWidgetItem
{
public:
    HOnlineTreeWidgetItem(QTreeWidget * parent, int type = UserType);
    HOnlineTreeWidgetItem(QTreeWidgetItem * parent, int type = UserType);
    ~HOnlineTreeWidgetItem();

public:
    void setGraphTreeID(int graphTreeID);
    int getGraphTreeID();
private:
    int wGraphTreeID;
};

class HOnlineTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    HOnlineTreeWidget(HWfSystemMgr *pMgr);
    ~HOnlineTreeWidget();
public:
    //初始化树结构
    void initGraphTreeWidget();
public slots:

    //打开画面
    void openGraph();

    //点击树
    void clickGraphItem(QTreeWidgetItem*,int);

signals:
    void graphOpen(const QString&,const int graphID);
protected:
    HWfSystemMgr* m_pWfSystemMgr;
    int nPreGraphID;
};

#endif // HGRAPHTREEWIDGET_H
