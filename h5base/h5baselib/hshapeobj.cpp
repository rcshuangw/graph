#include "hshapeobj.h"
#include "hrectangle.h"
HShapeObj::HShapeObj()
{
	m_bFill = false;
    m_nFillWay = 0;
	m_nFillStyle = (quint8)Qt::NoBrush;
	m_strFillColor = "#00FF00"; //填充颜色
	m_nFillDirection = DIRECT_BOTTOM_TO_TOP;
	m_nFillPercentage = 100;

	//边框透明度
	m_bFrameSee = true;
	m_nTransparency = 0; 
	
	//图片
	m_strImagePath = "";
    m_bKeepImageRatio = false;
    m_nImageDirect = 0;

    m_width = m_height = 50;
}

HShapeObj::~HShapeObj()
{

}

//二进制读写
void HShapeObj::readData(int v,QDataStream* data)
{
	if (!data) return;
    HBaseObj::readData(v,data);
    double r;
	*data >> r;
	m_width = r;
	*data >> r;
	m_height = r;
    //resize(m_width, m_height);
	quint8 n8;
	*data >> n8;
	m_nFillWay = n8;
	*data >> n8;
	m_nFillStyle = n8;
	QString s;
	*data >> s;
	m_strFillColor = s;
	*data >> n8;
	m_nFillDirection = n8;
	*data >> n8;
	m_nFillPercentage = n8;
	bool b;
	*data >> b;
	m_bFrameSee = b;
	*data >> n8;
	m_nTransparency = n8;
	*data >> s;
	m_strImagePath = s;
	*data >> b;
	m_bKeepImageRatio = b;
	*data >> n8;
	m_nImageDirect = n8;
}

void HShapeObj::writeData(int v,QDataStream* data)
{
	if (!data) return;
    HBaseObj::writeData(v,data);
    *data << (double)m_width;
    *data << (double)m_height;
	*data << (quint8)m_nFillWay;
	*data << (quint8)m_nFillStyle;
	*data << (QString)m_strFillColor;
	*data << (quint8)m_nFillDirection;
	*data << (quint8)m_nFillPercentage;
	*data << (bool)m_bFrameSee;
	*data << (quint8)m_nTransparency;
	*data << (QString)m_strImagePath;
	*data << (bool)m_bKeepImageRatio;
	*data << (quint8)m_nImageDirect;
}

//xml文件读写
void HShapeObj::readXml(int v,QDomElement* dom)
{
	if (!dom)
		return;
    HBaseObj::readXml(v,dom);
	m_width = dom->attribute("Width").toDouble();
	m_height = dom->attribute("Height").toDouble();
	m_nFillWay = dom->attribute("FillWay").toUInt();
	m_nFillStyle = dom->attribute("FillStyle").toUInt();
	m_strFillColor = dom->attribute("FillColor");
	m_nFillDirection = dom->attribute("FillDirection").toUInt();
	m_nFillPercentage = dom->attribute("nFillPercentage").toUInt();
	m_bFrameSee = (bool)dom->attribute("FrameSee").toUInt();
	m_nTransparency = dom->attribute("Transparency").toUInt();
	m_strImagePath = dom->attribute("ImagePath");
	m_bKeepImageRatio = dom->attribute("KeepImageRadio").toUInt();
	m_nImageDirect = dom->attribute("ImageDirect").toUInt();
}

void HShapeObj::writeXml(int v,QDomElement* dom)
{
	if (!dom)
		return;
    HBaseObj::writeXml(v,dom);
	dom->setAttribute("Width", m_width);
	dom->setAttribute("Height", m_height);
	dom->setAttribute("FillWay", m_nFillWay);
	dom->setAttribute("FillStyle", m_nFillStyle);
	dom->setAttribute("FillColor", m_strFillColor);
	dom->setAttribute("FillDirection", m_nFillDirection);
	dom->setAttribute("FillPercentage", m_nFillPercentage);
	dom->setAttribute("FrameSee", m_bFrameSee);
	dom->setAttribute("Transparency", m_nTransparency);
	dom->setAttribute("ImagePath", m_strImagePath);
	dom->setAttribute("KeepImageRadio", m_bKeepImageRatio);
	dom->setAttribute("ImageDirect", m_nImageDirect);
}

QString HShapeObj::tagName()
{
	return "Shape";
}

//拷贝克隆
void HShapeObj::copyTo(HBaseObj* ob)
{
	if (!ob) return;
	HBaseObj::copyTo(ob);
	HShapeObj* obj = (HShapeObj*)ob;
	obj->m_width = m_width;
	obj->m_height = m_height;
	obj->m_nFillWay = m_nFillWay;
	obj->m_nFillStyle = m_nFillStyle;
	obj->m_strFillColor = m_strFillColor;
	obj->m_nFillDirection = m_nFillDirection;
	obj->m_nFillPercentage = m_nFillPercentage;
	obj->m_bFrameSee = m_bFrameSee;
	obj->m_nTransparency = m_nTransparency;
	obj->m_strImagePath = m_strImagePath;
	obj->m_bKeepImageRatio = m_bKeepImageRatio;
	obj->m_nImageDirect = m_nImageDirect;
}

//变化可能是按比例也可能是直接更改w,h
void HShapeObj::resize(double w, double h, bool scale)
{
	HBaseObj::resize(w, h, scale);
	if (scale)
	{
		m_width = m_width * w;
		m_height = m_height * h;
	}
	else
	{
		m_width = w;
		m_height = h;
	}
}

void HShapeObj::expand(double dx1, double dx2, double dy1, double dy2, qint8 flag)
{

}

///绝对坐标
bool HShapeObj::setPointList(QPolygonF& list, qint8 flag)
{
	HBaseObj::setPointList(list, flag);
	QRectF rect = list.boundingRect();
	m_width = rect.width();
	m_height = rect.height();
	return true;
}

///获取点列表
QPolygonF HShapeObj::getPointList(qint8 flag)
{
	QPointF po(-m_width / 2, -m_height / 2);
	QRectF rect(po, QSizeF(m_width, m_height));
	QPolygonF list;
	if (qFuzzyCompare(m_height, 0) || qFuzzyCompare(m_width, 0))
	{
		return list;
	}
	list.append(rect.topLeft());
	list.append(rect.topRight());
	list.append(rect.bottomRight());
	list.append(rect.bottomLeft());
	maps(list, flag);
	return list;
}

//填充选择
void HShapeObj::setFillWay(quint8 fillWay)
{
	m_nFillWay = fillWay;
}

quint8 HShapeObj::getFillWay()
{
	return m_nFillWay;
}

//填充方式(风格)
void HShapeObj::setFillStyle(quint8 style)
{
	m_nFillStyle = style;
}

quint8 HShapeObj::getFillStyle()
{
	return m_nFillStyle;
}

//填充色
void HShapeObj::setFillColor(QString clrName)
{
	m_strFillColor = clrName;
}

QString HShapeObj::getFillColor()
{
	return m_strFillColor;
}

//填充方向
void HShapeObj::setFillDirection(quint8 fillDirection)
{
	m_nFillDirection = fillDirection;
}

quint8 HShapeObj::getFillDirection()
{
	return m_nFillDirection;
}

//填充比例
void HShapeObj::setFillPercentage(quint8 fillPer)
{
	m_nFillPercentage = fillPer;
}

quint8 HShapeObj::getFillPercentage()
{
	return m_nFillPercentage;
}

//边框可见
void HShapeObj::setFrameSee(bool frameSee)
{
	m_bFrameSee = frameSee;
}

bool HShapeObj::getFrameSee()
{
	return m_bFrameSee;
}

void HShapeObj::setPainter(QPainter* painter)
{
    HBaseObj::setPainter(painter);
	bool bFrameSee = getFrameSee();//边框可见
    if (!bFrameSee)
		painter->setPen(Qt::NoPen);

	//设置填充
	quint8 nFillWay = getFillWay();//填充选择
	quint8 nFillStyle = getFillStyle(); //填充风格
	quint8 nTransparency = getTransparency(); //透明度
	quint8 nFillDir = getFillDirection();//填充方向
    QColor fillClr = QColor(getFillColor());//填充颜色
	//quint8 nFillPercentage = getFillPercentage(); //填充比例
    m_list = getPointList(TRANS_NO_ROTATE|TRANS_NO_TURN);
    m_rect = m_list.boundingRect();
	QBrush brush;
	if (nFillWay > 0)
	{
        painter->setOpacity(1 - (double)nTransparency / 100.00);
		if (nFillWay == 1)
		{
			if (nFillStyle == Qt::LinearGradientPattern)
			{
				QPointF ps1, ps2;
				switch (nFillDir)
				{
				case DIRECT_BOTTOM_TO_TOP:
				{
                    ps2 = m_rect.topLeft();
                    ps1 = m_rect.bottomLeft();
					break;
				}
				case DIRECT_TOP_TO_BOTTOM: //有顶到底
				{
                    ps1 = m_rect.topLeft();
                    ps2 = m_rect.bottomLeft();
					break;
				}
				case DIRECT_LEFT_TO_RIGHT: //由左到右
				{
                    ps1 = m_rect.topLeft();
                    ps2 = m_rect.topRight();
					break;
				}
				case DIRECT_RIGHT_TO_LEFT: //由右到左
				{
                    ps1 = m_rect.topRight();
                    ps2 = m_rect.topLeft();
					break;
				}
				case DIRECT_VER_TO_OUT: //垂直到外
				{
                    ps1 = QPointF(m_rect.center().x(), m_rect.top());
                    ps2 = m_rect.topLeft();
					break;
				}
				case DIRECT_HORi_TO_OUT: //水平向外
				{
                    ps1 = QPointF(m_rect.left(), m_rect.center().y());
                    ps2 = m_rect.topLeft();
					break;
				}
				case DIRECT_VER_TO_IN: //垂直向里
				{
                    ps2 = QPointF(m_rect.center().x(), m_rect.top());
                    ps1 = m_rect.topLeft();
					break;
				}
				case DIRECT_HORI_TO_IN: //垂直向里
				{
                    ps2 = QPointF(m_rect.left(), m_rect.center().y());
                    ps1 = m_rect.topLeft();
					break;
				}
				}
				QLinearGradient lgrd(ps1, ps2);
				lgrd.setColorAt(0.0, fillClr);
				lgrd.setColorAt(0.5, fillClr.lighter(150));
				lgrd.setColorAt(1.0, fillClr.lighter(250));
				lgrd.setSpread(QGradient::ReflectSpread);
				QBrush brush2(lgrd);
				brush = brush2;
			}
			else if (nFillStyle == Qt::RadialGradientPattern)
			{
                QRadialGradient lgrd(m_rect.center(), qMin(m_rect.width(), m_rect.height()) / 2);
				lgrd.setColorAt(0.0, fillClr);
				lgrd.setColorAt(0.5, fillClr.dark(150));
				lgrd.setColorAt(1.0, fillClr.dark(250));
				lgrd.setSpread(QGradient::ReflectSpread);
				QBrush brush2(lgrd);
				brush = brush2;
			}
			else if (nFillStyle == Qt::ConicalGradientPattern)
			{
                QConicalGradient lgrd(m_rect.center(), 270);
				lgrd.setColorAt(0.0, fillClr);
				lgrd.setColorAt(0.5, fillClr.lighter(150));
				lgrd.setColorAt(1.0, fillClr.lighter(250));
				lgrd.setSpread(QGradient::ReflectSpread);
				QBrush brush2(lgrd);
				brush = brush2;
			}
			else
			{
				Qt::BrushStyle bs = (Qt::BrushStyle)nFillStyle;
				QBrush brush1(fillClr, bs);
				brush = brush1;
			}
			painter->setBrush(brush);
		}
		else if (nFillWay == 2)
		{
			QString strImagePath = getBkImagePath();//图片部分
			if (!strImagePath.isEmpty() || !strImagePath.isNull())
			{
				QPixmap pix, pix1;
				if (pix.load(strImagePath))
				{
					//painter->setClipPath(getPath());
					if (!m_bKeepImageRatio)
					{
                        pix1 = pix.scaled(m_rect.size().toSize());
                        painter->drawPixmap(m_rect.x(), m_rect.y(), pix1);
					}
					else
					{
                        pix1 = pix.scaledToHeight(m_rect.height());
                        QRectF rectF = m_rect;
						if (1 == m_nImageDirect)
						{
                            double deltaX = (m_rect.width() - pix1.width()) / 2;
                            rectF.setX(m_rect.x() + deltaX);
						}
						else if (2 == m_nImageDirect)
						{
                            double deltaX = (m_rect.width() - pix1.width());
                            rectF.setX(m_rect.x() + deltaX);
						}
                        painter->drawPixmap(rectF.x(), rectF.y(), pix1);
					}
				}
			}
		}
	}
}

bool HShapeObj::getPath(QPainterPath& path)
{
    DrawShape drawShape = getShapeType();
    if(drawShape == Rectangle || drawShape == Text)
    {
        HRectangle* obj = (HRectangle*)this;
        if(obj && obj->isRound())
        {
            path.addRoundedRect(m_rect,obj->getXAxis(),obj->getYAxis());
        }
        else
        {
            path.addRect(m_rect);
        }
    }
    else
    {
        path.addPolygon(m_list);
        path.closeSubpath();
    }
    return true;
}

void HShapeObj::paint(QPainter* painter)
{
   if(!painter)
    setPainter(painter);
}
///获得包裹区域位置大小
QRectF HShapeObj::boundingRect(qint8 flag)
{
    return HBaseObj::boundingRect(flag);
}

//获得绘图路径
QPainterPath HShapeObj::shape(qint8 flag)
{
	QPolygonF points = getPointList(flag);
	QPainterPath path;
	path.addPolygon(points);
	path.closeSubpath();
	return path;
}

//透明度
void HShapeObj::setTransparency(quint8 transparency)
{
	m_nTransparency = transparency;
}

quint8 HShapeObj::getTransparency()
{
	return m_nTransparency;
}

void HShapeObj::setBkImagePath(const QString& path)
{
	m_strImagePath = path;
}

QString HShapeObj::getBkImagePath()
{
	return m_strImagePath;
}

bool HShapeObj::isValidBkImagePath() const
{
	return !m_strImagePath.isEmpty() && !m_strImagePath.isNull();
}

void HShapeObj::setKeepImageRatio(bool bcheck)
{
	m_bKeepImageRatio = bcheck;
}

bool HShapeObj::getKeepImageRatio()
{
	return m_bKeepImageRatio;
}

void HShapeObj::setImageDirect(quint8 direct)
{
	m_nImageDirect = direct;
}

quint8 HShapeObj::getImageDirect()
{
	return m_nImageDirect;
}
