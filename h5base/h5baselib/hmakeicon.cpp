#include "hmakeicon.h"
#include <QProcessEnvironment>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include "hbaseobj.h"
#include "hicontemplate.h"
#include "hiconobj.h"
#include "hnormalobj.h"
#include "hline.h"
#include "hrectangle.h"
#include "hellipse.h"
#include "hcircle.h"
#include "htext.h"
#include "hpolygon.h"
#include "hpolyline.h"
#include "hgroup.h"
#include "harc.h"
#include "hgraph.h"
#include "htempcontainer.h"
HMakeIcon::HMakeIcon()
{
    m_pGraph = NULL;
}

HMakeIcon* HMakeIcon::m_pInstance = NULL;

HMakeIcon* HMakeIcon::Instance()
{
    if(!m_pInstance)
    {
        m_pInstance = new HMakeIcon();
    }
    return m_pInstance;
}

void HMakeIcon::Exstance()
{
    if(m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = NULL;
    }
}

HMakeIcon::~HMakeIcon()
{
}

HBaseObj* HMakeIcon::newObj(DrawShape nObjType,const QString& arg, HBaseObj* parent)
{
    HBaseObj* pObj = NULL;
    if (nObjType == Line)
    {
        pObj = new HLine();
    }
    else if (nObjType == Rectangle)
    {
        pObj = new HRectangle();
    }
    else if (nObjType == Ellipse)
    {
        pObj = new HEllipse();
    }
    else if (nObjType == Circle)
    {
        pObj = new HCircle();
    }
    else if (nObjType == Polygon)
    {
        pObj = new HPolygon();
    }
    else if (nObjType == Polyline)
    {
        pObj = new HPolyline();
    }
    else if (nObjType == Arc)
    {
        pObj = new HArc();
    }
    else if (nObjType == Text)
    {
        pObj = new HText();
    }
    else if (nObjType == Group)
    {
        pObj = new HGroup();
    }
    else if(nObjType == TempContainer)
    {
        pObj = new HTempContainer();
    }

    pObj->setShapeType((DrawShape)nObjType);
    return pObj;
}

HBaseObj* HMakeIcon::newObj(DrawShape nObjType,const QUuid& uuid,const QString& arg , HBaseObj* parent)
{
    if(m_pGraph == NULL)
        return NULL;
    HBaseObj* pObj = NULL;
    if(nObjType == Icon)
    {
        HIconTemplate* ptemplate = m_pGraph->findIconTemplate(uuid);
        if(ptemplate)
        {
            HIconObj* obj = new HIconObj(ptemplate);
            HIconObj* pIconObj = (HIconObj*)obj;
            pIconObj->initIconTemplate();
            pIconObj->iconSymbol()->setCurrentPattern(0);
            pObj = (HBaseObj*)obj;
        }
    }
    else if(nObjType == Normal)
    {
        HIconTemplate* ptemplate = m_pGraph->findIconTemplate(uuid);
        if(ptemplate)
        {
            HNormalObj* obj = new HNormalObj(ptemplate);
            HNormalObj* pIconObj = (HNormalObj*)obj;
            pIconObj->initIconTemplate();
            pIconObj->iconSymbol()->setCurrentPattern(0);
            pObj = (HBaseObj*)obj;
        }
    }
    if(pObj)
        pObj->setShapeType((DrawShape)nObjType);
    return pObj;
}

void HMakeIcon::setGraph(HGraph *graph)
{
    m_pGraph = graph;
}

HGraph* HMakeIcon::getGraph()
{
    return m_pGraph;
}
