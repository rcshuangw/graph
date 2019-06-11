#ifndef HNORMALOBJ_H
#define HNORMALOBJ_H
#include "h5baselibexport.h"
#include "hbaseobj.h"
class HIconTemplate;
class HIconSymbol;
class HText;
class H5BASELIB_EXPORT HNormalObj : public HBaseObj //图符类
{
public:
    HNormalObj();
    HNormalObj(HIconTemplate* it);
    virtual ~HNormalObj();
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

    void update();

public:
	//模板等指针
	void initIconTemplate();
	void setIconTemplate(HIconTemplate* t);
	void initDynamicData();

	HIconTemplate* iconTemplate();
	HIconSymbol* iconSymbol();

protected:
    HIconTemplate* m_pIconTemplate;//模板信息
    HIconSymbol* m_pIconSymbol;//实际对象Icon信息


    //icontemplate的信息
    QString strCatalogName;//目录名字
    int nCatalogType;//类型
    QString strUuid;//uuid

    //画面ID
    int nGraphID;


};

#endif // HICONOBJ_H
