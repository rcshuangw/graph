#include "hiconop.h"
#include <QScrollBar>
#include <QGraphicsView>
#include <QDir>
#include "hiconcommand.h"
#include "hiconitemgroup.h"
#include "publicdata.h"

HIconOp::HIconOp(HIconMgr* mgr)
    :pIconMgr(mgr)
{

}

void HIconOp::fitWidth()
{
    if(!pIconMgr || !pIconMgr->getIconFrame() || !pIconMgr->getIconFrame()->view())
        return;
    int nScrollWidth = 0;

    if(pIconMgr->getIconFrame()->view()->verticalScrollBar())
        nScrollWidth = pIconMgr->getIconFrame()->view()->verticalScrollBar()->width();
    double frameWidth = pIconMgr->getIconFrame()->width()-nScrollWidth-pIconMgr->getIconFrame()->vRulerWidth()-5;
    double screenWidth = pIconMgr->getIconFrame()->getLogicRect().width();
    double ratio = frameWidth/screenWidth;
    if(ratio<0 || qFuzzyCompare(ratio,1))
        return;
    pIconMgr->getIconFrame()->scaleChangedTo(ratio);

}

void HIconOp::fitHeight()
{
    if(!pIconMgr || !pIconMgr->getIconFrame() || !pIconMgr->getIconFrame()->view())
        return;
    int nScrollHeight = 0;
    if(pIconMgr->getIconFrame()->view()->horizontalScrollBar())
        nScrollHeight = pIconMgr->getIconFrame()->view()->horizontalScrollBar()->height();

    double frameHeight = pIconMgr->getIconFrame()->height()-nScrollHeight-pIconMgr->getIconFrame()->hRulerHeight()-5;
    double screenHeight = pIconMgr->getIconFrame()->getLogicRect().height();
    double ratio = frameHeight/screenHeight;
    if(ratio<0 || qFuzzyCompare(ratio,1))
        return;
    pIconMgr->getIconFrame()->scaleChangedTo(ratio);
}

void HIconOp::cut()
{
    copy();
    del();
}

void HIconOp::copy()
{
    if(!pIconMgr || !pIconMgr->getIconFrame() || !pIconMgr->getIconFrame()->getIconScene())
        return;
    //寻找当前页面的所有选择的图元
    QByteArray bytes;
    QDataStream stream(&bytes,QIODevice::WriteOnly);
    QList<QGraphicsItem*> itemSelectList = pIconMgr->getIconFrame()->getIconScene()->selectedItems();
    stream<<itemSelectList.count();
    stream<<pIconMgr->getIconTemplate()->getSymbol()->getCurrentPattern();
    for(int i =0; i < itemSelectList.count();i++)
    {
        HBaseObj* pObj = qgraphicsitem_cast<HIconGraphicsItem*>(itemSelectList[i])->getItemObj();
        if(!pObj) continue;
        stream<<(quint8)pObj->getShapeType();
        HBaseObj* pNewObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(pObj->getShapeType());
        if(!pNewObj) continue;
        pObj->clone(pNewObj);//需要clone吗？
        pNewObj->writeData(&stream);
        if(pNewObj)
        {
            delete pNewObj;
            pNewObj = NULL;
        }
    }
    QString clipboardPath = getClipboardFile();
    QFile file(clipboardPath);
    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream cbStream(&file);
        cbStream.writeRawData(bytes.data(),bytes.length());
        file.close();
    }
}

void HIconOp::paste()
{
    if(!pIconMgr || !pIconMgr->getIconFrame() || !pIconMgr->getIconFrame()->getIconScene())
        return;
    QString clipboardPath = getClipboardFile();
    QFile file(clipboardPath);
    if(!file.exists() || !file.open(QIODevice::ReadOnly))
        return;
    QList<HIconGraphicsItem*> copyItemList;
    QDataStream stream(&file);
    int num;
    stream>>num;
    int nPattern;
    stream>>nPattern;
    quint8 nType;
    QList<HBaseObj*> objList;
    for(int i = 0; i < num;i++)
    {
        stream>>nType;
        HBaseObj* pObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(nType);
        if(!pObj) continue;
        pObj->readData(&stream);
        objList.append(pObj);
        HIconGraphicsItem* item = pIconMgr->getIconFrame()->addItemByIconObj(pObj);
        pObj->nPattern = pIconMgr->getIconTemplate()->getSymbol()->getCurrentPattern();
        if(!item)
        {
            delete pObj;
            pObj = NULL;
            continue;
        }
        copyItemList.append(item);
        pIconMgr->getIconTemplate()->getSymbol()->addObj(pObj);
     }

    //改变选择状态，只选择拷贝后的图元元素
    foreach(QGraphicsItem* item,pIconMgr->getIconFrame()->getIconScene()->items())
    {
        item->setSelected(false);
    }
    foreach(HIconGraphicsItem* item,copyItemList)
    {
        item->setSelected(true);
    }

    if(nPattern == pIconMgr->getIconTemplate()->getSymbol()->getCurrentPattern())
    {
        for(int i = 0; i < copyItemList.count();i++)
        {
            HIconGraphicsItem* pItem = (HIconGraphicsItem*)copyItemList[i];
            if(!pItem) continue;
            QPointF pt(10,10);
            pItem->moveBy(pt.x(),pt.y());
            pItem->getItemObj()->moveBy(pt.x(),pt.y());
        }
    }
    pIconMgr->getIconFrame()->getIconScene()->update(pIconMgr->getIconFrame()->getLogicRect());
    HPasteIconCommand* pasteIconCommand = new HPasteIconCommand(pIconMgr,objList);
    pIconMgr->getIconUndoStack()->push(pasteIconCommand);
}

void HIconOp::del()
{
    if(!pIconMgr || !pIconMgr->getIconFrame() || !pIconMgr->getIconFrame()->getIconScene())
        return;
    QList<QGraphicsItem*> itemSelectList = pIconMgr->getIconFrame()->getIconScene()->selectedItems();
    QList<HBaseObj*> objList;
    foreach(QGraphicsItem* item,itemSelectList)
    {
        if(!item) continue;
        //不能直接删除 改成deleted=TRUE，只有到保存的时候才真正删除对象
        HBaseObj* pObj = ((HIconGraphicsItem*)item)->getItemObj();
        pObj->setDeleted(true);
        pObj->setVisible(false);
        item->setVisible(false);
        objList.append(pObj);
    }
    HDelIconCommand *delIconCommand = new HDelIconCommand(pIconMgr,objList);
    pIconMgr->getIconUndoStack()->push(delIconCommand);
}


QString HIconOp::getClipboardFile()
{
    char szDataPath[128];
    getDataFilePath(DFPATH_DATA,szDataPath);
    QString clipboardPath = QString(szDataPath);
    clipboardPath.append("/icon");
    QDir dirClipboard(clipboardPath);
    if(!dirClipboard.exists())
        dirClipboard.mkdir(clipboardPath);
    clipboardPath.append("/iconclipboard.data");
    return clipboardPath;
}

void HIconOp::bringToTop()
{
    if(!pIconMgr || !pIconMgr->getIconFrame() || !pIconMgr->getIconFrame()->getIconScene())
        return;

    int maxZValue = 0;
    QList<QGraphicsItem*> itemList = pIconMgr->getIconFrame()->getIconScene()->selectedItems();
    if(itemList.count() > 1) return;
    QGraphicsItem* pItem = itemList.at(0);
    QList<QGraphicsItem*> collItemList = pItem->collidingItems();
    if(collItemList.count()<=0) return;
    maxZValue = collItemList.at(0)->zValue();
    for(int i = 1; i < collItemList.count();i++)
    {
        QGraphicsItem* item = collItemList[i];
        if(item->zValue() > maxZValue)
            maxZValue = item->zValue();
    }
    if(pItem->zValue() > maxZValue)
        return;
    else
    {
        maxZValue++;
        pItem->setZValue(maxZValue);
        ((HIconGraphicsItem*)pItem)->getItemObj()->setStackOrder(maxZValue);
    }

}

void HIconOp::bringToBottom()
{
    if(!pIconMgr || !pIconMgr->getIconFrame() || !pIconMgr->getIconFrame()->getIconScene())
        return;
    int minZValue = 0;
    QList<QGraphicsItem*> itemList = pIconMgr->getIconFrame()->getIconScene()->selectedItems();
    if(itemList.count() > 1) return;
    QGraphicsItem* pItem = itemList.at(0);
    QList<QGraphicsItem*> collItemList = pItem->collidingItems();
    if(collItemList.count()<=0) return;
    minZValue = (int)(collItemList.at(0)->zValue());
    for(int i = 1; i < collItemList.count();i++)
    {
        QGraphicsItem* item = collItemList[i];
        if(item->zValue() < minZValue)
            minZValue = item->zValue();
    }
    if(pItem->zValue() < minZValue)
        return;
    else
    {
        minZValue--;
        pItem->setZValue(minZValue);
        ((HIconGraphicsItem*)pItem)->getItemObj()->setStackOrder(minZValue);
    }
}

void HIconOp::groupObj()
{
    if(!pIconMgr || !pIconMgr->getIconFrame() || !pIconMgr->getIconFrame()->getIconScene() ||!pIconMgr->getIconTemplate() || !pIconMgr->getIconTemplate()->getSymbol())
        return;
    QList<QGraphicsItem*> items = pIconMgr->getIconFrame()->getIconScene()->selectedItems();
    if(items.count() < 2) return;

    HBaseObj* pGroupObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(enumGroup);
    QRectF groupRect;
    for(int i = 0; i < items.count();i++)
    {
        HIconGraphicsItem* item = (HIconGraphicsItem*)items.at(i);
        HBaseObj* pObj = item->getItemObj();
        groupRect = groupRect.united(item->rect());
        pIconMgr->getIconTemplate()->getSymbol()->takeObj(pObj);//应该是take操作 不是删除
        ((HGroupObj*)pGroupObj)->addObj(pObj);
    }
    //矩形
    ((HGroupObj*)pGroupObj)->setObjRect(QRectF(0,0,groupRect.width(),groupRect.height()));
    HIconItemGroup *itemGroup = new HIconItemGroup(pGroupObj);
    pIconMgr->getIconTemplate()->getSymbol()->addObj(pGroupObj);
    itemGroup->setItemObj(pGroupObj);
    itemGroup->setRect(groupRect);
    foreach(QGraphicsItem* item,items)
    {
        pIconMgr->getIconFrame()->getIconScene()->removeItem(item);
        HBaseObj* pObj = ((HIconGraphicsItem*)item)->getItemObj();
        pObj->setIconGraphicsItem(NULL);
    }
    pIconMgr->getIconFrame()->getIconScene()->addItem(itemGroup);
    pIconMgr->setDrawShape(enumSelection);
}

void HIconOp::ungroupObj()
{
    if(!pIconMgr || !pIconMgr->getIconFrame() || !pIconMgr->getIconFrame()->getIconScene()||!pIconMgr->getIconTemplate() || !pIconMgr->getIconTemplate()->getSymbol())
        return;
    QList<QGraphicsItem*> items = pIconMgr->getIconFrame()->getIconScene()->selectedItems();
    for(int i = 0; i < items.count();i++)
    {
        HIconGraphicsItem* item = (HIconGraphicsItem*)items.at(i);
        if(item->type() != enumGroup) continue;
        HBaseObj* pObj = item->getItemObj();
        HGroupObj* pGroupObj = (HGroupObj*)pObj;
        while(!pGroupObj->isEmpty())
        {
            HBaseObj* pObj = (HBaseObj*)pGroupObj->takeFirst();
            pIconMgr->getIconTemplate()->getSymbol()->addObj(pObj);
            pIconMgr->getIconFrame()->getIconScene()->addItemByIconObj(pObj);
        }
        pIconMgr->getIconFrame()->getIconScene()->removeItem(item);
        pIconMgr->getIconTemplate()->getSymbol()->delObj(pObj);
    }
    pIconMgr->setDrawShape(enumSelection);
}

void HIconOp::zoomIn()
{


}

void HIconOp::zoomOut()
{

}
