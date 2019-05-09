#include "hiconcommand.h"
#include "hiconapi.h"
#include "hbaseobj.h"
#include "hiconobj.h"
//#include "hiconrectobj.h"
#include "hiconeditormgr.h"
#include "h5graphicsitem.h"
#include "hiconeditorframe.h"
#include "hiconeditorop.h"
//#include "hiconlineitem.h"
HIconCommand::HIconCommand(HIconEditorMgr* iconMgr):m_pIconEditorMgr(iconMgr)
{

    bFirstTime = true;
}

HIconCommand::~HIconCommand()
{

}


int HIconCommand::id() const
{
    return -1;
}
void HIconCommand::redo()
{

}

void HIconCommand::undo()
{

}


////////////////////////////////////////新建///////////////////////////////////////////
HNewIconCommand::HNewIconCommand(HIconEditorMgr* iconMgr,HBaseObj* obj):HIconCommand(iconMgr),pObj(obj)
{
    setText("create object");
}

HNewIconCommand::~HNewIconCommand()
{

}

int HNewIconCommand::id() const
{
    return New;
}

void HNewIconCommand::redo()
{
    if(!m_pIconEditorMgr || !pObj || !m_pIconEditorMgr->iconEditorFrame())
        return;
    //删除新建的
    pObj->setDeleted(false);
    //获取Item
    H5GraphicsItem* item = pObj->iconGraphicsItem();
    m_pIconEditorMgr->iconEditorFrame()->view()->ensureVisible(item);
    item->setVisible(true);
    m_pIconEditorMgr->iconEditorOp()->onRefreshSelect(pObj->boundingRect(1));
}

void HNewIconCommand::undo()
{
    if(!m_pIconEditorMgr || !pObj || !m_pIconEditorMgr->iconEditorFrame())
        return;
    //删除新建的
    pObj->setDeleted(true);
    //获取Item
    H5GraphicsItem* item = pObj->iconGraphicsItem();
    m_pIconEditorMgr->iconEditorFrame()->view()->ensureVisible(item);
    item->setVisible(false);
    m_pIconEditorMgr->iconEditorOp()->onRefreshSelect(pObj->boundingRect(1));
}

////////////////////////////////////////删除///////////////////////////////////////////
HDelIconCommand::HDelIconCommand(HIconEditorMgr* iconMgr,QList<HBaseObj*> objs):HIconCommand(iconMgr),pObjList(objs)
{
    setText("create object");
}

HDelIconCommand::~HDelIconCommand()
{

}

int HDelIconCommand::id() const
{
    return Delete;
}

void HDelIconCommand::redo()
{
    if(bFirstTime)
    {
        bFirstTime = false;
        return;
    }
    if(!m_pIconEditorMgr || pObjList.isEmpty() || !m_pIconEditorMgr->iconEditorFrame())
        return;
    QRectF bounding;
    for(int i = 0; i < pObjList.count();i++)
    {
        HBaseObj* obj = (HBaseObj*)pObjList[i];
        if(!obj) continue;
        H5GraphicsItem* item = obj->iconGraphicsItem();
        if(!item) continue;
        obj->setDeleted(true);
        bounding = bounding.united(item->boundingRect());
        item->setVisible(false);
    }
    m_pIconEditorMgr->iconEditorFrame()->refreshSelected(bounding);
}

void HDelIconCommand::undo()
{
    if(!m_pIconEditorMgr || pObjList.isEmpty() || !m_pIconEditorMgr->iconEditorFrame())
        return;
    QRectF bounding;
    for(int i = 0; i < pObjList.count();i++)
    {
        HBaseObj* obj = (HBaseObj*)pObjList[i];
        if(!obj) continue;
        H5GraphicsItem* item = obj->iconGraphicsItem();
        if(!item) continue;
        obj->setDeleted(false);
        bounding = bounding.united(item->boundingRect());
        item->setVisible(true);
    }
    m_pIconEditorMgr->iconEditorFrame()->refreshSelected(bounding);
}


////////////////////////////////////////粘贴///////////////////////////////////////////
HPasteIconCommand::HPasteIconCommand(HIconEditorMgr* iconMgr,QList<HBaseObj*> objs):HIconCommand(iconMgr),pObjList(objs)
{
    setText("create object");
}

HPasteIconCommand::~HPasteIconCommand()
{

}

int HPasteIconCommand::id() const
{
    return Paste;
}

void HPasteIconCommand::redo()
{
    if(bFirstTime)
    {
        bFirstTime = false;
        return;
    }
    if(!m_pIconEditorMgr || pObjList.isEmpty() || !m_pIconEditorMgr->iconEditorFrame())
        return;
    QRectF bounding;
    for(int i = 0; i < pObjList.count();i++)
    {
        HBaseObj* obj = (HBaseObj*)pObjList[i];
        if(!obj) continue;
        H5GraphicsItem* item = obj->iconGraphicsItem();
        if(!item) continue;
        obj->setDeleted(false);
        bounding = bounding.united(item->boundingRect());
        item->setVisible(true);
    }
    m_pIconEditorMgr->iconEditorFrame()->refreshSelected(bounding);
}

void HPasteIconCommand::undo()
{
    if(!m_pIconEditorMgr || pObjList.isEmpty() || !m_pIconEditorMgr->iconEditorFrame())
        return;
    QRectF bounding;
    for(int i = 0; i < pObjList.count();i++)
    {
        HBaseObj* obj = (HBaseObj*)pObjList[i];
        if(!obj) continue;
        H5GraphicsItem* item = obj->iconGraphicsItem();
        if(!item) continue;
        obj->setDeleted(true);
        bounding = bounding.united(item->boundingRect());
        item->setVisible(false);
    }
    m_pIconEditorMgr->iconEditorFrame()->refreshSelected(bounding);
}


////////////////////////////////////////移动///////////////////////////////////////////
HMoveIconCommand::HMoveIconCommand(HIconEditorMgr* iconMgr,QList<HBaseObj*> pObjs,qreal dx,qreal dy)
    :HIconCommand(iconMgr),pObjList(pObjs)
{
    for(int i = 0; i < pObjList.count();i++)
    {
        dxList.append(dx);
        dyList.append(dy);
    }
    setText("Move Object(s)");
}

HMoveIconCommand::HMoveIconCommand(HIconEditorMgr* iconMgr,QList<HBaseObj*> pObjs,QList<qreal> dxs,QList<qreal> dys)
    :HIconCommand(iconMgr),pObjList(pObjs),dxList(dxs),dyList(dys)
{
    setText("Move Object(s)");
}

HMoveIconCommand::HMoveIconCommand(HIconEditorMgr* iconMgr,QList<HBaseObj*> pObjs,QList<QPointF> oldPt,QList<QPointF> newPt)
    :HIconCommand(iconMgr),pObjList(pObjs)
{
    for(int i = 0; i< pObjList.count();i++)
    {
        dxList.append(newPt.at(i).x() - oldPt.at(i).x());
        dyList.append(newPt.at(i).y() - oldPt.at(i).y());
    }
    setText("Move Object(s)");
}

HMoveIconCommand::~HMoveIconCommand()
{

}

int HMoveIconCommand::id() const
{
    return Move;
}

void HMoveIconCommand::redo()
{
    //redo只能是undo完成之后的动作，第一次不能有redo动作
    if(bFirstTime)
    {
        bFirstTime = false;
        return;
    }
    if(!m_pIconEditorMgr || pObjList.isEmpty() || !m_pIconEditorMgr->iconEditorFrame())
        return;
    QRectF oldBounding;
    QRectF newBounding;
    for(int i = 0; i < pObjList.count();i++)
    {
        HBaseObj* obj = (HBaseObj*)pObjList[i];
        if(!obj) continue;
        H5GraphicsItem* item = obj->iconGraphicsItem();
        if(!item) continue;
        oldBounding = oldBounding.united(item->boundingRect());
        newBounding = newBounding.united(item->boundingRect().translated(dxList[i],dyList[i]));
        item->moveBy(dxList[i],dyList[i]);
    }
    m_pIconEditorMgr->iconEditorFrame()->refreshSelected(oldBounding);
    m_pIconEditorMgr->iconEditorFrame()->refreshSelected(newBounding);
    m_pIconEditorMgr->iconEditorFrame()->view()->ensureVisible(newBounding);
}

void HMoveIconCommand::undo()
{
    if(!m_pIconEditorMgr || pObjList.isEmpty() || !m_pIconEditorMgr->iconEditorFrame())
        return;
    QRectF oldBounding;
    QRectF newBounding;
    for(int i = 0; i < pObjList.count();i++)
    {
        HBaseObj* obj = (HBaseObj*)pObjList[i];
        if(!obj) continue;
        H5GraphicsItem* item = obj->iconGraphicsItem();
        if(!item) continue;
        oldBounding = oldBounding.united(item->boundingRect());
        newBounding = newBounding.united(item->boundingRect().translated(dxList[i],dyList[i]));
        item->moveBy(-dxList[i],-dyList[i]);
    }
    m_pIconEditorMgr->iconEditorFrame()->refreshSelected(oldBounding);
    m_pIconEditorMgr->iconEditorFrame()->refreshSelected(newBounding);
    m_pIconEditorMgr->iconEditorFrame()->view()->ensureVisible(newBounding);
}


////////////////////////////////////////旋转///////////////////////////////////////////
HRotateIconCommand::HRotateIconCommand(HIconEditorMgr* iconMgr,QList<HBaseObj*> pObjs,int angle)
    :HIconCommand(iconMgr),pObjList(pObjs)
{
    for(int i = 0; i < pObjList.count();i++)
    {
        angleList.append(angle);
    }
    setText("rotate object");
}

HRotateIconCommand::HRotateIconCommand(HIconEditorMgr* iconMgr,QList<HBaseObj*> pObjs,QList<int> angles)
    :HIconCommand(iconMgr),pObjList(pObjs),angleList(angles)
{
    setText("rotate object");
}

HRotateIconCommand::~HRotateIconCommand()
{

}

int HRotateIconCommand::id() const
{
    return Rotate;
}

void HRotateIconCommand::redo()
{
    if(bFirstTime)
    {
        bFirstTime = false;
        return;
    }
    if(!m_pIconEditorMgr || pObjList.isEmpty() || !m_pIconEditorMgr->iconEditorFrame())
        return;
    QRectF oldBounding;
    QRectF newBounding;
    for(int i = 0; i < pObjList.count();i++)
    {
        HBaseObj* obj = (HBaseObj*)pObjList[i];
        if(!obj) continue;
        H5GraphicsItem* item = obj->iconGraphicsItem();
        if(!item) continue;
        oldBounding = oldBounding.united(item->boundingRect());
        item->setRotation(obj->rotateAngle() - angleList[i]);
        newBounding = newBounding.united(item->boundingRect());
    }
    m_pIconEditorMgr->iconEditorFrame()->refreshSelected(oldBounding);
    m_pIconEditorMgr->iconEditorFrame()->refreshSelected(newBounding);
    m_pIconEditorMgr->iconEditorFrame()->view()->ensureVisible(newBounding);
}

void HRotateIconCommand::undo()
{
    if(!m_pIconEditorMgr || pObjList.isEmpty() || !m_pIconEditorMgr->iconEditorFrame())
        return;
    QRectF oldBounding;
    QRectF newBounding;
    for(int i = 0; i < pObjList.count();i++)
    {
        HBaseObj* obj = (HBaseObj*)pObjList[i];
        if(!obj) continue;
        H5GraphicsItem* item = obj->iconGraphicsItem();
        if(!item) continue;
        oldBounding = oldBounding.united(item->boundingRect());
        item->setRotation(obj->rotateAngle() + angleList[i]);
        newBounding = newBounding.united(item->boundingRect());
    }
    m_pIconEditorMgr->iconEditorFrame()->refreshSelected(oldBounding);
    m_pIconEditorMgr->iconEditorFrame()->refreshSelected(newBounding);
    m_pIconEditorMgr->iconEditorFrame()->view()->ensureVisible(newBounding);
}


////////////////////////////////////////翻转///////////////////////////////////////////
HTurnIconCommand::HTurnIconCommand(HIconEditorMgr* iconMgr,QList<HBaseObj*> objs,bool direction )
    :HIconCommand(iconMgr),pObjList(objs),bDirection(direction)
{
    setText("turn object");
}

HTurnIconCommand::~HTurnIconCommand()
{

}

int HTurnIconCommand::id() const
{
    return Turn;
}

void HTurnIconCommand::redo()
{

}

void HTurnIconCommand::undo()
{

}


////////////////////////////////////////改变大小///////////////////////////////////////////
HResizeIconCommand::HResizeIconCommand(HIconEditorMgr* iconMgr,QList<HBaseObj*> objs,QList<QPolygonF> oldPts,QList<QPolygonF> newPts)
    :HIconCommand(iconMgr),pObjList(objs),oldPtList(oldPts),newPtList(newPts)
{
    setText("resize object");
}

HResizeIconCommand::~HResizeIconCommand()
{

}

int HResizeIconCommand::id() const
{
    return Resize;
}

void HResizeIconCommand::redo()
{
    if(bFirstTime)
    {
        bFirstTime = false;
        return;
    }
    if(!m_pIconEditorMgr || pObjList.isEmpty() || !m_pIconEditorMgr->iconEditorFrame())
        return;
    QRectF oldBounding;
    QRectF newBounding;
    for(int i = 0; i < pObjList.count();i++)
    {
        HBaseObj* obj = (HBaseObj*)pObjList[i];
        if(!obj) continue;
        H5GraphicsItem* item = obj->iconGraphicsItem();
        if(!item) continue;
        oldBounding = oldBounding.united(item->boundingRect());
        //item->resi(newPtList[i]);
        newBounding = newBounding.united(item->boundingRect());
    }
    m_pIconEditorMgr->iconEditorFrame()->refreshSelected(oldBounding);
    m_pIconEditorMgr->iconEditorFrame()->refreshSelected(newBounding);
    m_pIconEditorMgr->iconEditorFrame()->view()->ensureVisible(newBounding);
}

void HResizeIconCommand::undo()
{
    if(!m_pIconEditorMgr || pObjList.isEmpty() || !m_pIconEditorMgr->iconEditorFrame())
        return;
    QRectF oldBounding;
    QRectF newBounding;
    for(int i = 0; i < pObjList.count();i++)
    {
        HBaseObj* obj = (HBaseObj*)pObjList[i];
        if(!obj) continue;
        H5GraphicsItem* item = obj->iconGraphicsItem();
        if(!item) continue;
        oldBounding = oldBounding.united(item->boundingRect());
        //item->resizeItem(oldPtList[i]);
        newBounding = newBounding.united(item->boundingRect());
    }
    m_pIconEditorMgr->iconEditorFrame()->refreshSelected(oldBounding);
    m_pIconEditorMgr->iconEditorFrame()->refreshSelected(newBounding);
    m_pIconEditorMgr->iconEditorFrame()->view()->ensureVisible(newBounding);
}
