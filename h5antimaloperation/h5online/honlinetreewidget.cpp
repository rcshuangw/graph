#include "honlinetreewidget.h"
#include <QContextMenuEvent>
#include "hwfsystemmgr.h"
#include "honlinedoc.h"
#include "hgraph.h"
#include <QMenu>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>

#define GRAPHTREE_TYPE_ROOT  0
#define GRAPHTREE_TYPE_FILE  1
#define GRAPHTREE_TYPE_CFILE 2

HOnlineTreeWidgetItem::HOnlineTreeWidgetItem(QTreeWidget * parent, int type ):QTreeWidgetItem(parent,type)
{

}

HOnlineTreeWidgetItem::HOnlineTreeWidgetItem(QTreeWidgetItem * parent, int type)
    :QTreeWidgetItem (parent,type)
{

}

HOnlineTreeWidgetItem::~HOnlineTreeWidgetItem()
{
    for(int i = 0; i < childCount();i++)
    {
        HOnlineTreeWidgetItem* item = (HOnlineTreeWidgetItem*)child(i);
        if(item)
        {
            delete item;
            item = NULL;
        }
    }
}

void HOnlineTreeWidgetItem::setGraphTreeID(int graphTreeID)
{
    wGraphTreeID = graphTreeID;
}

int HOnlineTreeWidgetItem::getGraphTreeID()
{
    return wGraphTreeID;
}

///////////////////////////////////////////////////////HOnlineTreeWidget////////////////////////////////////

HOnlineTreeWidget::HOnlineTreeWidget(HWfSystemMgr *pMgr)
    :m_pWfSystemMgr(pMgr)
{
    nPreGraphID = (int)-1;
    setRootIsDecorated(true);
    setHeaderLabel(QStringLiteral("画面"));
    initGraphTreeWidget();
}

HOnlineTreeWidget::~HOnlineTreeWidget()
{

}

void HOnlineTreeWidget::initGraphTreeWidget()
{
    HOnlineTreeWidgetItem* rootItem = new HOnlineTreeWidgetItem(this,GRAPHTREE_TYPE_ROOT);
    rootItem->setText(0,QStringLiteral("厂站五防画面总览"));
    rootItem->setIcon(0,QIcon(":/images/Folder.png"));
    rootItem->setGraphTreeID(9999);
    addTopLevelItem(rootItem);
    //expandItem(rootItem);

    HWfSystemDoc* doc = m_pWfSystemMgr->wfSystemDoc();
    if(!doc) return;
    QList<HGraph*> graphList = doc->pGraphList;
    for(int i = 0; i < graphList.count();i++)
    {
        HGraph* graph = (HGraph*)graphList[i];
        if(!graph)
            continue;
        HOnlineTreeWidgetItem* newItem = new HOnlineTreeWidgetItem(rootItem,GRAPHTREE_TYPE_FILE);
        newItem->setGraphTreeID(graph->getGraphID());
        newItem->setText(0,graph->graphName());
        newItem->setIcon(0,QIcon(":/images/Folder_Documents.png"));
        rootItem->addChild(newItem);
        HOnlineTreeWidgetItem* fileItem = new HOnlineTreeWidgetItem(newItem,GRAPHTREE_TYPE_CFILE);
        fileItem->setGraphTreeID(graph->getGraphID());
        fileItem->setIcon(0,QIcon(":/images/document-text.png"));
        fileItem->setText(0,QStringLiteral("最新版本"));
    }
    connect(this,SIGNAL(itemClicked(QTreeWidgetItem*,int)),SLOT(clickGraphItem(QTreeWidgetItem*,int)));
    //connect(this,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),SLOT(changedGraphItem(QTreeWidgetItem*,QTreeWidgetItem*)));

}

void HOnlineTreeWidget::clickGraphItem(QTreeWidgetItem* item,int column)
{
    HOnlineTreeWidgetItem* clickItem = dynamic_cast<HOnlineTreeWidgetItem*>(item);
    int nCurGraphID = clickItem->getGraphTreeID();
    if(nCurGraphID != nPreGraphID)
    {
        //if(GRAPHTREE_TYPE_FILE == clickItem->type());
        int count = topLevelItemCount();
        for(int k = 0; k < count;k++)
        {
            HOnlineTreeWidgetItem* rootItem = static_cast<HOnlineTreeWidgetItem*>(topLevelItem(k));
           if(!rootItem) continue;
           for(int i = 0;i < rootItem->childCount();i++)
           {
               HOnlineTreeWidgetItem* childItem = static_cast<HOnlineTreeWidgetItem*>(rootItem->child(i));
               collapseItem(childItem);
           }
       }
           if(GRAPHTREE_TYPE_ROOT == clickItem->type())
               expandItem(clickItem);
           else if(GRAPHTREE_TYPE_CFILE == clickItem->type())
           {
               if(clickItem->parent())
                expandItem(clickItem->parent());
           }
    }

    int type = clickItem->type();
    if(GRAPHTREE_TYPE_FILE == type)
    {
        //要切换到子文件里面
        HOnlineTreeWidgetItem* childItem = dynamic_cast<HOnlineTreeWidgetItem*>(clickItem->child(column));
        if(childItem && GRAPHTREE_TYPE_CFILE == childItem->type())
        {
            setCurrentItem(childItem);
        }
    }
    if(nCurGraphID == nPreGraphID) return;
    nPreGraphID = nCurGraphID;

    if(GRAPHTREE_TYPE_ROOT == clickItem->type())
        return;

    openGraph();
}

void HOnlineTreeWidget::openGraph()
{
    HOnlineTreeWidgetItem* pCurItem = dynamic_cast<HOnlineTreeWidgetItem*> (currentItem());
    if(!pCurItem) return;
    QString strGraphName = pCurItem->text(0);
    int nGraphID = pCurItem->getGraphTreeID();
    emit graphOpen(strGraphName,nGraphID);
}






