#ifndef HELLIPSE_H
#define HELLIPSE_H
#include "hrectangle.h"
//////////////////////////////////////////////////////////////////////////////////////
class H5BASELIB_EXPORT HEllipse : public HRectangle
{
public:
    HEllipse();
    virtual ~HEllipse();
public:
    virtual QString tagName();
    virtual QPainterPath shape(qint8 flag = 0);
    virtual void paint(QPainter* painter);

};


#endif // HRECTANGLE_H
