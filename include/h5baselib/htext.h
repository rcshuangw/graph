#ifndef HTEXT_H
#define HTEXT_H
#include "hrectangle.h"
///////////////////////////////////////////HRectangleObj///////////////////////////////////////////
class H5BASELIB_EXPORT HText : public HRectangle
{
public:
    HText();
    virtual ~HText();

    //二进制读写
    virtual void readData(int v,QDataStream* data);
    virtual void writeData(int v,QDataStream* data);

    //xml文件读写
    virtual void readXml(int v,QDomElement* data);
    virtual void writeXml(int v,QDomElement* data);

    virtual QString tagName();

    //拷贝克隆
    virtual void copyTo(HBaseObj* obj);

public:
   // virtual QRectF boundingRect(qint8 flag = 0);
    virtual QPainterPath shape(qint8 flag = 0);
    virtual void paint(QPainter* painter);
public:
    void setTextClr(QString strClrName);
    QString textClrName();

    void setLayout(ushort layout);
    ushort layout();

    void setHorizontalAlign(int hAlign);
    int horizontalAlign();

    void setVerticalAlign(int vAlign);
    int verticalAlign();

    //字体部分
    void setFont(QFont& font);
    QFont font();

    void setFontFamily(QString strFontName);
    QString fontFamily();

    void setFontSize(int ptSize);
    int fontSize();

    void setFontWeight(int weight);
    int fontWeight();

    void setFontItalic(bool bitalic);
    bool fontItalic();

    //内容、格式、前后缀
    void setText(QString strContent);
    QString text();

    void setTextFormat(uchar btType);
    uchar textFormat();

    void setTextPrefix(const QString& strPrefix);
    QString textPrefix();

    void setTextSuffix(const QString& strSuffix);
    QString textSuffix();

private:
    QString m_strText;//文字
    //文字颜色,文字字体,水平对齐，垂直对齐,布局方式
    ushort m_nLayout;
    int m_nHorizontalAlign;
    int m_nVerticalAlign;
    QString m_strPrefix;//前缀
    QString m_strSuffix;//后缀
    uchar   m_btFormat;//格式

    QString m_strTextClr;
    QFont m_Font;

    QString m_strFontFamily;
    int m_nFontSize;//字体大小
    int m_nFontWeight;//粗体
    bool m_nFontItalic;//斜体
};


#endif // HRECTANGLE_H
