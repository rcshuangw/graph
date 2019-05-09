#include "hdrawhelper.h"
#include "htempcontainer.h"
#include "hiconobj.h"
#include <QCursor>
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

HPointFList HDrawHelper::selectedPointList()
{
    HPointFList list;
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
    if(!m_pBaseObj)
        return;
    if(m_pBaseObj->getShapeType() == TempContainer)
    {
        HTempContainer *tempCon = (HTempContainer*)m_pBaseObj;
        QPointF cp;
        if(c)
        {
            cp = *c;
        }
        else
        {
            cp = tempCon->pos();
        }
        //坐标旋转
        QTransform transform;
        transform.translate(cp.x(),cp.y());
        transform.rotate(angle);
        transform.translate(-cp.x(),-cp.y());
        //容器内每个对象都旋转
        for(int i = 0; i < tempCon->getObjList().size();i++)
        {
            HBaseObj* pObj = (HBaseObj*)tempCon->getObjList().at(i);
            if(!pObj) continue;
            pObj->rotateBy(angle);
            QPointF pt = pObj->pos();
            QPointF newPt = transform.map(pt);
            pObj->move(newPt.x(),newPt.y());
            ((H5GraphicsItem*)pObj->iconGraphicsItem())->setPos(pObj->pos());

         }
        tempCon->rotateBy(angle);
    }
    else
    {
      m_pBaseObj->rotateBy(angle);
    }
}

void HDrawHelper::turn(bool b,QPointF* c)
{
    if(!m_pBaseObj)
        return;
    if(m_pBaseObj->getShapeType() == TempContainer || m_pBaseObj->getShapeType() == Icon)
    {
        HTempContainer *tempCon = (HTempContainer*)m_pBaseObj;
        QPointF cp;
        if(c)
        {
            cp = *c;
        }
        else
        {
            cp = tempCon->pos();
        }
        //坐标旋转
        QTransform transform;
        transform.translate(cp.x(),cp.y());
        if(b)
        {
            transform.scale(-1,1);
        }
        else
        {
            transform.scale(1,-1);
        }
        transform.translate(-cp.x(),-cp.y());
        //容器内每个对象都旋转
        for(int i = 0; i < tempCon->getObjList().size();i++)
        {
            HBaseObj* pObj = (HBaseObj*)tempCon->getObjList().at(i);
            if(!pObj) continue;
            //有些对象不能旋转
            bool isNoTurn = false;
            if(pObj->getShapeType() == Text)
                isNoTurn = true;
            if(!isNoTurn)
            {
                if(b)
                {
                    pObj->turn(!pObj->isHorizonTurn(),pObj->isVerticalTurn());
                }
                else
                {
                    pObj->turn(pObj->isHorizonTurn(),!pObj->isVerticalTurn());
                }
                QPointF pt = pObj->pos();
                QPointF newPt = transform.map(pt);
                pObj->move(newPt.x(),newPt.y());
                ((H5GraphicsItem*)pObj->iconGraphicsItem())->setPos(pObj->pos());
            }
         }
        tempCon->turn(b,!b);//自己的外部区域
    }
    else
    {
        if(b)
        {
            m_pBaseObj->turn(!m_pBaseObj->isHorizonTurn(),m_pBaseObj->isVerticalTurn());
        }
        else
        {
            m_pBaseObj->turn(m_pBaseObj->isHorizonTurn(),!m_pBaseObj->isVerticalTurn());
        }
    }
}

//获取某个点位置的鼠标状态
QCursor HDrawHelper::cursor(int index)
{
    return cursorOnPoint(m_pBaseObj->getShapeType(),index);
}

QCursor HDrawHelper::cursorOnPoint(DrawShape drawShape,int index)
{
    switch(drawShape)
    {
    case Line:
    case Polygon:
    case Polyline:
        return QCursor(Qt::SizeFDiagCursor);
    case Rectangle:
    case Ellipse:
    case Circle:
    case Text:
    case Icon:
    case TempContainer:
    case Group:
    {
        switch(index)
        {
        case 0:
        case 4:
            return QCursor(Qt::SizeFDiagCursor);
        case 1:
        case 5:
            return QCursor(Qt::SizeVerCursor);
        case 2:
        case 6:
            return QCursor(Qt::SizeBDiagCursor);
        case 3:
        case 7:
            return QCursor(Qt::SizeHorCursor);
        default:
            return QCursor();
        }
    }
    default:
        return QCursor();
    }
}

HPointFList HDrawHelper::selectedPointList(DrawShape drawshape)
{
    HPointFList list;
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
        HPointFList points = m_pBaseObj->getPointList(1);
        //再获取每个点的中间点
        list = getMidPoints(points);
    }
        break;
    case Icon:
    {
        //获取四角点
        HPointFList points = m_pBaseObj->getPointList(1);
        //再获取每个点的中间点
        list = getMidPoints(points);
    }
        break;
    case TempContainer:
    case Group:
    {
        //获取四角点
        HPointFList points = m_pBaseObj->getPointList(1);
        //再获取每个点的中间点
        list = getMidPoints(points);
    }
        break;

    default:
        break;
    }
    return list;
}

HPointFList HDrawHelper::getMidPoints(HPointFList points,bool bclose)
{
    HPointFList rPoints;
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

void HDrawHelper::movePoint(int index,QPointF& curPoint)
{
    if(!m_pBaseObj)
        return;
    movePoint(m_pBaseObj->getShapeType(),index,curPoint);
}

void HDrawHelper::movePoint(DrawShape drawShape,int index,QPointF& curPoint)
{
    switch(drawShape)
    {
    case Line:
        break;
    case Rectangle:
    case Text:
    case Ellipse:
    case Icon:
    {
        /*
         *   0   1  2
         *   7      3
         *   6   5  4
*/
        QTransform trans;
        m_pBaseObj->transform(trans,1);
        QPointF point = trans.inverted().map(curPoint);
        HPointFList ptList = m_pBaseObj->getPointList(1);
        HPointFList points = trans.inverted().map(ptList);
        QPointF topLeft = points.at(0);
        QPointF bottomRight = points.at(2);
        switch(index)
        {
        case 0:
            topLeft = point;
            break;
        case 1:
            topLeft.setY(point.y());
            break;
        case 2:
            topLeft.setY(point.y());
            bottomRight.setX(point.x());
            break;
        case 3:
            bottomRight.setX(point.x());
            break;
        case 4:
            bottomRight = point;
            break;
        case 5:
            bottomRight.setY(point.y());
            break;
        case 6:
            topLeft.setX(point.x());
            bottomRight.setY(point.y());
            break;
        case 7:
            topLeft.setX(point.x());
            break;
        default:
            break;
        }
        points.clear();
        points.append(topLeft);
        points.append(bottomRight);

        if(m_pBaseObj->getShapeType() == Icon)
        {
            HIconObj* pObj = (HIconObj*)m_pBaseObj;
            QRectF rectF = points.boundingRect();
            pObj->iconSymbol()->resize(rectF.width(),rectF.height());
        }
        points = trans.map(points);
        //--huangw--
        m_pBaseObj->setPointList(points,1);
        H5GraphicsItem* item = m_pBaseObj->iconGraphicsItem();
        if(item)
            item->setPos(m_pBaseObj->pos());
    }
        break;
    case Circle:
        break;
    case Group:
        break;
    case TempContainer:
        break;
    default:
        break;
    }
}















