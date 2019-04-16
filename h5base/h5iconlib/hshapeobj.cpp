#include "hshapeobj.h"
HShapeObj::HShapeObj()
{
	m_bFill = false;
    m_nFillWay = 0;
	m_nFillStyle = (quint8)Qt::NoBrush;
	m_strFillColor = "#00FF00"; //�����ɫ
	m_nFillDirection = DIRECT_BOTTOM_TO_TOP;
	m_nFillPercentage = 100;

	//�߿�͸����
	m_bFrameSee = true;
	m_nTransparency = 0; 
	
	//ͼƬ
	m_strImagePath = "";
	bool m_bKeepImageRatio = false; 
	m_nImageDirect = 0; 
}

HShapeObj::~HShapeObj()
{

}

//�����ƶ�д
void HShapeObj::readData(QDataStream* data)
{
	if (!data) return;
	HBaseObj::readData(data);
	qreal r;
	*data >> r;
	m_width = r;
	*data >> r;
	m_height = r;
	resize(m_width, m_height);
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

void HShapeObj::writeData(QDataStream* data)
{
	if (!data) return;
	HBaseObj::writeData(data);
	*data << (qreal)m_width;
	*data << (qreal)m_height;
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

//xml�ļ���д
void HShapeObj::readXml(QDomElement* dom)
{
	if (!dom)
		return;
	HBaseObj::readXml(dom);
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

void HShapeObj::writeXml(QDomElement* dom)
{
	if (!dom)
		return;
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

QString HShapeObj::TagName()
{
	return "Shape";
}

//������¡
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

void HShapeObj::clone(HBaseObj* ob)
{
	if (!ob)
		return;
	HBaseObj::clone(ob);
	copyTo(ob);
}

//�仯�����ǰ�����Ҳ������ֱ�Ӹ���w,h
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

///��������
bool HShapeObj::setPointList(QPolygonF& list, qint8 flag)
{
	HBaseObj::setPointList(list, flag);
	QRectF rect = list.boundingRect();
	m_width = rect.width();
	m_height = rect.height();
	return true;
}

///��ȡ���б�
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

//���ѡ��
void HShapeObj::setFillWay(quint8 fillWay)
{
	m_nFillWay = fillWay;
}

quint8 HShapeObj::getFillWay()
{
	return m_nFillWay;
}

//��䷽ʽ(���)
void HShapeObj::setFillStyle(quint8 style)
{
	m_nFillStyle = style;
}

quint8 HShapeObj::getFillStyle()
{
	return m_nFillStyle;
}

//���ɫ
void HShapeObj::setFillColorName(QString clrName)
{
	m_strFillColor = clrName;
}

QString HShapeObj::getFillColorName()
{
	return m_strFillColor;
}

//��䷽��
void HShapeObj::setFillDirection(quint8 fillDirection)
{
	m_nFillDirection = fillDirection;
}

quint8 HShapeObj::getFillDirection()
{
	return m_nFillDirection;
}

//������
void HShapeObj::setFillPercentage(quint8 fillPer)
{
	m_nFillPercentage = fillPer;
}

quint8 HShapeObj::getFillPercentage()
{
	return m_nFillPercentage;
}

//�߿�ɼ�
void HShapeObj::setFrameSee(bool frameSee)
{
	m_bFrameSee = frameSee;
}

bool HShapeObj::getFrameSee()
{
	return m_bFrameSee;
}

void HShapeObj::setPainter(QPainter* painter, const QRectF& rect)
{
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setRenderHint(QPainter::TextAntialiasing);
	painter->setRenderHint(QPainter::SmoothPixmapTransform);

	//��������
	QColor penClr = QColor(getLineColorName()); //������ɫ
	int penWidth = getLineWidth();//�������
	Qt::PenStyle penStyle = getLineStyle(); //������״
	Qt::PenCapStyle capStyle = getLineCapStyle(); //�����Ƕ�
	bool bFrameSee = getFrameSee();//�߿�ɼ�
	QPen pen = QPen(penClr);
	pen.setStyle(penStyle);
	pen.setWidth(penWidth);
	pen.setCapStyle(capStyle);
	if (bFrameSee)
		painter->setPen(pen);
	else
		painter->setPen(Qt::NoPen);

	//�������
	quint8 nFillWay = getFillWay();//���ѡ��
	quint8 nFillStyle = getFillStyle(); //�����
	quint8 nTransparency = getTransparency(); //͸����
	quint8 nFillDir = getFillDirection();//��䷽��
	QColor fillClr = QColor(getFillColorName());//�����ɫ
	//quint8 nFillPercentage = getFillPercentage(); //������

	QBrush brush;
	if (nFillWay > 0)
	{
		painter->setOpacity(1 - (qreal)nTransparency / 100.00);
		if (nFillWay == 1)
		{
			if (nFillStyle == Qt::LinearGradientPattern)
			{
				QPointF ps1, ps2;
				switch (nFillDir)
				{
				case DIRECT_BOTTOM_TO_TOP:
				{
					ps2 = rect.topLeft();
					ps1 = rect.bottomLeft();
					break;
				}
				case DIRECT_TOP_TO_BOTTOM: //�ж�����
				{
					ps1 = rect.topLeft();
					ps2 = rect.bottomLeft();
					break;
				}
				case DIRECT_LEFT_TO_RIGHT: //������
				{
					ps1 = rect.topLeft();
					ps2 = rect.topRight();
					break;
				}
				case DIRECT_RIGHT_TO_LEFT: //���ҵ���
				{
					ps1 = rect.topRight();
					ps2 = rect.topLeft();
					break;
				}
				case DIRECT_VER_TO_OUT: //��ֱ����
				{
					ps1 = QPointF(rect.center().x(), rect.top());
					ps2 = rect.topLeft();
					break;
				}
				case DIRECT_HORi_TO_OUT: //ˮƽ����
				{
					ps1 = QPointF(rect.left(), rect.center().y());
					ps2 = rect.topLeft();
					break;
				}
				case DIRECT_VER_TO_IN: //��ֱ����
				{
					ps2 = QPointF(rect.center().x(), rect.top());
					ps1 = rect.topLeft();
					break;
				}
				case DIRECT_HORI_TO_IN: //��ֱ����
				{
					ps2 = QPointF(rect.left(), rect.center().y());
					ps1 = rect.topLeft();
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
				QRadialGradient lgrd(rect.center(), qMin(rect.width(), rect.height()) / 2);
				lgrd.setColorAt(0.0, fillClr);
				lgrd.setColorAt(0.5, fillClr.dark(150));
				lgrd.setColorAt(1.0, fillClr.dark(250));
				lgrd.setSpread(QGradient::ReflectSpread);
				QBrush brush2(lgrd);
				brush = brush2;
			}
			else if (nFillStyle == Qt::ConicalGradientPattern)
			{
				QConicalGradient lgrd(rect.center(), 270);
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
			QString strImagePath = getBkImagePath();//ͼƬ����
			if (!strImagePath.isEmpty() || !strImagePath.isNull())
			{
				QPixmap pix, pix1;
				if (pix.load(strImagePath))
				{
					//painter->setClipPath(getPath());
					if (!m_bKeepImageRatio)
					{
						pix1 = pix.scaled(rect.size().toSize());
						painter->drawPixmap(rect.x(), rect.y(), pix1);
					}
					else
					{
						pix1 = pix.scaledToHeight(rect.height());
						QRectF rectF = rect;
						if (1 == m_nImageDirect)
						{
							double deltaX = (rect.width() - pix1.width()) / 2;
							rectF.setX(rect.x() + deltaX);
						}
						else if (2 == m_nImageDirect)
						{
							double deltaX = (rect.width() - pix1.width());
							rectF.setX(rect.x() + deltaX);
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
	return false;
}
///��ð�������λ�ô�С
QRectF HShapeObj::boundingRect(qint8 flag)
{
	return HShapeObj::boundingRect(flag);
}

//��û�ͼ·��
QPainterPath HShapeObj::shape(qint8 flag)
{
	QPolygonF points = getPointList(flag);
	QPainterPath path;
	path.addPolygon(points);
	path.closeSubpath();
	return path;
}

//͸����
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