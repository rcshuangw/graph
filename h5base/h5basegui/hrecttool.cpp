#include "hrecttool.h"
#include "hiconhelper.h"
#include "hellipse.h"
#include "hcircle.h"
#include "hrectangle.h"
#include "htext.h"
HRectTool::HRectTool(HDrawManager* manager,DrawShape objShape,const QString& name,const QString& uuid)
    :HDrawTool(manager, objShape, name, uuid)
{

}

HRectTool::~HRectTool()
{

}

void HRectTool::clear()
{
	m_ptStPoint = m_ptCurPoint = QPointF();
}

void HRectTool::onEvent(HEvent& e)
{
    HDrawTool::onEvent(e);
    if(e.event()->type() == QMouseEvent::MouseButtonPress)
    {
        onMousePressEvent((QMouseEvent*)e.event(),e.m_data);
    }
    else if(e.event()->type() == QMouseEvent::MouseMove)
    {
        onMouseMoveEvent((QMouseEvent*)e.event(), e.m_data);
    }
    else if(e.event()->type() == QMouseEvent::MouseButtonRelease)
    {
        onMouseReleaseEvent((QMouseEvent*)e.event(), e.m_data);
    }
}

void HRectTool::onMousePressEvent(QMouseEvent* event,QVariant &data)
{
    if(!m_pToolManager)
        return;
    if(event->button() != Qt::LeftButton)
        return;
    QPointF pt = data.toPointF();
    m_ptStPoint = m_ptCurPoint = pt;
}

void HRectTool::onMouseMoveEvent(QMouseEvent* event,QVariant &data)
{
    if(!m_pToolManager)
        return;
    if(!(event->buttons()&Qt::LeftButton))
        return;
    QPointF pt = data.toPointF();
    m_ptCurPoint = pt;
    QRectF bounding;
    if(m_edrawShape == Circle)
    {
        double r = distance(m_ptStPoint,m_ptCurPoint);
        bounding.setSize(QSizeF(r*2,r*2));
        bounding.moveCenter(m_ptStPoint);
    }
    else
    {
        bounding = QRectF(m_ptCurPoint,m_ptStPoint).normalized();
        QPointF topLeft = bounding.topLeft();
        if(event->modifiers()&Qt::ControlModifier)
        {
            //正方形
            double dx = qAbs(m_ptCurPoint.x() - m_ptStPoint.x());
            double dy = qAbs(m_ptCurPoint.y() - m_ptStPoint.x());
            bounding.setWidth(qMin(dx,dy));
            bounding.setHeight(qMin(dx,dy));
            bounding.setTopLeft(topLeft);
        }

    }
    QPainterPath painterPath;
    if(m_edrawShape == Circle || m_edrawShape == Ellipse)
    {
        painterPath.addEllipse(bounding);
    }
    else
    {
        painterPath.addRect(bounding);
    }

    //设置属性
    Path path;
    path.coordType = false;
    path.pen.setStyle(Qt::DashLine);
    path.painterPath = painterPath;
    if(m_edrawShape == Text)
    {
        path.pen.setWidth(0);
    }
    //由绘制管理发送给editor
    QList<Path> pathList;
    pathList.append(path);
	m_pToolManager->onDrawPath(pathList);
}

void HRectTool::onMouseReleaseEvent(QMouseEvent* event,QVariant &data)
{
    QPointF pt = data.toPointF();
    m_ptCurPoint = pt;
    if(event->button() != Qt::LeftButton)
        return;

    if(qFuzzyCompare(m_ptCurPoint.x(),m_ptStPoint.x()) && qFuzzyCompare(m_ptCurPoint.y(),m_ptStPoint.y()))
        return;

    HBaseObj* pObj = NULL;
    pObj = HIconHelper::Instance()->newObj(m_edrawShape);
    if(pObj)
    {
        QPolygonF points;
        QRectF bounding;
        if(m_edrawShape == Circle)
        {
            double r = distance(m_ptStPoint,m_ptCurPoint);
            bounding.setSize(QSizeF(r*2,r*2));
            bounding.moveCenter(m_ptStPoint);
        }
        else
        {
            bounding = QRectF(m_ptCurPoint,m_ptStPoint).normalized();
            QPointF topLeft = bounding.topLeft();
            if(event->modifiers()&Qt::ControlModifier)
            {
                //正方形
                double dx = qAbs(m_ptCurPoint.x() - m_ptStPoint.x());
                double dy = qAbs(m_ptCurPoint.y() - m_ptStPoint.x());
                bounding.setWidth(qMin(dx,dy));
                bounding.setHeight(qMin(dx,dy));
                bounding.setTopLeft(topLeft);
            }
        }
        //obj设置points
        //设置obj属性
        bounding = bounding.normalized();
        QPointF center = bounding.center();
        if(bounding.width() < 5)
            bounding.setWidth(5);
        if(bounding.height() < 5)
            bounding.setHeight(5);
        bounding.moveCenter(center);
        points.append(bounding.topLeft());
        points.append(bounding.bottomRight());
        pObj->setPointList(points);
        m_pToolManager->appendObj(pObj);
    }
	m_pToolManager->endDraw();
}
