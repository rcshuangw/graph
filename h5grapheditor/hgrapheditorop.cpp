#include "hgrapheditorop.h"
#include <QDir>
#include <QGraphicsItem>
#include <QProcessEnvironment>
#include <QScrollBar>
#include <QColorDialog>
#include <QMessageBox>
#include "hgrapheditormgr.h"
#include "hgrapheditorscene.h"
#include "hgrapheditordoc.h"
#include "hgrapheditorview.h"
#include "hbaseobj.h"
#include "hiconobj.h"
#include "hnormalobj.h"
#include "hrectangle.h"
#include "hcircle.h"
#include "hellipse.h"
#include "hline.h"
#include "hgraph.h"
#include "hgroup.h"
#include "htext.h"
#include "hselectedmgr.h"
#include "htempcontainer.h"
#include "hdrawhelper.h"
#include "hmakeicon.h"
#include "hgrapheditordrawtoolmgr.h"
#include "hgrapheditorselecttool.h"
#include "hgraphcommand.h"
HGraphEditorOp::HGraphEditorOp(HGraphEditorMgr* mgr)
    :m_pGraphEditorMgr(mgr)
{
    m_scale = 1.0;
}

HGraphEditorOp::~HGraphEditorOp()
{

}

void HGraphEditorOp::setGraphicsView()
{
    if(!m_pGraphEditorMgr->graphEditorDoc() || !m_pGraphEditorMgr->graphEditorDoc()->getCurGraph())
        return;

    int width = m_pGraphEditorMgr->graphEditorDoc()->getCurGraph()->m_width;
    int height = m_pGraphEditorMgr->graphEditorDoc()->getCurGraph()->m_height;
    QRectF newLogicRectF = QRectF(QPointF(0-width/2,0-height/2),QSizeF(width,height));
    if(!m_pGraphEditorMgr->graphEditorScene() || !m_pGraphEditorMgr->graphEditorView())
        return;
    m_pGraphEditorMgr->graphEditorScene()->setSceneRect(newLogicRectF);
    HGraphEditorView* pView = m_pGraphEditorMgr->graphEditorView();
    if(pView)
    {
        QScrollBar* pBar = pView->horizontalScrollBar();
        if(pBar && pBar->isHidden() == false)
        {
            pBar->setSliderPosition(pBar->minimum());
        }
        pBar = pView->verticalScrollBar();
        if(pBar && pBar->isHidden() == false)
        {
            pBar->setSliderPosition(pBar->minimum());
        }
    }
    m_pGraphEditorMgr->refreshView();
}

//创建测点图元 参数:遥信\遥测,uuid,shape(TEMPALTE_XXX_)
void HGraphEditorOp::createIconObj(const QString& strTypeName,const QString& uuid,int shape,QPointF fpoint,QList<H5GraphicsItem*> &items)
{
    if(!m_pGraphEditorMgr->graphEditorDoc() || !m_pGraphEditorMgr->graphEditorDoc()->getCurGraph())
        return;
    HIconTemplate* pIconTemplate = NULL;
    HGraphEditorDoc* pGraphEditorDoc = m_pGraphEditorMgr->graphEditorDoc();
    pIconTemplate = pGraphEditorDoc->findIconTemplate(uuid);
    if(!pIconTemplate)//没找到
    {
        return;
    }

    HBaseObj* pObj = NULL;
    if(shape > TEMPLATE_TYPE_NULL && shape <=TEMPLATE_TYPE_CONTROL)
    {
        pObj = pGraphEditorDoc->getCurGraph()->createBaseObj(Icon,pIconTemplate);
        HIconObj* pIconObj = (HIconObj*)pObj;
        pIconObj->setObjType(shape);
        pIconObj->setCatalogName(strTypeName);
    }
    else if(shape >=TEMPLATE_TYPE_TRANSFORMER2 && shape<=TEMPLATE_TYPE_REACTOR)
    {
        pObj = pGraphEditorDoc->getCurGraph()->createBaseObj(Normal,pIconTemplate);
        HNormalObj* pNormalObj = (HNormalObj*)pObj;
        pNormalObj->setObjType(shape);
        pNormalObj->setCatalogName(strTypeName);
    }
    pObj->setOX(fpoint.x());
    pObj->setOY(fpoint.y());
    //设置图元坐标位置
    double width = 100;
    double height = 100;
    QSizeF sizeF = pIconTemplate->getDefaultSize();
    double rectwidth = sizeF.width();
    double rectheight = sizeF.height();
    if(rectwidth > 0 || rectheight > 0)
    {
        width = rectwidth;
        height = rectheight;
    }
    else
    {
        width = 30;
        height = 30;
    }

    //pIconObj->setShapeType((DrawShape)shape);
    QPointF ptLeft = QPointF(fpoint.x() - width/2,fpoint.y() - height/2);
    QPointF ptRight = QPointF(fpoint.x() + width/2,fpoint.y() + height/2);
    HPointFList points;
    points<<ptLeft<<ptRight;
    pObj->setPointList(points);
    addIconObj(pObj);
    items.append(pObj->iconGraphicsItem());
}

//增加对象
void HGraphEditorOp::addIconObj(HBaseObj* pObj,bool bPaste)
{
    if(!pObj)
        return;
    m_pGraphEditorMgr->graphEditorDoc()->getCurGraph()->addIconObj(pObj);
    objCreated(pObj,bPaste);
}

void HGraphEditorOp::objCreated(HBaseObj* pObj,bool bPaste)
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorScene())
        return;
    m_pGraphEditorMgr->graphEditorScene()->onCreateObj(pObj,bPaste);
}

void HGraphEditorOp::objRemove(HBaseObj* pObj)
{
    if(m_pGraphEditorMgr && m_pGraphEditorMgr->graphEditorScene())
        m_pGraphEditorMgr->graphEditorScene()->onRemoveObj(pObj);
}

void HGraphEditorOp::objSelectChanged(HBaseObj *obj, bool isSelected)
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->selectedMgr())
        return;
    m_pGraphEditorMgr->selectedMgr()->selectChanged(obj,isSelected);
    m_pGraphEditorMgr->selectedMgr()->recalcSelect();
    emit updateBaseAction();
}

void HGraphEditorOp::onDrawPath(const QList<Path>& path)
{
    if(m_pGraphEditorMgr && m_pGraphEditorMgr->graphEditorScene())
        m_pGraphEditorMgr->graphEditorScene()->drawPath(path);
}

void HGraphEditorOp::onEndDraw()
{
    if(m_pGraphEditorMgr && m_pGraphEditorMgr->graphEditorScene())
        m_pGraphEditorMgr->graphEditorScene()->endDraw();
}

void HGraphEditorOp::drawTool(DrawShape drawShape)
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorDrawToolMgr())
        return;

    m_nToolType = ICON_DRAW_TOOL;
    m_pGraphEditorMgr->graphEditorDrawToolMgr()->selectTool(drawShape);
    onEndDraw();
    QCursor cursor = m_pGraphEditorMgr->graphEditorDrawToolMgr()->cursor();
    if(m_pGraphEditorMgr->graphEditorView())
        m_pGraphEditorMgr->graphEditorView()->setCursor(cursor);

}

void HGraphEditorOp::selectTool(SelectMode selMode)
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorSelectTool())
        return;

    m_nToolType = ICON_SELECT_TOOL;
    m_pGraphEditorMgr->graphEditorSelectTool()->setSelectMode(selMode);
    onEndDraw();
    QCursor cursor = m_pGraphEditorMgr->graphEditorSelectTool()->cursor();
    if(m_pGraphEditorMgr->graphEditorView())
        m_pGraphEditorMgr->graphEditorView()->setCursor(cursor);
}

void HGraphEditorOp::onRefreshSelect(const QRectF &rect)
{
    if(m_pGraphEditorMgr && m_pGraphEditorMgr->graphEditorScene())
        m_pGraphEditorMgr->graphEditorScene()->onRefreshSelect(rect);
}

void HGraphEditorOp::switchSelectTool()
{
  emit setSelectTool();
}

void HGraphEditorOp::onUpdateStatus(const QString &text)
{
    emit updateStatus(text);
}

void HGraphEditorOp::cut()
{
    copy();
    del();
}

void HGraphEditorOp::copy()
{
    //寻找当前页面的所有选择的图元
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->selectedMgr())
        return;

    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(!tempContainer) return;

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
    for(int i =0; i < tempContainer->getObjList().count();i++)
    {
        HBaseObj* pObj = (HBaseObj*)tempContainer->getObjList().at(i);
        if(!pObj) continue;
        stream<<(quint8)pObj->getShapeType();
        HBaseObj* pNewObj = NULL;
        //考虑objID,group,Icon
        if(pObj->getShapeType() == Icon || pObj->getShapeType() == Normal)
        {
            HIconObj* obj = (HIconObj*)pObj;
            stream<<obj->getUuid();
            HIconObj* pIconObj = (HIconObj*)m_pGraphEditorMgr->graphEditorDoc()->getCurGraph()->createBaseObj((DrawShape)obj->getShapeType(),obj->iconTemplate());
            pNewObj = (HBaseObj*)pIconObj;
        }
        else
        {
            pNewObj = m_pGraphEditorMgr->graphEditorDoc()->getCurGraph()->createBaseObj((DrawShape)pObj->getShapeType(),NULL);
        }
        if(!pNewObj) continue;
        pObj->copyTo(pNewObj);
        pNewObj->writeData(0,&stream);
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

void HGraphEditorOp::paste()
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorDoc() || !m_pGraphEditorMgr->graphEditorDoc()->getCurGraph())
        return;
    QString clipboardPath = getClipboardFile();
    QFile file(clipboardPath);
    if(!file.exists() || !file.open(QIODevice::ReadOnly))
        return;

    QDataStream stream(&file);
    int num;
    stream>>num;
    quint8 nType;
    QList<HBaseObj*> objList;
    for(int i = 0; i < num;i++)
    {
        stream>>nType;
        HBaseObj* pObj = NULL;
        if(nType == Icon || nType == Normal)
        {
            QString s;
            stream>>s;
            HIconTemplate* ptemp = m_pGraphEditorMgr->graphEditorDoc()->findIconTemplate(s);
            bool bOk = false;
            if(ptemp)
            {
                HBaseObj* obj = (HBaseObj*)m_pGraphEditorMgr->graphEditorDoc()->getCurGraph()->createBaseObj((DrawShape)nType,ptemp);
                if(nType == Icon)
                {
                    HIconObj* pIconObj = (HIconObj*)obj;
                    if(pIconObj)
                    {
                        bOk = true;
                        pIconObj->readData(0,&stream);
                    }
                }
                else if(nType == Normal)
                {
                    HNormalObj* pNormalObj = (HNormalObj*)pObj;
                    if(pNormalObj)
                    {
                        bOk = true;
                        pNormalObj->readData(0,&stream);
                    }
                }
                pObj = obj;
            }
            if(!bOk)
            {
                if(nType == Icon)
                {
                    HIconObj* pObj = new HIconObj(NULL);
                    pObj->readData(0,&stream);
                    delete pObj;
                    pObj = NULL;
                }
                else if(nType == Normal)
                {
                    HNormalObj* pObj = new HNormalObj(NULL);
                    pObj->readData(0,&stream);
                    delete pObj;
                    pObj = NULL;
                }
            }
        }
        else
        {
            HBaseObj* pObj = m_pGraphEditorMgr->graphEditorDoc()->getCurGraph()->createBaseObj((DrawShape)nType,NULL);
            if(!pObj) continue;
            pObj->readData(0,&stream);
        }
        m_pGraphEditorMgr->graphEditorDoc()->getCurGraph()->addIconObj(pObj);
        objCreated(pObj,true);
        objList.append(pObj);
     }

    //改变选择状态，原来选中图元取消选择
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    QList<HBaseObj*> oldSelList;
    for(int i = 0; i < tempContainer->getObjList().count();i++)
    {
        HBaseObj* pObj = (HBaseObj*)tempContainer->getObjList().at(i);
        if(!pObj || pObj->isDeleted() || !pObj->iconGraphicsItem())
            continue;
        oldSelList.append(pObj);
    }
    for(int i = 0; i < oldSelList.size();i++)
    {
        HBaseObj* pObj = (HBaseObj*)oldSelList.at(i);
        pObj->setModify(true);
        pObj->iconGraphicsItem()->setSelected(false);
    }

    //选择拷贝后的图元
    for(int i = 0; i < objList.count();i++)
    {
        H5GraphicsItem* pItem = (H5GraphicsItem*)(objList.at(i)->iconGraphicsItem());
        if(!pItem) continue;
       pItem->setSelected(true);
    }
    m_pGraphEditorMgr->selectedMgr()->refreshObjs();
    m_pGraphEditorMgr->selectedMgr()->recalcSelect();
    HGraphPasteCommand* pasteIconCommand = new HGraphPasteCommand(m_pGraphEditorMgr,objList);
    m_pGraphEditorMgr->graphEditorStack()->push(pasteIconCommand);
    m_pGraphEditorMgr->graphEditorView()->setFocus();
}

void HGraphEditorOp::del()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    QList<HBaseObj*> objList;
    for(int i = 0; i < tempContainer->getObjList().count();i++)
    {
        HBaseObj* pObj = (HBaseObj*)tempContainer->getObjList().at(i);
        if(!pObj) continue;
        pObj->setDeleted(true);
        objList.append(pObj);
    }
    //此处画面要设置modify ---huangw
    //m_pIconEditorMgr->iconTemplate()->setModify(true);
    m_pGraphEditorMgr->selectedMgr()->clear();
    HGraphDelCommand* delCommand = new HGraphDelCommand(m_pGraphEditorMgr,objList);
    m_pGraphEditorMgr->graphEditorStack()->push(delCommand);
}

QString HGraphEditorOp::getClipboardFile()
{
    QString clipboardPath = QProcessEnvironment::systemEnvironment().value("wfsystem_dir");
    clipboardPath.append("/temp/grapheditor");
    QDir dirClipboard(clipboardPath);
    if(!dirClipboard.exists())
        dirClipboard.mkdir(clipboardPath);
    clipboardPath.append("/graphclipboard.data");
    return clipboardPath;
}

bool HGraphEditorOp::isClipboardAvailable()
{
   QFile file(getClipboardFile());
   return file.exists()&&file.size()!=0;
}

//移动到顶层
void HGraphEditorOp::bringToTop()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->selectedMgr() )
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(!tempContainer) return;
    if(tempContainer->getObjList().count() != 1)
        return;
    int maxZValue = 0;
    HBaseObj* pObj = tempContainer->getObjList().at(0);
    if(!pObj) return;
    H5GraphicsItem* pItem = pObj->iconGraphicsItem();
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
        pObj->setZValue(maxZValue);
    }
}

//移动到底层
void HGraphEditorOp::bringToBottom()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(!tempContainer) return;
    if(tempContainer->getObjList().count() != 1)
        return;
    int minZValue = 0;
    HBaseObj* pObj = tempContainer->getObjList().at(0);
    if(!pObj) return;
    H5GraphicsItem* pItem = pObj->iconGraphicsItem();
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
        pObj->setZValue(minZValue);
    }
}

//组合
void HGraphEditorOp::groupObj()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->graphEditorScene() || !m_pGraphEditorMgr->graphEditorDoc())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(!tempContainer) return;
    if(tempContainer->getObjList().count() < 2) return;

    //不能与group合并
    bool bGroup = false;
    for(int i = 0; i < tempContainer->getObjList().size();i++)
    {
        HBaseObj* pObj = (HBaseObj*)tempContainer->at(i);
        if(pObj && pObj->getShapeType() == Group)
        {
            bGroup = true;
            break;
        }
    }

    if(bGroup)
    {
        QMessageBox::information(NULL, QString("提示"),QString("选择图符中包含组合，请先解除组合!"),QMessageBox::Ok,QMessageBox::Cancel);
        return;
    }

    for(int i = 0; i < tempContainer->getObjList().count();i++)
    {
        HBaseObj* pObj = (HBaseObj*)tempContainer->getObjList().at(i);
        if(!pObj) continue;
        m_pGraphEditorMgr->graphEditorScene()->onRemoveObj(pObj);//画面删除
        m_pGraphEditorMgr->graphEditorDoc()->getCurGraph()->takeIconObj(pObj);//pattern删除
        pObj->setDeleted(false);
    }

    HGroup* pGroup =  (HGroup*)HMakeIcon::Instance()->newObj(Group);
    tempContainer->makeGroup(pGroup);
    m_pGraphEditorMgr->selectedMgr()->clear();
    m_pGraphEditorMgr->graphEditorDoc()->getCurGraph()->addIconObj(pGroup);//增加到pattern
    m_pGraphEditorMgr->graphEditorScene()->onCreateObj(pGroup,false);//画面增加
}

//取消组合
void HGraphEditorOp::ungroupObj()
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->selectedMgr() || !m_pGraphEditorMgr->selectedMgr()->selectObj())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(tempContainer->getObjList().size() != 1 || tempContainer->getObjList().at(0)->getShapeType() != Group)
    {
        QMessageBox::information(NULL, QStringLiteral("提示"),QStringLiteral("请先单选组合再解除!"),QMessageBox::Ok,QMessageBox::Cancel);
        return;
    }
    HGroup* pGroup = (HGroup*)tempContainer->getObjList().at(0);
    if(!pGroup) return;
    HTempContainer* tc = (HTempContainer*)HMakeIcon::Instance()->newObj(TempContainer);
    pGroup->makeTempContainer(tc);
    for(int i = 0; i < tc->getObjList().count();i++)
    {
        HBaseObj* pObj = (HBaseObj*)tc->getObjList().at(i);
        if(!pObj) continue;
        m_pGraphEditorMgr->graphEditorScene()->onCreateObj(pObj,false);
        m_pGraphEditorMgr->graphEditorDoc()->getCurGraph()->addIconObj(pObj);//增加到pattern

    }
    m_pGraphEditorMgr->graphEditorScene()->onRemoveObj(pGroup);
    m_pGraphEditorMgr->graphEditorDoc()->getCurGraph()->removeIconObj(pGroup);
    m_pGraphEditorMgr->selectedMgr()->clear();

}

//对齐算法
void HGraphEditorOp::alignAlgorithm()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(tempContainer->size() < 2)
        return;

    QList<QPointF> oldPts;
    for(int i = 0; i < tempContainer->size();i++)
    {
        HBaseObj* pObj = (HBaseObj*)tempContainer->at(i);
        if(pObj){
            oldPts.append(pObj->pos(1));
        }
    }

    HBaseObj* pObj = tempContainer->at(0);
    if(!pObj) return;
    HPointFList points = pObj->getPointList(1);
    QRectF rectF = points.boundingRect();
    switch(m_Alignment)
    {
    case Qt::AlignLeft:
    {
        double fLeft = rectF.left();
        for(int i = 0; i < tempContainer->getObjList().size();i++)
        {
            HBaseObj* obj = (HBaseObj*)tempContainer->getObjList().at(i);
            if(obj)
            {
                QRectF nRect = obj->getPointList(1).boundingRect();
                qreal dleft = fLeft - nRect.left();
                obj->moveBy(dleft,0);
                obj->iconGraphicsItem()->setPos(obj->pos(1));
            }
        }
        break;
    }
    case Qt::AlignRight:
    {
        double fRight = rectF.right();
        for(int i = 0; i < tempContainer->getObjList().size();i++)
        {
            HBaseObj* obj = (HBaseObj*)tempContainer->getObjList().at(i);
            if(obj)
            {
                QRectF nRect = obj->getPointList(1).boundingRect();
                qreal dright = fRight - nRect.right();
                obj->moveBy(dright,0);
                obj->iconGraphicsItem()->setPos(obj->pos(1));
            }
        }
        break;
    }
    case Qt::AlignVCenter://垂直居中
    {
        double fVCenter = rectF.center().x();
        for(int i = 0; i < tempContainer->getObjList().size();i++)
        {
            HBaseObj* obj = (HBaseObj*)tempContainer->getObjList().at(i);
            if(obj)
            {
                QRectF nRect = obj->getPointList(1).boundingRect();
                qreal dVCenter = fVCenter - nRect.center().x();
                obj->moveBy(dVCenter,0);
                obj->iconGraphicsItem()->setPos(obj->pos(1));
            }
        }
        break;
    }
    case Qt::AlignTop:
    {
        double fTop = rectF.top();
        for(int i = 0; i < tempContainer->getObjList().size();i++)
        {
            HBaseObj* obj = (HBaseObj*)tempContainer->getObjList().at(i);
            if(obj)
            {
                QRectF nRect = obj->getPointList(1).boundingRect();
                qreal dTop = fTop - nRect.top();
                obj->moveBy(0,dTop);
                obj->iconGraphicsItem()->setPos(obj->pos(1));
            }
        }
        break;
    }
    case Qt::AlignBottom:
    {
        double fBottom = rectF.bottom();
        for(int i = 0; i < tempContainer->getObjList().size();i++)
        {
            HBaseObj* obj = (HBaseObj*)tempContainer->getObjList().at(i);
            if(obj)
            {
                QRectF nRect = obj->getPointList(1).boundingRect();
                qreal dBottom = fBottom - nRect.bottom();
                obj->moveBy(0,dBottom);
                obj->iconGraphicsItem()->setPos(obj->pos(1));
            }
        }
        break;
    }
    case Qt::AlignHCenter://水平居中
    {
        double fHCenter = rectF.center().y();
        for(int i = 0; i < tempContainer->getObjList().size();i++)
        {
            HBaseObj* obj = (HBaseObj*)tempContainer->getObjList().at(i);
            if(obj)
            {
                QRectF nRect = obj->getPointList(1).boundingRect();
                qreal dHCenter = fHCenter - nRect.center().y();
                obj->moveBy(0,dHCenter);
                obj->iconGraphicsItem()->setPos(obj->pos(1));
            }
        }
        break;
    }
    }

    m_pGraphEditorMgr->selectedMgr()->refreshObjs();
    m_pGraphEditorMgr->selectedMgr()->recalcSelect();

    QList<HBaseObj*> objs;
    QList<QPointF> newPts;
    for(int i = 0; i < tempContainer->size();i++)
    {
        HBaseObj* pObj = (HBaseObj*)tempContainer->at(i);
        if(pObj){
            objs.append(pObj);
            newPts.append(pObj->pos(1));
        }
    }
    HGraphMoveCommand* moveCommand = new HGraphMoveCommand(m_pGraphEditorMgr,objs,oldPts,newPts);
    m_pGraphEditorMgr->graphEditorStack()->push(moveCommand);
}

//左对齐
void HGraphEditorOp::alignLeft()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->graphEditorScene())
        return;
    m_Alignment = Qt::AlignLeft;
    alignAlgorithm();
}

//右对齐
void HGraphEditorOp::alignRight()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->graphEditorScene())
        return;
    m_Alignment = Qt::AlignRight;
    alignAlgorithm();
}

//垂直居中
void HGraphEditorOp::alignVCenter()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->graphEditorScene())
        return;
    m_Alignment = Qt::AlignVCenter;
    alignAlgorithm();
}

//上对齐
void HGraphEditorOp::alignTop()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->graphEditorScene())
        return;
    m_Alignment = Qt::AlignTop;
    alignAlgorithm();
}

//下对齐
void HGraphEditorOp::alignBottom()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->graphEditorScene())
        return;
    m_Alignment = Qt::AlignBottom;
    alignAlgorithm();
}

//水平居中
void HGraphEditorOp::alignHCenter()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->graphEditorScene())
        return;
    m_Alignment = Qt::AlignHCenter;
    alignAlgorithm();
}

//等宽
void HGraphEditorOp::sizeEqualWidth()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->graphEditorScene())
        return;
    m_Equalway = IconSize::EqualWidth;
    equalAlgorithm();
}

//等高
void HGraphEditorOp::sizeEqualHeight()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->graphEditorScene())
        return;
    m_Equalway = IconSize::EqualHeight;
    equalAlgorithm();
}

//完全相等
void HGraphEditorOp::sizeEqualComplete()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->graphEditorScene())
        return;
    m_Equalway = IconSize::EqualComplete;
    equalAlgorithm();
}

void HGraphEditorOp::equalAlgorithm()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(!tempContainer || tempContainer->size() < 2)
        return;
    QList<HPointFList> oldPts;
    QList<HBaseObj*> objs;
    QList<HPointFList> newPts;

    HBaseObj* pFObj = tempContainer->getObjList().at(0);
    if(!pFObj) return;
    QTransform trans;
    pFObj->transform(trans,1);
    qreal width = trans.inverted().map(pFObj->getPointList(1)).boundingRect().width();
    qreal height = trans.inverted().map(pFObj->getPointList(1)).boundingRect().height();
    for(int i = 0; i < tempContainer->getObjList().size();i++)
    {
        HBaseObj* obj = (HBaseObj*)tempContainer->getObjList().at(i);
        if(obj)
        {
            QTransform trans1;
            qreal oldWidth,oldHeight;
            if(m_Equalway = IconSize::EqualWidth)
            {
               obj->transform(trans1,1);
               oldHeight = trans1.inverted().map(obj->getPointList(1)).boundingRect().height();
               oldPts.append(obj->getPointList(1));
               obj->resize(width,oldHeight);
               newPts.append(obj->getPointList(1));
               objs.append(obj);
            }
            else if(m_Equalway == IconSize::EqualHeight)
            {
                obj->transform(trans1,1);
                oldWidth = trans1.inverted().map(obj->getPointList(1)).boundingRect().width();
                oldPts.append(obj->getPointList(1));
                obj->resize(oldWidth,height);
                newPts.append(obj->getPointList(1));
                objs.append(obj);
            }
            else if(m_Equalway == IconSize::EqualComplete)
            {
                oldPts.append(obj->getPointList(1));
                obj->resize(width,height);
                newPts.append(obj->getPointList(1));
                objs.append(obj);

            }
        }
    }
    m_pGraphEditorMgr->selectedMgr()->refreshObjs();
    m_pGraphEditorMgr->selectedMgr()->recalcSelect();

    HGraphResizeCommand* resizeCommand = new HGraphResizeCommand(m_pGraphEditorMgr,objs,oldPts,newPts);
    m_pGraphEditorMgr->graphEditorStack()->push(resizeCommand);
}

//横向等间距
void HGraphEditorOp::sizeHEqualSpace()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(tempContainer->size() < 3)
        return;
    QList<QPointF> oldPts;
    for(int i = 0; i < tempContainer->size();i++)
    {
        HBaseObj* pObj = (HBaseObj*)tempContainer->at(i);
        if(pObj){
            oldPts.append(pObj->pos(1));
        }
    }

    HBaseObj* pFObj = tempContainer->getObjList().first();
    HBaseObj* pLObj = tempContainer->getObjList().last();
    if(!pFObj || !pLObj) return;
    qreal dFdx = pFObj->getPointList(1).boundingRect().left();
    qreal dLdx = pLObj->getPointList(1).boundingRect().left();
    qreal dSpace = ( dLdx - dFdx)/(tempContainer->getObjList().count() - 1);
    for(int i = 0; i < tempContainer->getObjList().size() - 1;i++)
    {
        HBaseObj* obj = (HBaseObj*)tempContainer->getObjList().at(i);
        if(obj)
        {
            QRectF nRect = obj->getPointList(1).boundingRect();
            qreal dx = nRect.left();
            obj->moveBy(i*dSpace-(dx - dFdx),0);
            obj->iconGraphicsItem()->setPos(obj->pos(1));
        }
    }
    m_pGraphEditorMgr->selectedMgr()->refreshObjs();
    m_pGraphEditorMgr->selectedMgr()->recalcSelect();

    QList<HBaseObj*> objs;
    QList<QPointF> newPts;
    for(int i = 0; i < tempContainer->size();i++)
    {
        HBaseObj* pObj = (HBaseObj*)tempContainer->at(i);
        if(pObj){
            objs.append(pObj);
            newPts.append(pObj->pos(1));
        }
    }
    HGraphMoveCommand* moveCommand = new HGraphMoveCommand(m_pGraphEditorMgr,objs,oldPts,newPts);
    m_pGraphEditorMgr->graphEditorStack()->push(moveCommand);
}

//纵向等间距
void HGraphEditorOp::sizeVEqualSpace()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(tempContainer->size() < 3)
        return;
    QList<QPointF> oldPts;
    for(int i = 0; i < tempContainer->size();i++)
    {
        HBaseObj* pObj = (HBaseObj*)tempContainer->at(i);
        if(pObj){
            oldPts.append(pObj->pos(1));
        }
    }

    HBaseObj* pFObj = tempContainer->getObjList().first();
    HBaseObj* pLObj = tempContainer->getObjList().last();
    if(!pFObj || !pLObj) return;
    qreal dFdy = pFObj->getPointList(1).boundingRect().top();
    qreal dLdy = pLObj->getPointList(1).boundingRect().top();
    qreal dSpace = ( dLdy - dFdy)/(tempContainer->getObjList().count() - 1);
    for(int i = 0; i < tempContainer->getObjList().size() - 1;i++)
    {
        HBaseObj* obj = (HBaseObj*)tempContainer->getObjList().at(i);
        if(obj)
        {
            QRectF nRect = obj->getPointList(1).boundingRect();
            qreal dy = nRect.top();
            obj->moveBy(0,i*dSpace-(dy - dFdy));
            obj->iconGraphicsItem()->setPos(obj->pos(1));
        }
    }
    m_pGraphEditorMgr->selectedMgr()->refreshObjs();
    m_pGraphEditorMgr->selectedMgr()->recalcSelect();

    QList<HBaseObj*> objs;
    QList<QPointF> newPts;
    for(int i = 0; i < tempContainer->size();i++)
    {
        HBaseObj* pObj = (HBaseObj*)tempContainer->at(i);
        if(pObj){
            objs.append(pObj);
            newPts.append(pObj->pos(1));
        }
    }
    HGraphMoveCommand* moveCommand = new HGraphMoveCommand(m_pGraphEditorMgr,objs,oldPts,newPts);
    m_pGraphEditorMgr->graphEditorStack()->push(moveCommand);
}

void HGraphEditorOp::rotateLeft90()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->graphEditorScene())
        return;
    m_Flipway = IconFlip::LeftFlip90;
    rotateAlgorithm();

}

void HGraphEditorOp::rotateRight90()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->graphEditorScene())
        return;
    m_Flipway = IconFlip::RightFlip90;
    rotateAlgorithm();
}

void HGraphEditorOp::rotateAlgorithm()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(!tempContainer) return;
    QList<HBaseObj*> objs;
    QList<QPointF> oldPts;
    for(int i = 0; i < tempContainer->getObjList().size() - 1;i++)
    {
        HBaseObj* obj = (HBaseObj*)tempContainer->getObjList().at(i);
        if(obj)
        {
            objs.append(obj);
            oldPts.append(obj->pos(1));
        }
    }

    int rotate = -90;
    if(HDrawHelper::Instance())
    {
        if(m_Flipway == LeftFlip90)
        {
            rotate = -90;
            HDrawHelper::Instance()->rotate(-90);
        }
        else if(m_Flipway == RightFlip90)
        {
            rotate = 90;
            HDrawHelper::Instance()->rotate(90);
        }
    }

    QList<QPointF> newPts;
    for(int i = 0; i < tempContainer->getObjList().size() - 1;i++)
    {
        HBaseObj* obj = (HBaseObj*)tempContainer->getObjList().at(i);
        if(obj)
        {
            newPts.append(obj->pos(1));
        }
    }
    //trun
    m_pGraphEditorMgr->graphEditorStack()->beginMacro("Trun");
    HGraphMoveCommand* moveCommand = new HGraphMoveCommand(m_pGraphEditorMgr,objs,oldPts,newPts);
    m_pGraphEditorMgr->graphEditorStack()->push(moveCommand);
    HGraphRotateCommand* rotateCommand = new HGraphRotateCommand(m_pGraphEditorMgr,objs,rotate);
    m_pGraphEditorMgr->graphEditorStack()->push(rotateCommand);
    m_pGraphEditorMgr->graphEditorStack()->endMacro();

}

void HGraphEditorOp::flipHorizon()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->graphEditorScene())
        return;
    m_Flipway = IconFlip::HorizonFlip;
    flipAlgorithm();
}

void HGraphEditorOp::flipVertical()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->graphEditorScene())
        return;
    m_Flipway = IconFlip::VerticalFlip;
    flipAlgorithm();
}

void HGraphEditorOp::flipAlgorithm()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(!tempContainer) return;
    QList<HBaseObj*> objs;
    QList<QPointF> oldPts;
    for(int i = 0; i < tempContainer->getObjList().size() - 1;i++)
    {
        HBaseObj* obj = (HBaseObj*)tempContainer->getObjList().at(i);
        if(obj)
        {
            objs.append(obj);
            oldPts.append(obj->pos(1));
        }
    }

    bool bTurn = false;
    if(HDrawHelper::Instance())
    {
        if(m_Flipway == HorizonFlip)
        {
            bTurn = true;
            HDrawHelper::Instance()->turn(true);
        }
        else if(m_Flipway == VerticalFlip)
        {
            HDrawHelper::Instance()->turn(false);
        }
    }

    QList<QPointF> newPts;
    for(int i = 0; i < tempContainer->getObjList().size() - 1;i++)
    {
        HBaseObj* obj = (HBaseObj*)tempContainer->getObjList().at(i);
        if(obj)
        {
            newPts.append(obj->pos(1));
        }
    }
    //trun
    m_pGraphEditorMgr->graphEditorStack()->beginMacro("Rotate");
    HGraphMoveCommand* moveCommand = new HGraphMoveCommand(m_pGraphEditorMgr,objs,oldPts,newPts);
    m_pGraphEditorMgr->graphEditorStack()->push(moveCommand);
    HGraphTurnCommand* turnCommand = new HGraphTurnCommand(m_pGraphEditorMgr,objs,bTurn);
    m_pGraphEditorMgr->graphEditorStack()->push(turnCommand);
    m_pGraphEditorMgr->graphEditorStack()->endMacro();
}

void HGraphEditorOp::setupMatrix()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->graphEditorView())
        return;
    QMatrix oldMatrix = m_pGraphEditorMgr->graphEditorView()->matrix();
    m_pGraphEditorMgr->graphEditorView()->resetMatrix();
    m_pGraphEditorMgr->graphEditorView()->translate(oldMatrix.dx(), oldMatrix.dy());
    m_pGraphEditorMgr->graphEditorView()->scale(m_scale, m_scale);
}

void HGraphEditorOp::zoomIn()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->graphEditorView())
        return;
    m_scale += (qreal)0.2;
    if(m_scale > (qreal)2.0) m_scale = (qreal)2.0;
    if(m_scale < (qreal)0.5) m_scale = (qreal)0.5;
    setupMatrix();
}

void HGraphEditorOp::zoomOut()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->graphEditorView())
        return;
    m_scale -= (qreal)0.1;
    if(m_scale > (qreal)2.0) m_scale = (qreal)2.0;
    if(m_scale < (qreal)0.5) m_scale = (qreal)0.5;
    setupMatrix();
}

//自由缩放
void HGraphEditorOp::zoom()
{

}

//原始大小
void HGraphEditorOp::zoomSame()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->graphEditorView())
        return;
    m_scale = (qreal)1.0;
    setupMatrix();
}

//颜色部分
QColor HGraphEditorOp::getPenColor()
{
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(!tempContainer)
        return QColor();
    QColor clr;
    if(tempContainer->size() <= 0)
    {
        clr = m_pGraphEditorMgr->graphEditorDrawToolMgr()->m_vDrawAttribute.drawPen.color();
    }
    else
    {
        HBaseObj* pObj = tempContainer->at(0);
        if(pObj)
        {
            clr = QColor(pObj->getLineColor());
        }
    }

    clr = QColorDialog::getColor(clr);
    if(clr.isValid())
    {
        if(tempContainer->size() <= 0)
        {
            m_pGraphEditorMgr->graphEditorDrawToolMgr()->m_vDrawAttribute.drawPen.setColor(clr);
        }
        else
        {
            HBaseObj* pObj = tempContainer->at(0);
            if(pObj)
            {
                pObj->setLineColor(clr.name());
                if(pObj->getShapeType() == Text)
                {
                    pObj->setTextColor(clr.name());
                }
            }
        }
    }
    return clr;
}

QColor HGraphEditorOp::getFillColor()
{
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    QColor clr;
    if(!tempContainer)
        return clr;

    if(tempContainer->size() <= 0)
    {
        clr = m_pGraphEditorMgr->graphEditorDrawToolMgr()->m_vDrawAttribute.brush.color();
    }
    else
    {
        HBaseObj* pObj = tempContainer->at(0);
        HShapeObj* obj = dynamic_cast<HShapeObj*>(pObj);
        if(obj)
        {
            clr = QColor(obj->getFillColor());
        }
        else
        {
            clr = Qt::white;
        }
    }

    clr = QColorDialog::getColor(clr);
    if(clr.isValid())
    {
        if(tempContainer->size() <= 0)
        {
            m_pGraphEditorMgr->graphEditorDrawToolMgr()->m_vDrawAttribute.brush.setColor(clr);
        }
        else
        {
            HBaseObj* pObj = tempContainer->at(0);
            HShapeObj* obj = dynamic_cast<HShapeObj*>(pObj);
            if(obj)
            {
                obj->setFillColor(clr.name());
            }
            m_pGraphEditorMgr->graphEditorDrawToolMgr()->m_vDrawAttribute.brush.setColor(clr);
        }
    }
    return clr;
}

void HGraphEditorOp::setPicture()
{

}

//线型填充等部分
void HGraphEditorOp::setLineStyle(int linestyle)
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(!tempContainer)
        return;
    Qt::PenStyle style = (Qt::PenStyle)linestyle;
    m_pGraphEditorMgr->graphEditorDrawToolMgr()->m_vDrawAttribute.drawPen.setStyle(style);
    int sz = tempContainer->size();
    for(int i = 0;i < sz;i++)
    {
        HBaseObj* pObj = tempContainer->at(i);
        if(pObj)
        {
            pObj->setLineStyle(style);
        }
    }
}

void HGraphEditorOp::setLineWidth(int linewidth)
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(!tempContainer)
        return;
    m_pGraphEditorMgr->graphEditorDrawToolMgr()->m_vDrawAttribute.drawPen.setWidth(linewidth);
    int sz = tempContainer->size();
    for(int i = 0;i < sz;i++)
    {
        HBaseObj* pObj = tempContainer->at(i);
        if(pObj)
        {
            pObj->setLineWidth(linewidth);
        }
    }
}

void HGraphEditorOp::setFillBrush(int brushStyle)
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(!tempContainer)
        return;
    Qt::BrushStyle style = (Qt::BrushStyle)brushStyle;
    int sz = tempContainer->size();
    for(int i = 0;i < sz;i++)
    {
        HBaseObj* pObj = tempContainer->at(i);
        if(!pObj) continue;
        HShapeObj* obj = dynamic_cast<HShapeObj*>(pObj);
        if(obj)
        {
            obj->setFillStyle(style);
        }
    }
}

void HGraphEditorOp::setFontFamily(const QString& family)
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(!tempContainer)
        return;
    int sz = tempContainer->size();
    for(int i = 0;i < sz;i++)
    {
        HBaseObj* pObj = tempContainer->at(i);
        if(!pObj) continue;
        if(pObj->getShapeType() == Text)
        {
            HText *pText = (HText*)pObj;
            pText->setFontFamily(family);
        }
    }
}

void HGraphEditorOp::setFontSize(int size)
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(!tempContainer)
        return;
    int sz = tempContainer->size();
    for(int i = 0;i < sz;i++)
    {
        HBaseObj* pObj = tempContainer->at(i);
        if(!pObj) continue;
        if(pObj->getShapeType() == Text)
        {
            HText *pText = (HText*)pObj;
            pText->setFontSize(size);
        }
    }
}

void HGraphEditorOp::setBold(bool b)
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(!tempContainer)
        return;
    int sz = tempContainer->size();
    for(int i = 0;i < sz;i++)
    {
        HBaseObj* pObj = tempContainer->at(i);
        if(!pObj) continue;
        if(pObj->getShapeType() == Text)
        {
            HText *pText = (HText*)pObj;
            pText->setFontBold(b);
        }
    }
}

void HGraphEditorOp::setItalic(bool b)
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(!tempContainer)
        return;
    int sz = tempContainer->size();
    for(int i = 0;i < sz;i++)
    {
        HBaseObj* pObj = tempContainer->at(i);
        if(!pObj) continue;
        if(pObj->getShapeType() == Text)
        {
            HText *pText = (HText*)pObj;
            pText->setFontItalic(b);
        }
    }
}

void HGraphEditorOp::setUnderline(bool b)
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(!tempContainer)
        return;
    int sz = tempContainer->size();
    for(int i = 0;i < sz;i++)
    {
        HBaseObj* pObj = tempContainer->at(i);
        if(!pObj) continue;
        if(pObj->getShapeType() == Text)
        {
            HText *pText = (HText*)pObj;
            pText->setFontUnderline(b);
        }
    }
}

void HGraphEditorOp::setObjAttribute()
{
    emit attributeChanged();
}
