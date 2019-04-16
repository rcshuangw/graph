#ifndef HICONSYMBOL_H
#define HICONSYMBOL_H

#include <QObject>
#include <QtXml/QDomElement>
//存放每个一个图元内部的信息和图元本身的显示信息
#include "h5iconlibexport.h"
/*
#include "hpolygon.h"
#include "hpolyline.h"
#include "harc.h"
#include "hpie.h"
#include "htext.h"
#include "hcircle.h"
#include "hiconobj.h"
#include "hellipse.h"
#include "hgroupobj.h"
*/
class HIconShowPattern;
class HIconTemplate;
class HText;
class H5ICONLIB_EXPORT HIconSymbol:public QObject
{
public:
    HIconSymbol(HIconTemplate* t);
    ~HIconSymbol();

public:
    void clear();
    void readXml(QDomElement* dom);
    void writeXml(QDomElement *dom);

    void readData(int,QDataStream* d);
    void writeData(int,QDataStream *d);


    //新建一个图元元素(按类型)
    HBaseObj* newObj(int nObjType);
    HBaseObj* newObj(QString tagName);

    //增加删除一个图元元素
    void addObj(HBaseObj* pObj);
    void delObj(HBaseObj* pObj);
    void takeObj(HBaseObj* pObj);

    void copyTo(HIconSymbol* isymbol);

    void setSymbolName(const QString& strName);
    QString getSymolName();

    //void setSymbolType(const int& type);
    //int getSymbolType();

    void setIconSymbolWidth(double width);
    void setIconSymbolHeight(double height);


    int getObjID();
    bool findObjID(int nObjID);

    void setModify(bool modify);
    bool getModify();

    void updateShowPattern(QList<HBaseObj*> &list);
    //图元中多种状态的显示方案
    bool PatterIsValid(int nId);

    //新建
    HIconShowPattern* newPattern(const QString& name="");
    HIconShowPattern* newPattern(int id);

    //删除
    void delPattern(HIconShowPattern* sp);
    void delPattern(int id);
    void clearPattern();

    //查找
    int getMaxPattern(){return nMaxPattern;}

    //查找和设置
    int iconShowPatternCount(){return pShowPatternVector.count();}
    HIconShowPattern* findPatternById(int id);
    void setCurrentPattern(int id);
    int getCurrentPattern();
    int getCurrentPatternIndex();
    void setCurrentPatternPtr(HIconShowPattern* sp);
    HIconShowPattern* getCurrentPatternPtr();
    void resetRectPoint(const QPointF& pt1,const QPointF& pt2);
    void resize(double w,double h);

    //获取特定图元
    HText* getFirstTextObj();
public:
    QVector<HIconShowPattern*> pShowPatternVector;
private:
    QString strSymbolName;
    int usSymbolType;
    int nMaxPattern;
    int nCurPattern;
    HIconShowPattern* pCurPattern;
    HIconTemplate* pIconTemplate;

};

#endif // HICONSYMBOL_H
