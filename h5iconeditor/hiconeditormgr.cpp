#include "hiconeditormgr.h"

HIconEditorMgr::HIconEditorMgr()
    :m_bShowGrid(true),m_bShowCenterLine(true)
{
    m_pIconFrame = new HIconEditorFrame(this);
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

HIconDocument* HIconEditorMgr::getIconDocument()
{
    if(m_pIconDocument)
        return m_pIconDocument;
    return NULL;
}

HIconTemplate* HIconEditorMgr::getIconTemplate()
{
    if(m_pIconDocument)
        return m_pIconDocument->getCurrentTemplate();
    return NULL;
}

HIconFrame* HIconEditorMgr::getIconFrame()
{
    if(m_pIconFrame)
        return m_pIconFrame;
    return NULL;
}

QUndoStack* HIconEditorMgr::getIconUndoStack()
{
    if(m_pIconUndoStack)
        return m_pIconUndoStack;
    return NULL;
}

HIconOp* HIconEditorMgr::getIconOp()
{
    if(m_pIconOp)
        return m_pIconOp;
    return NULL;
}

void HIconEditorMgr::setBackgroundColor(QString clrName)
{
    m_strBgClr = clrName;
}

QString HIconEditorMgr::getBackgroundColor()
{
    return m_strBgClr;
}

void HIconEditorMgr::setShowGrid(bool show)
{
    m_bShowGrid = show;
}

bool HIconEditorMgr::getShowGrid()
{
    return m_bShowGrid;
}

void HIconEditorMgr::setShowCenterLine(bool show)
{
    m_bShowCenterLine = show;
}

bool HIconEditorMgr::getShowCenterLine()
{
    return m_bShowCenterLine;
}

void HIconEditorMgr::setDrawShape(DRAWSHAPE ds)
{
    m_drawShape = ds;
}

DrawShape HIconEditorMgr::getDrawShape()
{
    return m_drawShape;
}

void HIconEditorMgr::setSelectMode(SELECTMODE ds)
{
    m_selectMode = ds;
}

SELECTMODE HIconEditorMgr::getSelectMode()
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








