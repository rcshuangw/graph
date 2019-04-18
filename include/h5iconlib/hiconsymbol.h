#ifndef HICONSYMBOL_H
#define HICONSYMBOL_H

#include <QObject>
#include <QtXml/QDomElement>
//存放每个一个图元内部的信息和图元本身的显示信息
#include "h5iconlibexport.h"
#include "hcomplexobj.h"
class HIconShowPattern;
class HIconTemplate;
class HText;
class H5ICONLIB_EXPORT HIconSymbol:public HComplexObj
{
public:
    HIconSymbol(HIconTemplate* t);
    ~HIconSymbol();

public:
    void clear();
	virtual void readXml(int v,QDomElement* dom);
	virtual void writeXml(int v,QDomElement *dom);

	virtual void readData(int,QDataStream* d);
	virtual void writeData(int,QDataStream *d);

	virtual void copyTo(HBaseObj* obj);
	virtual QString TagName();

    //增加删除一个图元元素
    void addBaseObj(HBaseObj* pObj);
    void removeBaseObj(HBaseObj* pObj);

    int getObjID();
    bool findObjID(int nObjID);

    void updateShowPattern();
    bool PatterIsValid(int nId);

    //新建
    HIconShowPattern* newPattern(const QString& name="");
    HIconShowPattern* newPattern(int id);

    //删除
    void delPattern(HIconShowPattern* sp);
    void delPattern(int id);
    void clearPattern();

    //查找
    int getMaxPattern(){return m_nMaxPattern;}

    //查找和设置
    int iconShowPatternCount(){return m_pShowPatternVector.count();}
    HIconShowPattern* findPatternById(int id);
    void setCurrentPattern(int id);
    int getCurrentPattern();
    int getCurrentPatternIndex();
    void setCurrentPatternPtr(HIconShowPattern* sp);
    HIconShowPattern* getCurrentPatternPtr();

    //获取特定图元
    HText* getFirstTextObj();

public:
	virtual void paint(QPainter* painter);
public:
    QVector<HIconShowPattern*> m_pShowPatternVector;
private:
    QString strSymbolName;
    int usSymbolType;
    int m_nMaxPattern;
    int m_nCurPattern;
    HIconShowPattern* m_pCurPattern;
    HIconTemplate* m_pIconTemplate;

};

#endif // HICONSYMBOL_H
