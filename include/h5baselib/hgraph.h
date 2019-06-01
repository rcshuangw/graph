#ifndef HGRAPH_H
#define HGRAPH_H

#include <QObject>
#include "h5baselibexport.h"
#include "hiconapi.h"
#include "hicontemplate.h"
#include "hiconsymbol.h"
class QPainter;
class QDataStream;
class QDomElement;
class HContainerObj;
/*
 * 记录单个画面信息，包含画面所含的模板列表信息，各种图元信息，颜色，背景等等信息
 *
*/
class H5BASELIB_EXPORT HGraph : public HContainerObj
{
public:
    HGraph(const QString& name);
    ~HGraph();

public:
    virtual void readDataFile(const QString&);
    virtual void writeDateFile(const QString&);
    virtual void readData(int,QDataStream *d);
    virtual void writeData(int,QDataStream *d);

    virtual bool readXmlFile(const QString&);
    virtual bool writeXmlFile(const QString&);
    virtual void readXml(int,QDomElement *d);
    virtual void writeXml(int,QDomElement *d);

    virtual QString tagName();
    virtual void copyTo(HBaseObj* obj);

public:
    void setGraphName(const QString& name);
    QString getGraphName();

    void setRefreshInterval(int val);
    int getRefreshInterval();

    void setStartFlag(bool start);
    bool getStartFlag();

    void setGraphType(ushort type);
    ushort getGraphType();

    QString getStationName();

public:
    virtual void paint(QPainter* painter);
    virtual QRectF boundingRect(qint8 flag = 0);
    virtual QPainterPath shape(qint8 flag = 0);

public:
    void clear();
    void addIconObj(HBaseObj* pObj);
    void removeIconObj(HBaseObj* pObj);
    void takeIconObj(HBaseObj* pObj);

    //模板部分
    int iconTemplateNum();
    HIconTemplate* IconTemplateAt(int index);
    virtual HIconTemplate* findIconTemplate(const QUuid& uid);
    virtual HIconTemplate* addIconTemplate(HIconTemplate* temp);
    virtual void removeIconTemplate(HIconTemplate* temp);
    virtual void clearIconTemplate();
    virtual void resetIconTemplate();

    //缩放
    qreal zoomScale();
    void setZoomScale(qreal f);

public:
    QList<HIconTemplate*> pIconTemplateList;
protected:
    QString m_strGraphName; //名称
    double m_fZoomScale;
    int nRefreshInterval; //刷新间隔
    bool bStart; //启动画面
    ushort btType;//画面类
    ushort wStationID;//关联的厂站
};

#endif // HGRAPH_H
