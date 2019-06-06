#ifndef HICONHELPER_H
#define HICONHELPER_H
#include "h5basehelpexport.h"
#include <QPixmap>
#include <QString>
#include <QList>
#include <QComboBox>
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
    QPixmap iconPixmap(const QString& strType,const QString& uuid,const QSizeF &pt = QSizeF(0,0),int nCurPattern = 0);

    //加载文件信息
    void loadIconDoucument(QList<HIconTemplate*> *pIconTemplateList);
    void loadIconTemplateFile(QList<HIconTemplate*> *pIconTemplateList,QString strIconsPath);//加载所有的模板文件
    void saveIconDoucument(QList<HIconTemplate*> *pIconTemplateList);
    void saveIconTemplateFile(QList<HIconTemplate*> *pIconTemplateList,const QString& strIconsPath,const QString& strFolderName);//保存所有的模板文件
    QString getIconFolder(int nType);

    //通过图元类型来获得存储的文件夹类型
    bool IsIconInFolder(const QString& strFolderName,const int nIconType);


public:
    //绘制颜色或者填充颜色图符
    QIcon createPenorBrushColorIcon(const QIcon& icon,const QColor& clr);

    //初始化线宽列表
    void InitPenWidthComboBox(QComboBox* comboBox);

    //初始化线型列表
    void InitPenStyleComboBox(QComboBox* comboBox);

    //初始化线头列表
    void InitPenCapStyleComboBox(QComboBox* comboBox);

    //初始化填充方式列表
    void InitBrushStyleComboBox(QComboBox* comboBox);

    //初始化直线箭头列表
    void InitArrowStyleComboBox(QComboBox* comboBox,bool head = true);

private:
    //绘制线宽图符
    QIcon createPenWidthIcon(int width);

    //绘制线型图符
    QIcon createPenStyleIcon(Qt::PenStyle style);

    //绘制线头图符
    QIcon createPenCapStyleIcon(Qt::PenCapStyle capStyle);

    //绘制线刷(填充方式)图符
    QIcon createBrushStyleIcon(Qt::BrushStyle brushStyle);

    //绘制箭头
    QIcon createArrowIcon(quint8 style,bool head);


};

#endif // HICONHELPER_H
