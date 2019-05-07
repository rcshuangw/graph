#include "hdrawmanager.h"
#include "h5drawtool.h"
#include "hlinetool.h"
#include "hpolylinetool.h"
#include "hrecttool.h"
#include "harctool.h"
HDrawManager::HDrawManager()
{

}

HDrawManager::~HDrawManager()
{

}

void HDrawManager::onEvent(HEvent& e)
{
    if(m_pDrawTool)
        m_pDrawTool->onEvent(e);
}

void HDrawManager::selectTool(DrawShape shape,const QString& catalogName,const QString& uuid)
{
    switch(shape)
    {
    case Line:
        m_pDrawTool = new HLineTool(this,shape,catalogName,uuid);
        if(NULL == m_pDrawTool) return;
        m_drawToolList.append(m_pDrawTool);
        break;
    case Rectangle:
    case Ellipse:
    case Circle:
    case Text:
    case Group:
    case Icon:
        m_pDrawTool = new HRectTool(this,shape,catalogName,uuid);
        break;
    case Arc:
        //HArcTool
        break;
    case Polygon:
    case Polyline:
        m_pDrawTool = new HPolylineTool(this,shape,catalogName,uuid);
        if(NULL == m_pDrawTool) return;
        m_drawToolList.append(m_pDrawTool);
        break;
    default:
        m_pDrawTool = 0;
    }
}

bool HDrawManager::findTool(DrawShape shape,const QString& catalogName,const QString& uuid)
{
    for(int i = 0;i < m_drawToolList.count();i++)
    {
        HDrawTool* pTool = (HDrawTool*)m_drawToolList[i];
        if(pTool && pTool->drawShape() == shape && pTool->objTypeName() == catalogName && pTool->templateUuid() == uuid)
        {
            m_pDrawTool = pTool;
            m_pDrawTool->clear();
            return true;
        }
    }
    return false;
}

void HDrawManager::onDrawPath(const QList<Path> &pathList)
{
    emit drawPath(pathList);
}

void HDrawManager::onEndDraw()
{
    emit endDraw();
}
