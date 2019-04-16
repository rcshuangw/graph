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
	HLineObj* ob = (HLineObj*)obj;
	if (!obj) return;
	ob->setStartArrowType(m_nArrowStart);
	ob->setEndArrowType(m_nArrowEnd);
	ob->setArrowWidth(m_nArrowWidth);
	ob->setArrowHeight(m_nArrowHeight);
}

void HLineObj::clone(HBaseObj* obj)
{
	HLineObj* ob = (HLineObj*)obj;
	if (!obj) return;
	ob->setStartArrowType(m_nArrowStart);
	ob->setEndArrowType(m_nArrowEnd);
	ob->setArrowWidth(m_nArrowWidth);
	ob->setArrowHeight(m_nArrowHeight);
}

void HLineObj::setStartArrowType(quint8 start)
{
	m_nArrowStart = start;
}

quint8 HLineObj::getStartArrowType()
{
	return m_nArrowStart;
}

void HLineObj::setEndArrowType(quint8 end)
{
	m_nArrowEnd = end;
}

quint8 HLineObj::getEndArrowType()
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
//获取直线头尾的箭头绘制路径 
QPainterPath HLineObj::getArrowPath(HPointsList& points, bool head)
{
	QPointF ptS = points.at(0);
	QPointF ptE = points.at(1);
	QLineF line = QLineF(ptS, ptE);
	double angle = ::acos(line.dx() / line.length());
	if (line.dy() >= 0)
		angle = (PI * 2) - angle;
	int w = getArrowWidth();
	int h = getArrowHeight();
	quint16 arrowLength = sqrt(w*w + h * h);
	quint8 arrowS = getStartArrowType();
	quint8 arrowE = getEndArrowType();
	QPointF arrowP1;
	QPointF arrowP2;
	QPainterPath path;
	if (head)
	{
		if (arrowS == 1)//直线箭头
		{
			arrowP1 = ptS + QPointF(sin(angle + PI / 3)*arrowLength, cos(angle + PI / 3)*arrowLength);
			arrowP2 = ptS + QPointF(sin(angle + PI - PI / 3)*arrowLength, cos(angle + PI - PI / 3)*arrowLength);
			path.lineTo(arrowP1);
			path.moveTo(ptS);
			path.lineTo(arrowP2);
			path.moveTo(ptS);
		}
		else if (arrowS == 2)//空心三角箭头
		{
			arrowP1 = ptS + QPointF(sin(angle + PI / 3)*arrowLength, cos(angle + PI / 3)*arrowLength);
			arrowP2 = ptS + QPointF(sin(angle + PI - PI / 3)*arrowLength, cos(angle + PI - PI / 3)*arrowLength);
			QPolygonF arrowHead;
			arrowHead << arrowP1 << ptS << arrowP2;
			path.addPolygon(arrowHead);
			path.closeSubpath();

			double fh = sin(PI / 3)*arrowLength / line.length();
			QPointF pt = line.pointAt(fh);
			points[0] = pt;

		}
		else if (arrowS == 3)//实心三角箭头
		{
			arrowP1 = ptS + QPointF(sin(angle + PI / 3)*arrowLength, cos(angle + PI / 3)*arrowLength);
			arrowP2 = ptS + QPointF(sin(angle + PI - PI / 3)*arrowLength, cos(angle + PI - PI / 3)*arrowLength);
			QPolygonF arrowHead;
			arrowHead << ptS << arrowP1 << arrowP2;
			path.addPolygon(arrowHead);
			path.closeSubpath();
		}
	}
	else
	{
		if (arrowE == 1)
		{
			arrowP1 = ptE + QPointF(sin(angle - PI / 3)*arrowLength, cos(angle - PI / 3)*arrowLength);
			arrowP2 = ptE + QPointF(sin(angle - PI + PI / 3)*arrowLength, cos(angle - PI + PI / 3)*arrowLength);
			path.lineTo(arrowP1);
			path.moveTo(ptE);
			path.lineTo(arrowP2);
			path.moveTo(ptE);
		}
		else if (arrowE == 2)
		{
			arrowP1 = ptE + QPointF(sin(angle - PI / 3)*arrowLength, cos(angle - PI / 3)*arrowLength);
			arrowP2 = ptE + QPointF(sin(angle - PI + PI / 3)*arrowLength, cos(angle - PI + PI / 3)*arrowLength);
			QPolygonF arrowHead;
			arrowHead << arrowP1 << ptE << arrowP2;
			
			path.addPolygon(arrowHead);
			path.closeSubpath();

			double fh = sin(PI / 3)*arrowLength / line.length();
			QPointF pt = QLineF(ptE, ptS).pointAt(fh);
			points[1] = pt;
		}
		else if (arrowE == 3)
		{
			arrowP1 = ptE + QPointF(sin(angle - PI / 3)*arrowLength, cos(angle - PI / 3)*arrowLength);
			arrowP2 = ptE + QPointF(sin(angle - PI + PI / 3)*arrowLength, cos(angle - PI + PI / 3)*arrowLength);
			QPolygonF arrowHead;
			arrowHead << ptE << arrowP1 << arrowP2;
			path.addPolygon(arrowHead);
			path.closeSubpath();
		}
	}
	return path;
}

//改变大小
void HLineObj::resize(double w, double h, bool scale)
{
	HBaseObj::resize(w, h, scale);
}

void HLineObj::move(qreal dx, qreal dy, bool bscale)
{
	HBaseObj::move(dx, dy, bscale);
}

void HLineObj::moveBy(qreal dx, qreal dy, bool bscale)
{
	HBaseObj::moveBy(dx, dy, bscale);
}

bool HLineObj::setPointList(QPolygonF& list, qint8 flag)
{
	return HBaseObj::setPointList(list, flag);
}

void HLineObj::getBoundingRect(HPointsList& points, QPointF &headPoint, QPointF& tailPoint, double width)
{
	double range = width;
	QLineF lnf(headPoint, tailPoint);
	double len = lnf.length();
	double fw = 0;
	if (!qFuzzyCompare(len, 0)) {
		fw = range / len;
	}

	QPointF po2 = lnf.pointAt(fw);
	QPointF pos ;
	points.resize(4);
	QMatrix mx;
	mx.reset();
	mx.translate(headPoint.x(), headPoint.y());
	mx.rotate(-90);
	mx.translate(-headPoint.x(), -headPoint.y());
	pos = mx.map(po2);
	points[0] = pos;

	pos.setX(pos.x() + lnf.dx());
	pos.setY(pos.y() + lnf.dy());
	points[3] = pos;

	mx.reset();
	mx.translate(headPoint.x(), headPoint.y());
	mx.rotate(90);
	mx.translate(-headPoint.x(), -headPoint.y());
	pos = mx.map(po2);
	points[1] = pos;

	pos.setX(pos.x() + lnf.dx());
	pos.setY(pos.y() + lnf.dy());
	points[2] = pos;

}