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

void HShapeObj::resize(double w, double h, bool scale)
{

}

void HShapeObj::expand(double dx1, double dx2, double dy1, double dy2, qint8 flag)
{

}

///��������
bool HShapeObj::setPointList(QPolygonF& list, qint8 flag)
{

}

///��ȡ���б�
QPolygonF HShapeObj::getPointList(qint8 flag)
{

}

//���ѡ��
void HShapeObj::setFillWay(quint8 fillWay)
{

}

quint8 HShapeObj::getFillWay()
{

}

//��䷽ʽ(���)
void HShapeObj::setFillStyle(quint8 style)
{

}

quint8 HShapeObj::getFillStyle()
{

}

//���ɫ
void HShapeObj::setFillColorName(QString clrName)
{

}

QString HShapeObj::getFillColorName()
{

}

//��䷽��
void HShapeObj::setFillDirection(quint8 fillDirection)
{

}

quint8 HShapeObj::getFillDirection()
{

}

//������
void HShapeObj::setFillPercentage(quint8 fillPer)
{

}

quint8 HShapeObj::getFillPercentage()
{

}

//�߿�ɼ�
void HShapeObj::setFrameSee(bool frameSee)
{

}

bool HShapeObj::getFrameSee()
{

}

///��ð�������λ�ô�С
QRectF HShapeObj::bounding(qint8 flag)
{

}

//��û�ͼ·��
QPainterPath HShapeObj::shape(qint8 flag)
{

}

//͸����
void HShapeObj::setTransparency(quint8 transparency)
{

}

quint8 HShapeObj::getTransparency()
{

}

void HShapeObj::setBkImagePath(const QString& path)
{

}

QString HShapeObj::getBkImagePath()
{

}

bool HShapeObj::isValidBkImagePath() const
{

}

void HShapeObj::setKeepImageRatio(bool bcheck)
{

}

bool HShapeObj::getKeepImageRatio()
{

}

void HShapeObj::setImageDirect(quint8 direct)
{

}

quint8 HShapeObj::getImageDirect()
{

}