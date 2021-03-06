#include "htext.h"
#include <QApplication>
HText::HText()
    :HRectangle()
{
    setShapeType(Text);
    m_strText = QString("text example");

    m_strTextClr = "#000000";//线条颜色
    m_nLayout = LAYOUT_TEXT_NULL;
    m_nHorizontalAlign = Qt::AlignHCenter;
    m_nVerticalAlign = Qt::AlignVCenter;
    m_Font.setFamily( QStringLiteral("微软雅黑"));
    m_Font.setPointSize(18);

    m_bFrameSee = false;
    m_nFillStyle = (quint8)Qt::NoBrush;
    m_strPrefix.clear();//前缀
    m_strSuffix.clear();//后缀
    m_btFormat = TEXT_TWO_POINT;//格式
}

HText::~HText()
{

}

//二进制读写
void HText::readData(int v,QDataStream* data)
{
    if(!data) return;
    HRectangle::readData(v,data);
    QString s;
    *data>>s;
    m_strText = s;
    *data>>s;
    m_strTextClr = s;
    quint8 n8;
    *data>>n8;
    m_nLayout = n8;
    int n;
    *data>>n;
    m_nHorizontalAlign = n;
    *data>>n;
    m_nVerticalAlign = n;
    *data>>s;
    m_Font.setFamily(s);
    *data>>n;
    m_Font.setPointSize(n);
    bool b;
    *data>>b;
    m_Font.setBold(b);
    *data>>b;
    m_Font.setItalic(b);
    *data>>b;
    m_Font.setUnderline(b);
    *data>>s;
    m_strPrefix = s;
    *data>>s;
    m_strSuffix = s;
    uchar bt;
    *data>>bt;
    m_btFormat = bt;
}

void HText::writeData(int v,QDataStream* data)
{
    if(!data) return;
    HRectangle::writeData(v,data);
    *data<<(QString)m_strText;
    *data<<(QString)m_strTextClr;
    *data<<(quint8)m_nLayout;
    *data<<(int)m_nHorizontalAlign;
    *data<<(int)m_nVerticalAlign;
    *data<<(QString)m_Font.family();
    *data<<(int)m_Font.pointSize();
    *data<<(bool)m_Font.bold();
    *data<<(bool)m_Font.italic();
    *data<<(bool)m_Font.underline();
    *data<<(QString)m_strPrefix;
    *data<<(QString)m_strSuffix;
    *data<<(uchar)m_btFormat;
}

//xml文件读写
void HText::readXml(int v,QDomElement* dom)
{
    if(!dom) return;
    HRectangle::readXml(v,dom);
    m_strText = dom->attribute("Text");
    m_strTextClr = dom->attribute("TextColor");
    m_nLayout = dom->attribute("Layout").toInt();
    m_nHorizontalAlign = dom->attribute("HorizontalAlign").toInt();
    m_nVerticalAlign = dom->attribute("VerticalAlign").toInt();
    QString s = dom->attribute("FontFamily");
    m_Font.setFamily(s);
    int ptsz = dom->attribute("FontSize").toInt();
    m_Font.setPointSize(ptsz);
    bool b;
    b = dom->attribute("FontBold").toUInt();
    m_Font.setBold(b);
    b = dom->attribute("FontItalic").toUInt();
    m_Font.setItalic(b);
    b = dom->attribute("FontUnderline").toUInt();
    m_Font.setUnderline(b);
    m_strPrefix = dom->attribute("Prefix");
    m_strSuffix = dom->attribute("Suffix");
    m_btFormat = dom->attribute("Format").toUInt();
}

void HText::writeXml(int v,QDomElement* dom)
{
    if(!dom)return;
    HRectangle::writeXml(v,dom);
    dom->setAttribute("Text",m_strText);
    dom->setAttribute("TextColor",m_strTextClr);
    dom->setAttribute("Layout",m_nLayout);
    dom->setAttribute("HorizontalAlign",m_nHorizontalAlign);
    dom->setAttribute("VerticalAlign",m_nVerticalAlign);
    dom->setAttribute("FontFamily",m_Font.family());
    dom->setAttribute("FontSize",m_Font.pointSize());
    dom->setAttribute("FontBold",m_Font.bold());
    dom->setAttribute("FontItalic",m_Font.italic());
    dom->setAttribute("FontUnderline",m_Font.underline());
    dom->setAttribute("Prefix",m_strPrefix);
    dom->setAttribute("Suffix",m_strSuffix);
    dom->setAttribute("Format",m_btFormat);
}

QString HText::tagName()
{
    return "Text";
}

//拷贝克隆
void HText::copyTo(HBaseObj* obj)
{
    HText* ob = (HText*)obj;
    if(!ob) return;
    HRectangle::copyTo(ob);
    ob->m_strText = m_strText;
    ob->m_strTextClr = m_strTextClr;
    ob->m_nLayout = m_nLayout;
    ob->m_nHorizontalAlign = m_nHorizontalAlign;
    ob->m_nVerticalAlign = m_nVerticalAlign;
    ob->m_Font = m_Font;
    ob->m_strPrefix = m_strPrefix;
    ob->m_strSuffix = m_strSuffix;
    ob->m_btFormat = m_btFormat;
}

void HText::setTextColor(const QString& strClrName)
{
    m_strTextClr = strClrName;
}

QString HText::getTextColor()
{
    return m_strTextClr;
}

void HText::setLayout(ushort layout)
{
    this->m_nLayout = layout;
}

ushort HText::layout()
{
    return m_nLayout;
}

void HText::setHorizontalAlign(int hAlign)
{
    m_nHorizontalAlign = hAlign;
}

int HText::horizontalAlign()
{
    return m_nHorizontalAlign;
}

void HText::setVerticalAlign(int vAlign)
{
    m_nVerticalAlign = vAlign;
}

int HText::verticalAlign()
{
    return m_nVerticalAlign;
}

void HText::setFont(QFont &font)
{
    m_Font = font;
}

QFont HText::font()
{
    return m_Font;
}

void HText::setFontFamily(QString strFontName)
{
    //m_strFontFamily = strFontName;
    m_Font.setFamily(strFontName);
}

QString HText::fontFamily()
{
    //return m_strFontFamily;
    return m_Font.family();
}

void HText::setFontSize(int ptSize)
{
    //m_nFontSize = ptSize;
    m_Font.setPointSize(ptSize);
}

int HText::fontSize()
{
    //return m_nFontSize;
    return m_Font.pointSize();
}

void HText::setFontWeight(int weight)
{
    //this->m_nFontWeight = weight;
    m_Font.setWeight(weight);
}

int HText::fontWeight()
{
    //return m_nFontWeight;
    return m_Font.weight();
}
void HText::setFontBold(bool b)
{
    m_Font.setBold(b);
}

bool HText::fontBold()
{
    return m_Font.bold();
}

void HText::setFontUnderline(bool b)
{
    m_Font.setUnderline(b);
}

bool HText::fontUnderline()
{
    //return m_bFontUnderline;
    return m_Font.underline();
}

void HText::setFontItalic(bool bitalic)
{
    //m_nFontItalic = bitalic;
    m_Font.setItalic(bitalic);
}

bool HText::fontItalic()
{
    //return m_nFontItalic;
    return m_Font.italic();
}


void HText::setText(QString text)
{
    m_strText = text;
}

QString HText::text()
{
    return m_strText;
}

void HText::setTextFormat(uchar btType)
{
    m_btFormat = btType;
}

uchar HText::textFormat()
{
    return m_btFormat;
}

void HText::setTextPrefix(const QString& strPrefix)
{
    this->m_strPrefix = strPrefix;
}

QString HText::textPrefix()
{
    return this->m_strPrefix;
}

void HText::setTextSuffix(const QString& strSuffix)
{
    this->m_strSuffix = strSuffix;
}

QString HText::textSuffix()
{
    return this->m_strSuffix;
}

QPainterPath HText::shape(qint8 flag)
{
    return HShapeObj::shape(flag);
}

void HText::paint(QPainter* painter)
{
    ushort nLayout = layout();
    painter->save();
    HShapeObj::setPainter(painter);
    QRectF mainRectF = m_rect;
    QPainterPath path;
    if(getPath(path))
        painter->drawPath(path);

    //设置字体部分
    QFont font = m_Font;//(strFontFamily,nFontSize,nFontWeight,bFontItalic);
    QPen textPen = QPen(QColor(getTextColor()));
    painter->setPen(textPen);
    painter->setFont(font);

    int nAlign = horizontalAlign()|verticalAlign();
    QFontMetricsF fm(font);
    if(nLayout == LAYOUT_TEXT_FULL)
    {
        double fw = fm.width(text());
        double fh = fm.height();
        fh = mainRectF.height()/fh;
        fw = (mainRectF.width()+fh)/fw;
        painter->scale(fw,fh);
        mainRectF = QRectF(mainRectF.x()/fw,mainRectF.y()/fh,mainRectF.width()/fw,mainRectF.height()/fh);
        nAlign = Qt::AlignCenter | Qt::TextSingleLine;
    }
    painter->drawText(mainRectF,nAlign,textSuffix()+text()+textPrefix());
}
