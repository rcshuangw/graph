#include "harctool.h"
HArcTool::HArcTool(HToolManager* manager,DrawShape objShape,const QString& name,const QString& uuid)
        :HDrawTool(manager, objShape, name, uuid)//m_pToolManager(manager),m_edrawShape(objShape),m_strObjName(name),m_strObjUuid(uuid)
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

void HArcTool::onMousePressEvent(QMouseEvent* event,QVariant &data)
{

}

void HArcTool::onMouseMoveEvent(QMouseEvent* event,QVariant &data)
{

}

void HArcTool::onMouseReleaseEvent(QMouseEvent* event,QVariant &data)
{

}
