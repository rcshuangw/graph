#include "harc.h"
///////////////////////////////////////////////HArcObj//////////////////////////////////////
HArc::HArc()
{
    setShapeType(Arc);
    m_nStartAngle = 30;
    m_nSweepLength = 120;
}

//二进制读写
void HArc::readData(int v,QDataStream* data)
{
    if(!data) return;
    HLine::readData(v,data);
    int n;
    *data>>n;
    m_nStartAngle = n;
    *data>>n;
    m_nSweepLength = n;
}

void HArc::writeData(int v,QDataStream* data)
{
    if(!data) return;
    HLine::writeData(v,data);
    *data<<(int)m_nStartAngle;
    *data<<(int)m_nSweepLength;
}

void HArc::readXml(int v,QDomElement* dom)
{
    if(!dom) return;
    HLine::readXml(v,dom);
    m_nStartAngle = dom->attribute("StartAngle").toInt();
    m_nSweepLength = dom->attribute("SweepLength").toInt();
}

void HArc::writeXml(int v,QDomElement* dom)
{
    if(!dom)return;
    HLine::writeXml(v,dom);
    dom->setAttribute("StartAngle",m_nStartAngle);
    dom->setAttribute("SweepLength",m_nSweepLength);
}

QString HArc::TagName()
{
    return "Arc";
}

//拷贝克隆
void HArc::copyTo(HBaseObj* obj)
{
    HArc* ob = (HArc*)obj;
    HLine::copyTo(obj);
    ob->m_nStartAngle = m_nStartAngle;
    ob->m_nSweepLength = m_nSweepLength;
}

void HArc::setStartAngle(int sAngle)
{
    m_nStartAngle = sAngle;
}

int HArc::startAngle()
{
    return m_nStartAngle;
}

void HArc::setSweepLength(int spanangle)
{
    m_nSweepLength = spanangle;
}

int HArc::sweepLength()
{
    return m_nSweepLength;
}

QRectF HArc::boundingRect(qint8 flag)
{
    QRectF rectF(ptHeadPoint,ptTailPoint);
    QPolygonF list;
    list.append(rectF.topLeft());
    list.append(rectF.topRight());
    list.append(rectF.bottomRight());
    list.append(rectF.bottomLeft());
    maps(list, flag);
    return list.boundingRect();
}

QPainterPath HArc::shape(qint8 flag)
{
    QPainterPath path;
    path.arcTo(boundingRect(0),m_nStartAngle,m_nSweepLength);
    QTransform trans;
    transform(trans,flag);
    path = trans.map(path);
    return path;
}

void HArc::paint(QPainter* painter)
{
    painter->save();
    setPainter(painter);//设置Painter
    QRectF rectF = getPointList(TRANS_NO_ROTATE|TRANS_NO_TURN).boundingRect();
    QPainterPath path;
    path.arcMoveTo(rectF,m_nStartAngle);
    path.arcTo(rectF,m_nStartAngle,m_nSweepLength);
    painter->drawPath(path);
    painter->restore();
}
