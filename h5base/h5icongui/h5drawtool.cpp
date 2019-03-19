#include "h5drawtool.h"

HDrawTool::HDrawTool(HDrawManager* manager,DrawShape drawShape,const QString& name,const QString& uuid)
    :m_pDrawManager(manager),m_edrawShape(drawShape),m_strObjName(name),m_strObjUuid(uuid)
{

}

HDrawTool::~HDrawTool()
{

}

void HDrawTool::clear()
{

}

void HDrawTool::onEvent(HEvent& event)
{

}
