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
#include "h5baselibexport.h"
#include "h5graphicsitem.h"
typedef QPolygonF HPointFList;
class H5BASELIB_EXPORT HBaseObj: public QObject
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
    qint64 zValue();
    virtual void setZValue(qint64 nStack);

    void setPattern(quint8 pattern);
    quint8 getPattern();
//////////////////////////////////////////////////////////////////////////////////////////////////////
	///绝对坐标
	virtual bool setPointList(QPolygonF& list, qint8 flag = 1);
	virtual QPolygonF getPointList(qint8 flag = 0) = 0;

	virtual void setOX(double x);
	virtual double getOX();
	virtual void setOY(double y);
	virtual double getOY();

	virtual void setModify(bool modify);
	virtual bool isModify();

	QPointF pos();
    ///////////////////////////////////////////////////////操作属性/////////////////////////////
	//改变大小
	virtual void resize(double w, double h, bool scale);
	virtual void resetRectPoint(const QPointF& pt1, const QPointF& pt2);
    virtual bool transform(QTransform& transform1,quint8 flag);
    virtual void maps(QPolygonF& pylist,quint8 flag);
	virtual void rotate(float fAngle);
	virtual void turn(bool bHorizon, bool bVertical);

	virtual void move(qreal dx, qreal dy, bool bscale = false);
	virtual void moveBy(qreal dx, qreal dy,bool bscale = false);
    
	virtual bool isZero(double value);
	virtual bool isTurned(qint8 nFlag);
    virtual bool isRotated();

    virtual float rotateAngle();
    virtual void rotateBy(float fAngle);//add rotate

   
    
    //当前画面的比例缩放
    double curZoomScale();

    bool containsPattern(int nPatternId);

   

    //设置item对象
    virtual void setIconGraphicsItem(H5GraphicsItem* item);
    virtual H5GraphicsItem* iconGraphicsItem();

    virtual bool isHorizonTurn();//水平翻转
    virtual bool isVerticalTurn();//垂直翻转

    //void setSubObjRect(qreal dx,qreal dy);
public:
	void addPointList(QPolygonF& list, qint8 flag);
	void pointList(QPolygonF&list,qint8 flag);
	void clearPointList();
public:
	virtual QRectF boundingRect(qint8 flag = 0);
	virtual QPainterPath shape(qint8 flag = 0) = 0;
    virtual void paint(QPainter* painter) = 0;
  //  virtual QRectF boundingRect() const;
    virtual bool contains(const QPointF &point) const;
   // virtual QPainterPath shape() const;

//绘制对象的属性
protected:

    //基本信息
    QString m_strObjName; //对象名称
	DrawShape m_eDrawShape;
    double m_dOriginX;//原点位置（x,y)
    double m_dOriginY;

    float m_fRotateAngle;//旋转角度
    QString m_strLineColor;//线条颜色
    quint8 m_nLineWidth;//线宽
    quint8 m_nLineStyle;//线型
    quint8 m_nLineJoinStyle;//线连接处形状
    quint8 m_nLineCapStyle;//线端形状

    bool m_bHorizonTurn;//水平翻转
    bool m_bVerticalTurn;//垂直翻转
    bool m_bVisible;//是否显示
    bool m_bDeleted;//是否删除
	bool m_bModify;

    qint64 m_nZValue;
    quint8 m_nPattern;

    H5GraphicsItem* m_pIconGraphicsItem;

    //对象标识ID
    quint32 m_nObjectId;

private:
	QHash<qint8, QPolygonF> m_points;
protected:

    //父图符
    HBaseObj* m_pParent;


};


#endif // HBASEOBJ_H
