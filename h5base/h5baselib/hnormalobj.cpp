#include "hnormalobj.h"
#include "hicontemplate.h"
#include "hiconsymbol.h"
#include "hdynamicobj.h"
#include "hbaseobj.h"
#include "hiconshowpattern.h"
#include "htext.h"
#include "hmakeicon.h"
HNormalObj::HNormalObj()
{
    setShapeType(Normal);
    nGraphID = (int)-1;

}

HNormalObj::HNormalObj(HIconTemplate* it)
    :m_pIconTemplate(it)
{
    setShapeType(Normal);
    m_pIconSymbol = new HIconSymbol(it);
    m_pIconSymbol->setParent(this);
    nGraphID = (int)-1;
    initIconTemplate();
}

HNormalObj::~HNormalObj()
{
    if(iconSymbol())
    {
        delete m_pIconSymbol;
        m_pIconSymbol = NULL;
    }
    m_pIconTemplate = NULL;
}

void HNormalObj::initIconTemplate()
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

void HNormalObj::readData(int v, QDataStream* data)
{
    if(!data) return;
    HBaseObj::readData(v,data);
    if(iconSymbol())
    {
        iconSymbol()->HShapeObj::readData(v,data);
    }

}

void HNormalObj::writeData(int v, QDataStream* data)
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
    }
}

void HNormalObj::readXml(int v, QDomElement* dom)
{
    if(!dom) return;
    HBaseObj::readXml(v,dom);
    QDomElement symbolDom = dom->namedItem("IconSymbol").toElement();
    if(!symbolDom.isNull())
    {
        iconSymbol()->HShapeObj::readXml(v,&symbolDom);
        update();
    }
}

void HNormalObj::writeXml(int v, QDomElement* dom)
{
    if(!dom)return;
    HBaseObj::writeXml(v,dom);  
    QDomElement symbolDom = dom->ownerDocument().createElement("IconSymbol");
    dom->appendChild(symbolDom);
    if(iconSymbol())
    {
        iconSymbol()->HShapeObj::writeXml(v,&symbolDom);
    }
}

QString HNormalObj::tagName()
{
    return "Icon";
}

void HNormalObj::copyTo(HBaseObj* obj)
{
    HNormalObj* ob = (HNormalObj*)obj;
    QByteArray ba;
    QDataStream dsm(&ba,QIODevice::ReadWrite);
    int ver = 0;
    writeData(ver,&dsm);
    dsm.device()->seek(0);
    ob->setParent(parent());
    ob->readData(ver,&dsm);
}

bool HNormalObj::setPointList(QPolygonF& list, qint8 flag)
{
	HBaseObj::setPointList(list, flag);

	QRectF rectF = list.boundingRect();
	resize(rectF.width(), rectF.height());
	return true;
}

QPolygonF HNormalObj::getPointList(qint8 flag )
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

void HNormalObj::resize(double w, double h, bool bscale)
{
    iconSymbol()->resize(w, h, bscale);
}

void HNormalObj::move(double dx, double dy, bool bscale)
{
	HBaseObj::move(dx, dy,bscale);
}

void HNormalObj::moveBy(double dx,double dy, bool bscale)
{
	HBaseObj::moveBy(dx, dy,bscale);
}

QRectF HNormalObj::boundingRect(qint8 flag )
{
    return HBaseObj::boundingRect(flag);
}

QPainterPath HNormalObj::shape(qint8 flag)
{
    QPainterPath path;
    QPolygonF polygon = getPointList(flag);
    path.addPolygon(polygon);
	path.closeSubpath();
    return path;
}

void HNormalObj::paint(QPainter* painter)
{
	painter->save();
	iconSymbol()->paint(painter);
	painter->restore();
}

void HNormalObj::setUuid(const QString& uuid)
{
    this->strUuid = uuid;
}

QString HNormalObj::getUuid()
{
    return strUuid;
}

void HNormalObj::setCatalogName(const QString& catalogName)
{
    strCatalogName = catalogName;
}

QString HNormalObj::getCatalogName()
{
    return strCatalogName;
}

void HNormalObj::setObjType( uchar catalogType)
{
    nCatalogType = catalogType;
}

int HNormalObj::getObjType()
{
    return nCatalogType;
}

void HNormalObj::setSymbolName(const QString& symbolName)
{
    //strSymbolName = symbolName;
   // if(iconSymbol())
	//	iconSymbol()->setSymbolName(symbolName);
}

QString HNormalObj::getSymbolName()
{
   // if(iconSymbol())
	//	iconSymbol()->getSymolName();
    return "";
}

void HNormalObj::setSymbolType(int symbolType)
{
    //if(pIconSymbol)
     //   pIconSymbol->setSymbolType(symbolType);
}

int HNormalObj::getSymbolType()
{
    //if(pIconSymbol)
     //  return pIconSymbol->getSymbolType();
    return (int)-1;
}

void HNormalObj::setGraphID(int graphID)
{
    nGraphID = graphID;
}

int HNormalObj::getGraphID()
{
    return nGraphID;
}

void HNormalObj::setIconTemplate(HIconTemplate* t)
{
    m_pIconTemplate = t;
    //还要刷新m_pIconSymbol的内容 --huangw
    if(!m_pIconSymbol)
    {
        m_pIconSymbol = new HIconSymbol(t);
        initIconTemplate();
    }
}

HIconTemplate* HNormalObj::iconTemplate()
{
    return m_pIconTemplate;
}

HIconSymbol* HNormalObj::iconSymbol()
{
    return m_pIconSymbol;
}

void HNormalObj::update()
{
    if(!iconSymbol())
        return;
	int w = iconSymbol()->m_width;
	int h = iconSymbol()->m_height;
	initIconTemplate();
    iconSymbol()->resize(w, h);
    iconSymbol()->setParent(this);
}

