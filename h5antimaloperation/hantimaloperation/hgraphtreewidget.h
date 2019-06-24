#ifndef HONLINETREEWIDGET_H
#define HONLINETREEWIDGET_H
//左边的树结构
#include <QTreeWidget>
#include <QTreeWidgetItem>

class HAntiMalopMgr;
class QContextMenuEvent;
class HGraphTreeWidgetItem:public QTreeWidgetItem
{
public:
    HGraphTreeWidgetItem(QTreeWidget * parent, int type = UserType);
    HGraphTreeWidgetItem(QTreeWidgetItem * parent, int type = UserType);
    ~HGraphTreeWidgetItem();

public:
    void setGraphTreeID(int graphTreeID);
    int getGraphTreeID();
private:
    int wGraphTreeID;
};

class HGraphTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    HGraphTreeWidget(HAntiMalopMgr *pMgr);
    ~HGraphTreeWidget();
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
    HAntiMalopMgr* m_pAntiMalopMgr;
    int nPreGraphID;
};

#endif // HGRAPHTREEWIDGET_H
