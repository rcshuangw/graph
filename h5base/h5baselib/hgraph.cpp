#include "hgraph.h"
#include <QFile>
#include <QTextStream>
#include <QDomDocument>
#include <QDomElement>
#include <QTextCodec>

HGraph::HGraph(const QString& name)
    :sName(name)
{
    nGraphID = 0;
    nGraphWidth = 1000;
    nGraphHeight = 1000;
    nRefreshInterval = 3000;
    strFillColor = "#000000";
    bModify = false;
    bStart = false;
    btType = 0;
    nGraphID = (int)-1;
}

HGraph::~HGraph()
{

}


void HGraph::setGraphName(const QString& name)
{
    sName = name;
}

QString HGraph::getGraphName()
{
    return sName;
}

void HGraph::setGraphID(int id)
{
    nGraphID = id;
}

//获取ID
int HGraph::getGraphID()
{
    return nGraphID;
}

void HGraph::setGraphWidth(int width)
{
    nGraphWidth = width;
}

int HGraph::getGraphWidth()
{
    return nGraphWidth;
}

void HGraph::setGraphHeight(int height)
{
    nGraphHeight = height;
}

int HGraph::getGraphHeight()
{
    return nGraphHeight;
}

void HGraph::setFillColor(const QString& clr)
{
    strFillColor = clr;
}

QString HGraph::getFillColor()
{
    return strFillColor;
}

void HGraph::setFillPicture(const QString& strPic)
{
    strFillPicture = strPic;
}

QString HGraph::getFillPicture()
{
    return strFillPicture;
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
        pIconTemplate->readXml(&e);
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
        iconTemplate->writeXml(&tempDom);
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
    setFillColor("");
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
void HGraph::addObj(HBaseObj* pObj)
{

}

void HGraph::takeObj(HBaseObj* pObj)
{

}

void HGraph::removeObj(HBaseObj *pObj)
{

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

void HGraph::addIconTemplate(HIconTemplate* temp)
{
    if(!temp)
        return;
    if(NULL == findIconTemplate(temp->getUuid()))
        pIconTemplateList.append(temp);
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

}

QPainterPath HGraph::shape(qint8 flag)
{

}
