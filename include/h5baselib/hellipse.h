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
    virtual QString TagName();
    virtual QPainterPath shape(qint8 flag = 0);

};


#endif // HRECTANGLE_H
