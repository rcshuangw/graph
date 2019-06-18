#include "hgrapheditordrawtoolmgr.h"
#include <QObject>
#include <QPainterPath>
#include "hbaseobj.h"
#include "hgrapheditormgr.h"
#include "hicontemplate.h"
#include "hgrapheditorop.h"
#include "hgrapheditordoc.h"
#include "hgraph.h"
#include "hgraphcommand.h"
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
        m_pGraphEditorMgr->graphEditorDoc()->getCurGraph()->addIconObj(obj);
    }

    //画面增加
    if(m_pGraphEditorMgr && m_pGraphEditorMgr->graphEditorOp())
        m_pGraphEditorMgr->graphEditorOp()->objCreated(obj,false);

    //undostack增加
    HGraphNewCommand *newCommand = new HGraphNewCommand(m_pGraphEditorMgr,obj);
    if(!newCommand) return;
    m_pGraphEditorMgr->graphEditorStack()->push(newCommand);
}

