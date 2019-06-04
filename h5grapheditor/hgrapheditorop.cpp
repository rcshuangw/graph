#include "hgrapheditorop.h"
#include <QDir>
#include <QGraphicsItem>
#include <QProcessEnvironment>
#include "hgrapheditormgr.h"
#include "hgrapheditorscene.h"
#include "hgrapheditordoc.h"
#include "hgrapheditorview.h"
#include "hbaseobj.h"
#include "hiconobj.h"
#include "hrectangle.h"
#include "hcircle.h"
#include "hellipse.h"
#include "hline.h"
#include "hgraph.h"
#include "hgroup.h"
#include "hselectedmgr.h"
#include "htempcontainer.h"
#include "hdrawhelper.h"
#include "hmakeicon.h"
HGraphEditorOp::HGraphEditorOp(HGraphEditorMgr* mgr)
    :m_pGraphEditorMgr(mgr)
{
    m_scale = 1.0;
}

HGraphEditorOp::~HGraphEditorOp()
{

}

void HGraphEditorOp::createIconObj(const QString& TypeName,const QString& uuid,int shape,QPointF fpoint,QList<H5GraphicsItem*> &items)
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

    HBaseObj* pObj = pGraphEditorDoc->getCurGraph()->createBaseObj((DrawShape)shape,pIconTemplate);
    HIconObj* pIconObj = (HIconObj*)pObj;
    pIconObj->setOX(fpoint.x());
    pIconObj->setOY(fpoint.y());
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

    pIconObj->setShapeType((DrawShape)shape);
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
    ObjCreated(pObj,bPaste);
}

void HGraphEditorOp::ObjCreated(HBaseObj* pObj,bool bPaste)
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->graphEditorScene())
        return;
    m_pGraphEditorMgr->graphEditorScene()->onCreateObj(pObj,bPaste);
}

void HGraphEditorOp::objSelectChanged(HBaseObj *obj, bool isSelected)
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->selectedMgr())
        return;
    m_pGraphEditorMgr->selectedMgr()->selectChanged(obj,isSelected);
    emit updateBaseAction(obj);
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
    if(!m_pGraphEditorMgr /*|| !m_pGraphEditorMgr->iconEditorDrawToolMgr()*/)
        return;
    /*
    m_nToolType = ICON_DRAW_TOOL;
    m_pIconEditorMgr->iconEditorDrawToolMgr()->selectTool(drawShape);
    onEndDraw();
    QCursor cursor = m_pIconEditorMgr->iconEditorDrawToolMgr()->cursor();
    if(m_pIconEditorMgr->iconEditorFrame())
        m_pIconEditorMgr->iconEditorFrame()->cursorChanged(cursor);
        */
}

void HGraphEditorOp::selectTool(SelectMode selMode)
{
    if(!m_pGraphEditorMgr /*|| !m_pIconEditorMgr->iconEditorSelectTool()*/)
        return;
    /*
    m_nToolType = ICON_SELECT_TOOL;
    m_pIconEditorMgr->iconEditorSelectTool()->setSelectMode(selMode);
    onEndDraw();
    QCursor cursor = m_pIconEditorMgr->iconEditorSelectTool()->cursor();
    if(m_pIconEditorMgr->iconEditorFrame())
        m_pIconEditorMgr->iconEditorFrame()->cursorChanged(cursor);
        */
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
        if(pObj->getShapeType() == Icon)
        {
            HIconObj* obj = (HIconObj*)pObj;
            stream<<obj->getUuid();
            HIconObj* pIcon = new HIconObj(obj->iconTemplate());
            pIcon->initIconTemplate();
            pNewObj = (HBaseObj*)pIcon;
        }
        else
        {
            pNewObj = HMakeIcon::Instance()->newObj(pObj->getShapeType());
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
        if(nType == Icon)
        {
            QString s;
            stream>>s;
            HIconTemplate* ptemp = m_pGraphEditorMgr->graphEditorDoc()->findIconTemplate(s);
            bool bOk = false;
            if(ptemp)
            {
                HIconObj* pIconObj = (HIconObj*)m_pGraphEditorMgr->graphEditorDoc()->getCurGraph()->createBaseObj((DrawShape)nType,ptemp);
                if(pIconObj)
                {
                    bOk = true;
                    pIconObj->readData(0,&stream);
                }
                pObj = (HBaseObj*)pIconObj;
            }
            if(bOk)
            {
                HIconObj* pObj = new HIconObj(NULL);
                pObj->readData(0,&stream);
                delete pObj;
                pObj = NULL;
            }
        }
        else
        {
            HBaseObj* pObj = m_pGraphEditorMgr->graphEditorDoc()->getCurGraph()->createBaseObj((DrawShape)nType,NULL);
            if(!pObj) continue;
            pObj->readData(0,&stream);
        }
        ObjCreated(pObj,true);
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

    m_pGraphEditorMgr->addDelCommand(objList);
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
/*
    HTempContainer* tempSelect = (HTempContainer*)tempContainer;
    for(int i = 0; i < tempSelect->getObjList().count();i++)
    {
        HBaseObj* pObj = (HBaseObj*)tempSelect->getObjList().at(i);
        if(!pObj) continue;
        onRemoveObj(pObj);//画面删除
        //m_pIconEditorMgr->iconTemplate()->getSymbol()->removeBaseObj(pObj);//pattern删除
        pObj->setDeleted(false);
    }

    HGroup* pGroup =  (HGroup*)HMakeIcon::Instance()->newObj(Group);
    tempSelect->makeGroup(pGroup);
    m_pGraphEditorMgr->selectedMgr()->clear();
    //m_pGraphEditorMgr->iconTemplate()->getSymbol()->addBaseObj(pGroup);//增加到pattern
    onCreateObj(pGroup,false);//画面增加
    */
}

//取消组合
void HGraphEditorOp::ungroupObj()
{
    if(!m_pGraphEditorMgr || !m_pGraphEditorMgr->selectedMgr() || !m_pGraphEditorMgr->selectedMgr()->selectObj())
        return;

}

//对齐算法
void HGraphEditorOp::alignAlgorithm()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(tempContainer->size() < 2)
        return;
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

//横向等间距
void HGraphEditorOp::sizeHEqualSpace()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(tempContainer->size() < 3)
        return;
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
}

//纵向等间距
void HGraphEditorOp::sizeVEqualSpace()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(tempContainer->size() < 3)
        return;
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
}

void HGraphEditorOp::equalAlgorithm()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(!tempContainer || tempContainer->size() < 2)
        return;

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
               obj->resize(width,oldHeight);
            }
            else if(m_Equalway == IconSize::EqualHeight)
            {
                obj->transform(trans1,1);
                oldWidth = trans1.inverted().map(obj->getPointList(1)).boundingRect().width();
                obj->resize(oldWidth,height);
            }
            else if(m_Equalway == IconSize::EqualComplete)
            {
                obj->resize(width,height);
            }
        }
    }
    m_pGraphEditorMgr->selectedMgr()->refreshObjs();
    m_pGraphEditorMgr->selectedMgr()->recalcSelect();
}

void HGraphEditorOp::flipAlgorithm()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->selectedMgr())
        return;
    HTempContainer* tempContainer = m_pGraphEditorMgr->selectedMgr()->selectObj();
    if(!tempContainer) return;
    QList<HBaseObj*> objs;
    QList<QPointF> oldpts;
    for(int i = 0; i < tempContainer->getObjList().size() - 1;i++)
    {
        HBaseObj* obj = (HBaseObj*)tempContainer->getObjList().at(i);
        if(obj)
        {
            objs.append(obj);
            oldpts.append(obj->pos(1));
        }
    }

    if(HDrawHelper::Instance())
    {
        if(m_Flipway == LeftFlip90)
        {
            HDrawHelper::Instance()->ratate(-90);
        }
        else if(m_Flipway == RightFlip90)
        {
            HDrawHelper::Instance()->ratate(90);
        }
        else if(m_Flipway == HorizonFlip)
        {
            HDrawHelper::Instance()->turn(true);
        }
        else if(m_Flipway == VerticalFlip)
        {
            HDrawHelper::Instance()->turn(false);
        }
    }

    QList<QPointF> newpts;
    for(int i = 0; i < tempContainer->getObjList().size() - 1;i++)
    {
        HBaseObj* obj = (HBaseObj*)tempContainer->getObjList().at(i);
        if(obj)
        {
            newpts.append(obj->pos(1));
        }
    }
}

void HGraphEditorOp::flipLeft90()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->graphEditorScene())
        return;
    m_Flipway = IconFlip::LeftFlip90;
    flipAlgorithm();

}

void HGraphEditorOp::flipRight90()
{
    if(!m_pGraphEditorMgr && !m_pGraphEditorMgr->graphEditorScene())
        return;
    m_Flipway = IconFlip::RightFlip90;
    flipAlgorithm();
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

