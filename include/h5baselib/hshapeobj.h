#ifndef HSIMPLEOBJ_H
#define HSIMPLEOBJ_H
#include "hbaseobj.h"
class H5BASELIB_EXPORT HShapeObj : public HBaseObj
{
    Q_OBJECT
public:
    HShapeObj();
    virtual ~HShapeObj();

public:
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

    //填充选择
    virtual void setFillWay(quint8 fillWay);
    virtual quint8 getFillWay();

    //填充方式(风格)
    virtual void setFillStyle(quint8 style);
    virtual quint8 getFillStyle();

    //填充色
    virtual void setFillColor(QString clrName);
    virtual QString getFillColor();

    //填充方向
    virtual void setFillDirection(quint8 fillDirection);
    virtual quint8 getFillDirection();

    //填充比例
    virtual void setFillPercentage(quint8 fillPer);
    virtual quint8 getFillPercentage();

    //边框可见
    virtual void setFrameSee(bool frameSee);
    virtual bool getFrameSee();

    //设置贴片
    virtual void setTransparency(quint8 transparency);
    virtual quint8 getTransparency();

    virtual void setBkImagePath(const QString& path);
    virtual QString getBkImagePath();
    virtual bool isValidBkImagePath() const;

    virtual void setKeepImageRatio(bool bcheck);
    virtual bool getKeepImageRatio();

    virtual void setImageDirect(quint8 direct);
    virtual quint8 getImageDirect();

public:
    virtual void resize(double w, double h, bool scale = false);
    virtual void expand(double dx1, double dx2, double dy1, double dy2, qint8 flag = 0);
public:
    virtual bool setPointList(QPolygonF& list, qint8 flag = 1);
    virtual QPolygonF getPointList(qint8 flag = 0);
    virtual void setPainter(QPainter* painter);
    virtual bool getPath(QPainterPath& path);
    virtual void paint(QPainter* painter);
    virtual QRectF boundingRect(qint8 flag = 0);
    virtual QPainterPath shape(qint8 flag = 0);
    //////////////////////////////////////////设置属性//////////////////////////////////////
public:
	QPolygonF	m_list;
	QRectF		m_rect;
    double m_width;
    double m_height;
protected:
    //填充方面
	bool m_bFill;
    quint8 m_nFillWay;//填充方式
    quint8 m_nFillStyle;//填充风格
    QString m_strFillColor; //填充颜色
    quint8 m_nFillDirection;//填充方向
    quint8 m_nFillPercentage;//填充比例

    //边框透明度
    bool m_bFrameSee;//边框可见
    quint8 m_nTransparency; //透明度

private:
    //图片
    QString m_strImagePath;//图片路径
    bool m_bKeepImageRatio; //保持图片比例
    quint8 m_nImageDirect; //图片的方向
};

#endif // HSIMPLEOBJ_H
