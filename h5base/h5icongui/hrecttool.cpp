#include "hrecttool.h"
#include "hdrawmanager.h"
HRectTool::HRectTool(HDrawManager* manager,DrawShape objShape,const QString& name,const QString& uuid)
    :m_pDrawManager(manager),m_edrawShape(objShape),m_strObjName(name),m_strObjUuid(uuid)
{

}

HRectTool::~HRectTool()
{

}

void HRectTool::clear()
{

}

void HRectTool::onEvent(HEvent& e)
{
    HDrawTool::onEvent(e);
    if(e.event()->type() == QMouseEvent::MouseButtonPress)
    {
        onMousePress((QMouseEvent*)e.event(),e.data());
    }
    else if(e.event()->type() == QMouseEvent::MouseMove)
    {
        onMouseMove((QMouseEvent*)e.event(),e.data());
    }
    else if(e.event()->type() == QMouseEvent::MouseButtonRelease)
    {
        onMouseRelease((QMouseEvent*)e.event(),e.data());
    }
}

void HRectTool::onMousePress(QMouseEvent* event,QVariant &data)
{
    if(!m_pDrawManager)
        return;
    if(event->button() != Qt::LeftButton)
        return;
    QPointF pt = data.toPointF();
    m_ptStPoint = m_ptCurPoint = pt;
}

void HRectTool::onMouseMove(QMouseEvent* event,QVariant &data)
{
    if(!m_pDrawManager)
        return;
    if(!(event->button()&Qt::LeftButton))
        return;
    QPointF pt = data.toPointF();
    m_ptCurPoint = pt;
    QRectF bounding;
    if(m_edrawShape == Circle)
    {

    }
    else
    {
        bounding = QRectF(m_ptCurPoint,m_ptStPoint).normalized();
        QPointF topLeft = bounding.topLeft();
        if(event->modifiers()&Qt::ControlModifier)
        {
            //正方形
            qreal dx = qAbs(m_ptCurPoint.x() - m_ptStPoint.x());
            qreal dy = qAbs(m_ptCurPoint.y() - m_ptStPoint.x());
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
    path.painterPath = painterPath;
    //由绘制管理发送给editor
    QList<Path> pathList;
    pathList.append(Path);
    m_pDrawManager->onDrawPath(pathList);
}

void HRectTool::onMouseRelease(QMouseEvent* event,QVariant &data)
{
    QPointF pt = data.toPointF();
    m_ptCurPoint = pt;
    if(event->button() != Qt::LeftButton)
        return;

    if(qFuzzyCompare(m_ptCurPoint.x(),m_ptStPoint.x()) && qFuzzyCompare(m_ptCurPoint.y(),m_ptStPoint.y()))
        return;

    HBaseObj* pObj = NULL;
    switch(m_edrawShape)
    {
    default:
        //pObj = create
        break;
    }

    if(pObj)
    {
        QPolygonF points;
        QRectF bounding;
        if(m_edrawShape == Circle)
        {

        }
        else
        {
            bounding = QRectF(m_ptCurPoint,m_ptStPoint).normalized();
            QPointF topLeft = bounding.topLeft();
            if(event->modifiers()&Qt::ControlModifier)
            {
                //正方形
                qreal dx = qAbs(m_ptCurPoint.x() - m_ptStPoint.x());
                qreal dy = qAbs(m_ptCurPoint.y() - m_ptStPoint.x());
                bounding.setWidth(qMin(dx,dy));
                bounding.setHeight(qMin(dx,dy));
                bounding.setTopLeft(topLeft);
            }
            bounding = bounding.normalized();
            QPointF center = bounding.center();
            if(bounding.width() < 5)
                bounding.setWidth(5);
            if(bounding.height() < 5)
                bounding.setHeight(5);
            bounding.moveCenter(center);
            points.append(bounding.topLeft());
            points.append(bounding.bottomRight());

            //obj设置points
            //设置obj属性
            m_pDrawManager->appendObj(pObj);
        }
        m_pDrawManager->endDraw();
    }
}
