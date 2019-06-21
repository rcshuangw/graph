#include "honlinescene.h"
#include "hwfsystemmgr.h"
#include "honlinedoc.h"
#include "hicongraphicsitem.h"
#include "hiconlineitem.h"
#include "hiconrectangleitem.h"
#include "hiconellipseitem.h"
#include "hiconcircleitem.h"
#include "hiconpolygonitem.h"
#include "hiconpolylineitem.h"
#include "hiconarcitem.h"
#include "hiconpieitem.h"
#include "hicontextitem.h"
#include "hiconitemgroup.h"
#include "hiconshowpattern.h"
#include "hiconselectionitem.h"
#include "hiconcomplexitem.h"
#include "hiconapi.h"
#include "hiconsymbol.h"
#include "hgraph.h"
#include "hgraphframe.h"
#include <QMimeData>
HGraphicsScene::HGraphicsScene(HGraphFrame* parent)
    :m_pOnlineWindow(parent)
{
    //setAcceptDraps(true);
    complex = 0;
    rectangle = 0;
    line = 0;
    ellipse = 0;
    circle = 0;
    polygon = 0;
    polyline = 0;
    arc = 0;
    pie = 0;
    text = 0;
    select = 0;
    group = 0;
    m_pGraph = NULL;
}

void HGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    //if(NULL == m_pWfSystemMgr)
   //     return;
    painter->save();
    painter->setBrush(backgroundBrush());
    QGraphicsScene::drawBackground(painter,rect);

    HGraph* pGraph = m_pGraph;
    QColor clr;
    if(pGraph)
    {
        clr = QColor(pGraph->getFillColor());
    }
    else
    {
        clr = QColor(Qt::darkGray);
    }
    QRectF rectF = m_pOnlineWindow->getLogicRect();
    painter->fillRect(rectF,clr);
    painter->restore();
}


void HGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
   // if(!pOnlineMgr->onlineDoc() || !pOnlineMgr->onlineDoc()->getCurGraph())
   //     return;
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void HGraphicsScene::setItemProperty(QGraphicsItem* item)
{
    if(!item) return;
    HIconGraphicsItem* pItem = qgraphicsitem_cast<HIconGraphicsItem*>(item);
    HBaseObj* pObj = pItem->getItemObj();
    DRAWSHAPE drawShape = pObj->getShapeType();
    if(drawShape == enumComplex)
    {

    }
    else
    {

    }
}


void HGraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{

}

void HGraphicsScene::setGraph(HGraph *graph)
{
    m_pGraph = graph;
}

/*
 * 函数说明:加载图元到OnlineScene上面
 * 参数:pObj--图元 bdel：是否删除
*/
void HGraphicsScene::addGraphicsIconItem(HBaseObj* pObj,bool bdel)
{
    /*
    DRAWSHAPE drawShape = pObj->getShapeType();
    int nZValue = pObj->getStackOrder();
    //所有items不能具有seleced或者move的功能
    if(drawShape == enumLine)
    {
        line = new HIconLineItem(QLineF(((HLine*) pObj)->getHeadPoint(),((HLine*)pObj)->getTailPoint()));
        line->setItemObj(pObj);
        line->setZValue(nZValue);
        line->setFlag(QGraphicsItem::ItemIsMovable,false);
        line->setFlag(QGraphicsItem::ItemIsSelectable,false);
        addItem(line);

    }
    else if(drawShape == enumRectangle)
    {
        HRectangle* pObj1 = (HRectangle*)pObj;
        rectangle = new HIconRectItem(pObj1->getObjRect());
        rectangle->setItemObj(pObj);
        rectangle->setZValue(nZValue);
        rectangle->setFlag(QGraphicsItem::ItemIsMovable,false);
        rectangle->setFlag(QGraphicsItem::ItemIsSelectable,false);
        addItem(rectangle);
    }
    else if(drawShape == enumEllipse)
    {
        HEllipse* pObj1 = (HEllipse*)pObj;
        ellipse = new HIconEllipseItem(pObj1->getObjRect());
        ellipse->setItemObj(pObj);
        ellipse->setZValue(nZValue);
        ellipse->setFlag(QGraphicsItem::ItemIsMovable,false);
        ellipse->setFlag(QGraphicsItem::ItemIsSelectable,false);
        addItem(ellipse);
    }
    else if(drawShape == enumCircle)
    {
        HCircle* pObj1 = (HCircle*)pObj;
        circle = new HIconCircleItem(pObj1->getObjRect());
        circle->setItemObj(pObj);
        circle->setZValue(nZValue);
        circle->setFlag(QGraphicsItem::ItemIsMovable,false);
        circle->setFlag(QGraphicsItem::ItemIsSelectable,false);
        addItem(circle);
    }
    else if(drawShape == enumPolygon)
    {
        HPolygon* pObj1 = (HPolygon*)pObj;
        polygon = new HIconPolygonItem(pObj1->pylist);
        polygon->setItemObj(pObj);
        polygon->setZValue(nZValue);
        polygon->setFlag(QGraphicsItem::ItemIsMovable,false);
        polygon->setFlag(QGraphicsItem::ItemIsSelectable,false);
        addItem(polygon);
    }
    else if(drawShape == enumPolyline)
    {
        HPolyline* pObj1 = (HPolyline*)pObj;
        polyline = new HIconPolylineItem(pObj1->pylist);
        polyline->setItemObj(pObj);
        polyline->setZValue(nZValue);
        polyline->setFlag(QGraphicsItem::ItemIsMovable,false);
        polyline->setFlag(QGraphicsItem::ItemIsSelectable,false);
        addItem(polyline);
    }
    else if(drawShape == enumArc)
    {
        HArc* pObj1 = (HArc*)pObj;
        arc = new HIconArcItem(pObj1->getObjRect());
        arc->setItemObj(pObj);
        arc->setZValue(nZValue);
        arc->setFlag(QGraphicsItem::ItemIsMovable,false);
        arc->setFlag(QGraphicsItem::ItemIsSelectable,false);
        addItem(arc);
    }
    else if(drawShape == enumPie)
    {
        HPie* pObj1 = (HPie*)pObj;
        pie = new HIconPieItem(pObj1->getObjRect());
        pie->setItemObj(pObj);
        pie->setZValue(nZValue);
        pie->setFlag(QGraphicsItem::ItemIsMovable,false);
        pie->setFlag(QGraphicsItem::ItemIsSelectable,false);
        addItem(pie);
    }
    else if(drawShape == enumText)
    {
        HText* pObj1 = (HText*)pObj;
        text = new HIconTextItem(pObj1->getObjRect());
        text->setItemObj(pObj);
        text->setZValue(nZValue);
        text->setFlag(QGraphicsItem::ItemIsMovable,false);
        text->setFlag(QGraphicsItem::ItemIsSelectable,false);
        addItem(text);
    }
    else if(drawShape == enumComplex)
    {
        HIconObj* pObj1 = (HIconObj*)pObj;
        complex = new HIconComplexItem(pObj1->getObjRect().normalized());
        complex->setItemObj(pObj);
        complex->setZValue(nZValue);
        complex->setFlag(QGraphicsItem::ItemIsMovable,false);
        complex->setFlag(QGraphicsItem::ItemIsSelectable,false);
        addItem(complex);
        m_pOnlineWindow->m_pIconObjList.append(pObj1);//要析构--huangw
    }
    if(bdel)
    {
        if(drawShape == enumLine && line != 0)
        {
            line = 0;
        }
        else if(drawShape == enumRectangle && rectangle != 0)
        {
            rectangle = 0;
        }
        else if(drawShape == enumEllipse && ellipse != 0)
        {
            ellipse = 0;
        }
        else if(drawShape == enumCircle && circle != 0)
        {
            circle = 0;
        }
        else if(drawShape == enumPolyline && polyline != 0)
        {
            polyline = 0;
        }
        else if(drawShape == enumPolygon && polygon !=0)
        {
            polygon = 0;
        }
        else if(drawShape == enumArc && arc !=0)
        {
            arc = 0;
        }
        else if(drawShape == enumPie && pie !=0)
        {
            pie = 0;
        }
        else if(drawShape == enumText && text != 0)
        {
            text = 0;
        }
        else if(drawShape == enumComplex && complex != 0)
        {
            complex = 0;
        }
    }*/
}

void HGraphicsScene::openGraphicsSceneItems()
{
    HGraph* pGraph = m_pGraph;
    if(!pGraph)
        return;
    QList<HBaseObj*> pObjList = pGraph->getObjList();
    for(int i = 0; i < pObjList.count();i++)
    {
        HBaseObj* pObj = (HBaseObj*)pObjList[i];
        if(!pObj)
            continue;
        addGraphicsIconItem(pObj,true);
    }
}

/*********************************
 * 功能:清除scene上的所有item
**********************************/
void HGraphicsScene::delGraphicsSceneItems()
{
    foreach (QGraphicsItem *item, items())
    {
        HIconGraphicsItem* pItem = qgraphicsitem_cast<HIconGraphicsItem*>(item);
        if(!pItem) continue;
        removeItem(pItem);
        delete pItem;
     }
}

void HGraphicsScene::setItemCursor(QGraphicsSceneMouseEvent *mouseEvent)
{
}
