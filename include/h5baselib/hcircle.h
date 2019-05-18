#ifndef HCIRCLE_H
#define HCIRCLE_H
#include "hellipse.h"
///////////////////////////////////////////HRectangleObj///////////////////////////////////////////
class H5BASELIB_EXPORT HCircle : public HEllipse
{
public:
    HCircle();
    virtual ~HCircle();
public:
    virtual QString tagName();
    virtual void resize(double w, double h, bool scale = false);
    virtual bool setPointList(QPolygonF& list, qint8 flag = 1);

};


#endif // HCIRCLE_H
