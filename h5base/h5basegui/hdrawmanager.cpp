#include "hdrawmanager.h"
#include <QCursor>
#include "h5drawtool.h"
#include "hlinetool.h"
#include "hpolylinetool.h"
#include "hrecttool.h"
#include "harctool.h"
HDrawManager::HDrawManager()
{
    m_pDrawTool = NULL;
}

HDrawManager::~HDrawManager()
{
    while(!m_drawToolList.isEmpty())
        delete m_drawToolList.takeFirst();
}

void HDrawManager::onEvent(HEvent& e)
{
    if(m_pDrawTool)
        m_pDrawTool->onEvent(e);
}

void HDrawManager::selectTool(DrawShape shape,const QString& catalogName,const QString& uuid)
{
    if(findTool(shape,catalogName,uuid))
        return;
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
    case Icon:
        m_pDrawTool = new HRectTool(this,shape,catalogName,uuid);
        if(m_pDrawTool)
            m_drawToolList.append(m_pDrawTool);
        break;
    case Arc:
        m_pDrawTool = new HArcTool(this,shape,catalogName,uuid);
        if(m_pDrawTool)
            m_drawToolList.append(m_pDrawTool);
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

QCursor HDrawManager::cursor() const
{
    return QCursor(Qt::CrossCursor);
}


void HDrawManager::onDrawPath(const QList<Path> &pathList)
{
    emit drawPath(pathList);
}

void HDrawManager::onEndDraw()
{
    emit endDraw();
}
