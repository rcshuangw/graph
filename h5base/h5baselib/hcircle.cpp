#include "hcircle.h"
/////////////////////////////////////HCircle//////////////////////////////////////
HCircle::HCircle()
    :HEllipse()
{
    m_eDrawShape = Circle;
}

HCircle::~HCircle()
{

}

QString HCircle::tagName()
{
    return "Circle";
}

void HCircle::resize(double w, double h, bool scale )
{
    HShapeObj::resize(w,h,scale);
}

bool HCircle::setPointList(QPolygonF& list, qint8 flag)
{
    HShapeObj::setPointList(list,flag);
    double v = qMin(m_width,m_height);
    m_width = v;
    m_height = v;
    return true;
}
