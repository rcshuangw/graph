#include "harctool.h"
#include "hmakeicon.h"
#include "harc.h"
HArcTool::HArcTool(HDrawManager* manager,DrawShape objShape,const QString& name,const QString& uuid)
        :HDrawTool(manager, objShape, name, uuid),m_nArcState(Rect)
{

    m_nStartAngle = 0;
    m_nSweepLength = 0;
}

HArcTool::~HArcTool()
{

}

void HArcTool::clear()
{

}

void HArcTool::onEvent(HEvent& e)
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

void HArcTool::onMousePressEvent(QMouseEvent* event,QVariant &data)
{
    if(!m_pToolManager)
        return;
    if(event->button() != Qt::LeftButton)
        return;
    QPointF pt = data.toPointF();
    if(m_nArcState == Rect)
        m_ptStPoint = m_ptCurPoint = pt;
}

void HArcTool::onMouseMoveEvent(QMouseEvent* event,QVariant &data)
{
    if(!m_pToolManager)
        return;
    if(!(event->buttons()&Qt::LeftButton))
        return;
    QPointF pt = data.toPointF();
    m_ptCurPoint = pt;
    QRectF bounding;
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

    //设置属性
    QPainterPath painterPath;
    painterPath.moveTo(bounding.center());
    painterPath.arcTo(bounding,30,120);
    painterPath.closeSubpath();
    Path path;
    path.coordType = false;
    path.pen = m_pToolManager->m_vDrawAttribute.drawPen;
    path.pen.setStyle(Qt::DashLine);
    path.painterPath = painterPath;

    //由绘制管理发送给editor
    QList<Path> pathList;
    pathList.append(path);
    m_pToolManager->onDrawPath(pathList);
}

void HArcTool::onMouseReleaseEvent(QMouseEvent* event,QVariant &data)
{
    QPointF pt = data.toPointF();
    m_ptCurPoint = pt;
    if(event->button() != Qt::LeftButton)
        return;

    if(qFuzzyCompare(m_ptCurPoint.x(),m_ptStPoint.x()) && qFuzzyCompare(m_ptCurPoint.y(),m_ptStPoint.y()))
        return;

    HArc* pObj = NULL;
    pObj = (HArc*)HMakeIcon::Instance()->newObj(m_edrawShape);
    if(pObj)
    {
        QPolygonF points;
        QRectF bounding;
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
        pObj->setStartAngle(30);
        pObj->setSweepLength(120);
        m_pToolManager->appendObj(pObj);
    }
    m_pToolManager->endDraw();
}
