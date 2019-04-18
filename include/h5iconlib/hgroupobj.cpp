#include "hgroupobj.h"
#include "hline.h"
#include "hrectangle.h"
HGroupObj::HGroupObj()
{

}

HGroupObj::~HGroupObj()
{

}

//二进制读写
void HGroupObj::readData(QDataStream* data)
{

}

void HGroupObj::writeData(QDataStream* data)
{

}

//xml文件读写
void HGroupObj::readXml(QDomElement* dom)
{
	if (!dom) return;
	HShapeObj::readXml(dom);

	QDomElement objEle = dom->namedItem("Children").toElement();
	QDomNode n = objEle.firstChild();
	for (int i = 0; !n.isNull(); n = n.nextSibling(), i++)
	{
		QDomElement e = n.toElement();
		DrawShape objType = (DrawShape)e.attribute("ObjType").toInt();
		HBaseObj* pObj = newObj(objType);
		if (!pObj) continue;
		pObj->readXml(&e);
		addObj(pObj);
	}
}

void HGroupObj::writeXml(QDomElement* dom)
{
	if (!dom) return;
	HShapeObj::writeXml(dom);
	dom->setTagName(TagName());
	QDomElement childDom = dom->ownerDocument().createElement("Children");
	dom->appendChild(childDom);
	for (int i = 0; i < m_pObjList.count(); i++)
	{
		HBaseObj* pObj = (HBaseObj*)m_pObjList[i];
		if (!pObj || pObj->isDeleted())
		{
			m_pObjList.removeAt(i);
			delete pObj;
			i--;
			continue;
		}
		QDomElement childEle = dom->ownerDocument().createElement(pObj->TagName());
		childDom.appendChild(childEle);
		pObj->writeXml(&childEle);
	}
}

QString HGroupObj::TagName()
{
	return "GroupObj";
}

//拷贝克隆
void HGroupObj::copyTo(HBaseObj* obj)
{

}

void HGroupObj::clone(HBaseObj* obj)
{

}

HBaseObj* HGroupObj::newObj(QString tagName)
{
	DrawShape drawShape = No;
	if (tagName == "Line")
		drawShape = Line;
	else if (tagName == "Rectangle")
		drawShape = Rectangle;
	else if (tagName == "Ellipse")
		drawShape = Ellipse;
	else if (tagName == "Circle")
		drawShape = Circle;
	else if (tagName == "Polyline")
		drawShape = Polyline;
	else if (tagName == "Arc")
		drawShape = Arc;
	else if (tagName == "Text")
		drawShape = Text;
	else if (tagName == "Polygon")
		drawShape = Polygon;
	else if (tagName == "Group")
		drawShape = Group;
	return newObj(drawShape);
}

HBaseObj* HGroupObj::newObj(DrawShape nObjType)
{
	HBaseObj* pObj = NULL;
	if (nObjType == Line)
	{
		pObj = new HLine();
	}
	else if (nObjType == Rectangle)
	{
		pObj = new HRectangle();
	}
	/*else if (nObjType == Ellipse)
	{
		pObj = new HEllipse();
	}
	else if (nObjType == Circle)
	{
		pObj = new HCircle();
	}
	else if (nObjType == Polygon)
	{
		pObj = new HPolygon();
	}
	else if (nObjType == Polyline)
	{
		pObj = new HPolyline();
	}
	else if (nObjType == enumArc)
	{
		pObj = new HArc();
	}
	else if (nObjType == enumPie)
	{
		pObj = new HPie();
	}
	else if (nObjType == enumText)
	{
		pObj = new HText();
	}
	else if (nObjType == enumGroup)
	{
		pObj = new HGroupObj();
	}*/
	pObj->setShapeType((DrawShape)nObjType);
	if (pObj)
	{
		int objID = getObjID();
		pObj->setObjID(objID);
	}
	return pObj;
}

///
void HGroupObj::resize(double w, double h, bool scale)
{
	double dw, dh;
	if (scale)
	{
		dw = w;
		dh = h;
		m_width = dw * m_width;
		m_height = dh * m_height;
	}
	else
	{
		double n = 5.0;
		if (qFuzzyCompare(w, m_width) && qFuzzyCompare(h, m_height))
			return;
		dw = w / m_width; //变换比例
		dh = h / m_height;
		m_width = w;
		m_height = h;
	}

	transform(dw, dh);
}

void HGroupObj::expand(double dx1, double dx2, double dy1, double dy2, qint8 flag)
{

}

//将列表的所有图符 由原始绘制的尺寸按照比例缩小同时改变其原点位置
bool HGroupObj::transform(double dx, double dy)
{
	int count = m_pObjList.size();
	for (int i = 0; i < count; i++)
	{
		HBaseObj* pObj = m_pObjList.at(i);
		pObj->resize(dx, dy, true);
		pObj->move(dx, dy, true);
	}
	return true;
}

void HGroupObj::move(qreal dx, qreal dy, bool scale)
{
	for (int i = 0; i < m_pObjList.size(); i++)
	{
		HBaseObj* pObj = (HBaseObj*)m_pObjList.at(i);
		if (!pObj) continue;
		pObj->move(dx, dy, scale);
	}
}

void HGroupObj::moveBy(qreal dx, qreal dy, bool scale)
{
	for (int i = 0; i < m_pObjList.size(); i++)
	{
		HBaseObj* pObj = (HBaseObj*)m_pObjList.at(i);
		if (!pObj) continue;
		pObj->moveBy(dx, dy, scale);
	}
}

QRectF HGroupObj::boundingRect(qint8 flag)
{
	QRectF rectF(0,0,0,0);
	int count = m_pObjList.size();
	for (int i = 0; i < count; i++)
	{
		HBaseObj* pObj = m_pObjList.at(i);
		if (!pObj || pObj->isDeleted())
			continue;
		rectF = rectF.united(pObj->boundingRect().normalized());
	}
	return rectF;
}

QPainterPath HGroupObj::shape(qint8 flag)
{
	QPainterPath path;
	int count = m_pObjList.size();
	for (int i = 0; i < count; i++)
	{
		HBaseObj* pObj = m_pObjList.at(i);
		if (!pObj || pObj->isDeleted())
			continue;
		path.addPath(pObj->shape());
	}
	return path;
}

//针对objList的操作 参考QVector类的函数
void HGroupObj::clear()
{
	while (!m_pObjList.empty())
	{
		delete (HBaseObj*)m_pObjList.takeFirst();
	}
	m_pObjList.clear();
}

void HGroupObj::addObj(HBaseObj* obj)
{
	if (!obj) return;
	m_pObjList.append(obj);
}

void HGroupObj::removeObj(HBaseObj* obj)
{
	if (!obj) return;
	m_pObjList.removeOne(obj);
}

bool HGroupObj::contains(HBaseObj* obj)
{
	if (!obj) return false;
	return m_pObjList.contains(obj);
}

int HGroupObj::size()
{
	return m_pObjList.size();
}

HBaseObj* HGroupObj::at(int index)
{
	if (index < 0 || index > m_pObjList.size())
		return NULL;
	return m_pObjList.at(index);
}

QVector<HBaseObj*>& HGroupObj::getObjList()
{
	return m_pObjList;
}