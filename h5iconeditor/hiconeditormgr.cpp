#include "hiconeditormgr.h"
#include "hiconeditorscene.h"
#include "hiconeditorframe.h"
#include "hiconeditordoc.h"
#include "hiconeditorop.h"
#include "hselectedmgr.h"
#include "hiconeditordrawtoolmgr.h"
#include "hiconeditorselecttool.h"
HIconEditorMgr::HIconEditorMgr()
    :m_bShowGrid(true),m_bShowCenterLine(true)
{
    m_pIconEditorFrame = new HIconEditorFrame(this);
    //pIconFrame->setIconMgr(this);
	m_pIconEditorDoc = new HIconEditorDoc(this);
    //m_pIconState = new HIconState(this);
   // m_pIconEditorOp = new HIconOp(this);
    m_pIconUndoStack = new QUndoStack;
    m_bShowGrid = true;
    m_bShowCenterLine = true;
    m_strBgClr = "#FFFFFF";
    m_drawShape = No;
}

HIconEditorMgr::~HIconEditorMgr()
{

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

HIconEditorFrame* HIconEditorMgr::iconEditorFrame()
{
    if(m_pIconEditorFrame)
        return m_pIconEditorFrame;
    return NULL;
}

void HIconEditorMgr::setIconEditorFrame(HIconEditorFrame* frame)
{
	m_pIconEditorFrame = frame;
}

QUndoStack* HIconEditorMgr::iconEditorUndoStack()
{
    if(m_pIconUndoStack)
        return m_pIconUndoStack;
    return NULL;
}

HIconEditorOp* HIconEditorMgr::iconEditorOp()
{
    if(m_pIconEditorOp)
        return m_pIconEditorOp;
    return NULL;
}

HSelectedMgr* HIconEditorMgr::selectedMgr()
{
    if(m_pSelectedMgr)
        return m_pSelectedMgr;
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

void HIconEditorMgr::setDrawShape(DrawShape ds)
{
    m_drawShape = ds;
}

DrawShape HIconEditorMgr::getDrawShape()
{
    return m_drawShape;
}

void HIconEditorMgr::setLogicRect(QRectF &rectF)
{
	if (rectF == m_sceneRect)
		return;
	m_sceneRect = rectF;
	if (m_pIconEditorFrame && m_pIconEditorFrame->view() && m_pIconEditorFrame->view()->scene())
	{
		m_pIconEditorFrame->view()->setSceneRect(rectF);
		int f_width = m_pIconEditorFrame->width();
		int f_height = m_pIconEditorFrame->height();
		m_pIconEditorFrame->resize(f_width - 1, f_height);
		m_pIconEditorFrame->resize(f_width, f_height);
	}
}

QRectF HIconEditorMgr::getLogicRect()
{
	return m_sceneRect;
}

bool HIconEditorMgr::initIconEditorMgr()
{
    if(!m_pIconEditorDrawToolMgr)
    {
        m_pIconEditorDrawToolMgr = new m_pIconEditorDrawToolMgr;
        connect(m_pIconEditorDrawToolMgr,SIGNAL(drawPath(QList<Path>&)),m_pIconEditorOp,SLOT(onDrawPath(QList<Path>&)));
        connect(m_pIconEditorDrawToolMgr,SIGNAL(endDraw()),m_pIconEditorOp,SLOT(onEndDraw()));

        connect(m_pIconEditorSelectToolMgr,SIGNAL(refreshSelect(QRectF)),m_pIconEditorOp,SLOT(onRefreshSelect(QRectF)));
        connect(m_pIconEditorSelectToolMgr,SIGNAL(endDraw()),m_pIconEditorOp,SLOT(endDraw()));

        connect(m_pIconEditorOp,SIGNAL(selectChanged()),m_pIconEditorSelectToolMgr,SLOT(onSelectChanged()));

    }
}

void HIconEditorMgr::New(const QString& strTemplateName,const QString& strCatalogName,const int& nCatalogType)
{
    initIconEditorMgr();
    m_pIconEditorDoc->New(strTemplateName,strCatalogName,nCatalogType);
}

void HIconEditorMgr::Del(const QString &strTemplateName, int nTemplateType, const QString &strUuid)
{
	m_pIconEditorDoc->Del(strTemplateName,nTemplateType,strUuid);
}

bool HIconEditorMgr::Save(bool savefile)
{
    return m_pIconEditorDoc->Save(savefile);
}

void HIconEditorMgr::Open(const QString &strTemplateName, int nTemplateType, const QString &strUuid)
{
	m_pIconEditorDoc->Open(strTemplateName,nTemplateType,strUuid);
}








