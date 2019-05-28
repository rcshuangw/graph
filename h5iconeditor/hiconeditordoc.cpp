#include "hiconeditordoc.h"
#include <QDir>
#include <QProcessEnvironment>
#include <QMessageBox>
#include "hiconapi.h"
#include "hicontemplate.h"
#include "hiconeditormgr.h"
#include "hiconhelper.h"
#include "hselectedmgr.h"
HIconEditorDoc::HIconEditorDoc(HIconEditorMgr* iconMgr):m_pIconEditorMgr(iconMgr)
{
    m_pCurIconTemplate = new HIconTemplate("0000");
}

HIconEditorDoc::~HIconEditorDoc()
{
    if(m_pCurIconTemplate)
    {
        delete m_pCurIconTemplate;
		m_pCurIconTemplate = NULL;
    }
}

void HIconEditorDoc::loadIconDoucument()
{
    HIconHelper::Instance()->loadIconDoucument(&m_pIconTemplateList);

    //刷新一下id
}

void HIconEditorDoc::saveIconDoucument()
{
    if(!m_pIconTemplateList.isEmpty())
        HIconHelper::Instance()->saveIconDoucument(&m_pIconTemplateList);
}

HIconTemplate* HIconEditorDoc::getCurrentTemplate()
{
    return m_pCurIconTemplate;
}

void HIconEditorDoc::New(const QString& strTemplateName,const QString& strCatalogName,const int& nCatalogType)
{
    if(m_pCurIconTemplate)
    {
		m_pCurIconTemplate->clear();
    }

    HIconTemplate *pTemplate = new HIconTemplate("");
    pTemplate->setCatalogName(strCatalogName);//普通开关
    pTemplate->setCatalogType(nCatalogType);//遥信类
    pTemplate->getSymbol()->setObjName(strTemplateName);
    pTemplate->getSymbol()->newPattern(QStringLiteral("缺省"));
    m_pIconTemplateList.append(pTemplate);

    pTemplate->copyTo(m_pCurIconTemplate);
}

void HIconEditorDoc::Del(const QString &strTemplateName, int nTemplateType, const QString &strUuid)
{

    char szIconPath[128];
    //getDataFilePath(DFPATH_ICON,szIconPath);
    QString iconsPath = QString(szIconPath);
    if(m_pCurIconTemplate->getCatalogType() == nTemplateType && m_pCurIconTemplate->getUuid().toString() == strUuid)
    {
		m_pCurIconTemplate->clear();
    }

    for(int i = 0; i < m_pIconTemplateList.size();i++)
    {
        HIconTemplate* pIconTemplate = (HIconTemplate*)m_pIconTemplateList.at(i);
        if(!pIconTemplate)
            return;
        if(pIconTemplate->getCatalogType() == nTemplateType && pIconTemplate->getUuid().toString() == strUuid)
        {
            QString strFileName = "";//iconsPath + "/" + HIconHelper::Instance()->getIconFolder(pIconTemplate->getCatalogType())+ "/" +pIconTemplate->getUuid().toString() + ".xic";
            if(QFile::exists(strFileName))
            {
                QFile::remove(strFileName);
            }
			m_pIconTemplateList.removeOne(pIconTemplate);
            delete pIconTemplate;
            pIconTemplate = NULL;
        }
    }
}

void HIconEditorDoc::Open(const QString &strTemplateName, int nTemplateType, const QString &strUuid)
{
    if(!m_pCurIconTemplate)
    {
        return;
    }

    HIconTemplate* pTemplate = findIconTemplateByTypeAndUuid(nTemplateType,strUuid);
    if(pTemplate && pTemplate->getSymbol()->getObjName() == strTemplateName)
    {
        m_pCurIconTemplate->clear();
        pTemplate->copyTo(m_pCurIconTemplate);
        m_pCurIconTemplate->setModify(pTemplate->isModify());
    }
}

bool HIconEditorDoc::Save(bool savefile)
{
    if(!m_pCurIconTemplate)
    {
        return false;
    }

    HIconTemplate* pTemplate = findIconTemplateByTypeAndUuid(m_pCurIconTemplate->getCatalogType(),m_pCurIconTemplate->getUuid().toString());
    if(pTemplate)
    {
        pTemplate->clear();
		m_pCurIconTemplate->copyTo(pTemplate);
    }

    if(savefile)
        saveIconDoucument();
    //一定要保存之后再修改
    if(pTemplate)
    {
        pTemplate->setModify(false);
		m_pCurIconTemplate->setModify(false);
    }
    m_pIconEditorMgr->selectedMgr()->clear();
    m_pIconEditorMgr->iconEditorUndoStack()->clear();
    m_pIconEditorMgr->iconEditorUndoStack()->setClean();
    return true;
}

HIconTemplate* HIconEditorDoc::findIconTemplateByTemplateName(const QString& strTemplateName)
{
    for(int i = 0; i < m_pIconTemplateList.size();i++)
    {
        HIconTemplate* pIconTemplate = (HIconTemplate*)m_pIconTemplateList.at(i);
        if(pIconTemplate && pIconTemplate->getSymbol()->getObjName() == strTemplateName)

            return pIconTemplate;
    }
    return NULL;
}

HIconTemplate* HIconEditorDoc::findIconTemplateByTypeAndUuid(int nTemplateType, const QString &strUuid)
{
    for(int i = 0; i < m_pIconTemplateList.size();i++)
    {
        HIconTemplate* pIconTemplate = (HIconTemplate*)m_pIconTemplateList.at(i);
        if(!pIconTemplate)
            return NULL;
        if(pIconTemplate->getCatalogType() == nTemplateType && pIconTemplate->getUuid().toString() == strUuid)
        {
            return pIconTemplate;
        }
    }
    return NULL;
}
