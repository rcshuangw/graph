#include "h5drawtool.h"
#include "htext.h"
#include "hshapeobj.h"
HDrawTool::HDrawTool(HDrawManager* manager,DrawShape drawShape,const QString& name,const QString& uuid)
    :m_pToolManager(manager),m_edrawShape(drawShape),m_strObjName(name),m_strObjUuid(uuid)
{

}

HDrawTool::~HDrawTool()
{

}

void HDrawTool::clear()
{

}

void HDrawTool::onEvent(HEvent& e)
{
    if (!e.event())
		return;
}

void HDrawTool::setDrawAttribute(HBaseObj *obj)
{
    if(!obj || !m_pToolManager)
        return;
    if(obj->getShapeType() == Icon)
        return;
    QColor clr = m_pToolManager->m_vDrawAttribute.drawPen.color();
    obj->setLineColorName(clr.name());
    obj->setLineStyle(m_pToolManager->m_vDrawAttribute.drawPen.style());
    if(obj->getShapeType() == Text)
    {
        obj->setLineWidth(0);
    }
    else
    {
        obj->setLineWidth(m_pToolManager->m_vDrawAttribute.drawPen.width());
    }

    HText* pText = NULL;
    if(obj->getShapeType() == Text)
    {
        pText = (HText*)obj;
        pText->setTextClr(m_pToolManager->m_vDrawAttribute.textPen.color().name());
        pText->setFont(m_pToolManager->m_vDrawAttribute.font);
    }

    DrawShape drawShape = obj->getShapeType();
    if(drawShape == Rectangle ||drawShape ==Text || drawShape == Circle || drawShape == Ellipse || drawShape == Polygon)
    {
        HShapeObj* pSObj = dynamic_cast<HShapeObj*>(obj);
        pSObj->setFillColorName(m_pToolManager->m_vDrawAttribute.brush.color().name());
        pSObj->setFillStyle((qint8)m_pToolManager->m_vDrawAttribute.brush.style());
    }

}
