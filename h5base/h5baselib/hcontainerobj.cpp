#include "hcontainerobj.h"
#include "hgroup.h"
#include "hline.h"
#include "hrectangle.h"
#include "hellipse.h"
#include "htext.h"
#include "hcircle.h"
#include "hpolygon.h"
#include "hpolyline.h"
#include "hmakeicon.h"
HContainerObj::HContainerObj()
{

}

HContainerObj::~HContainerObj()
{
    clear();
}

//二进制读写
void HContainerObj::readData(int v,QDataStream* data)
{
	if (!data) return;
    HShapeObj::readData(v,data);
	int sz;
	*data >> sz;
	quint8 type = 0;
	for (int i = 0; i < sz; i++)
	{
		*data >> type;
        HBaseObj* pObj = HMakeIcon::Instance()->newObj(DrawShape(type));
		if (!pObj) continue;
        pObj->readData(v,data);
        pObj->setParent(this);
        getObjList().append(pObj);
	}
}

void HContainerObj::writeData(int v, QDataStream* data)
{
	if (!data) return;
    HShapeObj::writeData(v,data);

	int sz = (int)m_pObjList.size();
	int count = 0;
	for (int i = 0; i < sz; i++)
	{
		HBaseObj* pObj = (HBaseObj*)m_pObjList.at(i);
		if (pObj && pObj->isDeleted())
			continue;
		count++;
	}

	*data<<(int)count;
	for (int i = 0; i < sz; i++)
	{
		HBaseObj* pObj = (HBaseObj*)m_pObjList.at(i);
		if (pObj && pObj->isDeleted()) continue;
		*data << (quint8)pObj->getShapeType();
        pObj->writeData(v,data);
	}
}

//xml文件读写
void HContainerObj::readXml(int v, QDomElement* dom)
{
	if (!dom) return;
    HShapeObj::readXml(v,dom);

	QDomElement objEle = dom->namedItem("Children").toElement();
	QDomNode n = objEle.firstChild();
	for (int i = 0; !n.isNull(); n = n.nextSibling(), i++)
	{
		QDomElement e = n.toElement();
		DrawShape objType = (DrawShape)e.attribute("ObjType").toInt();
        HBaseObj* pObj = HMakeIcon::Instance()->newObj(objType);
		if (!pObj) continue;
        pObj->readXml(v,&e);
        pObj->setParent(this);
        getObjList().append(pObj);//不能调用addObj(pObj)如果这样会再次resetParent会造成错误
	}
}

void HContainerObj::writeXml(int v, QDomElement* dom)
{
	if (!dom) return;
    HShapeObj::writeXml(v,dom);
	dom->setTagName(tagName());
	QDomElement childDom = dom->ownerDocument().createElement("Children");
	dom->appendChild(childDom);
	for (int i = 0; i < m_pObjList.count(); i++)
	{
		HBaseObj* pObj = (HBaseObj*)m_pObjList[i];
		if (!pObj || pObj->isDeleted())
		{
			continue;
		}
		QDomElement childEle = dom->ownerDocument().createElement(pObj->tagName());
		childDom.appendChild(childEle);
        pObj->writeXml(v,&childEle);
	}
}

QString HContainerObj::tagName()
{
	return "GroupObj";
}

//拷贝克隆
void HContainerObj::copyTo(HBaseObj* obj)
{
	HContainerObj* pComplexObj = (HContainerObj*)obj;
	HShapeObj::copyTo(pComplexObj);
	for (int i = 0; i < m_pObjList.count(); i++)
	{
		HBaseObj* pObj = (HBaseObj*)m_pObjList[i];
		if (!pObj || pObj->isDeleted())
		{
			continue;
		}
        HBaseObj* pnewObj = HMakeIcon::Instance()->newObj(pObj->getShapeType());
        pObj->copyTo(pnewObj);
        pnewObj->setParent(pComplexObj);
        pComplexObj->getObjList().append(pnewObj);
    }
}

void HContainerObj::resize(double w, double h, bool scale)
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

  objsTransform(dw, dh);
}

bool HContainerObj::objsTransform(double dx,double dy)
{
    int sz = m_pObjList.size();
    for (int i = 0; i < sz; i++)
    {
        HBaseObj* pObj = m_pObjList.at(i);
        pObj->resize(dx, dy, true);

        QPointF po = pObj->pos(1);
        QPointF ce = pos(1);
        po -=ce;
        po.rx()*=dx;
        po.ry()*=dy;
        po +=ce;

        if(pObj->parent()){
            QPointF p = pObj->parent()->pos(1);
            po-=p;
        }
        pObj->move(po.x(),po.y(),false);
    }
    return true;
}

void HContainerObj::expand(double dx1, double dx2, double dy1, double dy2, qint8 flag)
{

}

//将列表的所有图符 由原始绘制的尺寸按照比例缩小同时改变其原点位置
/*
bool HContainerObj::transform(double dx, double dy)
{
	int count = m_pObjList.size();
	for (int i = 0; i < count; i++)
	{
		HBaseObj* pObj = m_pObjList.at(i);
		pObj->resize(dx, dy, true);
        //pObj->move(dx, dy, true);
	}
	return true;
}

void HContainerObj::move(double dx, double dy, bool scale)
{
	for (int i = 0; i < m_pObjList.size(); i++)
	{
		HBaseObj* pObj = (HBaseObj*)m_pObjList.at(i);
		if (!pObj) continue;
		pObj->move(dx, dy, scale);
	}
}*/

/*
void HContainerObj::moveBy(double dx, double dy, bool scale)
{
	for (int i = 0; i < m_pObjList.size(); i++)
	{
		HBaseObj* pObj = (HBaseObj*)m_pObjList.at(i);
		if (!pObj) continue;
		pObj->moveBy(dx, dy, scale);
	}
}*/

QRectF HContainerObj::objsRect(qint8 flag)
{
    QRectF rectF;
    int count = m_pObjList.size();
    for (int i = 0; i < count; i++)
    {
        HBaseObj* pObj = m_pObjList.at(i);
        if (!pObj || pObj->isDeleted())
            continue;
        if(rectF.isNull())
        {
            rectF = pObj->getPointList(flag).boundingRect();
            if(rectF.isValid())
            {
                if(rectF.width() < 0) rectF.setWidth(1);
                if(rectF.height()< 0) rectF.setHeight(1);
            }
        }
        else
        {
            QRectF sRectF = pObj->getPointList(flag).boundingRect().normalized();
            if(sRectF.isValid())
            {
                if(sRectF.width() < 0) sRectF.setWidth(1);
                if(sRectF.height()< 0) sRectF.setHeight(1);
            }
            rectF = rectF.united(sRectF);
        }
    }
    return rectF;
}

QRectF HContainerObj::boundingRect(qint8 flag)
{
    QRectF rectF = objsRect(flag);

    m_width = rectF.width();
    m_height = rectF.height();
	return rectF;
}

QPainterPath HContainerObj::shape(qint8 flag)
{
	QPainterPath path;
	int count = m_pObjList.size();
	for (int i = 0; i < count; i++)
	{
		HBaseObj* pObj = m_pObjList.at(i);
		if (!pObj || pObj->isDeleted())
			continue;
        path.addPath(pObj->shape(flag));
	}
	return path;
}

void HContainerObj::rePos()
{

}

//针对objList的操作 参考QVector类的函数
void HContainerObj::clear()
{
    while (!m_pObjList.empty())
	{
        HBaseObj* pObj = (HBaseObj*)m_pObjList.takeFirst();
        if(pObj)
        {
            delete pObj;
            pObj = NULL;
        }
	}
	m_pObjList.clear();
}

void HContainerObj::addObj(HBaseObj* obj)
{
	if (!obj) return;
    if(m_bTempObj)
        m_pObjList.append(obj);
    else
        obj->resetParent(this);
    //--huangw--
    rePos();
}

void HContainerObj::removeObj(HBaseObj* obj)
{
	if (!obj) return;
	m_pObjList.removeOne(obj);
    rePos();
}

bool HContainerObj::contains(HBaseObj* obj)
{
	if (!obj) return false;
	return m_pObjList.contains(obj);
}

int HContainerObj::size()
{
	return m_pObjList.size();
}

HBaseObj* HContainerObj::at(int index)
{
	if (index < 0 || index > m_pObjList.size())
		return NULL;
	return m_pObjList.at(index);
}

void HContainerObj::addObjList(QList<HBaseObj*> objs)
{
    clear();
	int count = objs.size();
	for (int i = 0; i < count; i++)
	{
		HBaseObj* obj = objs.at(i);
		if (!obj) continue;
		addObj(obj);
	}
    rePos();
}

QVector<HBaseObj*>& HContainerObj::getObjList()
{
	return m_pObjList;
}
