#include "hlinetool.h"
HLineTool::HLineTool(HDrawManager* manager,DrawShape objShape,const QString& name,const QString& uuid)
    :m_pDrawManager(manager),m_edrawShape(objShape),m_strObjName(name),m_strObjUuid(uuid)
{

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

void HLineTool::onMousePress(QMouseEvent* event,QVariant &data)
{

}

void HLineTool::onMouseMove(QMouseEvent* event,QVariant &data)
{

}

void HLineTool::onMouseRelease(QMouseEvent* event,QVariant &data)
{

}
