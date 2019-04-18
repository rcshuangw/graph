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
    void addObj(HBaseObj* pObj);
    void removeObj(HBaseObj* pObj);
    void copyTo(HIconShowPattern* sp);
    void clear();
	QVector<HBaseObj*>& getObjList() {
		return m_pObjList;
	}
public:
    int nPattern;
    QString strName;
    QString strAlias;
private:
    HIconSymbol* m_pSymbol;
	QVector<HBaseObj*> m_pObjList;//当前显示界面所包含的图元
};

#endif // HICONSHOWPATTERN_H
