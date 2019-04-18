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
    while(!m_pObjList.isEmpty())
    {
        HBaseObj* pObj = m_pObjList.takeFirst();
        if(pObj)
        {
            delete pObj;
            pObj = NULL;
        }
    }
    m_pObjList.clear();
}






