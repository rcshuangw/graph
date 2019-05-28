#include "hpolygon.h"

///////////////////////////////////////////////HPolygon//////////////////////////////////////
HPolygon::HPolygon()
{
    setShapeType(Polygon);
    pylist.clear();
}

HPolygon::~HPolygon()
{

}

void HPolygon::readData(int v,QDataStream* data)
{
    if(!data) return;
    pylist.clear();
    HShapeObj::readData(v,data);
    quint16 n = pylist.count();
    *data>>n;
    for(int i = 0; i < n;i++)
    {
        QPointF pt;
        *data>>pt;
        pylist.append(pt);
    }
}

void HPolygon::writeData(int v,QDataStream* data)
{
    if(!data) return;
    HShapeObj::writeData(v,data);
    *data<<(quint16)pylist.count();
    for(int i = 0; i < pylist.count();i++)
    {
        *data<<pylist.at(i);
    }
}

void HPolygon::readXml(int v,QDomElement* dom)
{
    if(!dom) return;
    pylist.clear();
    HShapeObj::readXml(v,dom);
    for(QDomNode n = dom->firstChild(); !n.isNull(); n = n.nextSibling())
    {
        QDomElement pointDom = n.toElement();
        QPointF pt;
        pt.setX(pointDom.attribute("PosX").toDouble());
        pt.setY(pointDom.attribute("PosY").toDouble());
        pylist.append(pt);
    }
}

void HPolygon::writeXml(int v,QDomElement* dom)
{
    if(!dom || pylist.count() <= 0)return;
    HShapeObj::writeXml(v,dom);
    for(int i = 0; i < pylist.count();i++)
    {
        QDomElement Pointdom = dom->ownerDocument().createElement("Point");
        dom->appendChild(Pointdom);
        QPointF pt = pylist.at(i);
        Pointdom.setAttribute("PosX",pt.x());
        Pointdom.setAttribute("PosY",pt.y());
    }
}

QString HPolygon::tagName()
{
    return "Polygon";
}

//拷贝克隆
void HPolygon::copyTo(HBaseObj* obj)
{
    HPolygon* ob = (HPolygon*)obj;
    if(!ob) return;
    ob->pylist.clear();
    HShapeObj::copyTo(ob);
    for(int i = 0;i<pylist.count();i++)
    {
        ob->pylist.append(pylist.at(i));
    }
}

bool HPolygon::setPointList(QPolygonF& list, qint8 flag)
{
    if(list.size() < 3) return false;
    HShapeObj::setPointList(list,flag);
    pylist = list;
    return true;
}

QPolygonF HPolygon::getPointList(qint8 flag)
{
    HPointFList list;
    list = pylist;
    maps(list,flag);
    return list;
}

void HPolygon::resize(double w, double h, bool scale)
{
    double dx, dy;
    if (scale)
    {
        //w,h已经是变换后的deltax,deltay
        dx = w;
        dy = h;
    }
    else
    {
        QRectF rect = pylist.boundingRect();
        dx = w/rect.width();
        dy = h/rect.height();
    }
    if(qFuzzyCompare(dx, 0))
        dx = 1.0;
    if (qFuzzyCompare(dy, 0))
        dy = 1.0;
    HShapeObj::resize(w, h, scale);
    int sz = pylist.size();
    for(int i = 0; i < sz;i++)
    {
        pylist[i].rx()*=dx;
        pylist[i].ry()*=dy;
    }
}

QRectF HPolygon::boundingRect(qint8 flag)
{
   return getPointList(flag).boundingRect();
}

QPainterPath HPolygon::shape(qint8 flag)
{
    QPainterPath path;
    HPointFList list = getPointList(flag);
    path.addPolygon(list);
    path.closeSubpath();
    return path;
}

void HPolygon::paint(QPainter* painter)
{
    if(!painter) return;
    painter->save();
    HShapeObj::setPainter(painter);
    QPainterPath path;
    if(getPath(path))
        painter->drawPath(path);

    painter->restore();
}

