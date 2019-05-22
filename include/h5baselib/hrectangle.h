#ifndef HRECTANGLE_H
#define HRECTANGLE_H
#include "hshapeobj.h"
///////////////////////////////////////////HRectangleObj///////////////////////////////////////////
class H5BASELIB_EXPORT HRectangle : public HShapeObj
{
public:
    HRectangle();
    virtual ~HRectangle();

    //二进制读写
    virtual void readData(QDataStream* data);
    virtual void writeData(QDataStream* data);

    //xml文件读写
    virtual void readXml(QDomElement* data);
    virtual void writeXml(QDomElement* data);

    virtual QString tagName();

    //拷贝克隆
    virtual void copyTo(HBaseObj* obj);
    virtual void clone(HBaseObj* obj);

	///设置贴片
	virtual void setBkImagePath(const QString& s);

	virtual void setRound(bool bcheck);
	virtual bool getRound();
	virtual void setXAxis(int xAxis);
	virtual quint8 getXAxis();
	virtual void setYAxis(int yAxis);
	virtual quint8 getYAxis();

public:
	virtual QRectF boundingRect(qint8 flag = 0);
	virtual QPainterPath shape(qint8 flag = 0);
	virtual void paint(QPainter* painter);
protected:
	bool m_bRound;
	quint8 m_nXAxis;
	quint8 m_nYAxis;
};


#endif // HRECTANGLE_H
