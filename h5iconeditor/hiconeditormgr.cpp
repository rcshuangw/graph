#include "hiconeditormgr.h"

HIconEditorMgr::HIconEditorMgr()
    :m_bShowGrid(true),m_bShowCenterLine(true)
{
    m_pIconEditorFrame = new HIconEditorFrame(this);
    //pIconFrame->setIconMgr(this);
	m_pIconEditorDoc = new HIconDocument(this);
    //m_pIconState = new HIconState(this);
   // m_pIconEditorOp = new HIconOp(this);
    m_pIconEditorUndo = new QUndoStack;
    m_bShowGrid = true;
    m_bShowCenterLine = true;
    m_strBgClr = "#FFFFFF";
    m_drawShape = No;
}

HIconEditorDoc* HIconEditorMgr::iconEditorDocument()
{
    if(m_pIconEditorDoc)
        return m_pIconEditorDoc;
    return NULL;
}

HIconTemplate* HIconEditorMgr::iconTemplate()
{
    if(m_pIconEditorDoc)
        return m_pIconEditorDoc->getCurrentTemplate();
    return NULL;
}

HIconFrame* HIconEditorMgr::iconEditorFrame()
{
    if(m_pIconFrame)
        return m_pIconFrame;
    return NULL;
}

QUndoStack* HIconEditorMgr::iconEditorUndoStack()
{
    if(m_pIconUndoStack)
        return m_pIconUndoStack;
    return NULL;
}

HIconOp* HIconEditorMgr::iconEditorOp()
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


void HIconEditorMgr::New(const QString& strTemplateName,const QString& strCatalogName,const int& nCatalogType)
{
    m_pIconDocument->New(strTemplateName,strCatalogName,nCatalogType);
}

void HIconEditorMgr::Del(const QString &strTemplateName, int nTemplateType, const QString &strUuid)
{
    m_pIconDocument->Del(strTemplateName,nTemplateType,strUuid);
}

bool HIconEditorMgr::Save(bool savefile)
{
    return m_pIconDocument->Save(savefile);
}

void HIconEditorMgr::Open(const QString &strTemplateName, int nTemplateType, const QString &strUuid)
{
    m_pIconDocument->Open(strTemplateName,nTemplateType,strUuid);
}








