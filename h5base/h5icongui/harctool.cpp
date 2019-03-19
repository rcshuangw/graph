#include "harctool.h"
HArcTool::HArcTool(HDrawManager* manager,DrawShape objShape,const QString& name,const QString& uuid)
        :m_pDrawManager(manager),m_edrawShape(objShape),m_strObjName(name),m_strObjUuid(uuid)
{

}

HArcTool::~HArcTool()
{

}

void HArcTool::clear()
{

}

void HArcTool::onEvent(HEvent& event)
{

}

void HArcTool::onMousePress(QMouseEvent* event,QVariant &data)
{

}

void HArcTool::onMouseMove(QMouseEvent* event,QVariant &data)
{

}

void HArcTool::onMouseRelease(QMouseEvent* event,QVariant &data)
{

}
