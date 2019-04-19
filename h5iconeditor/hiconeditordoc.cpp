#include "hicondocument.h"
#include <QDir>
#include <QProcessEnvironment>
#include <QMessageBox>
#include "publicdata.h"
HIconDocument::HIconDocument(HIconMgr* iconMgr):pIconMgr(iconMgr)
{
    pCurIconTemplate = new HIconTemplate("0000");
}

HIconDocument::~HIconDocument()
{
    if(pCurIconTemplate)
    {
        delete pCurIconTemplate;
        pCurIconTemplate = NULL;
    }
}

void HIconDocument::loadIconDoucument()
{
    HIconHelper::Instance()->loadIconDoucument(&pIconTemplateList);
}

void HIconDocument::saveIconDoucument()
{
    if(!pIconTemplateList.isEmpty())
        HIconHelper::Instance()->saveIconDoucument(&pIconTemplateList);
}

HIconTemplate* HIconDocument::getCurrentTemplate()
{
    return pCurIconTemplate;
}


void HIconDocument::New(const QString& strTemplateName,const QString& strCatalogName,const int& nCatalogType)
{
    if(pCurIconTemplate)
    {
        pCurIconTemplate->clear();
    }

    HIconTemplate *pTemplate = new HIconTemplate("");
    pTemplate->setCatalogName(strCatalogName);//普通开关
    pTemplate->setCatalogType(nCatalogType);//遥信类
    pTemplate->getSymbol()->setSymbolName(strTemplateName);
    pTemplate->getSymbol()->newPattern(QStringLiteral("缺省"));
    pIconTemplateList.append(pTemplate);

    pTemplate->copyTo(pCurIconTemplate);
}

void HIconDocument::Del(const QString &strTemplateName, int nTemplateType, const QString &strUuid)
{

    char szIconPath[128];
    getDataFilePath(DFPATH_ICON,szIconPath);
    QString iconsPath = QString(szIconPath);
    if(pCurIconTemplate->getCatalogType() == nTemplateType && pCurIconTemplate->getUuid().toString() == strUuid)
    {
        pCurIconTemplate->clear();
    }

    for(int i = 0; i < pIconTemplateList.size();i++)
    {
        HIconTemplate* pIconTemplate = (HIconTemplate*)pIconTemplateList.at(i);
        if(!pIconTemplate)
            return;
        if(pIconTemplate->getCatalogType() == nTemplateType && pIconTemplate->getUuid().toString() == strUuid)
        {
            QString strFileName = iconsPath + "/" + HIconHelper::Instance()->getIconFolder(pIconTemplate->getCatalogType())+ "/" +pIconTemplate->getUuid().toString() + ".xic";
            if(QFile::exists(strFileName))
            {
                QFile::remove(strFileName);
            }
            pIconTemplateList.removeOne(pIconTemplate);
            delete pIconTemplate;
            pIconTemplate = NULL;
        }
    }
}

void HIconDocument::Open(const QString &strTemplateName, int nTemplateType, const QString &strUuid)
{
    if(!pCurIconTemplate)
    {
        return;
    }

    HIconTemplate* pTemplate = findIconTemplateByTypeAndUuid(nTemplateType,strUuid);
    if(pTemplate && pTemplate->getSymbol()->getSymolName() == strTemplateName)
    {
        pCurIconTemplate->clear();
        pTemplate->copyTo(pCurIconTemplate);
        pCurIconTemplate->setModify(pTemplate->getModify());
    }
}

bool HIconDocument::Save(bool savefile)
{
    if(!pCurIconTemplate)
    {
        return false;
    }

    HIconTemplate* pTemplate = findIconTemplateByTypeAndUuid(pCurIconTemplate->getCatalogType(),pCurIconTemplate->getUuid().toString());
    if(pTemplate)
    {
        pTemplate->clear();
        pCurIconTemplate->copyTo(pTemplate);
    }

    if(savefile)
        saveIconDoucument();
    //一定要保存之后再修改
    if(pTemplate)
    {
        pTemplate->setModify(false);
        pCurIconTemplate->setModify(false);
    }
    return true;
}

HIconTemplate* HIconDocument::findIconTemplateByTemplateName(const QString& strTemplateName)
{
    for(int i = 0; i < pIconTemplateList.size();i++)
    {
        HIconTemplate* pIconTemplate = (HIconTemplate*)pIconTemplateList.at(i);
        if(pIconTemplate && pIconTemplate->getSymbol()->getSymolName() == strTemplateName)

            return pIconTemplate;
    }
    return NULL;
}

HIconTemplate* HIconDocument::findIconTemplateByTypeAndUuid(int nTemplateType, const QString &strUuid)
{
    for(int i = 0; i < pIconTemplateList.size();i++)
    {
        HIconTemplate* pIconTemplate = (HIconTemplate*)pIconTemplateList.at(i);
        if(!pIconTemplate)
            return NULL;
        if(pIconTemplate->getCatalogType() == nTemplateType && pIconTemplate->getUuid().toString() == strUuid)
        {
            return pIconTemplate;
        }
    }
    return NULL;
}
