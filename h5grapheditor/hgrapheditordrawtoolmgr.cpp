#include "hgrapheditordrawtoolmgr.h"
#include <QObject>
#include <QPainterPath>
#include "hbaseobj.h"
#include "hgrapheditormgr.h"
#include "hicontemplate.h"
#include "hgrapheditorop.h"
#include "hgrapheditordoc.h"
#include "hgraph.h"
//#include "hiconcommand.h"
HGraphEditorDrawToolMgr::HGraphEditorDrawToolMgr(HGraphEditorMgr* pMgr):m_pGraphEditorMgr(pMgr)
{
    //curDrawShape = enumSelection;
}

HGraphEditorDrawToolMgr::~HGraphEditorDrawToolMgr()
{

}


void HGraphEditorDrawToolMgr::appendObj(HBaseObj *obj)
{
    if(!m_pGraphEditorMgr)
        return;
    //模板里面增加
    if(m_pGraphEditorMgr && m_pGraphEditorMgr->graphEditorDoc() && m_pGraphEditorMgr->graphEditorDoc()->getCurGraph())
    {
        m_pGraphEditorMgr->graphEditorDoc()->getCurGraph()->createBaseObj(obj->getShapeType(),NULL);
    }

    //画面增加
    if(m_pGraphEditorMgr && m_pGraphEditorMgr->graphEditorOp())
        m_pGraphEditorMgr->graphEditorOp()->ObjCreated(obj,false);

    //undostack增加
    /*
    HNewIconCommand *newCommand = new HNewIconCommand(m_pIconEditorMgr,obj);
    if(!newCommand) return;
    m_pIconEditorMgr->iconEditorUndoStack()->push(newCommand);*/
}

