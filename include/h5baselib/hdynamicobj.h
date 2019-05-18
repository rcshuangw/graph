#ifndef HDYNAMICOBJ_H
#define HDYNAMICOBJ_H

#include <QObject>
#include <QDataStream>
#include <QDomElement>
#include "h5baselibexport.h"
class H5BASELIB_EXPORT HDynamicObj : public QObject
{
public:
    HDynamicObj();
    virtual ~HDynamicObj();
public:
    //二进制读写
    virtual void readData(QDataStream* data);
    virtual void writeData(QDataStream* data);

    //xml文件读写
    virtual void readXml(QDomElement* data);
    virtual void writeXml(QDomElement* data);

    virtual QString tagName();

    //拷贝克隆
    virtual void copyTo(HDynamicObj* obj);
    virtual void clone(HDynamicObj* obj);

public:
    void setDBStation(ushort wStation);
    ushort getDBStation();
    void setDBPoint(ushort wPoint);
    ushort getDBPoint();
    void setDBAttr(ushort wAttr);
    ushort getDBAttr();

    void setValueType(uchar btFt);
    uchar getValueType();
    void setFormula(ushort formula);
    ushort getFormula();

protected:
    uchar btFieldType;//测点类型
    ushort wFormula;//公式
    ushort wStation;//厂站
    ushort wPoint;//测点
    ushort wAttrib;//属性
};

#endif // HDYNAMICOBJ_H
