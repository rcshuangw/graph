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
/*
 * 记录单个画面信息，包含画面所含的模板列表信息，各种图元信息，颜色，背景等等信息
 *
*/
class H5BASELIB_EXPORT HGraph : public QObject
{
public:
    HGraph(const QString& name);
    ~HGraph();
public:
    void setGraphName(const QString& name);
    QString getGraphName();

    void setFillColor(const QString& clr);
    QString getFillColor();

    void setGraphID(int id);
    int getGraphID();

    void setGraphWidth(int width);
    int getGraphWidth();

    void setGraphHeight(int height);
    int getGraphHeight();

    void setFillPicture(const QString& strPic);
    QString getFillPicture();

    void setRefreshInterval(int val);
    int getRefreshInterval();

    void setStartFlag(bool start);
    bool getStartFlag();

    void setGraphType(ushort type);
    ushort getGraphType();

    QString getStationName();
	
    void setModify(bool modify);
    bool getModify();
public:
    virtual void readDataFile(const QString&);

    virtual void writeDateFile(const QString&);

    virtual bool readXmlFile(const QString&);

    virtual bool writeXmlFile(const QString&);

    virtual void readData(int,QDataStream *d);

    virtual void writeData(int,QDataStream *d);

    virtual void readXml(QDomElement *d);
    
    virtual void writeXml(QDomElement *d);

    void Draw(QPainter* p);

    void clear();

    void copyTo(HGraph* graph);

    HBaseObj* newObj(int nObjType,const QString &strUuid = QString());

    HBaseObj* newObj(QString tagName,const QString &strUuid = QString());

    void addObj(HBaseObj* pObj);

    void removeObj(HBaseObj* pObj);

    void delObj(HBaseObj* pObj);

    int getObjID();

    bool findObjID(int nObjID);

    QList<HBaseObj*> getObjList();

    //模板部分
    int iconTemplateNum();

    HIconTemplate* IconTemplateAt(int index);

    virtual HIconTemplate* findIconTemplate(const QUuid& uid);

    virtual void addIconTemplate(HIconTemplate* temp);

    virtual void removeIconTemplate(HIconTemplate* temp);

    virtual void clearIconTemplate();

    virtual void resetIconTemplate();

    //qreal zoomScale();

    //void setZoomScale(qreal f);
public:
    QList<HIconTemplate*> pIconTemplateList;
protected:
    QString sName; //名称

    int nGraphID;//画面ID

    int nGraphWidth; //长度，

    int nGraphHeight; //高度

    int nRefreshInterval; //刷新间隔

    QString strFillColor;//背景填充颜色

    QString strFillPicture;

    bool bStart; //启动画面

    ushort btType;//画面类型

    ushort wStationID;//关联的厂站

    bool bModify; //是否修改，不需要保存

    QList<HBaseObj*> pObjList;//所有图元信息

    //缩放比例

    //所有模板信息

    //QList<HStation> stationList;
};

#endif // HGRAPH_H
