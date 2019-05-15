#include "hline.h"
HLine::HLine()
{
	setShapeType(Line);
	ptHeadPoint = ptTailPoint = QPointF(0.0, 0.0);
}

HLine::~HLine()
{

}

//二进制读写
void HLine::readData(QDataStream* data)
{
	if (!data)return;
	HLineObj::readData(data);
	qreal qr;
	*data >> qr;
	ptHeadPoint.setX(qr);
	*data >> qr;
	ptHeadPoint.setY(qr);
	*data >> qr;
	ptTailPoint.setX(qr);
	*data >> qr;
	ptTailPoint.setY(qr);
}

void HLine::writeData(QDataStream* data)
{
	if (!data) return;
	HLineObj::writeData(data);
	*data << (qreal)ptHeadPoint.x();
	*data << (qreal)ptHeadPoint.y();
	*data << (qreal)ptTailPoint.x();
	*data << (qreal)ptTailPoint.y();
}

//xml文件读写
void HLine::readXml(QDomElement* dom)
{
	if (!dom) return;
	HLineObj::readXml(dom);
	ptHeadPoint.setX(dom->attribute("HeadPointx").toDouble());
	ptHeadPoint.setY(dom->attribute("HeadPointy").toDouble());
	ptTailPoint.setX(dom->attribute("TailPointx").toDouble());
	ptTailPoint.setY(dom->attribute("TailPointy").toDouble());
}

void HLine::writeXml(QDomElement* dom)
{
	if (!dom)return;
	HLineObj::writeXml(dom);
	dom->setAttribute("HeadPointx", ptHeadPoint.x());
	dom->setAttribute("HeadPointy", ptHeadPoint.y());
	dom->setAttribute("TailPointx", ptTailPoint.x());
	dom->setAttribute("TailPointy", ptTailPoint.y());
}

QString HLine::TagName()
{
	return "Line";
}

//拷贝克隆
void HLine::copyTo(HBaseObj* obj)
{
	HLine* ob = (HLine*)obj;
	if (!ob) return;
	HLineObj::copyTo(ob);
	ob->ptHeadPoint = ptHeadPoint;
	ob->ptTailPoint = ptTailPoint;
}

void HLine::clone(HBaseObj* obj)
{
	HLine* ob = (HLine*)obj;
	if (!ob) return;
	HLineObj::copyTo(ob);
	ob->ptHeadPoint = ptHeadPoint;
	ob->ptTailPoint = ptTailPoint;
}

///////////////////////////////////////////////////////操作属性/////////////////////////////
//改变大小 w,h传递的是相对原来的点的值
void HLine::resize(double w, double h, bool scale)
{
	HLineObj::resize(w, h, scale);
	double dx, dy;
	if (scale)
	{
		//w,h已经是变换后的deltax,deltay
		dx = w;
		dy = h;
	}
	else
	{
		QRectF rect = boundingRect();
		dx = w/rect.width();
		dy = h/rect.height();
	}
	if(qFuzzyCompare(dx, 0))
		dx = 1.0;
	if (qFuzzyCompare(dy, 0))
		dy = 1.0;

    ptHeadPoint.rx()*=dx;
    ptHeadPoint.ry()*=dy;
    ptTailPoint.rx()*=dx;
    ptTailPoint.ry()*=dy;
}

bool HLine::setPointList(QPolygonF& list, qint8 flag)
{
	if (list.size() < 2) return false;
	HLineObj::setPointList(list, flag);
	ptHeadPoint = list.at(0);
	ptTailPoint = list.at(1);
}

QPolygonF HLine::getPointList(qint8 flag)
{
	QPolygonF list;
	list.append(ptHeadPoint);
	list.append(ptTailPoint);
	maps(list, flag);
	return list;
}

QRectF HLine::boundingRect(qint8 flag)
{
    QPainterPath path;
    HPointFList points;
    double n = getLineWidth();
    if (n < 5) n = 5;
    getBoundingRect(points, ptHeadPoint, ptTailPoint, n);
    maps(points, flag);

	QPainterPath pathhead = getArrowPath(points, true);
	if (!pathhead.isEmpty())
		path.addPath(pathhead);
	QPainterPath pathtail = getArrowPath(points, false);
	if (!pathtail.isEmpty())
		path.addPath(pathtail);
    QRectF rectF = points.boundingRect().united(path.boundingRect());
	return rectF;
}

QPainterPath HLine::shape(qint8 flag)
{
    HPointFList points;
	double n = getLineWidth();
	if (n < 5) n = 5;
	getBoundingRect(points, ptHeadPoint, ptTailPoint, n);
	maps(points, flag);
	QPainterPath path;
	path.addPolygon(points);
	path.closeSubpath();
	return path;
}

void HLine::paint(QPainter* painter)
{
	if (!painter) return;
	QColor penClr = QColor(getLineColorName());
	int penWidth = getLineWidth();
	Qt::PenStyle penStyle = getLineStyle();
	Qt::PenCapStyle capStyle = getLineCapStyle();

	painter->save();
	QPen pen = QPen(penClr);
	pen.setStyle(penStyle);
	pen.setWidth(penWidth);
	pen.setCapStyle(capStyle);
	painter->setPen(pen);
    HPointFList list = getPointList(0);
	//画箭头
	if (getArrowWidth() > 0 && getArrowHeight() > 0)
	{
		QPainterPath path;
		path = getArrowPath(list, true);
		if (!path.isEmpty())
		{
			painter->save();
			painter->setBrush(Qt::NoBrush);
			if (getStartArrowType() == 3)
			{
				painter->setBrush(QColor(penClr));
			}
			painter->drawPath(path);
			painter->restore();
		}
		path = getArrowPath(list, false);
		if (!path.isEmpty())
		{
			painter->save();
			painter->setBrush(Qt::NoBrush);
			if (getEndArrowType() == 3)
			{
				painter->setBrush(QColor(penClr));
			}
			painter->drawPath(path);
			painter->restore();
		}
	}
	painter->drawPolyline(list);
	painter->restore();
}
