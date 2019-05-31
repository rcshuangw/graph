#ifndef HICONOBJ_H
#define HICONOBJ_H
#include "h5baselibexport.h"
#include "hbaseobj.h"
class HIconTemplate;
class HIconSymbol;
class HDynamicObj;
class HText;
class H5BASELIB_EXPORT HIconObj : public HBaseObj //图符类
{
public:
    HIconObj();
    HIconObj(HIconTemplate* it);
    virtual ~HIconObj();
public:
//二进制读写
    virtual void readData(int v,QDataStream* data);
    virtual void writeData(int v, QDataStream* data);

    //xml文件读写
    virtual void readXml(int v, QDomElement* dom);
    virtual void writeXml(int v, QDomElement* dom);

    virtual QString tagName();
    virtual void copyTo(HBaseObj* obj);

public:
	virtual bool setPointList(QPolygonF& list, qint8 flag = 1);
	virtual QPolygonF getPointList(qint8 flag = 0);

	virtual void move(double dx, double dy, bool bscale = false);
    virtual void moveBy(double dx,double dy,bool bscale = false);
    virtual void resize(double w,double h, bool bscale = false);

public:
	virtual void paint(QPainter* painter);
    virtual QRectF boundingRect(qint8 flag = 0);
    virtual QPainterPath shape(qint8 flag = 0);

public:
	//属性
    void setUuid(const QString&);
    QString getUuid();
    void setCatalogName(const QString&);
    QString getCatalogName();
    void setObjType( uchar catalogType);
    int getObjType();
    void setSymbolName(const QString&);
    QString getSymbolName();
    void setSymbolType(int symbolType);
    int getSymbolType();
    void setGraphID(int graphID);
    int getGraphID();
    void setGraphOperator(uchar graphOperator);
    uchar getGraphOpeartor();
    void setGraphComfirm(uchar graphComfirm);
    uchar getGraphComfirm();
    void update();
public:
    HText* firstText();
public:
	//模板等指针
	void initIconTemplate();
	void setIconTemplate(HIconTemplate* t);
	void initDynamicData();
	void clearDynamicData();
	HIconTemplate* iconTemplate();
	HIconSymbol* iconSymbol();
	HDynamicObj* dynamicObj();
protected:
    HIconTemplate* m_pIconTemplate;//模板信息
    HIconSymbol* m_pIconSymbol;//实际对象Icon信息
    //如果一个对象可以关联厂站装置测点，也可以关联厂站间隔，那么这个地方就要是列表来存储
    HDynamicObj* m_pDynamicObj;//实际对象动态信息

    //icontemplate的信息
    QString strCatalogName;//目录名字
    int nCatalogType;//类型
    QString strUuid;//uuid

    //iconsymbol的信息
    //QString strSymbolName;
    //int nSymbolType;

    //画面ID
    int nGraphID;

    //画面操作方式
    uchar btGraphOperator;

    //画面确认方式
    uchar btGraphComfirm;
};

#endif // HICONOBJ_H
