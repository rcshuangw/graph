#include "hopterm.h"
#include "dbtoolapi.h"
HOpTerm::HOpTerm(QObject *parent) : QObject(parent)
{

}
ushort HOpTerm::getOpTermID()
{
    return opTerm.wOpTermID;
}

ushort HOpTerm::getOpTermGroupID()
{
    return opTerm.wOpTermGroupID;
}

uchar HOpTerm::getOpTermType()
{
    return opTerm.btOpTermType;
}

QString HOpTerm::getOpTermName()
{
    return QString(opTerm.szOpTerm);
}

////////////////////////////////////////////////////////操作术语组//////////////////////////////////////////////////////////
HOpTermGroup::HOpTermGroup(QObject *parent):QObject(parent)
{

}

HOpTermGroup::~HOpTermGroup()
{
    while(!m_pOpTermList.isEmpty())
        delete m_pOpTermList.takeFirst();
}

bool HOpTermGroup::loadData(FILEHANDLE &fileHandle)
{
    int fd = openDB(FILE_TYPE_OPTERM);
    if(fd == (int)-1)
        return false;
    for(int i = 0; i < opTermGroup.wOpTermCounts;i++)
    {
        HOpTerm* pOpTerm = new OPTERM;
        if(false == loadDBRecord(fd,++fileHandle.wOpTerm,pOpTerm))
        {
            delete pOpTerm;
            break;
        }
        m_pOpTermList.append(pOpTerm);
    }
    closeDB(FILE_TYPE_OPTERM);
    return true;
}

ushort HOpTermGroup::getOpTermGroupID()
{
    return opTermGroup.wOpTermGroupID;
}

QString HOpTermGroup::getOpTermGroupName()
{
    return QString(opTermGroup.szOpTermGroup);
}

HOpTerm* HOpTermGroup::opTermFen()
{
    for(int i = 0;i < m_pOpTermList.count();i++)
    {
        HOpTerm* pOpTerm = m_pOpTermList[i];
        if(pOpTerm->getOpTermType() == TYPE_OPTERM_FEN)
            return pOpTerm;
    }
    return NULL;
}

HOpTerm* HOpTermGroup::opTermHe()
{
    for(int i = 0;i < m_pOpTermList.count();i++)
    {
        HOpTerm* pOpTerm = m_pOpTermList[i];
        if(pOpTerm->getOpTermType() == TYPE_OPTERM_HE)
            return pOpTerm;
    }
    return NULL;
}

HOpTerm* HOpTermGroup::findOpTerm(ushort wTermID)
{
    for(int i = 0;i < m_pOpTermList.count();i++)
    {
        HOpTerm* pOpTerm = m_pOpTermList[i];
        if(pOpTerm->getOpTermID() == wTermID)
            return pOpTerm;
    }
    return NULL;
}

//////////////////////////////////////////测点类型/////////////////////////////////////////////////
HPointTerm::HPointTerm(QObject* parent)
{

}

ushort HPointTerm::getPointTermID()
{
    return pointTerm.wTermID;
}

QString HPointTerm::getPointTermName()
{
    return QString(pointTerm.szTermName);
}
