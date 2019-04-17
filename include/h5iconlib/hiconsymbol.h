#ifndef HICONSYMBOL_H
#define HICONSYMBOL_H

#include <QObject>
#include <QtXml/QDomElement>
//存放每个一个图元内部的信息和图元本身的显示信息
#include "h5iconlibexport.h"
#include "hgroupobj.h"
class HIconShowPattern;
class HIconTemplate;
class HText;
class H5ICONLIB_EXPORT HIconSymbol:public HGroupObj
{
public:
    HIconSymbol(HIconTemplate* t);
    ~HIconSymbol();

public:
    void clear();
	virtual void readXml(QDomElement* dom);
	virtual void writeXml(QDomElement *dom);

	virtual void readData(int,QDataStream* d);
	virtual void writeData(int,QDataStream *d);

	virtual void copyTo(HIconSymbol* isymbol);
	virtual QString TagName();

   

    //增加删除一个图元元素
    void addObj(HBaseObj* pObj);
    void delObj(HBaseObj* pObj);
    void takeObj(HBaseObj* pObj);

    

    void setSymbolName(const QString& strName);
    QString getSymolName();

    //void setSymbolType(const int& type);
    //int getSymbolType();

    void setIconSymbolWidth(double width);
    void setIconSymbolHeight(double height);


    int getObjID();
    bool findObjID(int nObjID);

    void setModify(bool modify);
    bool getModify();

    void updateShowPattern(QList<HBaseObj*> &list);
    //图元中多种状态的显示方案
    bool PatterIsValid(int nId);

    //新建
    HIconShowPattern* newPattern(const QString& name="");
    HIconShowPattern* newPattern(int id);

    //删除
    void delPattern(HIconShowPattern* sp);
    void delPattern(int id);
    void clearPattern();

    //查找
    int getMaxPattern(){return nMaxPattern;}

    //查找和设置
    int iconShowPatternCount(){return pShowPatternVector.count();}
    HIconShowPattern* findPatternById(int id);
    void setCurrentPattern(int id);
    int getCurrentPattern();
    int getCurrentPatternIndex();
    void setCurrentPatternPtr(HIconShowPattern* sp);
    HIconShowPattern* getCurrentPatternPtr();
    void resetRectPoint(const QPointF& pt1,const QPointF& pt2);
    void resize(double w,double h);

    //获取特定图元
    HText* getFirstTextObj();
public:
    QVector<HIconShowPattern*> pShowPatternVector;
private:
    QString strSymbolName;
    int usSymbolType;
    int nMaxPattern;
    int m_nCurPattern;
    HIconShowPattern* pCurPattern;
    HIconTemplate* pIconTemplate;

};

#endif // HICONSYMBOL_H
