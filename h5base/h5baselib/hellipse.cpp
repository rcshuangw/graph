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

QString HEllipse::TagName()
{
    return "Ellipse";
}

QPainterPath HEllipse::shape(qint8 flag)
{
    QPainterPath path;

    QRect rectF = boundingRect(flag);
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
    path.addPath(path);
    return path;
}


