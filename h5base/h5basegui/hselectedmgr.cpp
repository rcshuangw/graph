#include "hselectedmgr.h"
#include "htempcontainer.h"
#include "hdrawhelper.h"
HSelectedMgr::HSelectedMgr()
{
	m_pTempContainer = new HTempContainer;
    //m_pDrawHelper = new HDrawHelper;
}

HSelectedMgr::~HSelectedMgr()
{
	if (m_pTempContainer)
	{
		delete m_pTempContainer;
		m_pTempContainer = NULL;
	}
}

#include <QDebug>
void HSelectedMgr::paint(QPainter* painter, const QRectF& rect, const QRectF &selectRect)
{
    if(m_pTempContainer->getObjList().size() <=0)
        return;

    if(m_pTempContainer->getObjList().size() > 1)
    {
        painter->save();
        QPen pen;
        pen.setCosmetic(true);
        pen.setColor(Qt::green);
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
        painter->drawPolygon(m_selectedPoints.toPolygon());
        qDebug()<<"count："<<m_selectedPoints.count();
        painter->restore();
        if(m_pTempContainer->getObjList().size() > 0)
        {
            painter->save();
            pen.setColor(Qt::magenta);
            pen.setStyle(Qt::SolidLine);
            painter->setPen(pen);
            for(int i=0; i<m_pTempContainer->getObjList().size(); i++){
                HBaseObj* obj = m_pTempContainer->getObjList().at(i);
                if(!obj||obj->isDeleted()||!obj->isVisible()){
                    continue;
                }
                if(i==0){
                    pen.setWidth(3);
                    painter->setPen(pen);
                }
                HPointFList points = obj->getPointList(1);
                if(obj->getShapeType()==Arc)
                {
                    //QRectF bounding = obj->boundingRect(1);
                    //painter->drawRect(bounding);
                }
                else
                {
                    painter->drawPolygon(points);
                }
                if(i==0){
                    pen.setWidth(1);
                    painter->setPen(pen);
                }
            }
            painter->restore();
        }
    }
    painter->save();
    painter->setPen(Qt::green);
    if(1)
    {
        QRectF rect1 = selectRect.isNull()?QRectF(QPoint(),QSize(6,6)):selectRect;
        for(int i = 0; i < m_selectedPoints.count();i++)
        {
            rect1.moveCenter(m_selectedPoints.at(i));
            painter->drawRect(rect1);
        }
    }
    else
    {
        QPen pen = painter->pen();
        pen.setStyle(Qt::DotLine);
        painter->setPen(pen);
        painter->drawPolygon(m_selectedPoints.toPolygon());
    }
    painter->restore();
}

void HSelectedMgr::addObj(HBaseObj* obj)
{
	m_pTempContainer->addObj(obj);
    HDrawHelper* pDrawHelper = HDrawHelper::Instance();
    if(pDrawHelper)
    {
        if(m_pTempContainer->getObjList().count() == 0)
        {
            pDrawHelper->setBaseObj(NULL);
        }
       else if(m_pTempContainer->getObjList().count() == 1)
        {
            pDrawHelper->setBaseObj(m_pTempContainer->getObjList().at(0));
        }
        else
        {
            pDrawHelper->setBaseObj(m_pTempContainer);
        }
    }
}

void HSelectedMgr::removeObj(HBaseObj* obj)
{
	m_pTempContainer->removeObj(obj);
    HDrawHelper* pDrawHelper = HDrawHelper::Instance();
    if(pDrawHelper)
    {
        if(m_pTempContainer->getObjList().count() == 0)
        {
            pDrawHelper->setBaseObj(NULL);
        }
       else if(m_pTempContainer->getObjList().count() == 1)
        {
            pDrawHelper->setBaseObj(m_pTempContainer->getObjList().at(0));
        }
        else
        {
            pDrawHelper->setBaseObj(m_pTempContainer);
        }
    }
}

void HSelectedMgr::setSelectObj(QList<HBaseObj*> objs)
{
	m_pTempContainer->addObjList(objs);
    HDrawHelper* pDrawHelper = HDrawHelper::Instance();
    if(pDrawHelper)
    {
        if(m_pTempContainer->getObjList().count() == 0)
        {
            pDrawHelper->setBaseObj(NULL);
        }
       else if(m_pTempContainer->getObjList().count() == 1)
        {
            pDrawHelper->setBaseObj(m_pTempContainer->getObjList().at(0));
        }
        else
        {
            pDrawHelper->setBaseObj(m_pTempContainer);
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
        rectF.setSize(QSizeF(6,6));
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
    for(int i = 0; i < m_pTempContainer->getObjList().count();i++)
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
    HDrawHelper* pDrawHelper = HDrawHelper::Instance();
    if(pDrawHelper)
        m_selectedPoints = pDrawHelper->selectedPointList();
    if(m_selectedPoints.count() <=0)
        m_SelectBounding = QRectF();
    else
        m_SelectBounding = m_selectedPoints.boundingRect().adjusted(-10,-10,10,10);
}

void HSelectedMgr::refreshObjs()
{
    m_pTempContainer->RePos();
}
