#include "hiconshowpattern.h"

HIconShowPattern::HIconShowPattern(HIconSymbol* symbol):m_pSymbol(symbol)
{
}

HIconShowPattern::~HIconShowPattern()
{
    clear();
}

void HIconShowPattern::addObj(HBaseObj* pObj)
{
    if(!pObj)
        return;
    if(-1 != m_pObjList.indexOf(pObj))
        return;
    pObj->setPattern(nPattern);
    pObj->setParent(m_pSymbol);
    m_pObjList.append(pObj);
}

void HIconShowPattern::removeObj(HBaseObj* pObj)
{
    if(!pObj)
        return;
	m_pObjList.removeOne(pObj);
	pObj->setDeleted(true);
}


void HIconShowPattern::copyTo(HIconShowPattern* sp)
{
    if(!sp)
        return;
    sp->strName = strName;
    sp->nPattern = nPattern;
    sp->strAlias = strAlias;
    sp->m_pSymbol = m_pSymbol;
    //sp->clear();
}

void HIconShowPattern::clear()
{
	//对象由HIconSymbol来释放
    m_pObjList.clear();
}






