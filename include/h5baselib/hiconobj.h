#ifndef HICONOBJ_H
#define HICONOBJ_H
#include "hicontemplate.h"
#include "hiconsymbol.h"
#include "hdynamicobj.h"
#include "hbaseobj.h"
class HIconTemplate;
class HIconSymbol;

/*此图符类型是包含关联数据的，不仅可以作为4遥信基本图符使用，也可以作为一次设备图符使用，比如进线等基本图符关联数据使用
*/
class H5BASELIB_EXPORT HIconObj : public HBaseObj //图符类
{
public:
    HIconObj();
    HIconObj(HIconTemplate* it);
    virtual ~HIconObj();
public:
    /*
     * 存储分为两个部分
*/
//二进制读写
    virtual void readData(int v,QDataStream* data);
    virtual void writeData(int v, QDataStream* data);

    //xml文件读写
    virtual void readXml(int v, QDomElement* dom);
    virtual void writeXml(int v, QDomElement* dom);

    virtual QString tagName();

    //拷贝克隆
    virtual void copyTo(HBaseObj* obj);

    virtual DrawShape getShapeType();

public:
	///绝对坐标
	virtual bool setPointList(QPolygonF& list, qint8 flag = 1);
	virtual QPolygonF getPointList(qint8 flag = 0);
	//操作函数
	virtual void move(double dx, double dy, bool bscale = false);
    virtual void moveBy(double dx,double dy,bool bscale = false);
    virtual void resize(double w,double h, bool bscale = false);

public:
	//HGrphicsItem的虚函数
	virtual void paint(QPainter* painter);
    virtual QRectF boundingRect(qint8 flag = 0);
	virtual bool contains(const QPointF &point);
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
    void updateResize();

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

    HText* pText;
};

#endif // HICONOBJ_H
