#ifndef HRECTANGLE_H
#define HRECTANGLE_H
#include "hshapeobj.h"

///////////////////////////////////////////HRectangleObj///////////////////////////////////////////
class H5ICONLIB_EXPORT HRectangle : public HShapeObj
{
public:
    HRectangle();
    virtual ~HRectangle();

    //二进制读写
    virtual void readData(QDataStream* data);
    virtual void writeData(QDataStream* data);

    //xml文件读写
    virtual void readXml(QDomElement* data);
    virtual void writeXml(QDomElement* data);

    virtual QString TagName();

    //拷贝克隆
    virtual void copyTo(HBaseObj* obj);
    virtual void clone(HBaseObj* obj);

    //与QGraphicsItem相关
    virtual DRAWSHAPE getShapeType();
    virtual void moveBy(qreal dx,qreal dy);
    virtual void resize(double w,double h);
    virtual void paint(QPainter* painter);
    virtual void setPainter(QPainter* painter,const QRectF& rect);
    virtual QRectF boundingRect();
    virtual bool contains(const QPointF &point) ;
    virtual QPainterPath shape() ;
    virtual void resetRectPoint(const QPointF& pt1,const QPointF& pt2);
    virtual void setObjRect(const QRectF& rect);
    virtual QRectF getObjRect();



    //设置相关属性
    virtual void setTopLeft(const QPointF& point);
    virtual QPointF getTopLeft();
    virtual void setRectWidth(double width);
    virtual double getRectWidth();
    virtual void setRectHeight(double height);
    virtual double getRectHeight();
    virtual QPolygonF getRectLists();


    //设置其他功能
    virtual QPainterPath getPath();//只提供矩形，圆，椭圆，文字三种支持图片
    //设置绘制选择状态
    virtual void drawSelect(QPainter* painter);//单个选择
    virtual void drawMulSelect(QPainter* painter,bool benchmark); //多选择

public:
    QPointF ptOld,ptNew;
protected:
    QPointF topLeft;
    double rectWidth;
    double rectHeight;
};


#endif // HRECTANGLE_H
