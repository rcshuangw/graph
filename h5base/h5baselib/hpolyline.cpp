#include "hpolyline.h"
///////////////////////////////////////////////HPolyline//////////////////////////////////////
HPolyline::HPolyline()
{
    setShapeType(Polyline);
    pylist.clear();
}

HPolyline::~HPolyline()
{

}

void HPolyline::readData(QDataStream* data)
{
    if(!data) return;
    pylist.clear();
    HLineObj::readData(data);
    quint16 n = pylist.count();
    *data>>n;
    for(int i = 0; i < n;i++)
    {
        QPointF pt;
        *data>>pt;
        pylist.append(pt);
    }
}

void HPolyline::writeData(QDataStream* data)
{
    if(!data) return;
    HLineObj::writeData(data);
    *data<<(quint16)pylist.count();
    for(int i = 0; i < pylist.count();i++)
    {
        *data<<pylist.at(i);
    }
}

void HPolyline::readXml(QDomElement* dom)
{
    if(!dom) return;
    pylist.clear();
    HLineObj::readXml(dom);
    for(QDomNode n = dom->firstChild(); !n.isNull(); n = n.nextSibling())
    {
        QDomElement pointDom = n.toElement();
        QPointF pt;
        pt.setX(pointDom.attribute("PosX").toDouble());
        pt.setY(pointDom.attribute("PosY").toDouble());
        pylist.append(pt);
    }
}

void HPolyline::writeXml(QDomElement* dom)
{
    if(!dom || pylist.count() <= 0)return;
    HLineObj::writeXml(dom);
    for(int i = 0; i < pylist.count();i++)
    {
        QDomElement Pointdom = dom->ownerDocument().createElement("Point");
        dom->appendChild(Pointdom);
        QPointF pt = pylist.at(i);
        Pointdom.setAttribute("PosX",pt.x());
        Pointdom.setAttribute("PosY",pt.y());
    }
}

QString HPolyline::tagName()
{
    return "Polyline";
}

//拷贝克隆
void HPolyline::copyTo(HBaseObj* obj)
{
    HPolyline* ob = (HPolyline*)obj;
    ob->pylist.clear();
    for(int i = 0;i<pylist.count();i++)
    {
        ob->pylist.append(pylist.at(i));
    }
}

void HPolyline::clone(HBaseObj *obj)
{
    if(!obj) return;
    HBaseObj::clone(obj);
    copyTo(obj);
}

bool HPolyline::setPointList(QPolygonF& list, qint8 flag)
{
    HLineObj::setPointList(list,flag);
    pylist = list;
    return false;
}

QPolygonF HPolyline::getPointList(qint8 flag)
{
    HPointFList list;
    list = pylist;
    maps(list,flag);
    return list;
}

void HPolyline::resize(double w, double h, bool scale)
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
        QRectF rect = pylist.boundingRect();
        dx = w/rect.width();
        dy = h/rect.height();
    }
    if(qFuzzyCompare(dx, 0))
        dx = 1.0;
    if (qFuzzyCompare(dy, 0))
        dy = 1.0;
    int sz = pylist.size();
    for(int i = 0; i < sz;i++)
    {
        pylist[i].rx()*=dx;
        pylist[i].ry()*=dy;
    }
}

QRectF HPolyline::boundingRect(qint8 flag)
{
   return getPointList(flag).boundingRect();
}

QPainterPath HPolyline::shape(qint8 flag)
{
    QPainterPath path;
    HPointFList list = getPointList(flag);
    path.addPolygon(list);
    QPainterPathStroker ps;
    int pen = 2;
    ps.setWidth(pen);
    QPainterPath p = ps.createStroke(path);
    return p;
}

void HPolyline::paint(QPainter* painter)
{
    QColor penClr = QColor(getLineColorName()); //线条颜色
    int penWidth = getLineWidth();//线条宽度
    Qt::PenStyle penStyle = getLineStyle(); //线条形状
    Qt::PenCapStyle capStyle = getLineCapStyle(); //线条角度

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::TextAntialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);

    QPen pen = QPen(penClr);
    pen.setStyle(penStyle);
    pen.setWidth(penWidth);
    pen.setCapStyle(capStyle);
    painter->setPen(pen);

    /*
    QPolygonF polygon(pylist);
    QPainterPath path;
    path.moveTo(polygon.at(0));
    for(int i = 1; i < polygon.size();i++)
        path.lineTo(polygon.at(i));
    painter->drawPath(path);*/
    HPointFList list = getPointList();
    painter->drawPolyline(list);
    painter->restore();
}
