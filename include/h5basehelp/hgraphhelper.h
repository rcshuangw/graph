#ifndef HGRAPHHELPER_H
#define HGRAPHHELPER_H

#include <QPixmap>
#include <QString>
#include "h5basehelpexport.h"
#include <QList>
class HGraph;
class HIconTemplate;

class H5BASEHELP_EXPORT HGraphHelper
{
public:
    HGraphHelper();

public:
    static HGraphHelper* m_pInstance;
    static HGraphHelper* Instance();

public:

    //加载模板文件信息
    void loadIconTemplate(QList<HIconTemplate*> *pIconTemplateList);
    void loadIconTemplateFile(QList<HIconTemplate*> *pIconTemplateList,QString strIconsPath);//加载所有的模板文件

    //加载画面文件
    void loadAllGraph(QList<HGraph*> *pGraphList);
    void saveAllGraph(QList<HGraph*> *pGraphList,HGraph* pCurGraph);


    //保存画面
    void saveGraph(HGraph* graph);
    void saveGraph(HGraph* graph,QString& path,HGraph* pCurGraph);

    QString getIconFolder(int nType);

    //通过图元类型来获得存储的文件夹类型
    bool IsIconInFolder(const QString& strFolderName,const int nIconType);

};


#endif // HGRAPHHELPER_H
