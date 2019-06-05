#include "hiconobj.h"
#include "hicontemplate.h"
#include "hiconsymbol.h"
#include "hdynamicobj.h"
#include "hbaseobj.h"
#include "hiconshowpattern.h"
#include "htext.h"
#include "hmakeicon.h"
HIconObj::HIconObj()
{
    setShapeType(Icon);
    //去掉本身所有的边框颜色设置，这些都是不需要的
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
    m_pDynamicObj = NULL;
    m_pIconSymbol = new HIconSymbol(it);
    m_pIconSymbol->setParent(this);
    //initIconTemplate();
    //bFrameSee = false;
    nGraphID = (int)-1;
    btGraphOperator = MODE_OPEN_GRAPH;
    btGraphComfirm = COMFIRM_MODE_GRAPH;
    initIconTemplate();

}

HIconObj::~HIconObj()
{
    clearDynamicData();
    if(iconSymbol())
    {
        delete m_pIconSymbol;
        m_pIconSymbol = NULL;
    }
    m_pIconTemplate = NULL;
}

void HIconObj::initIconTemplate()
{
    strCatalogName = iconTemplate()->getCatalogName();
    nCatalogType = iconTemplate()->getCatalogType();
    strUuid = iconTemplate()->getUuid().toString();

    //本地从图符模板库中拷贝
    iconTemplate()->getSymbol()->copyTo(iconSymbol());
    iconSymbol()->setParent(this);
    iconSymbol()->setOX(0.0);
    iconSymbol()->setOY(0.0);
}

void HIconObj::readData(int v, QDataStream* data)
{
    if(!data) return;
    HBaseObj::readData(v,data);
    if(iconSymbol())
    {
        iconSymbol()->HShapeObj::readData(v,data);
    }

    qint8 n8;
    *data>>n8;
    if(n8)
    {
        HText* text = firstText();
        if(text)
        {
            text->readData(v,data);
        }
        else
        {
            text = (HText*)HMakeIcon::Instance()->newObj(Text);
            text->readData(v,data);
            delete text;
            text = NULL;
        }
    }

    if(dynamicObj())
    {
        clearDynamicData();
        dynamicObj()->readData(v,data);
    }
}

void HIconObj::writeData(int v, QDataStream* data)
{
    if(!data) return;
    HBaseObj::writeData(v,data);
    /*
    QString strCatalogName;//目录名字
    int nCatalogType;//类型
    QString strUuid;//uuid
    int nGraphID;
    uchar btGraphOperator;
    uchar btGraphComfirm;
    */
    if(iconSymbol())
    {
        iconSymbol()->HShapeObj::writeData(v,data);
        qint8 n8 = 0;
        HText* text = firstText();
        if(text)
        {
            n8 = 1;
            *data<<n8;
            text->writeData(v,data);
        }
        else
        {
            *data<<n8;
        }
    }

    if (dynamicObj())
    {
        dynamicObj()->writeData(v,data);
    }
}

void HIconObj::readXml(int v, QDomElement* dom)
{
    if(!dom) return;
    HBaseObj::readXml(v,dom);
    QDomElement symbolDom = dom->namedItem("IconSymbol").toElement();
    if(!symbolDom.isNull())
    {
        iconSymbol()->HShapeObj::readXml(v,&symbolDom);
        update();
    }
    
    HText* pText = firstText();
    if(!pText)
    {
        QDomElement textDom = dom->namedItem(pText->tagName()).toElement();
        if(!textDom.isNull())
        {
            pText->readXml(v,&textDom);
        }
    }

    QDomElement RelationDom = dom->namedItem("Relation").toElement();
    if (dynamicObj())
    {
        clearDynamicData();
        dynamicObj()->readXml(v,&RelationDom);
    }
}

void HIconObj::writeXml(int v, QDomElement* dom)
{
    if(!dom)return;
    HBaseObj::writeXml(v,dom);  
    QDomElement symbolDom = dom->ownerDocument().createElement("IconSymbol");
    dom->appendChild(symbolDom);
    if(iconSymbol())
    {
        iconSymbol()->HShapeObj::writeXml(v,&symbolDom);
    }
    HText* pText = firstText();
    if(pText)
    {
        QDomElement childEle = dom->ownerDocument().createElement(pText->tagName());
        dom->appendChild(childEle);
        pText->writeXml(v,&childEle);
    }

    QDomElement RelationDom = dom->ownerDocument().createElement("Relation");
    dom->appendChild(RelationDom);
    if (dynamicObj())
    {
        dynamicObj()->writeXml(v,&RelationDom);
    }
}

QString HIconObj::tagName()
{
    return "Icon";
}

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

HText* HIconObj::firstText()
{
    if(iconSymbol())
        return iconSymbol()->getFirstTextObj();
    return NULL;
}
