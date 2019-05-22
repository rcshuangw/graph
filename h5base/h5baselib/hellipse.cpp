#include "hellipse.h"
/////////////////////////////////////HRectObj//////////////////////////////////////
HEllipse::HEllipse()
    :HRectangle()
{
    m_eDrawShape = Ellipse;
}

HEllipse::~HEllipse()
{

}

QString HEllipse::tagName()
{
    return "Ellipse";
}

QPainterPath HEllipse::shape(qint8 flag)
{
    QPainterPath path;

    QRectF rectF = boundingRect(flag);
    QPainterPath p;
    if (m_bFill && m_nFillWay > 0)
    {
        p.addEllipse(rectF);
    }
    else
    {
        int n = getLineWidth();
        if(n < 5) n = 5;
        p.addEllipse(rectF.adjusted(n,n,-n,-n));
        p.addEllipse(rectF.adjusted(-n,-n,n,n));
    }
    path.addPath(p);
    return path;
}

void HEllipse::paint(QPainter *painter)
{
    if (!painter)
        return;
    painter->save();
    HShapeObj::setPainter(painter);
    QPainterPath path;
    path.addEllipse(m_rect);
    painter->drawPath(path);

    painter->restore();
}


