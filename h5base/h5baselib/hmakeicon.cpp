#include "hmakeicon.h"
#include <QProcessEnvironment>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include "hbaseobj.h"
#include "hicontemplate.h"
#include "hiconobj.h"
#include "hline.h"
#include "hrectangle.h"
#include "hellipse.h"
#include "hcircle.h"
#include "htext.h"
#include "hpolygon.h"
#include "hpolyline.h"
#include "hgroup.h"
#include "htempcontainer.h"
HMakeIcon::HMakeIcon()
{
    clear();
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
    clear();
}

void HMakeIcon::clear()
{
    m_nIdList.clear();
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
        //pObj = new HArc();
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

void HMakeIcon::addObjID(int id)
{
    if(-1 == m_nIdList.indexOf(id))
        m_nIdList.append(id);
}

//获取ObjID
int HMakeIcon::getObjID()
{
    int nObjID = 1;
    while(findObjID(nObjID))
        nObjID++;
    return nObjID;
}

bool HMakeIcon::findObjID(int nObjID)
{
    if(-1 == m_nIdList.indexOf(nObjID))
        return false;
    return true;
}
