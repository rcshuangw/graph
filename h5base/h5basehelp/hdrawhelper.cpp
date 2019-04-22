#include "hdrawhelper.h"
HDrawHelper::HDrawHelper()
{
    m_pBaseObj = NULL;
}

HDrawHelper::~HDrawHelper()
{

}

void HDrawHelper::setBaseObj(HBaseObj* pObj)
{
    m_pBaseObj = pObj;
}

HPointsList HDrawHelper::selectedPointList()
{
    HPointsList list;
    if(!m_pBaseObj)
        return list;
    list = selectedPointList(m_pBaseObj->getShapeType());
    return list;
}

void HDrawHelper::updatePoints()
{

}

void HDrawHelper::ratate(int angle,QPointF* c)
{

}

void HDrawHelper::turn(bool b,QPointF* c)
{

}

QCursor HDrawHelper::cursor(int index)
{

}

QCursor HDrawHelper::cursorOnPoint(DrawShape drawShape)
{
    switch(drawshape)
    {
    case Rectangle:
    case Ellipse:
    case Circle:
    case Text:
    case Icon:
    case TempContainer:
    case Group:
        break;
    }
}

HPointsList HDrawHelper::selectedPointList(DrawShape drawshape)
{
    HPointsList list;
    switch(drawshape)
    {
    case Line:
    {
        list = m_pBaseObj->getPointList(1);
        break;
    }
    case Polyline:
        break;
    case Polygon:
        break;
    case Rectangle:
    case Ellipse:
    case Circle:
    case Text:
    {
        //获取四角点
        HPointsList points = m_pBaseObj->getPointList(1);
        //再获取每个点的中间点
        list = getMidPoints(points);
    }
        break;
    case Icon:
    {
        //获取四角点
        HPointsList points = m_pBaseObj->getPointList(1);
        //再获取每个点的中间点
        list = getMidPoints(points);
    }
        break;
    case TempContainer:
    case Group:
    {
        //获取四角点
        HPointsList points = m_pBaseObj->getPointList(1);
        //再获取每个点的中间点
        list = getMidPoints(points);
    }
        break;

    default:
        break;
    }
    return list;
}

HPointsList HDrawHelper::getMidPoints(HPointsList points,bool bclose)
{
    HPointsList rPoints;
    if(points.count() < 2) return rPoints;
    for(int i = 0; i < points.count();i++)
    {
        if(i == 0) rPoints.append(points[i]);
        else
        {
            QPointF pt((points.at(i-1).x()+points.at(i).x()),(points.at(i-1).y()+points.at(i).y()));
            rPoints.append(pt);
            rPoints.append(points.at(i));
        }
    }
    if(bclose)
    {
        QPointF pt((points.first().x()+points.last().x()),(points.first().y()+points.last().y()));
        rPoints.append(pt);
    }
    return rPoints;

}
