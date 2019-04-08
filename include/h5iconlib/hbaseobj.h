#ifndef HBASEOBJ_H
#define HBASEOBJ_H
#include <qmath.h>
#include <QObject>
#include <QColor>
#include <QVector>
#include <QDataStream>
#include <QDomElement>
#include <QPainterPath>
#include <QPainter>
#include <QTransform>
#include "hiconapi.h"
#include "h5iconlibexport.h"
#include "h5graphicsitem.h"

class H5ICONLIB_EXPORT HBaseObj: public QObject
{
public:
    HBaseObj(QObject *parent = 0);
    virtual ~HBaseObj();

public:
    void init();

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

    virtual void setObjName(const QString strName);//
    virtual QString getObjName();
    //形状类型
    virtual DrawShape getShapeType();
    virtual void setShapeType(DrawShape t);

    //ObjID
    virtual int getObjID();
    virtual void setObjID(int nObjID);

    //线条颜色
    virtual void setLineColorName(QString clrName);
    virtual QString getLineColorName();

    //线宽
    virtual void setLineWidth(quint8 lineWidth);
    virtual quint8 getLineWidth();

    virtual void setLineStyle(Qt::PenStyle style);
    virtual Qt::PenStyle getLineStyle();

    //线连接处形状
    virtual void setLineJoinStyle(Qt::PenJoinStyle style);
    virtual Qt::PenJoinStyle getLineJoinStyle();

    //线端形状
    virtual void setLineCapStyle(Qt::PenCapStyle style);
    virtual Qt::PenCapStyle getLineCapStyle();



    //边框色
    virtual void setBorderColor(const QColor* c);
    virtual QColor getBorderColor();

    //文字色
    virtual void setTextColor(const QColor* c);
    virtual QColor getTextColor();

    //是否可见
    virtual void setVisible(bool,int nFlag = 0);
    virtual bool isVisible();

    //是否删除
    virtual void setDeleted(bool bDel);
    virtual bool isDeleted();

    //叠放次序
    qint64 getStackOrder();
    virtual void setStackOrder(qint64 nStack);

    void setPattern(quint8 pattern);
    quint8 getPattern();

	///区域位置大小
	virtual QRectF getBounding(qint8 flag = 0);

	///绘图路径
	virtual QPainterPath getShape(qint8 flag = 0) = 0;

	///绝对坐标
	virtual bool setPointList(QPolygonF& list, qint8 flag = 1);

	///相对坐标
	///flag:bit0是否绝对坐标, bit1是否不旋转, bit2是否不翻转
	virtual QPolygonF getPointList(qint8 flag = 0) = 0;

    ///////////////////////////////////////////////////////操作属性/////////////////////////////
    //设置转换
    virtual bool getTransform(QTransform& transform,quint8 flag);

    //设置映射
    virtual void Maps(QPolygonF& pylist,quint8 flag);

    //是否0值
    virtual bool isZero(double value);

    /////////////////////////////////////旋转//////////////////////////////
    //是否旋转
    virtual bool isRotated();

    //旋转角度
    virtual void Rotate(float fAngle);
    virtual float rotateAngle();

    //增加角度
    virtual void RotateBy(float fAngle);

    //翻转
    virtual bool isTurned(qint8 nFlag);

    //设置翻转
    virtual void turn(bool bHorizon,bool bVertical);

	virtual void move(qreal dx, qreal dy, bool bscale = false);
	virtual void moveBy(qreal dx, qreal dy);


    //obj的当前位置
    QPointF pos();

    virtual void setOX(double x);
    virtual double getOX();
    virtual void setOY(double y);
    virtual double getOY();

    virtual void setModify(bool modify);
    virtual bool getModify();

    //当前画面的比例缩放
    double curZoomScale();

    bool contains(int nPatternId);

   

    //设置item对象
    virtual void setIconGraphicsItem(H5GraphicsItem* item);
    virtual H5GraphicsItem* getIconGraphicsItem();

    //改变大小
    virtual void resize(double w,double h);
    virtual void resetRectPoint(const QPointF& pt1,const QPointF& pt2);
    //void setSubObjRect(qreal dx,qreal dy);

public:
    virtual void paint(QPainter* painter);
    virtual QRectF boundingRect() const;
    virtual bool contains(const QPointF &point) const;
    virtual QPainterPath shape() const;

//绘制对象的属性
public:

    //基本信息
    QString strObjName; //对象名称
    double originX;//原点位置（x,y)
    double originY;

    float fRotateAngle;//旋转角度
    QString strLineColor;//线条颜色
    quint8 nLineWidth;//线宽
    quint8 nLineStyle;//线型
    quint8 nLineJoinStyle;//线连接处形状
    quint8 nLineCapStyle;//线端形状

    bool bHorizonTurn;//水平翻转
    bool bVerticalTurn;//垂直翻转
    bool bVisible;//是否显示
    bool bDeleted;//是否删除

    qint64 nStackOrder;
    quint8 nPattern;

    H5GraphicsItem* pIconGraphicsItem;
    DrawShape m_eDrawShape;//图符类型(直线\圆)

    //对象标识ID
    quint32 nObjectId;

private:

protected:

    //父图符
    HBaseObj* m_pParent;


};


#endif // HBASEOBJ_H
