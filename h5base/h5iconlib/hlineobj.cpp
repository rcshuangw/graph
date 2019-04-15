#include "hlineobj.h"
HLineObj::HLineObj()
{
	m_nArrowStart = 0;
	m_nArrowEnd = 0;
	m_nArrowWidth = 10;
	m_nArrowHeight = 0;
}

HLineObj::~HLineObj()
{

}

//二进制读写
void HLineObj::readData(QDataStream* data)
{
	if (!data)return;
	HBaseObj::readData(data);

	quint8 n8;
	*data >> n8;
	m_nArrowStart = n8;
	*data >> n8;
	m_nArrowEnd = n8;
	
	*data >> n8;
	m_nArrowWidth = n8;
	*data >> n8;
	m_nArrowHeight = n8;
}

void HLineObj::writeData(QDataStream* data)
{
	if (!data) return;
	HBaseObj::writeData(data);

	*data << (quint8)m_nArrowStart;
	*data << (quint8)m_nArrowEnd;
	*data << (quint8)m_nArrowWidth;
	*data << (quint8)m_nArrowHeight;
}

//xml文件读写
void HLineObj::readXml(QDomElement* dom)
{
	if (!dom) return;
	HBaseObj::readXml(dom);
	m_nArrowStart = dom->attribute("ArrowStart").toUInt();
	m_nArrowEnd = dom->attribute("ArrowEnd").toUInt();
	m_nArrowWidth = dom->attribute("ArrowWidth").toDouble();
	m_nArrowHeight = dom->attribute("ArrowHeight").toDouble();
}

void HLineObj::writeXml(QDomElement* dom)
{
	if (!dom)return;
	HBaseObj::writeXml(dom);
	dom->setAttribute("arrowStart", m_nArrowStart);
	dom->setAttribute("arrowEnd", m_nArrowEnd);
	dom->setAttribute("arrowWidth", m_nArrowWidth);
	dom->setAttribute("arrowHeight", m_nArrowHeight);
}

QString HLineObj::TagName()
{
	return "Line";
}

//拷贝克隆
void HLineObj::copyTo(HBaseObj* obj)
{

}

void HLineObj::clone(HBaseObj* obj)
{

}

bool HLineObj::getPath(QPainterPath& path)
{

}

void HLineObj::setArrowStart(quint8 start)
{
	m_nArrowStart = start;
}

quint8 HLineObj::getArrowStart()
{
	return m_nArrowStart;
}

void HLineObj::setArrowEnd(quint8 end)
{
	m_nArrowEnd = end;
}

quint8 HLineObj::getArrowEnd()
{
	return m_nArrowEnd;
}

void HLineObj::setArrowWidth(quint8 width)
{
	m_nArrowWidth = width;
}

quint8 HLineObj::getArrowWidth()
{
	return m_nArrowWidth;
}

void HLineObj::setArrowHeight(quint8 height)
{
	m_nArrowHeight = height;
}

quint8 HLineObj::getArrowHeight()
{
	return m_nArrowHeight;
}

///////////////////////////////////////////////////////操作属性/////////////////////////////
//改变大小
void HLineObj::resize(double w, double h, bool scale)
{

}

void HLineObj::move(qreal dx, qreal dy, bool bscale = false)
{

}

void HLineObj::moveBy(qreal dx, qreal dy, bool bscale = false)
{

}

bool HLineObj::setPointList(QPolygonF& list, qint8 flag = 1)
{

}

QPolygonF HLineObj::getPointList(qint8 flag = 0)
{

}

QRectF HLineObj::boundingRect(qint8 flag = 0)
{

}

QPainterPath HLineObj::shape(qint8 flag = 0)
{

}

void HLineObj::paint(QPainter* painter)
{

}

bool HLineObj::contains(const QPointF &point) const
{

}