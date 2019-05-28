#include "hrectangle.h"
/////////////////////////////////////HRectObj//////////////////////////////////////
HRectangle::HRectangle()
{
	m_eDrawShape = Rectangle;
	m_nXAxis = m_nYAxis = 0;
    m_bRound = false;
}

HRectangle::~HRectangle()
{

}

//二进制读写
void HRectangle::readData(int v,QDataStream* data)
{
    if(!data) return;
    HShapeObj::readData(v,data);
    quint8 n8;
    *data>>n8;
	setXAxis(n8);
    *data>>n8;
    setYAxis(n8);
}

void HRectangle::writeData(int v,QDataStream* data)
{
    if(!data) return;
    HShapeObj::writeData(v,data);
    *data<<(quint8)getXAxis();
    *data<<(quint8)getYAxis();
}

void HRectangle::readXml(int v,QDomElement* dom)
{
    if(!dom) return;
    HShapeObj::readXml(v,dom);
    m_nXAxis = dom->attribute("XAxis").toDouble();
    m_nYAxis = dom->attribute("YAxis").toDouble();
}

void HRectangle::writeXml(int v,QDomElement* dom)
{
    if(!dom)return;
    HShapeObj::writeXml(v,dom);
    dom->setAttribute("XAxis",m_nXAxis);
    dom->setAttribute("YAxis",m_nYAxis);
}

QString HRectangle::tagName()
{
    return "Rectangle";
}

//拷贝克隆
void HRectangle::copyTo(HBaseObj* obj)
{
	HShapeObj::copyTo(obj);
    HRectangle* ob = (HRectangle*)obj;
	ob->setXAxis(getXAxis());
	ob->setYAxis(getYAxis());
}

/*
bool HRectangle::getPath(QPainterPath& path)
{
    bool bRound = isRound();
	int nXAxis = getXAxis();
	int nYAxis = getYAxis();
	QRectF rect = getPointList(0).boundingRect();
	if (!bRound)
	{
		path.addRect(rect);
	}
	else
	{
		path.addRoundedRect(rect, nXAxis, nYAxis);
	}
	return true;
}*/

QRectF HRectangle::boundingRect(qint8 flag)
{
	QRectF rect = HShapeObj::boundingRect(flag);
	return rect;
}

QPainterPath HRectangle::shape(qint8 flag)
{
	QPainterPath path;
    if (m_nFillWay > 0)
	{
       return HShapeObj::shape(flag);
	}
    QPolygonF points = getPointList(flag);
    path.addPolygon(points);
    QRectF rect = points.boundingRect().adjusted(5, 5, -5, -5);
    path.addRect(rect);
    return path;

}

void HRectangle::paint(QPainter* painter)
{
	if (!painter)
		return;
	painter->save();
    HShapeObj::setPainter(painter);
	QPainterPath path;
	if(getPath(path))
		painter->drawPath(path);

	painter->restore();
}

///设置贴片
void HRectangle::setBkImagePath(const QString& s)
{
	HShapeObj::setBkImagePath(s);
}

//矩形框的x,y轴弯曲度  放到rect里面
void HRectangle::setRound(bool bcheck)
{
	m_bRound = bcheck;
}

bool HRectangle::isRound()
{
	return m_bRound;
}

//圆角x轴
void HRectangle::setXAxis(int xAxis)
{
	m_nXAxis = xAxis;
}

quint8 HRectangle::getXAxis()
{
	return m_nXAxis;
}

//圆角y轴
void HRectangle::setYAxis(int yAxis)
{
	m_nYAxis = yAxis;
}

quint8 HRectangle::getYAxis()
{
	return m_nYAxis;
}

