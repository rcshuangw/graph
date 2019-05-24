#ifndef HICONHELPER_H
#define HICONHELPER_H
#include "h5basehelpexport.h"
#include <QPixmap>
#include <QString>
#include <QList>
#include "hiconapi.h"
class HBaseObj;
class HIconTemplate;

class H5BASEHELP_EXPORT HIconHelper
{
public:
    HIconHelper();

public:
    static HIconHelper* m_pInstance;
    static HIconHelper* Instance();

public:
    //获取某个图符的pixmap  模板类型，模板uuid,图符大小，当前curpattern
    QPixmap iconPixmap(const QString& strType,const QString& uuid,const QSizeF &size = QSizeF(0,0),int nCurPattern = 0);

    //加载文件信息
    void loadIconDoucument(QList<HIconTemplate*> *pIconTemplateList);
    void loadIconTemplateFile(QList<HIconTemplate*> *pIconTemplateList,QString strIconsPath);//加载所有的模板文件
    void saveIconDoucument(QList<HIconTemplate*> *pIconTemplateList);
    void saveIconTemplateFile(QList<HIconTemplate*> *pIconTemplateList,const QString& strIconsPath,const QString& strFolderName);//保存所有的模板文件
    QString getIconFolder(int nType);

    //通过图元类型来获得存储的文件夹类型
    bool IsIconInFolder(const QString& strFolderName,const int nIconType);

};

#endif // HICONHELPER_H
