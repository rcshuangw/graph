﻿#include "hselectedmgr.h"
#include "htempcontainer.h"
#include "hdrawhelper.h"
HSelectedMgr::HSelectedMgr()
{
	m_pTempContainer = new HTempContainer;
    m_pDrawHelper = new HDrawHelper;
}

HSelectedMgr::~HSelectedMgr()
{
	if (m_pTempContainer)
	{
		delete m_pTempContainer;
		m_pTempContainer = NULL;
	}

    if(m_pDrawHelper)
    {
        delete m_pDrawHelper;
        m_pDrawHelper = NULL;
    }
}


void HSelectedMgr::paint(QPainter* painter, const QRectF& rect, const QRectF &selectRect = QRectF())
{

}

void HSelectedMgr::addObj(HBaseObj* obj)
{
	m_pTempContainer->addObj(obj);
    if(m_pDrawHelper)
    {
        if(m_pTempContainer->getObjList().count() == 0)
        {
            m_pDrawHelper->setBaseObj(NULL);
        }
       else if(m_pTempContainer->getObjList().count() == 1)
        {
            m_pDrawHelper->setBaseObj(m_pTempContainer->getObjList().at(0));
        }
        else
        {
            m_pDrawHelper->setBaseObj(m_pTempContainer);
        }
    }
}

void HSelectedMgr::removeObj(HBaseObj* obj)
{
	m_pTempContainer->removeObj(obj);
    if(m_pDrawHelper)
    {
        if(m_pTempContainer->getObjList().count() == 0)
        {
            m_pDrawHelper->setBaseObj(NULL);
        }
       else if(m_pTempContainer->getObjList().count() == 1)
        {
            m_pDrawHelper->setBaseObj(m_pTempContainer->getObjList().at(0));
        }
        else
        {
            m_pDrawHelper->setBaseObj(m_pTempContainer);
        }
    }
}

void HSelectedMgr::setSelectObj(QList<HBaseObj*> objs)
{
	m_pTempContainer->addObjList(objs);
    if(m_pDrawHelper)
    {
        if(m_pTempContainer->getObjList().count() == 0)
        {
            m_pDrawHelper->setBaseObj(NULL);
        }
       else if(m_pTempContainer->getObjList().count() == 1)
        {
            m_pDrawHelper->setBaseObj(m_pTempContainer->getObjList().at(0));
        }
        else
        {
            m_pDrawHelper->setBaseObj(m_pTempContainer);
        }
    }
}

void HSelectedMgr::selectChanged(HBaseObj* obj, bool isSelect)
{
	if (isSelect)
	{
		addObj(obj);
	}
	else
	{
		removeObj(obj);
	}
}

void HSelectedMgr::clear()
{
    emit refreshSelect(m_SelectBounding);
    QVector<HBaseObj*> objLists;
    objLists = m_pTempContainer->getObjList();
    for (int i = 0; i < objLists.count(); i++)
    {
        HBaseObj* pObj = objLists.at(i);
        if (pObj && pObj->iconGraphicsItem())
            ((H5GraphicsItem*)pObj->iconGraphicsItem())->setSelected(false);
    }
    m_pTempContainer->clear();
    m_selectedPoints.clear();
}

bool HSelectedMgr::isSelected(HBaseObj* obj)
{
	return m_pTempContainer->contains(obj);
}

//是否点(point)到选中点上(selectPoint)
int HSelectedMgr::isOnPoint(const QPointF& point, QPointF& selectPoint)
{
    QRectF rectF;
    for(int i = 0; i < m_selectedPoints.count();i++)
    {
        QPointF pos = m_selectedPoints.at(i);
        rectF.setSize(QSizeF(3,3));
        rectF.moveCenter(pos);
        if(rectF.contains(point))
        {
            selectPoint = pos;
            return i;
        }
    }
    return -1;
}

bool HSelectedMgr::isOnObj(const QPointF& point)//在point点上是否选中obj
{
    for(int i = ; i < m_pTempContainer->getObjList().count();i++)
    {
        HBaseObj* pObj = m_pTempContainer->getObjList().at(i);
        if(pObj && pObj->contains(point))
            return true;
    }
    return false;
}

//图元周围的选择框
void HSelectedMgr::recalcSelect()
{
	QRectF rectF = m_SelectBounding;
	calcPoints();
	QVector<HBaseObj*> objLists;
	objLists = m_pTempContainer->getObjList();
	for (int i = 0; i < objLists.count(); i++)
	{
		HBaseObj* pObj = objLists.at(i);
		if (pObj && pObj->iconGraphicsItem())
			pObj->iconGraphicsItem()->update();
	}
	emit refreshSelect(m_SelectBounding.united(rectF));
}

void HSelectedMgr::calcPoints()
{
    m_selectedPoints.clear();
    if(m_pDrawHelper)
        m_selectedPoints = m_pDrawHelper->selectedPointList();
    if(m_selectedPoints.count() <=0)
        m_SelectBounding = QRectF();
    else
        m_SelectBounding = m_selectedPoints.boundingRect().adjusted(-10,-10,10,10);
}

void HSelectedMgr::refreshObjs()
{
    m_pTempContainer->RePos();
}
