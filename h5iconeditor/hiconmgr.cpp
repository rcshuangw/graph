#include "hiconmgr.h"

HIconMgr::HIconMgr()
    :m_bShowGrid(true),m_bShowCenterLine(true)
{
    m_pIconFrame = new HIconFrame(this);
    //pIconFrame->setIconMgr(this);
    m_pIconDocument = new HIconDocument(this);
    m_pIconState = new HIconState(this);
    m_pIconOp = new HIconOp(this);
    m_pIconUndoStack = new QUndoStack;
    m_bShowGrid = true;
    m_bShowCenterLine = true;
    m_strBgClr = "#FFFFFF";
    m_drawShape = enumNo;
    m_selectMode = enumSelect;
}

HIconDocument* HIconMgr::getIconDocument()
{
    if(m_pIconDocument)
        return m_pIconDocument;
    return NULL;
}

HIconTemplate* HIconMgr::getIconTemplate()
{
    if(m_pIconDocument)
        return m_pIconDocument->getCurrentTemplate();
    return NULL;
}

HIconFrame* HIconMgr::getIconFrame()
{
    if(m_pIconFrame)
        return m_pIconFrame;
    return NULL;
}

QUndoStack* HIconMgr::getIconUndoStack()
{
    if(m_pIconUndoStack)
        return m_pIconUndoStack;
    return NULL;
}

HIconOp* HIconMgr::getIconOp()
{
    if(m_pIconOp)
        return m_pIconOp;
    return NULL;
}

void HIconMgr::setBackgroundColor(QString clrName)
{
    m_strBgClr = clrName;
}

QString HIconMgr::getBackgroundColor()
{
    return m_strBgClr;
}

void HIconMgr::setShowGrid(bool show)
{
    m_bShowGrid = show;
}

bool HIconMgr::getShowGrid()
{
    return m_bShowGrid;
}

void HIconMgr::setShowCenterLine(bool show)
{
    m_bShowCenterLine = show;
}

bool HIconMgr::getShowCenterLine()
{
    return m_bShowCenterLine;
}

void HIconMgr::setDrawShape(DRAWSHAPE ds)
{
    m_drawShape = ds;
}

DRAWSHAPE HIconMgr::getDrawShape()
{
    return m_drawShape;
}

void HIconMgr::setSelectMode(SELECTMODE ds)
{
    m_selectMode = ds;
}

SELECTMODE HIconMgr::getSelectMode()
{
    return m_selectMode;
}


void HIconMgr::New(const QString& strTemplateName,const QString& strCatalogName,const int& nCatalogType)
{
    m_pIconDocument->New(strTemplateName,strCatalogName,nCatalogType);
}

void HIconMgr::Del(const QString &strTemplateName, int nTemplateType, const QString &strUuid)
{
    m_pIconDocument->Del(strTemplateName,nTemplateType,strUuid);
}

bool HIconMgr::Save(bool savefile)
{
    return m_pIconDocument->Save(savefile);
}

void HIconMgr::Open(const QString &strTemplateName, int nTemplateType, const QString &strUuid)
{
    m_pIconDocument->Open(strTemplateName,nTemplateType,strUuid);
}








