#ifndef HDRAWHELPER_H
#define HDRAWHELPER_H
#include "h5basehelpexport.h"
#include "hbaseobj.h"
class H5BASEHELP_EXPORT HDrawHelper
{
public:
    HDrawHelper();
    ~HDrawHelper();

public:
    void setBaseObj(HBaseObj* pObj);
    HPointsList selectedPointList();
    HPointsList getMidPoints(HPointsList points,bool bclose = true);
    void updatePoints();

    void ratate(int angle,QPointF* c=0);
    void turn(bool b,QPointF* c = 0);

    QCursor cursor(int index);

private:
    QCursor cursorOnPoint(DrawShape drawShape,int index);
    HPointsList selectedPointList(DrawShape drawshape);


private:
    HBaseObj* m_pBaseObj;
};
#endif // HDRAWHELPER_H
