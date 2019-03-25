#include "hicondrawmanager.h"
#include "hiconobj.h"

HIconState::HIconState(HIconMgr* pMgr):pIconMgr(pMgr)
{
    curDrawShape = enumSelection;
}

HIconState::~HIconState()
{

}


void HIconState::appendObj(HBaseObj *obj)
{
    //模板里面增加
    if(pIconMgr && pIconMgr->getIconTemplate() && pIconMgr->getIconTemplate()->getSymbol())
        pIconMgr->getIconTemplate()->getSymbol()->addObj(obj);
}

