#include "hgraph.h"
#include <QFile>
#include <QTextStream>
#include <QDomDocument>
#include <QDomElement>
#include <QTextCodec>
#include "hiconobj.h"
#include "hgroup.h"
#include "hnormalobj.h"
#include "hmakeicon.h"
#include "hgraph.h"
HGraph::HGraph(const QString& name)
    :m_strGraphName(name)
{
    nRefreshInterval = 3000;
    bStart = false;
    btType = 0;
    setFillColorName("#000000");
    m_width = 1000;
    m_height = 1000;
    setOX(0);
    setOY(0);
    setFrameSee(false);
}

HGraph::~HGraph()
{

}

void HGraph::setGraphID(int id)
{
    m_nID = id;
}

int HGraph::graphID()
{
    return m_nID;
}

void HGraph::setGraphName(const QString& name)
{
    m_strGraphName = name;
}

QString HGraph::getGraphName()
{
    return m_strGraphName;
}

void HGraph::setRefreshInterval(int val)
{
    nRefreshInterval = val;
}

int HGraph::getRefreshInterval()
{
    return nRefreshInterval;
}

void HGraph::setStartFlag(bool start)
{
    bStart = start;
}

bool HGraph::getStartFlag()
{
    return bStart;
}

void HGraph::setGraphType(ushort type)
{
    btType = type;
}

ushort HGraph::getGraphType()
{
    return btType;
}

QString HGraph::getStationName()
{
    return "";
}

//画面文件需要同时保存到二进制文件和xml文件?
void HGraph::readDataFile(const QString&)
{

}

 void HGraph::writeDateFile(const QString&)
{

}

void HGraph::readData(int v,QDataStream *d)
{
    if(!d)
        return;

    //画面属性
    int n;
    nRefreshInterval = n;

    //模板
    *d>>n;
    int nCount = n;

    QString s;
    clearIconTemplate();
    for(int i = 0; i < nCount;i++)
    {
        *d>>s;
        QUuid uuid(s);
        HIconTemplate* iconTemplate = new HIconTemplate(uuid);
        if(iconTemplate){
            iconTemplate->readData(v,d);
            addIconTemplate(iconTemplate);
        }
    }

    //画面里对象
    HContainerObj::readData(v,d);
}

void HGraph::writeData(int v,QDataStream *d)
{
    if(!d)
        return;
    *d<<nRefreshInterval;

    *d<<pIconTemplateList.count();
    for(int i = 0; i < pIconTemplateList.count();i++)
    {
        HIconTemplate* iconTemplate = (HIconTemplate*)pIconTemplateList[i];
        QString struuid;
        if(!iconTemplate)
        {
            continue;
        }
        struuid = iconTemplate->getUuid().toString();
        *d<<struuid;
        iconTemplate->writeData(v,d);
    }

    HContainerObj::writeData(v,d);
}

 //先打开文件
bool HGraph::readXmlFile(const QString& fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
        return false;
    QTextStream dsm(&file);
    QDomDocument doc;
    dsm.setCodec("GB2312");
    QString errorString;
    int errorLine;
    int errorColumn;
    if(!doc.setContent(&file,false,&errorString,&errorLine,&errorColumn))
    {
        file.close();
        return false;
    }
    QDomElement root = doc.documentElement();
    if(root.isNull())
        return false;
    readXml(0,&root);
    file.close();
    return true;
}

//读具体的信息
void HGraph::readXml(int v,QDomElement *d)
{
  //分为本身属性，模板部分，动态数据部分
    if(!d)
        return;
    nRefreshInterval = d->attribute("RefreshInterval").toInt();

    //读取模板信息
    clearIconTemplate();
    QDomElement templateDom = d->namedItem("IconTemplates").toElement();
    QDomNode n = templateDom.firstChild();
    for(int i = 0;!n.isNull();n=n.nextSibling(),i++)
    {
        QDomElement e = n.toElement();
        QUuid uuid = QUuid(e.attribute("Uuid"));
        HIconTemplate *pIconTemplate = new HIconTemplate(uuid);//需要定义一个不带uuid的参数
        if(!pIconTemplate) continue;
        pIconTemplate->readXml(v,&e);
        addIconTemplate(pIconTemplate);
    }

    HContainerObj::readXml(v,d);

}

bool HGraph::writeXmlFile(const QString& fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
        return false;
    QTextStream dsm(&file);
    QDomDocument doc;
    QTextCodec* c = QTextCodec::codecForLocale();
    QString strLocal = QString("version=\"1.0\" encoding=\"GB2312\"");
    QDomProcessingInstruction instruct = doc.createProcessingInstruction("xml",strLocal);
    doc.appendChild(instruct);
    QDomElement root = doc.createElement("Graph");
    if(root.isNull())
        return false;
    doc.appendChild(root);
    writeXml(0,&root);
    dsm.setCodec("GB2312");
    doc.save(dsm,1);
    file.close();
    return true;
}

void HGraph::writeXml(int v,QDomElement *d)
{
    if(!d)
        return;
    d->setAttribute("RefreshInterval",nRefreshInterval);

    //再创建模板的xml结构
    QDomElement templateDom = d->ownerDocument().createElement("IconTemplates");
    d->appendChild(templateDom);
    for(int i = 0; i < pIconTemplateList.count();i++)
    {
        HIconTemplate* iconTemplate = (HIconTemplate*)pIconTemplateList[i];
        if(!iconTemplate) continue;
        QDomElement tempDom = templateDom.ownerDocument().createElement("IconTemplate");
        templateDom.appendChild(tempDom);
        iconTemplate->writeXml(v,&tempDom);
    }

    HContainerObj::writeXml(v,d);
}

QString HGraph::tagName()
{
    return "Graph";
}

void HGraph::copyTo(HBaseObj* ob)
{
    if(!ob) return;
    HGraph* graph = (HGraph*)ob;
    HContainerObj::copyTo(graph);
    graph->nRefreshInterval = nRefreshInterval;
}

void HGraph::clear()
{
    setBkImagePath("");
    HContainerObj::clear();
    clearIconTemplate();
    m_width = 1000;
    m_height = 1000;
    setOX(0.0);
    setOY(0.0);
    m_bFrameSee = false;
    m_strGraphName = QStringLiteral("新画面");
    m_fZoomScale = 1.0;

}

HBaseObj* HGraph::createBaseObj(DrawShape s, HIconTemplate* icontemplate)
{
    HBaseObj* pObj = NULL;
    if(s == Icon)
    {
        if(!icontemplate)
            return NULL;
        HIconTemplate* pTemplate = new HIconTemplate("");
        icontemplate->copyTo(pTemplate);
        //addIconTemplate(pTemplate);

        HIconObj* obj = new HIconObj(pTemplate);
        HIconObj* pIconObj = (HIconObj*)obj;
        pIconObj->initIconTemplate();
        pIconObj->iconSymbol()->setCurrentPattern(0);
        pObj = (HBaseObj*)obj;
    }
    else if(s == Normal)
    {
        if(!icontemplate)
            return NULL;
        HIconTemplate* pTemplate = new HIconTemplate("");
        icontemplate->copyTo(pTemplate);
        //addIconTemplate(pTemplate);

        HNormalObj* obj = new HNormalObj(pTemplate);
        HNormalObj* pIconObj = (HNormalObj*)obj;
        pIconObj->initIconTemplate();
        pIconObj->iconSymbol()->setCurrentPattern(0);
        pObj = (HBaseObj*)obj;
    }
    else
    {
        pObj = HMakeIcon::Instance()->newObj(s);
    }
    pObj->setShapeType((DrawShape)s);
    if(pObj)
    {
        int objID = getObjID();
        pObj->setObjID(objID);
    }

    return pObj;
}

void HGraph::addIconObj(HBaseObj* pObj)
{
    if(!pObj) return;

    addObj(pObj);

    //如果是iconsymbol就要修正对应模板
    if(pObj->getShapeType() == Icon)
    {
        HIconObj* io = (HIconObj*)pObj;
        HIconTemplate* it = io->iconTemplate();
        if(it)
        {
            HIconTemplate*itt = addIconTemplate(it);
            if(itt!=it)
            {
                io->setIconTemplate(itt);
                if(it){
                    delete it;
                    it = NULL;
                }
            }
        }
    }
    else if(pObj->getShapeType() == Normal)
    {
        HNormalObj* io = (HNormalObj*)pObj;
        HIconTemplate* it = io->iconTemplate();
        if(it)
        {
            HIconTemplate*itt = addIconTemplate(it);
            if(itt!=it)
            {
                io->setIconTemplate(itt);
                if(it){
                    delete it;
                    it = NULL;
                }
            }
        }
    }


    //group里面有iconsymbol
    if(pObj->getShapeType() == Group)
    {
        HContainerObj* co = (HContainerObj*)pObj;
        int sz = co->getObjList().size();
        for(int i = 0; i < sz;i++)
        {
            HBaseObj* bo = (HBaseObj*)co->getObjList().at(i);
            if(bo && bo->getShapeType() == Icon)
            {
                HIconObj* io = (HIconObj*)bo;
                HIconTemplate* it = io->iconTemplate();
                if(it)
                {
                    HIconTemplate*itt = addIconTemplate(it);
                    if(itt!=it)
                    {
                        io->setIconTemplate(itt);
                    }
                }
            }
        }
    }
}

void HGraph::takeIconObj(HBaseObj* pObj)
{
    if(!pObj) return;
    removeObj(pObj);
}

void HGraph::removeIconObj(HBaseObj *pObj)
{
    if(!pObj) return;
    removeObj(pObj);
    delete pObj;
    pObj = NULL;
}

//获取ObjID
int HGraph::getObjID()
{
    int nObjID = 1;
    while(findObjID(nObjID))
        nObjID++;
    return nObjID;
}

bool HGraph::findObjID(int nObjID)
{
    //这里要修改，有obj存在group等组合图形里面，不在getObjList()里面--huangw
    for(int i = 0;i < getObjList().count();i++)
    {
        HBaseObj* pObj = (HBaseObj*)getObjList().at(i);
       if(pObj)
       {
           if(pObj->getShapeType() == Group)
           {
               HGroup* pGroup = (HGroup*)pObj;
               //两个group组合到一起还是一个group包含所有对象，而不是一个group包含两个group,所以此处不必递归查找
               for(int j = 0; j < pGroup->getObjList().size();i++)
               {
                   HBaseObj* obj = pGroup->at(i);
                   if(obj && obj->getObjID() == nObjID)
                       return true;
               }
           }
           else
           {
               if(pObj->getObjID() == nObjID)
                   return true;
           }
       }
    }
    return false;
}

//模板部分
int HGraph::iconTemplateNum()
{
    return pIconTemplateList.count();
}

HIconTemplate* HGraph::IconTemplateAt(int index)
{
    return pIconTemplateList[index];
}

HIconTemplate* HGraph::findIconTemplate(const QUuid& uid)
{
    QString struuid = uid.toString();
    for(int i = 0; i < pIconTemplateList.count();i++)
    {
        HIconTemplate* iconTemplate = (HIconTemplate*)pIconTemplateList[i];
        if(iconTemplate->getUuid() == struuid)
            return iconTemplate;
    }
    return NULL;
}

HIconTemplate* HGraph::addIconTemplate(HIconTemplate* temp,bool bCopy)
{
    if(!temp)
        return NULL;
    HIconTemplate* it = findIconTemplate(temp->getUuid());
    if(!it){
        it = new HIconTemplate(temp->getUuid());
        if(pIconTemplateList.indexOf(it) < 0){
            temp->copyTo(it);
            pIconTemplateList.append(it);
        }
    }
    else if(bCopy)
    {
        temp->copyTo(it);
    }
    return it;
}

void HGraph::removeIconTemplate(HIconTemplate* temp)
{
    if(!temp)return;
    pIconTemplateList.removeAt(pIconTemplateList.indexOf(temp));
}

void HGraph::clearIconTemplate()
{
    while(!pIconTemplateList.isEmpty())
        delete pIconTemplateList.takeFirst();
    pIconTemplateList.clear();
}

void HGraph::resetIconTemplate()
{
    clearIconTemplate();
}

void HGraph::paint(QPainter* painter)
{

}

QRectF HGraph::boundingRect(qint8 flag)
{
    return QRectF();
}

QPainterPath HGraph::shape(qint8 flag)
{
    return QPainterPath();
}
