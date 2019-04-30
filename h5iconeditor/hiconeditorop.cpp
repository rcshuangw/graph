#include "hiconeditorop.h"
#include <QScrollBar>
#include <QGraphicsView>
#include <QDir>
#include "hiconeditormgr.h"
#include "hicontemplate.h"
#include "hiconeditorframe.h"
#include "hselectedmgr.h"
#include "htempcontainer.h"
#include "hiconcommand.h"
HIconEditorOp::HIconEditorOp(HIconEditorMgr* mgr)
    :m_pIconEditorMgr(mgr)
{

}

HIconEditorOp::~HIconEditorOp()
{

}

void HIconEditorOp::New(const QString& strTemplateName,const QString& strCatalogName,const int& nCatalogType)
{
    //iconTemplate()获取是临时对象
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconTemplate())
        return;
    QSizeF sizeF = m_pIconEditorMgr->iconTemplate()->getDefaultSize();//获取默认大小
    if(sizeF.width() > 0 && sizeF.height())
    {
        QSizeF nSizeF = sizeF * m_pIconEditorMgr->getRatio();
        QRectF rectF = QRectF(QPointF(-nSizeF.width()/2,-nSizeF.height()/2),sizeF.width(),sizeF.height());
        m_pIconEditorMgr->iconTemplate()->getSymbol()->m_width = nSizeF.width();
        m_pIconEditorMgr->iconTemplate()->getSymbol()->m_height = nSizeF.height();
        m_pIconEditorMgr->setLogicRect(rectF);
    }
}

void HIconEditorOp::Open(const QString &strTemplateName, int nTemplateType, const QString &strUuid)
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconTemplate())
        return;

    int width = m_pIconEditorMgr->iconTemplate()->getSymbol()->m_width;
    int height = m_pIconEditorMgr->iconTemplate()->getSymbol()->m_height;
    QSizeF sizeF = m_pIconEditorMgr->iconTemplate()->getDefaultSize();//获取默认大小
    if(width > 0 && height > 0 && sizeF.width() > 0 && sizeF.height())
    {
        m_pIconEditorMgr->setRatio(qMin(width/sizeF.width(),height/sizeF.height()));
        QRectF rectF = QRectF(QPointF(-width/2,-height/2),QSizeF(width,height));
        m_pIconEditorMgr->setLogicRect(rectF);
    }

    //所有false
    HIconTemplate* pTemplate = m_pIconEditorMgr->iconTemplate();
    if(!pTemplate) return;
    for(int i = 0; i < pTemplate->getSymbol()->getObjList().count();i++)
    {
        HBaseObj* pObj = pTemplate->getSymbol()->getObjList().at(i);
        if(pObj && pObj->getPattern() != newPatternId)
        {
            H5GraphicsItem* item = (H5GraphicsItem*)pObj->iconGraphicsItem();
            if(item)
                item->setVisible(false);
        }
    }
}

void HIconEditorOp::onCreateObj(HBaseObj* pObj,bool isPaste )
{
    if(!m_pIconEditorMgr && !m_pIconEditorMgr->iconEditorFrame())
        m_pIconEditorMgr->iconEditorFrame()->objCreated(pObj,isPaste);
}

void HIconEditorOp::onRemoveObj(HBaseObj* pObj)
{
    if(!m_pIconEditorMgr && !m_pIconEditorMgr->iconEditorFrame())
        m_pIconEditorMgr->iconEditorFrame()->objRemoved(pObj);
}

void HIconEditorOp::fitWidth()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconEditorFrame() || !m_pIconEditorMgr->iconEditorFrame()->view())
        return;
    int nScrollWidth = 0;

    if(m_pIconEditorMgr->iconEditorFrame()->view()->verticalScrollBar())
        nScrollWidth = m_pIconEditorMgr->iconEditorFrame()->view()->verticalScrollBar()->width();
    double frameWidth = m_pIconEditorMgr->iconEditorFrame()->width()-nScrollWidth- m_pIconEditorMgr->iconEditorFrame()->vRulerWidth()-5;
    double screenWidth = m_pIconEditorMgr->getLogicRect().width();
    double ratio = frameWidth/screenWidth;
    if(ratio<0 || qFuzzyCompare(ratio,1))
        return;
	m_pIconEditorMgr->iconEditorFrame()->scaleChangedTo(ratio);

}

void HIconEditorOp::fitHeight()
{
	if (!m_pIconEditorMgr || !m_pIconEditorMgr->iconEditorFrame() || !m_pIconEditorMgr->iconEditorFrame()->view())
		return;
    int nScrollHeight = 0;
    if(m_pIconEditorMgr->iconEditorFrame()->view()->horizontalScrollBar())
        nScrollHeight = m_pIconEditorMgr->iconEditorFrame()->view()->horizontalScrollBar()->height();

    double frameHeight = m_pIconEditorMgr->iconEditorFrame()->height()-nScrollHeight- m_pIconEditorMgr->iconEditorFrame()->hRulerHeight()-5;
    double screenHeight = m_pIconEditorMgr->getLogicRect().height();
    double ratio = frameHeight/screenHeight;
    if(ratio<0 || qFuzzyCompare(ratio,1))
        return;
	m_pIconEditorMgr->iconEditorFrame()->scaleChangedTo(ratio);
}

void HIconEditorOp::cut()
{
    copy();
    del();
}

void HIconEditorOp::copy()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->selectedMgr() || !m_pIconEditorMgr->selectedMgr()->selectObj())
        return;
    //寻找当前页面的所有选择的图元
    HTempContainer* tempContainer = m_pIconEditorMgr->selectedMgr()->selectObj();
    QByteArray bytes;
    QDataStream stream(&bytes,QIODevice::WriteOnly);
    int num = 0;
    for(int i = 0; i < tempContainer->getObjList().count();i++)
    {
        HBaseObj* pObj = (HBaseObj*)tempContainer->getObjList().at(i);
        if(!pObj || pObj->isDeleted())
            continue;
        num++;
    }
    stream<<num;
    stream<<m_pIconEditorMgr->iconTemplate()->getSymbol()->getCurrentPattern();
    for(int i =0; i < tempContainer->getObjList().count();i++)
    {
        HBaseObj* pObj = (HBaseObj*)tempContainer->getObjList().at(i);
        if(!pObj) continue;
        stream<<(quint8)pObj->getShapeType();
        HBaseObj* pNewObj = m_pIconEditorMgr->iconTemplate()->getSymbol()->newObj(pObj->getShapeType());
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

void HIconEditorOp::paste()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->selectedMgr() || !m_pIconEditorMgr->selectedMgr()->selectObj())
        return;
    QString clipboardPath = getClipboardFile();
    QFile file(clipboardPath);
    if(!file.exists() || !file.open(QIODevice::ReadOnly))
        return;

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
        HBaseObj* pObj = m_pIconEditorMgr->iconTemplate()->getSymbol()->newObj(nType);
        if(!pObj) continue;
        pObj->readData(&stream);
        objList.append(pObj);

        m_pIconEditorMgr->iconEditorFrame()->objCreated(pObj,true);
        m_pIconEditorMgr->iconTemplate()->getSymbol()->addBaseObj(pObj);
     }

    //改变选择状态，原来选中图元取消选择
    HTempContainer* tempContainer = m_pIconEditorMgr->selectedMgr()->selectObj();
    for(int i = 0; i < tempContainer->getObjList().count();i++)
    {
        HBaseObj* pObj = (HBaseObj*)tempContainer->getObjList().at(i);
        if(!pObj || pObj->isDeleted() || !pObj->iconGraphicsItem())
            continue;
        (H5GraphicsItem*)pObj->iconGraphicsItem()->setVisible(false);
    }

    //选择拷贝后的图元
    for(int i = 0; i < objList.count();i++)
    {
        H5GraphicsItem* pItem = (H5GraphicsItem*)(objList.at(i)->iconGraphicsItem());
        if(!pItem) continue;
       pItem->setVisible(true);
    }

    //拷贝后的图元移动 防止覆盖
    if(nPattern == m_pIconEditorMgr->iconTemplate()->getSymbol()->getCurrentPattern())
    {
        for(int i = 0; i < objList.count();i++)
        { 
            H5GraphicsItem* pItem = (H5GraphicsItem*)(objList.at(i)->iconGraphicsItem());
            if(!pItem) continue;
            QPointF pt(10,10);
            pItem->moveBy(pt.x(),pt.y());
        }
    }

    //还有一个--huangw
    m_pIconEditorMgr->selectedMgr()->recalcSelect();

    HPasteIconCommand* pasteIconCommand = new HPasteIconCommand(m_pIconEditorMgr,objList);
    m_pIconEditorMgr->iconEditorUndoStack()->push(pasteIconCommand);
    m_pIconEditorMgr->iconEditorFrame()->view()->setFocus();
}

void HIconEditorOp::del()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->selectedMgr() || !m_pIconEditorMgr->selectedMgr()->selectObj())
        return;
    HTempContainer* tempContainer = m_pIconEditorMgr->selectedMgr()->selectObj();
    QList<HBaseObj*> objList;
    for(int i = 0; i < tempContainer->getObjList().count();i++)
    {
        HBaseObj* pObj = (HBaseObj*)tempContainer->getObjList().at(i);
        if(!pObj) continue;
        pObj->setDeleted(true);
        objList.append(pObj);
    }

    m_pIconEditorMgr->selectedMgr()->clear();
    HDelIconCommand *delIconCommand = new HDelIconCommand(m_pIconEditorMgr,objList);
    m_pIconEditorMgr->iconEditorUndoStack()->push(delIconCommand);
}


QString HIconEditorOp::getClipboardFile()
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

bool HIconEditorOp::isClipboardAvailable()
{
   QFile file(getClipboardFile());
   return file.exists()&&file.size()!=0;
}

void HIconEditorOp::bringToTop()
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

void HIconEditorOp::bringToBottom()
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

void HIconEditorOp::groupObj()
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

void HIconEditorOp::ungroupObj()
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

void HIconEditorOp::zoomIn()
{


}

void HIconEditorOp::zoomOut()
{

}
