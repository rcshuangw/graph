#include "hgraphtreewidget.h"
#include <QContextMenuEvent>
#include "hantimalopmgr.h"
#include "hantimalopdoc.h"
#include "hgraph.h"
#include <QMenu>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>

#define GRAPHTREE_TYPE_ROOT  0
#define GRAPHTREE_TYPE_FILE  1
#define GRAPHTREE_TYPE_CFILE 2

HGraphTreeWidgetItem::HGraphTreeWidgetItem(QTreeWidget * parent, int type ):QTreeWidgetItem(parent,type)
{

}

HGraphTreeWidgetItem::HGraphTreeWidgetItem(QTreeWidgetItem * parent, int type)
    :QTreeWidgetItem (parent,type)
{

}

HGraphTreeWidgetItem::~HGraphTreeWidgetItem()
{
    for(int i = 0; i < childCount();i++)
    {
        HGraphTreeWidgetItem* item = (HGraphTreeWidgetItem*)child(i);
        if(item)
        {
            delete item;
            item = NULL;
        }
    }
}

void HGraphTreeWidgetItem::setGraphTreeID(int graphTreeID)
{
    wGraphTreeID = graphTreeID;
}

int HGraphTreeWidgetItem::getGraphTreeID()
{
    return wGraphTreeID;
}

///////////////////////////////////////////////////////HGraphTreeWidget////////////////////////////////////

HGraphTreeWidget::HGraphTreeWidget(HAntiMalopMgr *pMgr)
    :m_pAntiMalopMgr(pMgr)
{
    nPreGraphID = (int)-1;
    setRootIsDecorated(true);
    setHeaderLabel(QStringLiteral("画面"));
    initGraphTreeWidget();
}

HGraphTreeWidget::~HGraphTreeWidget()
{

}

void HGraphTreeWidget::initGraphTreeWidget()
{
    HGraphTreeWidgetItem* rootItem = new HGraphTreeWidgetItem(this,GRAPHTREE_TYPE_ROOT);
    rootItem->setText(0,QStringLiteral("厂站五防画面"));
    rootItem->setIcon(0,QIcon(":/images/Folder.png"));
    rootItem->setGraphTreeID(9999);
    addTopLevelItem(rootItem);
    //expandItem(rootItem);

    HAntiMalopDoc* doc = m_pAntiMalopMgr->antiMalopDoc();
    if(!doc) return;
    QList<HGraph*> graphList = doc->m_pGraphList;
    for(int i = 0; i < graphList.count();i++)
    {
        HGraph* graph = (HGraph*)graphList[i];
        if(!graph)
            continue;
        HGraphTreeWidgetItem* newItem = new HGraphTreeWidgetItem(rootItem,GRAPHTREE_TYPE_FILE);
        newItem->setGraphTreeID(graph->graphID());
        newItem->setText(0,graph->graphName());
        newItem->setIcon(0,QIcon(":/images/Folder_Documents.png"));
        rootItem->addChild(newItem);
        HGraphTreeWidgetItem* fileItem = new HGraphTreeWidgetItem(newItem,GRAPHTREE_TYPE_CFILE);
        fileItem->setGraphTreeID(graph->graphID());
        fileItem->setIcon(0,QIcon(":/images/document-text.png"));
        fileItem->setText(0,QStringLiteral("最新版本"));
    }
    connect(this,SIGNAL(itemClicked(QTreeWidgetItem*,int)),SLOT(clickGraphItem(QTreeWidgetItem*,int)));
    //connect(this,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),SLOT(changedGraphItem(QTreeWidgetItem*,QTreeWidgetItem*)));

}

void HGraphTreeWidget::clickGraphItem(QTreeWidgetItem* item,int column)
{
    HGraphTreeWidgetItem* clickItem = dynamic_cast<HGraphTreeWidgetItem*>(item);
    int nCurGraphID = clickItem->getGraphTreeID();
    if(nCurGraphID != nPreGraphID)
    {
        int count = topLevelItemCount();
        for(int k = 0; k < count;k++)
        {
            HGraphTreeWidgetItem* rootItem = static_cast<HGraphTreeWidgetItem*>(topLevelItem(k));
           if(!rootItem) continue;
           for(int i = 0;i < rootItem->childCount();i++)
           {
               HGraphTreeWidgetItem* childItem = static_cast<HGraphTreeWidgetItem*>(rootItem->child(i));
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
        HGraphTreeWidgetItem* childItem = dynamic_cast<HGraphTreeWidgetItem*>(clickItem->child(column));
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

void HGraphTreeWidget::openGraph()
{
    HGraphTreeWidgetItem* pCurItem = dynamic_cast<HGraphTreeWidgetItem*> (currentItem());
    if(!pCurItem) return;
    QString strGraphName = pCurItem->text(0);
    int nGraphID = pCurItem->getGraphTreeID();
    emit graphOpen(strGraphName,nGraphID);
}






