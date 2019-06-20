#include "hiconeditordrawtoolmgr.h"
#include <QObject>
#include <QPainterPath>
#include "hbaseobj.h"
#include "hiconeditormgr.h"
#include "hicontemplate.h"
#include "hiconeditorop.h"
#include "hiconcommand.h"
HIconEditorDrawToolMgr::HIconEditorDrawToolMgr(HIconEditorMgr* pMgr):m_pIconEditorMgr(pMgr)
{
    //curDrawShape = enumSelection;
}

HIconEditorDrawToolMgr::~HIconEditorDrawToolMgr()
{

}


void HIconEditorDrawToolMgr::appendObj(HBaseObj *obj)
{
    if(!m_pIconEditorMgr)
        return;
    //模板里面增加
    if(m_pIconEditorMgr && m_pIconEditorMgr->iconTemplate() && m_pIconEditorMgr->iconTemplate()->getSymbol())
        m_pIconEditorMgr->iconTemplate()->getSymbol()->addBaseObj(obj);

    //画面增加
    if(m_pIconEditorMgr && m_pIconEditorMgr->iconEditorOp())
        m_pIconEditorMgr->iconEditorOp()->onCreateObj(obj,false);
    //undostack增加
    HNewIconCommand *newCommand = new HNewIconCommand(m_pIconEditorMgr,obj);
    if(!newCommand) return;
    m_pIconEditorMgr->iconEditorUndoStack()->push(newCommand);
}

