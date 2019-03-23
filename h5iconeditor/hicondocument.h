#ifndef HICONDOCUMENT_H
#define HICONDOCUMENT_H

#include <QObject>
#include "hiconapi.h"
#include "hicontemplate.h"
#include "hiconmgr.h"
#include "hiconhelper.h"
class HIconMgr;
class HIconDocument : public QObject
{
public:
    HIconDocument(HIconMgr* iconMgr);
    ~HIconDocument();
public:
    void loadIconDoucument();
    void saveIconDoucument();
public:
    void New(const QString& strTemplateName,const QString& strCatalogName,const int& nCatalogType);
    void Del(const QString &strTemplateName, int nTemplateType, const QString &strUuid);
    void Open(const QString &strTemplateName, int nTemplateType, const QString &strUuid);
    bool Save(bool savefile = false);
    HIconTemplate* getCurrentTemplate();
    HIconTemplate* findIconTemplateByTypeAndUuid(int nTemplateType,const QString& strUuid);
    HIconTemplate* findIconTemplateByTemplateName(const QString& strTemplateName);
public:
    HIconTemplate* pCurIconTemplate;
    HIconMgr* pIconMgr;
    QList<HIconTemplate*> pIconTemplateList;
};

#endif // HICONDOCUMENT_H
