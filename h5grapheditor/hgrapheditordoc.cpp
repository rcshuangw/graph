#include "hgrapheditordoc.h"
#include "hgrapheditormgr.h"
#include "hgraph.h"
#include "hicontemplate.h"
#include "hstation.h"
#include "hgraphhelper.h"
#include "hiconobj.h"
#include "hmakeicon.h"
#include <QDir>
#include <QFile>
#include <QFileInfoList>
#include <QProcessEnvironment>
//图形文件存储类
HGraphEditorDoc::HGraphEditorDoc(HGraphEditorMgr* mgr)
    :m_pGraphEditorMgr(mgr)
{
    m_pCurGraph = NULL;
    m_bGraphValid = false;
    HMakeIcon::Instance()->setGraph(0);
}

HGraphEditorDoc::~HGraphEditorDoc()
{

}

//加载厂站信息
void HGraphEditorDoc::loadStation()
{
    //读取厂站信息
    /*
    FILEHANDLE fileHandle;
    memset(&fileHandle,0,sizeof(FILEHANDLE));
    DATAFILEHEADER dataFileHandle;

    openDB(FILE_TYPE_STATION);
    loadDataFileHeader(FILE_TYPE_STATION,&dataFileHandle);
    //int wStation = 0;
    for(int i = 0 ; i < dataFileHandle.wTotal; i++)
    {
        HStation* pStation = new HStation;
        if(!pStation)
            break;

        if ( false == loadDBRecord(FILE_TYPE_STATION, ++fileHandle.wStation, &pStation->station ) )
        {
            delete pStation;
            pStation=NULL;
            break;
        }
        if(false == pStation->loadData(fileHandle))
        {
            delete pStation;
            pStation = NULL;
            break;
        }
        pStationList.append(pStation);
    }
    closeDB(FILE_TYPE_STATION);
    */
}


//厂站ID获取厂站
HStation* HGraphEditorDoc::getStation(quint16 wStationID)
{
    for(int i = 0; i < m_pStationList.count();i++)
    {
        HStation* pStation = m_pStationList[i];
        if(wStationID == pStation->getNo())
            return pStation;
    }
    return NULL;
}

//厂站地址获取厂站
HStation* HGraphEditorDoc::getRtu(quint16 wStationAddress)
{
    for(int i = 0; i < m_pStationList.count();i++)
    {
        HStation* pStation = m_pStationList[i];
        if(wStationAddress == pStation->getAddress())
            return pStation;
    }
    return NULL;
}

//索引厂站
HStation* HGraphEditorDoc::findStation(int nIndex)
{
    return m_pStationList.value(nIndex);
}

//加载模板信息
void HGraphEditorDoc::loadIconTemplate()
{
    HGraphHelper::Instance()->loadIconTemplate(&m_pIconTemplateList);
}

//寻找模板
HIconTemplate* HGraphEditorDoc::findIconTemplate(const QString &uuid)
{
    for(int i = 0; i < m_pIconTemplateList.count();i++)
    {
        HIconTemplate* iconTemplate = (HIconTemplate*)m_pIconTemplateList[i];
        if(iconTemplate->getUuid().toString() == uuid)
            return iconTemplate;
    }
    return NULL;
}

//加载画面信息
void HGraphEditorDoc::loadAllGraph()
{
    HGraphHelper::Instance()->loadAllGraph(&m_pGraphList);

    //加载完画面之后需要更新每一个画面里面的图元控件
    updateGraphList();

}

//更新所有画面里面的模板信息
void HGraphEditorDoc::updateGraphList()
{
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
                if(pObj->getShapeType() == Icon)
                {
                    HIconObj* pObj1 = (HIconObj*)pObj;//
                    if(!pObj1->iconTemplate()->getUuid().toString().compare(findTemp->getUuid().toString()))
                    {
                        findTemp->getSymbol()->copyTo(pObj1->iconSymbol());
                        pObj1->update();
                    }
                }
            }
        }
    }
}

void HGraphEditorDoc::saveAllGraph()
{
    HGraphHelper::Instance()->saveAllGraph(&m_pGraphList,getCurGraph());
}

void HGraphEditorDoc::saveCurGraph()
{
    if(!m_pCurGraph)
    {
        return;
    }
    HGraph* graph = findGraph(m_pCurGraph->graphID());
    if(!graph)
        return;
    m_pCurGraph->copyTo(graph);
    HGraphHelper::Instance()->saveGraph(graph);
}

int HGraphEditorDoc::importGraph(const QString& name)
{
    //HMakeIcon::Instance()->setGraph(0);  --huangw 确定要还是不要
    char szGraphPath[128];
    getDataFilePath(DFPATH_GRAPH,szGraphPath);
    QString graphsPath = QString(szGraphPath);
    //需要判一下 这个文件是否已经在graph里面了
    bool bFind = false;
    QString strNewFile = name;
    QFileInfo graphInfo(name);
    QString strGraphName = graphInfo.fileName();
    QString strFolderPath = name.left(name.lastIndexOf('/',-(strGraphName.length()+1)));
    strFolderPath = strFolderPath.left(strFolderPath.lastIndexOf('/',-1));
    if(QDir::toNativeSeparators(strFolderPath).compare(QDir::toNativeSeparators(graphsPath)) == 0)
        bFind = true;
    QString strFolder;
    if(!bFind)
    {
        strFolder = name.section('/',-2,-2);

        //搜索是否有重名的文件夹
        int nCount = 0;
        QDir graphsDir(graphsPath);
        QFileInfoList graphFolderList = graphsDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
        foreach(QFileInfo info,graphFolderList)
        {
            if(info.isFile())continue;
            if(info.fileName().contains(strFolder))
                nCount++;
        }

        if(!QDir(strFolder).exists())
        {   if(nCount > 0)
            {
                strFolder = strFolder + QString("_%2").arg(nCount);
            }
            if(!graphsDir.mkdir(strFolder))
                return (int)-1;
        }
        //将源文件拷贝过来 如果失败了，还需要删除文件夹
        strNewFile = graphsPath + "/" + strFolder + "/0.grf";
        if(!QFile::copy(name,strNewFile))
            return false;
    }
    HGraph* pGraph = new HGraph("");
    if(!pGraph)
        return (int)-1;
    if(!pGraph->readXmlFile(strNewFile))
    {
        delete pGraph;
        pGraph = NULL;
        return (int)-1;
    }
    if(pGraph->getGraphName().compare(strFolder) != 0)
        pGraph->setGraphName(strFolder);
    //在里面寻找graphID 如果找到了，graphID就要更改了
    if(findGraph(pGraph->graphID()))
        pGraph->setGraphID(getGraphID());
    pGraph->writeXmlFile(strNewFile);//更新完要写进去
    m_pGraphList.append(pGraph);

    return pGraph->graphID();
}

//获取一个新graph的ID
int HGraphEditorDoc::getGraphID()
{
    int nID = 0;
    while(findGraph(nID)!=NULL)
        nID++;
    return nID;
}

//按照ID查找画面
HGraph* HGraphEditorDoc::findGraph(int graphID)
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

HGraph* HGraphEditorDoc::findGraph(const QString& graphName)
{
    HGraph *graph = NULL;
    QList<HGraph*>::Iterator graphIterator;
    for(graphIterator = m_pGraphList.begin();graphIterator != m_pGraphList.end();graphIterator++)
    {
        graph = *graphIterator;
        if(graph->getGraphName() == graphName)
            return graph;
    }
    return NULL;
}

//新建画面
HGraph* HGraphEditorDoc::addGraph(const QString& name)
{
    if(!m_pGraphEditorMgr) return NULL;
    if(m_pCurGraph)
    {
        m_pCurGraph->clear();
        delete m_pCurGraph;
        m_pCurGraph = NULL;
    }
    HGraph* newGraph = new HGraph(name);
    newGraph->setGraphID(getGraphID());
    newGraph->m_height = m_pGraphEditorMgr->getLogicRect().height();
    newGraph->m_width = m_pGraphEditorMgr->getLogicRect().width();
    m_pGraphList.append(newGraph);

    m_pCurGraph = new HGraph("tempGraph");
    newGraph->copyTo(m_pCurGraph);
    HMakeIcon::Instance()->setGraph(m_pCurGraph);
    m_bGraphValid = true;
    return newGraph;
}

//删除画面(名字可以唯一，但内部采用id)
bool HGraphEditorDoc::delGraph(const QString& name,const int id)
{
    HGraph* graph = findGraph(id);
    if(!graph)
        return false;
    m_pGraphList.removeOne(graph);
    delete graph;
    graph = NULL;

    if(m_pCurGraph)
    {
        delete m_pCurGraph;
        m_pCurGraph = NULL;
    }
    HMakeIcon::Instance()->setGraph(0);
    m_bGraphValid = false;
    return true;
}

//打开画面
bool HGraphEditorDoc::openGraph(const QString& name,const int id)
{
    HGraph* graph = findGraph(id);
    if(!graph)
        return false;

    if(m_pCurGraph)
    {
        if(m_pCurGraph->graphID() == graph->graphID())
            return true;
        m_pCurGraph->clear();
        delete m_pCurGraph;
        m_pCurGraph = NULL;
    }

    m_pCurGraph = new HGraph("tempGraph");
    if(!m_pCurGraph) return false;
    graph->copyTo(m_pCurGraph);
    HMakeIcon::Instance()->setGraph(m_pCurGraph);
    m_bGraphValid = true;
    return true;
}

//拷贝画面
void HGraphEditorDoc::copyGraph(HGraph* graph)
{

}

HGraph* HGraphEditorDoc::getCurGraph()
{
    return m_pCurGraph;
}

QList<HIconTemplate*> HGraphEditorDoc::getIconTemplateList()
{
    return m_pIconTemplateList;
}

QList<HGraph*> HGraphEditorDoc::getGraphList()
{
    return m_pGraphList;
}

//判断graph文件是否修改
bool HGraphEditorDoc::isGraphModify()
{
    //只需要判断当前画面是否存在修改
    if(!m_pCurGraph)
        return false;
    //return m_pCurGraph->odify();
    return false;
}
