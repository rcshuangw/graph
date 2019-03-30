#ifndef HSIMPLEOBJ_H
#define HSIMPLEOBJ_H
#include "hbaseobj.h"
class H5ICONLIB_EXPORT HShapeObj : public HBaseObj
{
    Q_OBJECT
public:
    HShapeObj();
    virtual ~HShapeObj();

public:
    //二进制读写
    virtual void readData(QDataStream* data);
    virtual void writeData(QDataStream* data);

    //xml文件读写
    virtual void readXml(QDomElement* data);
    virtual void writeXml(QDomElement* data);

    virtual QString TagName();

    //拷贝克隆
    virtual void copyTo(HBaseObj* obj);
    virtual void clone(HBaseObj* obj);
public:

    //填充选择
    virtual void setFillWay(quint8 fillWay);
    virtual quint8 getFillWay();

    //填充方式(风格)
    virtual void setFillStyle(quint8 style);
    virtual quint8 getFillStyle();

    //填充色
    virtual void setFillColorName(QString clrName);
    virtual QString getFillColorName();

    //填充方向
    virtual void setFillDirection(quint8 fillDirection);
    virtual quint8 getFillDirection();

    //填充比例
    virtual void setFillPercentage(quint8 fillPer);
    virtual quint8 getFillPercentage();

    //边框可见
    virtual void setFrameSee(bool frameSee);
    virtual bool getFrameSee();

    //透明度
    virtual void setTransparency(quint8 transparency);
    virtual quint8 getTransparency();

    virtual void setImagePath(const QString& path);
    virtual QString getImagePath();
    virtual bool isValidImagePath() const;

    virtual void setKeepImageRatio(bool bcheck);
    virtual bool getKeepImageRatio();

    virtual void setImageDirect(quint8 direct);
    virtual quint8 getImageDirect();

    //////////////////////////////////////////设置属性//////////////////////////////////////
public:
    qreal width;
    qreal height;

    //填充方面
    quint8 nFillWay;//填充方式
    quint8 nFillStyle;//填充风格
    QString strFillColor; //填充颜色
    quint8 nFillDirection;//填充方向
    quint8 nFillPercentage;//填充比例

    //边框透明度
    bool bFrameSee;//边框可见
    quint8 nTransparency; //透明度

    //图片
    QString strImagePath;//图片路径
    bool bKeepImageRatio; //保持图片比例
    quint8 nImageDirect; //图片的方向
};

#endif // HSIMPLEOBJ_H
