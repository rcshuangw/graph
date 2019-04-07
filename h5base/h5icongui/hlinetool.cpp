#include "hlinetool.h"
#include "htoolmanager.h"
HLineTool::HLineTool(HToolManager* manager,DrawShape objShape,const QString& name,const QString& uuid)
    :HDrawTool(manager,objShape,name,uuid)
{
	m_bDrawStart = false;
}

HLineTool::~HLineTool()
{

}

void HLineTool::clear()
{

}

void HLineTool::onEvent(HEvent& e)
{
    HDrawTool::onEvent(e);
    if(e.event()->type() == QMouseEvent::MouseButtonPress)
    {
        onMousePressEvent((QMouseEvent*)e.event(), e.m_data);
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

void HLineTool::onMousePressEvent(QMouseEvent* event,QVariant &data)
{
	if (!m_pToolManager)
		return;
	if (event->button() != Qt::LeftButton)
		return;
	QPointF pt = data.toPointF();
	//if (!m_bDrawStart)
	{
		m_ptStPoint = m_ptCurPoint = pt;
	//	m_bDrawStart = true;
	}
}

void HLineTool::onMouseMoveEvent(QMouseEvent* event,QVariant &data)
{
	if (!m_pToolManager)
		return;
	if (!(event->button()&Qt::LeftButton))
		return;
	QPointF pt = data.toPointF();
	m_ptCurPoint = pt;
	
	QPainterPath painterPath;
	painterPath.moveTo(m_ptStPoint);
	painterPath.lineTo(m_ptCurPoint);
	//��������
	Path path;
	path.coordType = false;
	path.painterPath = painterPath;
	//�ɻ��ƹ����͸�editor
	QList<Path> pathList;
	pathList.append(path);
	m_pToolManager->onDrawPath(pathList);
}

void HLineTool::onMouseReleaseEvent(QMouseEvent* event,QVariant &data)
{
	QPointF pt = data.toPointF();
	m_ptCurPoint = pt;
	if (event->button() != Qt::LeftButton)
		return;

	if (qFuzzyCompare(m_ptCurPoint.x(), m_ptStPoint.x()) && qFuzzyCompare(m_ptCurPoint.y(), m_ptStPoint.y()))
		return;

	HBaseObj* pObj = NULL;
	if (0 == m_edrawShape)
	{
	}
	else
	{
		//����lineobj����
	}

	if (pObj)
	{
		QPolygonF points;
		points << m_ptStPoint << m_ptCurPoint;
		m_pToolManager->appendObj(pObj);
	}
	m_pToolManager->endDraw();
}
