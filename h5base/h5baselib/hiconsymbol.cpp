#include "hiconsymbol.h"
#include "hiconshowpattern.h"
#include "hicontemplate.h"
#include "hline.h"
#include "hrectangle.h"
#include <QVariant>
HIconSymbol::HIconSymbol(HIconTemplate* t):m_pIconTemplate(t)
{
    setShapeType(Icon);
    m_nMaxPattern = 0;
    m_nCurPattern = 0;
    m_pCurPattern = NULL;
    m_bModify = false;
    move(0,0);
}

HIconSymbol::~HIconSymbol()
{
   HContainerObj::clear();
   clear();
}

void HIconSymbol::clear()
{
    HContainerObj::clear();

    while(!m_pShowPatternVector.isEmpty())
    {
        HIconShowPattern* pattern = (HIconShowPattern*)m_pShowPatternVector.takeFirst();
        if(pattern)
        {
            delete pattern;
            pattern = NULL;
        }
    }
    m_pShowPatternVector.clear();
}

QString HIconSymbol::tagName()
{
	return "IconSymbol";
}

void HIconSymbol::readXml(int v,QDomElement* dom)
{
    if(!dom)
        return;
	int nCur = dom->attribute("CurPattern").toInt();
    HContainerObj::readXml(v,dom);

    QDomElement spEle = dom->namedItem("ShowPatterns").toElement();
    //构建下面的元素对象
	QDomNode n = spEle.firstChild();
    for(int i = 0;!n.isNull();n=n.nextSibling(),i++)
    {
        QDomElement e = n.toElement();
        if(e.tagName() != "ShowPattern") continue;

		int nPattern = e.attribute("PatternID").toInt();
        HIconShowPattern* pattern = newPattern(nPattern);
        if(!pattern)
        {
            delete pattern;
            pattern = NULL;
            continue;
        }
        pattern->strName = e.attribute("Name");
        pattern->strAlias = e.attribute("Alias");
    }
    updateShowPattern();
    setCurrentPattern(nCur);
    //还要刷新一下 把对应的Obj 放到showPattern下面
}

void HIconSymbol::writeXml(int v,QDomElement *dom)
{
    if(!dom)
        return;
	dom->setAttribute("CurPattern", m_nCurPattern);
    HContainerObj::writeXml(v,dom);


    //再创建显示方案的xml结构
    QDomElement patternDom = dom->ownerDocument().createElement("ShowPatterns");
    dom->appendChild(patternDom);
    for(int i = 0; i < m_pShowPatternVector.size();i++)
    {
        HIconShowPattern* pattern = (HIconShowPattern*)m_pShowPatternVector[i];
        if(!pattern)continue;
        QDomElement patternChildDom = dom->ownerDocument().createElement("ShowPattern");
        patternChildDom.setAttribute("Name",pattern->strName);
        patternChildDom.setAttribute("Alias",pattern->strAlias);
        patternChildDom.setAttribute("PatternID",pattern->nPattern);
        patternDom.appendChild(patternChildDom);
    }
}

void HIconSymbol::readData(int v,QDataStream* d)
{
	if (!d) return;
	int n;
	*d >> n;
	m_nCurPattern = n;
	*d >> n;
	int count = n;
	for (int i = 0; i < count; i++)
	{
		int nPattern;
		*d >> nPattern;
		HIconShowPattern* pSP = findPatternById(nPattern);
		if (!pSP)
		{
			pSP = newPattern(nPattern);
		}
		QString s;
		*d >> s;
		pSP->strName = s;
		*d >> s;
		pSP->strAlias = s;
	}
    HContainerObj::readData(v, d);
}

void HIconSymbol::writeData(int v,QDataStream *d)
{
	if (!d) return;
	*d << (int)m_nCurPattern;
	int count = m_pShowPatternVector.size();
	*d << (int)count;
	for (int i = 0; i < count; i++)
	{
		HIconShowPattern* pSP = m_pShowPatternVector.at(i);
		if (!pSP) continue;
		*d << (int)pSP->nPattern;
		*d << pSP->strName;
		*d << pSP->strAlias;
	}
    HContainerObj::writeData(v, d);
}

void HIconSymbol::addBaseObj(HBaseObj* pObj)
{
    if(!pObj)
        return;

    int objID = getObjID();
    pObj->setObjID(objID);
    QString strObjName = QString("%1_%2_%3").arg(pObj->tagName()).arg(pObj->getShapeType()).arg(pObj->getObjID());
    pObj->setObjName(strObjName);


	//先放到总列表中，这个list维护所有创建的图符
    addObj(pObj);

	//再放到对应的pattern列表中
    HIconShowPattern* pSP = getCurrentPatternPtr();
    if(!pSP)
        return;
    pSP->addObj(pObj);
}

void HIconSymbol::removeBaseObj(HBaseObj* pObj)
{
    if(!pObj)
        return;
	//从对应的pattern中删除，注意不能从总列表中删除。
    HIconShowPattern* pSP = getCurrentPatternPtr();
    if(!pSP)
        return;
    pSP->removeObj(pObj);
}

void HIconSymbol::copyTo(HBaseObj *obj)
{
    if(!obj) return;
	HIconSymbol* pSymbol = (HIconSymbol*)obj;
    pSymbol->clear();
    HContainerObj::copyTo(pSymbol);

    for(int i = 0; i < m_pShowPatternVector.size();i++)
    {
        HIconShowPattern* pattern = (HIconShowPattern*)m_pShowPatternVector[i];
		HIconShowPattern* newPattern = pSymbol->newPattern(pattern->nPattern);
        pattern->copyTo(newPattern);
    }
	pSymbol->m_nMaxPattern = m_nMaxPattern;
	pSymbol->updateShowPattern();
    pSymbol->setCurrentPattern(m_nCurPattern);
}

//获取ObjID
int HIconSymbol::getObjID()
{
    int nObjID = 1;
    while(findObjID(nObjID))
        nObjID++;
    return nObjID;
}

bool HIconSymbol::findObjID(int nObjID)
{
    for(int i = 0;i < getObjList().count();i++)
    {
        HBaseObj* pObj = (HBaseObj*)getObjList().at(i);
       if(pObj && pObj->getObjID() == nObjID)
           return true;
    }
    return false;
}

void HIconSymbol::updateShowPattern()
{
    foreach (HBaseObj* pObj, m_pObjList) {
        HIconShowPattern* pattern = findPatternById(pObj->getPattern());
        if(!pattern) continue;
        pattern->addObj(pObj);
    }
}

bool HIconSymbol::PatterIsValid(int nId)
{
    if(nId < 0)
        return false;
    return true;
}

//新建
HIconShowPattern* HIconSymbol::newPattern(const QString& name)
{
    HIconShowPattern* newSP = new HIconShowPattern(this);
    newSP->strName = name;
    newSP->nPattern = m_nMaxPattern;
    m_nMaxPattern++;
    m_pShowPatternVector.append(newSP);
    setCurrentPatternPtr(newSP);
    return newSP;
}

HIconShowPattern* HIconSymbol::newPattern(int id)
{
    //if()
    HIconShowPattern* newSP = new HIconShowPattern(this);
    newSP->nPattern = id;
    m_pShowPatternVector.append(newSP);
    if(id >= m_nMaxPattern)
        m_nMaxPattern++;
    setCurrentPatternPtr(newSP);
    return newSP;
}

//删除
void HIconSymbol::delPattern(HIconShowPattern* sp)
{
    for(int i = 0; i< m_pShowPatternVector.size();i++)
    {
        HIconShowPattern* pPattern = m_pShowPatternVector.at(i);
        if(pPattern->nPattern == sp->nPattern)
        {
            pPattern->clear();
            m_pShowPatternVector.remove(i);
            delete pPattern;
            pPattern = NULL;
        }
    }
}

void HIconSymbol::delPattern(int id)
{
    for(int i = 0; i< m_pShowPatternVector.size();i++)
    {
        HIconShowPattern* pPattern = m_pShowPatternVector.at(i);
        if(pPattern->nPattern == id)
        {
            pPattern->clear();
			m_pShowPatternVector.remove(i);
            delete pPattern;
            pPattern = NULL;
        }
    }
}

void HIconSymbol::clearPattern()
{
    while (!m_pShowPatternVector.isEmpty()) {
        HIconShowPattern* pPattern = m_pShowPatternVector.takeFirst();
        pPattern->clear();
        delete pPattern;
        pPattern = NULL;
    }
}

//查找和设置
HIconShowPattern* HIconSymbol::findPatternById(int id)
{
    for(int i = 0; i< m_pShowPatternVector.size();i++)
    {
        HIconShowPattern* pPattern = m_pShowPatternVector.at(i);
        if(pPattern->nPattern == id)
            return pPattern;
    }
    return NULL;
}

void HIconSymbol::setCurrentPattern(int id)
{
    m_nCurPattern = id;
    setCurrentPatternPtr(findPatternById(id));
}

int HIconSymbol::getCurrentPattern()
{
    return m_nCurPattern;
}

int HIconSymbol::getCurrentPatternIndex()
{
    if(!m_pCurPattern || m_pShowPatternVector.isEmpty())
        return -1;
    return m_pShowPatternVector.indexOf(m_pCurPattern);
}

void HIconSymbol::setCurrentPatternPtr(HIconShowPattern* sp)
{
	m_pCurPattern = sp;
	m_nCurPattern = sp->nPattern;
}

HIconShowPattern* HIconSymbol::getCurrentPatternPtr()
{
    return m_pCurPattern;
}

HText* HIconSymbol::getFirstTextObj()
{
    HText* pTextObj = NULL;
    HIconShowPattern* curPattern = (HIconShowPattern*)findPatternById(0);
	QVector<HBaseObj*> pObjList = curPattern->getObjList();
    if(curPattern)
    {
        for(int i = 0; i < pObjList.count();i++)
        {
            HBaseObj* pObj = pObjList.at(i);
            if(pObj->isDeleted() || !pObj || pObj->getShapeType() != Text)
                continue;
            pTextObj = (HText*)pObj;
            break;
        }
    }
    return pTextObj;
}

void HIconSymbol::paint(QPainter* painter)
{
	if (!painter)
		return;
	painter->save();
	HIconShowPattern* pattern = getCurrentPatternPtr();
	if (!pattern)
	{
		painter->restore();
		return;
	}

	//先要根据zvalue
	for (int i = 0; i < pattern->getObjList().count(); i++)
	{
		HBaseObj* pObj = (HBaseObj*)(pattern->getObjList().at(i));
		if (pObj)
		{
			pObj->paint(painter);
		}
	}
	painter->restore();

}

void HIconSymbol::setModify(bool b)
{
    m_bModify = b;
}

bool HIconSymbol::isModify()
{
    return m_bModify;
}
