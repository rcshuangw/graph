#include "hantimalopdoc.h"
#include "hantimalopmgr.h"
#include "hgraph.h"
#include "hgraphhelper.h"
#include <QDir>
#include <QFile>
#include <QFileInfoList>
#include <QProcessEnvironment>
//图形文件存储类
HAntiMalopDoc::HAntiMalopDoc(HAntiMalopMgr* mgr)
    :m_pAntiMalopMgr(mgr)
{
    m_pCurGraph = NULL;
}

HAntiMalopDoc::~HAntiMalopDoc()
{

}

void HAntiMalopDoc::loadAllGraph()
{
    HGraphHelper::Instance()->loadAllGraph(&m_pGraphList);
    m_pCurGraph = getRootGraph();

    //刷新模板
    updateGraphList();
}

//更新所有画面里面的模板信息
void HAntiMalopDoc::updateGraphList()
{
    /*
    for(int i = 0; i < m_pGraphList.count();i++)
    {
        HGraph* pGraph = (HGraph*)m_pGraphList[i];
        if(!pGraph) continue;
        HIconTemplate* findTemp = NULL;
        for(int j = 0; j < pGraph->pIconTemplateList.count();j++)
        {
            HIconTemplate* pGraphTemp = (HIconTemplate*)pGraph->pIconTemplateList[j];
            if(!pGraphTemp)
                continue;
            findTemp = findIconTemplate(pGraphTemp->getUuid().toString());
            if(findTemp)
            {
                findTemp->copyTo(pGraphTemp);
            }
            for(int k = 0; k < pGraph->getObjList().count();k++)
            {
                HBaseObj* pObj = (HBaseObj*)pGraph->getObjList().at(k);
                if(pObj->getShapeType() == enumComplex)
                {
                    HIconObj* pObj1 = (HIconObj*)pObj;//
                    if(!pObj1->iconTemplate()->getUuid().toString().compare(findTemp->getUuid().toString()))
                    {
                        findTemp->getSymbol()->copyTo(pObj1->getIconSymbol());
                        pObj1->updateResize();
                        int a = 0;
                    }
                }
            }
        }
    }*/
}

HGraph* HAntiMalopDoc::getRootGraph()
{
    HGraph* pRootGraph = NULL;
    for(int i = 0; i < m_pGraphList.count();i++)
    {
        HGraph* pGraph = (HGraph*)m_pGraphList[i];
        if(pGraph /*&& pGraph->bStart*/)
        {
            pRootGraph = pGraph;
            break;
        }
    }
    return pRootGraph;
}

HGraph* HAntiMalopDoc::findGraph(int graphID)
{
    HGraph *graph = NULL;
    QList<HGraph*>::Iterator graphIterator;
    for(graphIterator = m_pGraphList.begin();graphIterator != m_pGraphList.end();graphIterator++)
    {
        graph = *graphIterator;
        if(graph->graphID() == graphID)
            return graph;
    }
    return NULL;
}

HGraph* HAntiMalopDoc::findGraph(const QString& graphName)
{
    HGraph *graph = NULL;
    QList<HGraph*>::Iterator graphIterator;
    for(graphIterator = m_pGraphList.begin();graphIterator != m_pGraphList.end();graphIterator++)
    {
        graph = *graphIterator;
        if(graph->graphName() == graphName)
            return graph;
    }
    return NULL;
}

bool HAntiMalopDoc::openGraph(const QString& name,const int id)
{
    HGraph* graph = findGraph(id);
    if(!graph)
        return false;
    m_pCurGraph = graph;
    return true;
}

HGraph* HAntiMalopDoc::getCurGraph()
{
    return m_pCurGraph;
}
