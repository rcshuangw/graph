﻿#include "hbaseobj.h"
#include <QVariant>
#include "htempcontainer.h"
HBaseObj::HBaseObj(HBaseObj *parent)
{
    m_pParent = parent;
    init();
    m_pIconGraphicsItem = NULL;
}

HBaseObj::~HBaseObj()
{
}

QString HBaseObj::tagName()
{
    return QString("base");
}

void HBaseObj::init()
{
    m_strObjName = QString("baseobj"); //对象名称
    m_eDrawShape = No;//图符类型(直线\圆)
    m_dOriginX = 0;//原点位置（x,y)
    m_dOriginY = 0;

    //线条方面
    m_strLineColor = "#000000";//线条颜色
	m_nLineWidth = 0;//线宽
	m_nLineStyle = (qint8)Qt::SolidLine;//线型
	m_nLineJoinStyle = (qint8)Qt::BevelJoin;//线连接处形状
	m_nLineCapStyle = (qint8)Qt::RoundCap;//线端形状

	m_fRotateAngle = 0.0;//旋转角度
	m_bHorizonTurn = false;//水平翻转
	m_bVerticalTurn = false;//垂直翻转
	m_bVisible = true;//是否显示
	m_bDeleted = false;//是否删除
	m_nZValue = 0;

	m_nPattern = 0;
    
    //bModify = false;
    //父图符
    m_pParent = NULL;
    m_bTempObj = false;
    m_bModify = false;
}

void HBaseObj::readData(int v,QDataStream *data)
{
    if(!data) return;
    QString s;
    quint8 n8;
    *data>>n8;
    m_eDrawShape = (DrawShape)n8;
    double ff;
    *data>>ff;
    m_dOriginX = ff;
    *data>>ff;
    m_dOriginY = ff;
    *data>>s;
    m_strLineColor = s;
    *data>>n8;
    m_nLineWidth = n8;
    *data>>n8;
    m_nLineStyle = n8;
    *data>>n8;
    m_nLineJoinStyle = n8;
    *data>>n8;
    m_nLineCapStyle = n8;
    
    float f;
    *data>>f;
    m_fRotateAngle = f;
	bool b;
	*data>>b;
    m_bHorizonTurn = b;
    *data>>b;
    m_bVerticalTurn = b;
    *data>>b;
    m_bVisible = b;
    *data>>b;
    m_bDeleted = b;
    quint64 n64;
    *data>>n64;
	m_nZValue = n64;
 
    *data>>n8;
    m_nPattern = n8;
    *data>>b;
    m_bModify = b;
}

void HBaseObj::writeData(int v,QDataStream *data)
{
    if(!data) return;
    //*data<<strObjName;
    //*data<<(quint32)nObjectId;
    *data<<(quint8)m_eDrawShape;
    *data<<(double)m_dOriginX;
    *data<<(double)m_dOriginY;
    *data<<(QString)m_strLineColor;
    *data<<(quint8)m_nLineWidth;
    *data<<(quint8)m_nLineStyle;
    *data<<(quint8)m_nLineJoinStyle;
    *data<<(quint8)m_nLineCapStyle;
    
    *data<<(float)m_fRotateAngle;
    *data<<(bool)m_bHorizonTurn;
    *data<<(bool)m_bVerticalTurn;
    *data<<(bool)m_bVisible;
    *data<<(bool)m_bDeleted;
    *data<<(quint64)m_nZValue;
    *data<<(quint8)m_nPattern;
    *data<<(bool)m_bModify;
}

void HBaseObj::readXml(int v,QDomElement* dom)
{
    if(!dom)
        return;

    m_strObjName = dom->attribute("ObjName");
    m_nObjectId = dom->attribute("ObjId").toUInt();
    m_eDrawShape = (DrawShape)dom->attribute("ObjType").toUInt();
    m_dOriginX = dom->attribute("X").toDouble();
    m_dOriginY = dom->attribute("Y").toDouble();
    m_strLineColor = dom->attribute("LineColor");
    m_nLineWidth = dom->attribute("LineWidth").toUInt();
    m_nLineStyle = dom->attribute("LineStyle").toUInt();
    m_nLineJoinStyle = dom->attribute("LineJoinStyle").toUInt();
    m_nLineCapStyle = dom->attribute("LineCapStyle").toUInt();
   
    m_fRotateAngle = dom->attribute("RotateAngle").toDouble();
    m_bHorizonTurn = dom->attribute("HorizonTurn").toInt();
    m_bVerticalTurn = dom->attribute("VerticalTurn").toInt();
    m_bVisible = dom->attribute("Visible").toInt();
	m_nZValue = dom->attribute("StackOrder").toInt();
    m_nPattern = dom->attribute("nPattern").toUInt();
}

void HBaseObj::writeXml(int v,QDomElement* dom)
{
    if(!dom)
        return;
    dom->setAttribute("ObjName",m_strObjName);
    dom->setAttribute("ObjId",m_nObjectId);
    dom->setAttribute("ObjType",m_eDrawShape); 
    dom->setAttribute("X",m_dOriginX);
    dom->setAttribute("Y",m_dOriginY);
    dom->setAttribute("LineColor",m_strLineColor);
    dom->setAttribute("LineWidth",m_nLineWidth);
    dom->setAttribute("LineStyle",m_nLineStyle);
    dom->setAttribute("LineJoinSytle",m_nLineJoinStyle);
    dom->setAttribute("LineCapSytle",m_nLineCapStyle);
    
    dom->setAttribute("RotateAngle",m_fRotateAngle);
    dom->setAttribute("HorizonTurn",m_bHorizonTurn);
    dom->setAttribute("VerticalTurn",m_bVerticalTurn);
    dom->setAttribute("Visible",m_bVisible);
    dom->setAttribute("StackOrder", m_nZValue);
    dom->setAttribute("nPattern",m_nPattern);

}

//拷贝克隆
void HBaseObj::copyTo(HBaseObj* obj)
{
    //id暂时不能复制 只能等到粘贴的时候才能赋值
    obj->m_eDrawShape = m_eDrawShape;
    obj->m_strObjName = m_strObjName;
    obj->m_nObjectId = m_nObjectId;
    obj->m_dOriginX = m_dOriginX;
    obj->m_dOriginY = m_dOriginY;
    obj->m_strLineColor = m_strLineColor;
    obj->m_nLineWidth = m_nLineWidth;
    obj->m_nLineStyle = m_nLineStyle;
    obj->m_nLineJoinStyle = m_nLineJoinStyle;
    obj->m_nLineCapStyle = m_nLineCapStyle;

    obj->m_fRotateAngle = m_fRotateAngle;
    obj->m_bHorizonTurn = m_bHorizonTurn;
    obj->m_bVerticalTurn = m_bVerticalTurn;
    obj->m_bVisible = m_bVisible;
    obj->m_bDeleted = m_bDeleted;
    obj->m_nZValue = m_nZValue;
    obj->m_nPattern = m_nPattern;
    obj->m_bModify = m_bModify;
    //obj->m_pParent = m_pParent;
}

//设置属性值 By Name
void HBaseObj::setObjName(const QString strName)
{
   m_strObjName = strName;
}

QString HBaseObj::getObjName()
{
   return m_strObjName;
}

int HBaseObj::getObjID()
{
    return m_nObjectId;
}

void HBaseObj::setObjID(int nObjID)
{
    m_nObjectId = nObjID;
}

void HBaseObj::setOX(double x)
{
    m_dOriginX = x;
}

void HBaseObj::setOY(double y)
{
    m_dOriginY = y;
}

double HBaseObj::getOX()
{
    return m_dOriginX;
}

double HBaseObj::getOY()
{
    return m_dOriginY;
}

//m_dOrigiX,m_dOrigiY总是映射于包容它的对象的原点后的值
//如果该对象存在于scene就是映射于scene原点后的位置,如果对象存在于另一个对象(父对象，如Group)中，则是映射于父对象原点后的值
//所以绝对坐标必须是二者相加
QPointF HBaseObj::pos(qint8 flag)
{
    HBaseObj* parObj = parent();
    if(!parObj)
        return QPointF(m_dOriginX,m_dOriginY);
    else if(flag & TRANS_ABSOLUTE)
    {
        return parObj->pos(flag) + QPointF(m_dOriginX,m_dOriginY);
    }
	return QPointF(m_dOriginX, m_dOriginY);
}

//形状类型
DrawShape HBaseObj::getShapeType()
{
    return (DrawShape)m_eDrawShape;
}

void HBaseObj::setShapeType(DrawShape t)
{
    m_eDrawShape = t;
}

//线条颜色
void HBaseObj::setLineColor(QString clrName)
{
    m_strLineColor = clrName;
}

QString HBaseObj::getLineColor()
{
   return m_strLineColor;
}

//线宽
void HBaseObj::setLineWidth(quint8 lineWidth)
{
    m_nLineWidth = lineWidth;
}

quint8 HBaseObj::getLineWidth()
{
    return m_nLineWidth;
}

void HBaseObj::setLineStyle(Qt::PenStyle style)
{
    m_nLineStyle = style;
}

Qt::PenStyle HBaseObj::getLineStyle()
{
    return (Qt::PenStyle)m_nLineStyle;
}

//线连接处形状
void HBaseObj::setLineJoinStyle(Qt::PenJoinStyle style)
{
    m_nLineJoinStyle = style;
}

Qt::PenJoinStyle HBaseObj::getLineJoinStyle()
{
    return (Qt::PenJoinStyle)m_nLineJoinStyle;
}

//线端形状
void HBaseObj::setLineCapStyle(Qt::PenCapStyle style)
{
    m_nLineCapStyle = style;
}

Qt::PenCapStyle HBaseObj::getLineCapStyle()
{
    return (Qt::PenCapStyle)m_nLineCapStyle;
}

//边框色
void HBaseObj::setBorderColor(const QString& s)
{

}

QString HBaseObj::getBorderColor()
{
    return QString();
}

//文字色
void HBaseObj::setTextColor(const QString& c)
{

}

QString HBaseObj::getTextColor()
{
    return QString();
}


void HBaseObj::setPattern(quint8 pattern)
{
    m_nPattern = pattern;
}

quint8 HBaseObj::getPattern()
{
    return m_nPattern;
}

//
void HBaseObj::resetParent(HBaseObj* obj)
{
    if(m_pParent == obj)
        return;
    HBaseObj* oldParent = m_pParent;
    //获取绝对坐标
    QPointF pt = pos(1);
    if(obj)
    {
        //相对于父对象原点的位置，后面还要进行坐标变换
        pt -= obj->pos(1);
        if(1)
        {
            HTempContainer* tc = (HTempContainer*)obj;
            tc->getObjList().append(this);
        }
    }
    m_pParent = obj;
    if(obj)
    {
        bool bok = false;
        QTransform trans;
        HBaseObj* o = obj;
        while(o && (o!=oldParent))
        {
            if(o->transform(trans,1,true))
                bok = true;
            o = o->parent();
        }
        if(bok)
            pt = trans.inverted().map(pt);
    }
    m_dOriginX = pt.x();
    m_dOriginY = pt.y();

    if(oldParent)
    {
        if(1)
        {
            HTempContainer* tc = (HTempContainer*)oldParent;
            int index = tc->getObjList().indexOf(this);
            if(index >= 0 && index < tc->getObjList().size())
                tc->getObjList().remove(index);
        }
    }

}

void HBaseObj::setParent(HBaseObj* obj)
{
    m_pParent = obj;
}

HBaseObj* HBaseObj::parent()
{
    return m_pParent;
}

//list中的点都是绝对坐标，变换操作后都是相对坐标
bool HBaseObj::setPointList(QPolygonF& list, qint8 flag)
{
	int i = 0; 
	int sz = list.size();
	if (flag)
	{
		QPointF pt = list.boundingRect().center();
		m_dOriginX = pt.x();
		m_dOriginY = pt.y();
		for (i = 0; i < sz; i++)
			list[i] -= pt;
	}
    if(!isTurned(flag) && !isRotated(flag))
        return true;
	QTransform mx;
    bool bok = transform(mx, 0);
	if (!bok)
		return true;
	mx = mx.inverted(&bok);
    //QPointF pt1 = mx.map(pos());
	if (!bok)
		return false;
	for (int i = 0; i < sz; i++)
		list[i] = mx.map(list[i]);

}

//设置转换
bool HBaseObj::transform(QTransform& transform1,quint8 flag,bool bNoTrans)
{
    bool bok = false;
    if(flag&TRANS_ABSOLUTE && !bNoTrans)
    {
        QPointF pt = QPointF(getOX(), getOY());
        transform1 = transform1.translate(pt.x(), pt.y());
        bok = true;
    }
    else if(flag&TRANS_PARENT && !bNoTrans)
    {
        transform1 = transform1.translate(m_dOriginX,m_dOriginY);
        bok = true;
    }
//
    if(isTurned(flag))
    {
		//transform1.translate(getOX(),getOY());
        if(m_bHorizonTurn)
        {
            transform1 = transform1.scale(-1,1);
            bok = true;
        }
        if(m_bVerticalTurn)
        {
            transform1 = transform1.scale(1,-1);
            bok = true;
        }
		//transform1.translate(-getOX(),-getOY());
    }

    if(isRotated(flag))
    {
		//transform1.translate(getOX(),getOY());
        transform1 = transform1.rotate(m_fRotateAngle);
        bok = true;
		//transform1.translate(-getOX(),-getOY());
    }

    return bok;
}

//改变大小
void HBaseObj::resize(double w, double h, bool scale)
{

}

QRectF HBaseObj::boundingRect(qint8 flag)
{
	QRectF rectF = getPointList(flag).boundingRect();
	return rectF;
}

//设置翻转
void HBaseObj::turn(bool bHorizon, bool bVertical)
{
    m_bHorizonTurn = bHorizon;
    m_bVerticalTurn = bVertical;
}

void HBaseObj::rotate(float fAngle)
{
	m_fRotateAngle = fAngle;
}

void HBaseObj::moveBy(double dx, double dy, bool bscale)
{
	if (bscale)
	{
		m_dOriginX += m_dOriginX * dx;
		m_dOriginY += m_dOriginY * dy;
	}
	else
	{
		m_dOriginX += dx;
		m_dOriginY += dy;
	}
}

void HBaseObj::move(double dx, double dy, bool bscale)
{
	if (bscale)
	{
		m_dOriginX = m_dOriginX * dx;
		m_dOriginY = m_dOriginY * dy;
	}
	else
	{
		m_dOriginX = dx;
		m_dOriginY = dy;
	}
}

//设置映射
void HBaseObj::maps(QPolygonF& pylist,quint8 flag)
{
    QTransform trans;
    transform(trans,flag);
    pylist = trans.map(pylist);
}

bool HBaseObj::isZero(double value)
{
    if(value == 0.0)
    {
        return true;
    }
    if(((value>0.0) && (value<0.0001))||((value<0.0)&&(value>-0.0001)))
    {
        return true;
    }
    return false;
}

bool HBaseObj::isRotated(qint8 flag)
{
    return !( (flag&TRANS_NO_ROTATE)||isZero(m_fRotateAngle));
}

//翻转
bool HBaseObj::isTurned(qint8 flag)
{
    return(!(flag&TRANS_NO_TURN))&&(m_bHorizonTurn || m_bVerticalTurn);
}

float HBaseObj::rotateAngle()
{
    return m_fRotateAngle;
}

//增加一个角度
void HBaseObj::rotateBy(float fAngle)
{
    m_fRotateAngle += fAngle;
}

void HBaseObj::setModify(bool modify)
{
    m_bModify = modify;
}

bool HBaseObj::isModify()
{
    return m_bModify;
}

void HBaseObj::setVisible(bool bvisible,int nFlag)
{
    m_bVisible = bvisible;
}

bool HBaseObj::isVisible()
{
    return m_bVisible;
}

void HBaseObj::setDeleted(bool bDel)
{
    m_bDeleted = bDel;
}

bool HBaseObj::isDeleted()
{
    return m_bDeleted;
}

//就是zValue
qint64 HBaseObj::zValue()
{
    return m_nZValue;
}

void HBaseObj::setZValue(qint64 nStack)
{
	m_nZValue = nStack;
}

bool HBaseObj::containsPattern(int nPatternId)
{
    return m_nPattern == nPatternId;
}

bool HBaseObj::contains(const QPointF &point)
{
    QRectF rectF = getPointList(0).boundingRect();
    return shape(1).contains(point);
}

void HBaseObj::setPainter(QPainter* painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::TextAntialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    qint8 flag = 0;
    HBaseObj* parObj = parent();
    if(parObj && parObj->getShapeType() == Group)
    {
        flag|=TRANS_PARENT;
    }
    else if(parObj && (parObj->getShapeType() == Icon||parObj->getShapeType() == Normal))
    {
        if(parObj->parent())
            flag|= TRANS_PARENT;
    }
    QTransform trans;
    if(transform(trans,flag))
    {
        painter->setTransform(trans,true);
    }
    //设置属性
    QColor penClr = QColor(getLineColor()); //线条颜色
    int penWidth = getLineWidth();//线条宽度
    Qt::PenStyle penStyle = getLineStyle(); //线条形状
    Qt::PenCapStyle capStyle = getLineCapStyle(); //线条角度
    QPen pen = QPen(penClr);
    pen.setStyle(penStyle);
    pen.setWidth(penWidth);
    pen.setCapStyle(capStyle);
    painter->setPen(pen);
}

void HBaseObj::paint(QPainter* painter)
{


}

void HBaseObj::setIconGraphicsItem(H5GraphicsItem* item)
{
    m_pIconGraphicsItem = item;
}

H5GraphicsItem* HBaseObj::iconGraphicsItem()
{
    return m_pIconGraphicsItem;
}

bool HBaseObj::isHorizonTurn()
{
    return m_bHorizonTurn;
}

bool HBaseObj::isVerticalTurn()
{
    return m_bVerticalTurn;
}
