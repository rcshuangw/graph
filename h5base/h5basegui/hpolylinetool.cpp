#include "hpolylinetool.h"
#include "hmakeicon.h"
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
    //if(event->buttons()&Qt::LeftButton)
    {

       // m_ptCurPoint = point;
    }
    //之前的的
    QPainterPath painterPath;
    painterPath.addPolygon(m_ptPolygons);
    Path path;
    path.coordType = false;
    path.pen.setStyle(Qt::SolidLine);
    path.painterPath = painterPath;
    //当前的
    QPainterPath painterPath1;
    painterPath1.moveTo(m_ptCurPoint);
    painterPath1.lineTo(point);
    Path path1;
    path1.coordType = false;
    path1.pen.setStyle(Qt::DashLine);
    path1.painterPath = painterPath1;

    //由绘制管理发送给editor
    QList<Path> pathList;
    pathList.append(path);
    pathList.append(path1);
    m_pToolManager->onDrawPath(pathList);

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
        pObj = HMakeIcon::Instance()->newObj(m_edrawShape);
        if(NULL == pObj) return;
        pObj->setPointList(m_ptPolygons);
        m_pToolManager->appendObj(pObj);
        m_pToolManager->endDraw();
        m_bStart = false;
    }
}
