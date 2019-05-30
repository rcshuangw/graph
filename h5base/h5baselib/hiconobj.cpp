#include "hiconobj.h"
#include "hiconshowpattern.h"
/*************************************图符类**********************************/
/*
 * 图符类只用于drawgrph和在线系统上面，所以保存的信息和基本图元是不一致的。
*/
HIconObj::HIconObj()
{
    setShapeType(Icon);
    //去掉本身所有的边框颜色设置，这些都是不需要的
    pText = NULL;
    m_pDynamicObj = new HDynamicObj;
    //bFrameSee = false;
    nGraphID = (int)-1;
    btGraphOperator = MODE_OPEN_GRAPH;
    btGraphComfirm = COMFIRM_MODE_GRAPH;
}

HIconObj::HIconObj(HIconTemplate* it)
    :m_pIconTemplate(it)
{
    setShapeType(Icon);
    pText = NULL;
    m_pDynamicObj = new HDynamicObj;
    m_pIconSymbol = new HIconSymbol(it);
    m_pIconSymbol->setParent(this);
    //initIconTemplate();
    //bFrameSee = false;
    nGraphID = (int)-1;
    btGraphOperator = MODE_OPEN_GRAPH;
    btGraphComfirm = COMFIRM_MODE_GRAPH;

}

HIconObj::~HIconObj()
{
    clearDynamicData();

    if(iconSymbol())
    {
        delete m_pIconSymbol;
        m_pIconSymbol = NULL;
    }
    
	/*
    if(pText)
    {
        delete pText;
        pText = NULL;
    }*/
    m_pIconTemplate = NULL;
}

void HIconObj::initIconTemplate()
{
    strCatalogName = iconTemplate()->getCatalogName();
    nCatalogType = iconTemplate()->getCatalogType();
    strUuid = iconTemplate()->getUuid().toString();
    iconTemplate()->getSymbol()->copyTo(iconSymbol());
    iconSymbol()->setParent(this);
    iconSymbol()->m_width = 0.0;
    iconSymbol()->m_height = 0.0;
    /*
	if(TEMPLATE_TYPE_ANALOGUE == nCatalogType || TEMPLATE_TYPE_CONTROL == nCatalogType)
    {
        HText *pTemp = pIconSymbol->getFirstTextObj();
        if(!pText)
        {
            pText = new HText();
            pTemp->copyTo(pText);
        }
    }*/
}

//二进制读写
void HIconObj::readData(int v, QDataStream* data)
{
    if(!data) return;
    HBaseObj::readData(v,data);
    /*
    QString s;
    *data>>s;
    strCatalogName = s;
    int n;
    *data>>n;
    nCatalogType = n;
    *data>>s;
    strUuid = s;
    *data>>n;
    nGraphID = n;
    uchar bt;
    *data>>bt;
    btGraphOperator = bt;
    *data>>bt;
    btGraphComfirm = bt;*/

    if(iconSymbol())
    {
        iconSymbol()->HShapeObj::readData(v,data);
        /*
		if(TEMPLATE_TYPE_ANALOGUE == nCatalogType || TEMPLATE_TYPE_CONTROL == nCatalogType)
        {
            HText *pText = pIconSymbol->getFirstTextObj();
            pText->readData(data);
        }*/
    }
    //动态数据
    /*
	if (dynamicObj())
	{
        dynamicObj()->readData(v,data);
    }*/
}

void HIconObj::writeData(int v, QDataStream* data)
{
    if(!data) return;
    HBaseObj::writeData(v,data);
    *data<<strCatalogName;
    *data<<nCatalogType;
    *data<<strUuid;
    *data<<nGraphID;
    *data<<btGraphOperator;
    *data<<btGraphComfirm;

    if(iconSymbol())
    {
        iconSymbol()->HShapeObj::writeData(v,data);
        /*
		if(TEMPLATE_TYPE_ANALOGUE == nCatalogType || TEMPLATE_TYPE_CONTROL == nCatalogType)
        {
            HText *pText = pIconSymbol->getFirstTextObj();
            pText->writeData(data);
        }*/
    }

    //动态数据
    /*
	if (dynamicObj())
	{
        dynamicObj()->writeData(v,data);
    }*/
}

//xml文件读写
void HIconObj::readXml(int v, QDomElement* dom)
{
    if(!dom) return;
    HBaseObj::readXml(v,dom);
    /*
    strCatalogName = dom->attribute("CatalogName");
    nCatalogType = dom->attribute("CatalogType").toInt();
    strUuid = dom->attribute("Uuid");
    nGraphID = dom->attribute("graphID").toInt();
    btGraphOperator = dom->attribute("graphOperator").toUInt();
    btGraphComfirm = dom->attribute("graphComfirm").toUInt();
    */
    //先读，在从Template里面刷新
    QDomElement symbolDom = dom->namedItem("IconSymbol").toElement();
    if(!symbolDom.isNull())
    {
        iconSymbol()->HShapeObj::readXml(v,&symbolDom);
        update();
    }
    
	/*
    //如果是遥测类型或者控制点类型 还需要保存first text信息
    if(TEMPLATE_TYPE_ANALOGUE == nCatalogType || TEMPLATE_TYPE_CONTROL == nCatalogType)
    {
        pText = new HText();
        if(pText)
        {
            QDomElement textDom = dom->namedItem(pText->tagName()).toElement();
            if(!textDom.isNull())
            {
                pText->readXml(&textDom);
            }
            else
            {
                delete pText;
                pText = NULL;
            }
        }
    }*/

    //动态数据
    /*
    QDomElement RelationDom = dom->namedItem("Relation").toElement();
	if (dynamicObj())
	{
        dynamicObj()->readXml(v,&RelationDom);
    }*/
}

void HIconObj::writeXml(int v, QDomElement* dom)
{
    if(!dom)return;
    HBaseObj::writeXml(v,dom);
    /*
    dom->setAttribute("CatalogName",strCatalogName);
    dom->setAttribute("CatalogType",nCatalogType);
    dom->setAttribute("Uuid",strUuid);
    dom->setAttribute("graphID",nGraphID);
    dom->setAttribute("graphOperator",btGraphOperator);
    dom->setAttribute("graphComfirm",btGraphComfirm);
    */

   
    QDomElement symbolDom = dom->ownerDocument().createElement("IconSymbol");
    dom->appendChild(symbolDom);
    if(iconSymbol())
    {
        iconSymbol()->HShapeObj::writeXml(v,&symbolDom);
    } /*
    //如果是遥测类型或者控制点类型 还需要保存first text信息
    if(TEMPLATE_TYPE_ANALOGUE == nCatalogType || TEMPLATE_TYPE_CONTROL == nCatalogType)
    {
        if(pText)
        {
            QDomElement childEle = dom->ownerDocument().createElement(pText->tagName());
            dom->appendChild(childEle);
            pText->writeXml(&childEle);
        }
    }*/

    //动态数据 放到测点Icon里面
    /*
    QDomElement RelationDom = dom->ownerDocument().createElement("Relation");
    dom->appendChild(RelationDom);
	if (dynamicObj())
	{
        dynamicObj()->writeXml(v,&RelationDom);
    }*/
}


QString HIconObj::tagName()
{
    return "Icon";
}

//拷贝克隆
void HIconObj::copyTo(HBaseObj* obj)
{
    HIconObj* ob = (HIconObj*)obj;
    QByteArray ba;
    QDataStream dsm(&ba,QIODevice::ReadWrite);
    int ver = 0;
    writeData(ver,&dsm);
    dsm.device()->seek(0);
    ob->setParent(parent());
    ob->readData(ver,&dsm);
}

bool HIconObj::setPointList(QPolygonF& list, qint8 flag)
{
	HBaseObj::setPointList(list, flag);

	QRectF rectF = list.boundingRect();
	resize(rectF.width(), rectF.height());
	return true;
}

QPolygonF HIconObj::getPointList(qint8 flag )
{
	double w = iconSymbol()->m_width;
	double h = iconSymbol()->m_height;
    QPointF po(-w/2, -h/2);
	QRectF rect(po, QSizeF(w, h));
	QPolygonF list;
	if (qFuzzyCompare(w, 0) || qFuzzyCompare(h, 0))
	{
		return list;
	}
	list.append(rect.topLeft());
	list.append(rect.topRight());
	list.append(rect.bottomRight());
	list.append(rect.bottomLeft());
	maps(list, flag);
	return list;
}

DrawShape HIconObj::getShapeType()
{
    return DrawShape::Icon;
}


void HIconObj::resize(double w, double h, bool bscale)
{
    iconSymbol()->resize(w, h, bscale);
}

void HIconObj::move(double dx, double dy, bool bscale)
{
	HBaseObj::move(dx, dy,bscale);
}

void HIconObj::moveBy(double dx,double dy, bool bscale)
{
	HBaseObj::moveBy(dx, dy,bscale);
}

QRectF HIconObj::boundingRect(qint8 flag )
{
    return HBaseObj::boundingRect(flag);
}

QPainterPath HIconObj::shape(qint8 flag)
{
    QPainterPath path;
    QPolygonF polygon = getPointList(flag);
    path.addPolygon(polygon);
	path.closeSubpath();
    return path;
}

void HIconObj::paint(QPainter* painter)
{
	painter->save();
	iconSymbol()->paint(painter);
	painter->restore();
}


void HIconObj::setUuid(const QString& uuid)
{
    this->strUuid = uuid;
}

QString HIconObj::getUuid()
{
    return strUuid;
}

void HIconObj::setCatalogName(const QString& catalogName)
{
    strCatalogName = catalogName;
}

QString HIconObj::getCatalogName()
{
    return strCatalogName;
}

void HIconObj::setObjType( uchar catalogType)
{
    nCatalogType = catalogType;
}

int HIconObj::getObjType()
{
    return nCatalogType;
}

void HIconObj::setSymbolName(const QString& symbolName)
{
    //strSymbolName = symbolName;
   // if(iconSymbol())
	//	iconSymbol()->setSymbolName(symbolName);
}

QString HIconObj::getSymbolName()
{
   // if(iconSymbol())
	//	iconSymbol()->getSymolName();
    return "";
}

void HIconObj::setSymbolType(int symbolType)
{
    //if(pIconSymbol)
     //   pIconSymbol->setSymbolType(symbolType);
}

int HIconObj::getSymbolType()
{
    //if(pIconSymbol)
     //  return pIconSymbol->getSymbolType();
    return (int)-1;
}

void HIconObj::setGraphID(int graphID)
{
    nGraphID = graphID;
}

int HIconObj::getGraphID()
{
    return nGraphID;
}

void HIconObj::setGraphOperator(uchar graphOperator)
{
    btGraphOperator = graphOperator;
}

uchar HIconObj::getGraphOpeartor()
{
    return btGraphOperator;
}

void HIconObj::setGraphComfirm(uchar graphComfirm)
{
    btGraphComfirm = graphComfirm;
}

uchar HIconObj::getGraphComfirm()
{
    return btGraphComfirm;
}

void HIconObj::setIconTemplate(HIconTemplate* t)
{
    m_pIconTemplate = t;
    if(!m_pIconSymbol)
    {
        m_pIconSymbol = new HIconSymbol(t);
        initIconTemplate();
    }
}

HIconTemplate* HIconObj::iconTemplate()
{
    return m_pIconTemplate;
}

HIconSymbol* HIconObj::iconSymbol()
{
    return m_pIconSymbol;
}

HDynamicObj* HIconObj::dynamicObj()
{
    return m_pDynamicObj;
}

void HIconObj::initDynamicData()
{
    clearDynamicData();
}

void HIconObj::clearDynamicData()
{
    if(dynamicObj())
    {
        delete m_pDynamicObj;
        m_pDynamicObj = NULL;
    }
}

void HIconObj::update()
{
    if(!iconSymbol())
        return;
	int w = iconSymbol()->m_width;
	int h = iconSymbol()->m_height;
	initIconTemplate();
    iconSymbol()->resize(w, h);
    iconSymbol()->setParent(this);
}
