#include "hpolylinetool.h"
#include "hpolygon.h"
#include "hpolyline.h"
HPolylineTool::HPolylineTool(HDrawManager* manager,DrawShape objShape,const QString& name,const QString& uuid)
        :HDrawTool(manager, objShape, name, uuid)
{
    m_bStart = false;
}

HPolylineTool::~HPolylineTool()
{

}

void HPolylineTool::clear()
{
    m_ptPolygons.clear();
}

void HPolylineTool::onEvent(HEvent& e)
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

void HPolylineTool::onMousePressEvent(QMouseEvent* event,QVariant &data)
{
    if(!m_pToolManager)
        return;
    if(event->button() != Qt::LeftButton)
        return;
    if(!m_bStart)
    {
        m_ptPolygons.clear();
        QPointF point = data.toPointF();
        m_ptStPoint = m_ptCurPoint = point;
        m_bStart = true;
        m_ptPolygons.append(point);
    }
    else
    {
        m_ptStPoint = m_ptCurPoint;
        QPointF point = data.toPointF();
        m_ptCurPoint = point;
        m_ptPolygons.append(point);

        QPainterPath painterPath;
        painterPath.addPolygon(m_ptPolygons);
        Path path;
        path.coordType = false;
        path.pen.setStyle(Qt::DashLine);
        path.painterPath = painterPath;
        //由绘制管理发送给editor
        QList<Path> pathList;
        pathList.append(path);
        m_pToolManager->onDrawPath(pathList);
    }
}

void HPolylineTool::onMouseMoveEvent(QMouseEvent* event,QVariant &data)
{
    if(!m_pToolManager)
        return;
    if(!m_bStart)
        return;
    QPointF point = data.toPointF();
    if(event->buttons()&Qt::LeftButton)
    {
        m_ptPolygons.append(point);
        m_ptCurPoint = point;
    }

}

void HPolylineTool::onMouseReleaseEvent(QMouseEvent* event,QVariant &data)
{
    if(!m_pToolManager)
        return;
    if(event->button() == Qt::RightButton)
    {
        if(!m_bStart) return;
        HBaseObj* pObj = NULL;
        if(m_edrawShape == Polyline && m_ptPolygons.size()<2 || m_edrawShape == Polygon && m_ptPolygons.size()<3)
            return;
        switch(m_edrawShape)
        {
        case Polyline:
            pObj = new HPolyline();
            break;
        case Polygon:
            pObj = new HPolygon();
            break;
        }
        if(NULL == pObj) return;
        pObj->setPointList(m_ptPolygons);
        m_pToolManager->appendObj(pObj);
        m_pToolManager->endDraw();
        m_bStart = false;
    }
}
