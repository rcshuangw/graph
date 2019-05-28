#ifndef HICONTREEWIDGET_H
#define HICONTREEWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QContextMenuEvent>
#include <QAction>
#include <QUuid>
#include "hiconapi.h"
#include "hicontemplate.h"

class HIconEditorMgr;
class HIconTreeWidget;
/*
 测点
  |-遥信
     |--开关(HIconTemplate->HIconSymbol)
         |-开关分（showPattern)
         |-开关合
         |-开关双位置分错
         |-开关双位置合错
  |-遥测
  |-光字牌
  |-遥控
  |-遥脉
  |-档位
*/

//#define ICON_TYPE_DIGITAL 0x001
//#define


class HIconTreeWidgetItem : public QTreeWidgetItem
{
public:
    HIconTreeWidgetItem(HIconTreeWidget* parent,int type = QTreeWidgetItem::UserType);
    HIconTreeWidgetItem(HIconTreeWidgetItem* parent,int type = QTreeWidgetItem::UserType);
    void setUuid(QString uuid);
    QString getUuid();
private:
    QString strUuid;

};

class HIconTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    HIconTreeWidget(HIconEditorMgr* iconMgr,QWidget* parent = 0,int type = QTreeWidgetItem::UserType);
    ~HIconTreeWidget();
public:
    void init();
    void initTemplateFile();
    void initTemplateMenu(QContextMenuEvent *event);
    void initTemplateChildMenu(QContextMenuEvent* event);
    void addIconTreeWigetItem();
    void delIconTreeWidgetItem();
    void renameIconTreeWidgetItem();
    HIconTreeWidgetItem* findIconTreeWigetItem(int treeData);
    void expandIconItem(HIconTreeWidgetItem* item);

protected:
    void contextMenuEvent(QContextMenuEvent *event);
signals:
    void IconNew(const QString& strTemplateName,const QString& strCatalogName,const int& nCatalogType);
    void IconDel(const QString& strCatalogName,const int& nCatalogType,const QString& strUuid);
    void IconOpen(const QString& strCatalogName,const int& nCatalogType,const QString& strUuid);
    void IconRename(const QString& strTemplateName,const int& nCatalogType,const QString& strUuid);
public slots:
    void newIcon();
    void deleteIcon();
    void renameIcon();
    void importIcon();
    void openIcon(QTreeWidgetItem*,int);

public:
    //普通图符
    HIconTreeWidgetItem* trans2Item;
    HIconTreeWidgetItem* trans3Item;
    HIconTreeWidgetItem* generatorItem;
    HIconTreeWidgetItem* capacitorItem;
    HIconTreeWidgetItem* otherdeviceItem;
    HIconTreeWidgetItem* ptItem;
    HIconTreeWidgetItem* ctItem;
    HIconTreeWidgetItem* arresterItem;
    HIconTreeWidgetItem* reactorItem;
    //测点类
    HIconTreeWidgetItem* digitalItem;
    HIconTreeWidgetItem* analogueItem;
    HIconTreeWidgetItem* lightItem;
    HIconTreeWidgetItem* relayItem;
    HIconTreeWidgetItem* pulseItem;//遥脉
    HIconTreeWidgetItem* tapItem;
    HIconTreeWidgetItem* controlItem;
    //其他类
    HIconTreeWidgetItem* paiItem;
    HIconTreeWidgetItem* otherItem;

    HIconTreeWidgetItem* m_pCurItem;

private:
    QAction* newAct;
    QAction* delAct;
    QAction* renameAct;
    QAction* importAct;

    HIconEditorMgr* m_pIconEditorMgr;
};

#endif // HICONTREEWIDGET_H
