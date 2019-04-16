#ifndef HICONSHOWPATTERN_H
#define HICONSHOWPATTERN_H

#include "hiconsymbol.h"
#include "hbaseobj.h"
//图元显示单元(分,合，双位置分错，双位置合错)
class H5ICONLIB_EXPORT HIconShowPattern
{
public:
    HIconShowPattern(HIconSymbol* symbol);
    ~HIconShowPattern();

public:
    void readXml(QDomElement* dom);
    void writeXml(QDomElement *dom);
    void addObj(HBaseObj* pObj,bool badd=true);
    void delObj(HBaseObj* pObj);
    void takeObj(HBaseObj* pObj);
    void copyTo(HIconShowPattern* sp);
    void clear();
    void resetRectPoint(const QPointF& pt1,const QPointF& pt2);
    void resize(double w,double h);
public:
    int nPattern;
    QString strName;
    QString strAlias;
    QList<HBaseObj*> pObjList;
    HIconSymbol* pSymbol;
};

#endif // HICONSHOWPATTERN_H
