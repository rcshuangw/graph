#include "hbaseobj.h"
#include <QVariant>

HBaseObj::HBaseObj(QObject *parent) : QObject(parent)
{
    init();
    m_pIconGraphicsItem = NULL;
}

HBaseObj::~HBaseObj()
{
}

QString HBaseObj::TagName()
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
	m_strLineColor = "#00FF00";//线条颜色
	m_nLineWidth = 0;//线宽
	m_nLineStyle = (qint8)Qt::SolidLine;//线型
	m_nLineJoinStyle = (qint8)Qt::BevelJoin;//线连接处形状
	m_nLineCapStyle = (qint8)Qt::RoundCap;//线端形状

	m_fRotateAngle = 0.0;//旋转角度
	m_bHorizonTurn = false;//水平翻转
	m_bVerticalTurn = false;//垂直翻转
	m_bVisible = true;//是否显示
	m_bDeleted = false;//是否删除
	m_nStackOrder = 0;

	m_nPattern = 0;
    
    //bModify = false;
    //父图符
    m_pParent = NULL;
}

void HBaseObj::readData(QDataStream *data)
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
    m_bVisible = n8;
    *data>>b;
    m_bDeleted = b;
    quint64 n64;
    *data>>n64;
    m_nStackOrder = n64;
 
    *data>>n8;
    m_nPattern = n8;
    *data>>b;
    m_bModify = b;
    *data>>b;
}

void HBaseObj::writeData(QDataStream *data)
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
    *data<<(quint64)m_nStackOrder;
    *data<<(quint8)m_nPattern;
    *data<<(bool)m_bModify;
}

void HBaseObj::readXml(QDomElement* dom)
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
    m_nStackOrder = dom->attribute("StackOrder").toInt();
    m_nPattern = dom->attribute("nPattern").toUInt();
}

void HBaseObj::writeXml(QDomElement* dom)
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
    dom->setAttribute("StackOrder",m_nStackOrder);
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
    obj->m_nStackOrder = m_nStackOrder;
    obj->m_nPattern = m_nPattern;
    obj->m_bModify = m_bModify;
}

void HBaseObj::clone(HBaseObj* ob)
{
    if(!ob) return;
    HBaseObj::copyTo(ob);
}

//设置属性值 By Name
void HBaseObj::setObjName(const QString strName)
{
   strObjName = strName;
}

QString HBaseObj::getObjName()
{
   return strObjName;
}

int HBaseObj::getObjID()
{
    return nObjectId;
}

void HBaseObj::setObjID(int nObjID)
{
    nObjectId = nObjID;
}

void HBaseObj::setOX(double x)
{
    originX = x;
}

void HBaseObj::setOY(double y)
{
    originY = y;
}

double HBaseObj::getOX()
{
    return originX;
}

double HBaseObj::getOY()
{
    return originY;
}

//形状类型
DRAWSHAPE HBaseObj::getShapeType()
{
    return (DRAWSHAPE)drawShape;
}

void HBaseObj::setShapeType(DRAWSHAPE t)
{
    drawShape = t;
}

//线条颜色
void HBaseObj::setLineColorName(QString clrName)
{
    strLineColor = clrName;
}

QString HBaseObj::getLineColorName()
{
   return strLineColor;
}

//线宽
void HBaseObj::setLineWidth(quint8 lineWidth)
{
    nLineWidth = lineWidth;
}

quint8 HBaseObj::getLineWidth()
{
    return nLineWidth;
}

void HBaseObj::setLineStyle(Qt::PenStyle style)
{
    nLineStyle = style;
}

Qt::PenStyle HBaseObj::getLineStyle()
{
    return (Qt::PenStyle)nLineStyle;
}

//线连接处形状
void HBaseObj::setLineJoinStyle(Qt::PenJoinStyle style)
{
    nLineJoinStyle = style;
}

Qt::PenJoinStyle HBaseObj::getLineJoinStyle()
{
    return (Qt::PenJoinStyle)nLineJoinStyle;
}

//线端形状
void HBaseObj::setLineCapStyle(Qt::PenCapStyle style)
{
    nLineCapStyle = style;
}

Qt::PenCapStyle HBaseObj::getLineCapStyle()
{
    return (Qt::PenCapStyle)nLineCapStyle;
}

//边框色
void HBaseObj::setBorderColor(const QColor* c)
{

}

QColor HBaseObj::getBorderColor()
{
    return QColor();
}

//文字色
void HBaseObj::setTextColor(const QColor* c)
{

}

QColor HBaseObj::getTextColor()
{
    return QColor();
}


void HBaseObj::setPattern(quint8 pattern)
{
    nPattern = pattern;
}

quint8 HBaseObj::getPattern()
{
    return nPattern;
}




//设置转换
bool HBaseObj::getTransform(QTransform& transform,quint8 flag)
{
    bool bok = false;
    quint8 nFlag = flag;

    if(isTurned(nFlag))
    {
        transform.translate(getOX(),getOY());
        if(bHorizonTurn)
        {
            transform.scale(-1,1);
            bok = true;
        }
        if(bVerticalTurn)
        {
            transform.scale(1,-1);
            bok = true;
        }
        transform.translate(-getOX(),-getOY());
    }

    if(isRotated())
    {
        transform.translate(getOX(),getOY());
        transform.rotate(fRotateAngle);
        bok = true;
        transform.translate(-getOX(),-getOY());
    }

    return bok;
}

//设置映射
void HBaseObj::Maps(QPolygonF& pylist,quint8 flag)
{
    QTransform transform;
    getTransform(transform,flag);
    pylist = pylist*transform;
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

bool HBaseObj::isRotated()
{
    return !isZero(fRotateAngle);
}

//旋转角度
void HBaseObj::setRotateAngle(float rotate)
{
    fRotateAngle = rotate;
}

float HBaseObj::getRotateAngle()
{
    return fRotateAngle;
}

//增加一个角度
void HBaseObj::setRotateAdd(float fAngle)
{
    fRotateAngle += fAngle;
}

//翻转
bool HBaseObj::isTurned(qint8 nFlag)
{
    return (bHorizonTurn||bVerticalTurn);
}

void HBaseObj::setModify(bool modify)
{
    bModify = modify;
}

bool HBaseObj::getModify()
{
    return bModify;
}

//设置翻转
void HBaseObj::setTurn(bool bHorizon,bool bVertical)
{
    bHorizonTurn = bHorizon;
    bVerticalTurn = bVertical;
}

//是否可见
void HBaseObj::setVisible(bool bvisible,int nFlag)
{
    bVisible = bvisible;
}

bool HBaseObj::isVisible()
{
    return bVisible;
}

//是否删除
void HBaseObj::setDeleted(bool bDel)
{
    bDeleted = bDel;
}

bool HBaseObj::isDeleted()
{
    return bDeleted;
}

//叠放次序
qint64 HBaseObj::getStackOrder()
{
    return nStackOrder;
}

void HBaseObj::setStackOrder(qint64 nStack)
{
    nStackOrder = nStack;
}

bool HBaseObj::contains(int nPatternId)
{
    return nPattern == nPatternId;
}

void HBaseObj::move(qreal dx, qreal dy,bool bscale)
{
    if(bscale)
    {
        originX = originX * dx;
        originY = originY * dy;
    }
    else
    {
        originX = dx;
        originY = dy;
    }
}

void HBaseObj::moveBy(qreal dx, qreal dy,bool bscale)
{
    if(bscale)
    {
        originX += originX * dx;
        originY += originY * dy;
    }
    else
    {
        originX += dx;
        originY += dy;
    }
}

void HBaseObj::paint(QPainter* painter)
{

}

//设置item对象
void HBaseObj::setIconGraphicsItem(HIconGraphicsItem* item)
{
    pIconGraphicsItem = item;
}

HIconGraphicsItem* HBaseObj::getIconGraphicsItem()
{
    return pIconGraphicsItem;
}

void HBaseObj::resize(double w,double h)
{

}

void HBaseObj::resetRectPoint(const QPointF& pt1,const QPointF& pt2)
{

}

QRectF HBaseObj::boundingRect() const
{
    return QRectF();
}

bool HBaseObj::contains(const QPointF &point) const
{
    return false;
}

QPainterPath HBaseObj::shape() const
{
    return QPainterPath();

}

void HBaseObj::setImagePath(const QString& path)
{
    strImagePath = path;
}

QString HBaseObj::getImagePath()
{
    return strImagePath;
}

bool HBaseObj::isValidImagePath() const
{
    return !strImagePath.isEmpty() && !strImagePath.isNull();
}

void HBaseObj::setKeepImageRatio(bool bcheck)
{
    bKeepImageRatio = bcheck;
}

bool HBaseObj::getKeepImageRatio()
{
    return bKeepImageRatio;
}

void HBaseObj::setImageDirect(quint8 direct)
{
    nImageDirect = direct;
}

quint8 HBaseObj::getImageDirect()
{
    return nImageDirect;
}

