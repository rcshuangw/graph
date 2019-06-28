#include "hopsheet.h"
#include "honlineapi.h"
#include "hdbtoolapi.h"
#include "hantimalopmgr.h"
#include <QtAlgorithms>

///////////////////////////////////////////////////////////////////////////////
//
HOpSheetInfo::HOpSheetInfo()
{
    memset(&m_opSheetInfo,0,sizeof(OPSHEETINFO));
    m_opSheetInfo.wStationID = (ushort)-1;
    m_opSheetInfo.wGroupID = (ushort)-1;
    m_opSheetInfo.wOpSheetID = (ushort)-1;
    m_opSheetInfo.wOpSheetNo = (ushort)-1;
    qstrcpy(m_opSheetInfo.szOpSheetTitle,"新票");
    qstrcpy(m_opSheetInfo.szOpSheetDescripe,"新票");
    qstrcpy(m_opSheetInfo.szOpSheetTask,"");
    m_opSheetInfo.btOpSheetType = OPSHEET_TYPE_TEMP;
    m_opSheetInfo.nOpSheetSteps = 0;
}

HOpSheetInfo::~HOpSheetInfo()
{

}

void HOpSheetInfo::setOpSheetInfo(OPSHEETINFO* info)
{
    if(!info) return;
    memcpy(&m_opSheetInfo,info,sizeof(OPSHEETINFO));
}

void HOpSheetInfo::getOpSheetInfo(OPSHEETINFO* info)
{
    if(!info) return;
    memcpy(info,&m_opSheetInfo,sizeof(OPSHEETINFO));
}

bool HOpSheetInfo::getAttr(ushort wAttr,void* pVal,size_t size)
{
    if(!pVal)
        return false;
    switch(wAttr)
    {
    case OPSHEET_ATTR_ID      : *((ushort*)pVal) = m_opSheetInfo.wOpSheetID;break;
    case OPSHEET_ATTR_NO      : *((ushort*)pVal) = m_opSheetInfo.wOpSheetNo;break;
    case OPSHEET_ATTR_TASKTYPE: *((ushort*)pVal) = m_opSheetInfo.btOpSheetTaskType;break;
    case OPSHEET_ATTR_STID    : *((ushort*)pVal) = m_opSheetInfo.wStationID;break;
    case OPSHEET_ATTR_GROUPID : *((ushort*)pVal) = m_opSheetInfo.wGroupID;break;
    case OPSHEET_ATTR_TYPE    : *((ushort*)pVal) = m_opSheetInfo.btOpSheetType;break;
    case OPSHEET_ATTR_STEPS   :	*((int*)pVal) = m_opSheetInfo.nOpSheetSteps;break;
    case OPSHEET_ATTR_TITLE   :	qstrcpy((char*)pVal,m_opSheetInfo.szOpSheetTitle);break;
    case OPSHEET_ATTR_DESCRIBE:	qstrcpy((char*)pVal,m_opSheetInfo.szOpSheetDescripe);break;
    case OPSHEET_ATTR_TASK    : qstrcpy((char*)pVal,m_opSheetInfo.szOpSheetTask);break;
    case OPSHEET_ATTR_OPERATOR: qstrcpy((char*)pVal,m_opSheetInfo.szOperator);break;
    case OPSHEET_ATTR_GUARDIAN:	qstrcpy((char*)pVal,m_opSheetInfo.szGuardian);break;
    case OPSHEET_ATTR_EDITOR  :	qstrcpy((char*)pVal,m_opSheetInfo.szEditor);break;
    case OPSHEET_ATTR_MAKETIME:*((time_t*)pVal) = m_opSheetInfo.tOperTime;break;
    default: return false;
    }
    return true;
}

bool HOpSheetInfo::setAttr(ushort wAttr,void* pVal,size_t size)
{
    if(!pVal)
        return false;
    switch(wAttr)
    {
    case OPSHEET_ATTR_ID      : m_opSheetInfo.wOpSheetID = *((ushort*)pVal);break;
    case OPSHEET_ATTR_NO      : m_opSheetInfo.wOpSheetNo = *((ushort*)pVal);break;
    case OPSHEET_ATTR_TASKTYPE: m_opSheetInfo.btOpSheetTaskType = *((ushort*)pVal);break;
    case OPSHEET_ATTR_STID    : m_opSheetInfo.wStationID = *((ushort*)pVal);break;
    case OPSHEET_ATTR_GROUPID : m_opSheetInfo.wGroupID = *((ushort*)pVal);break;
    case OPSHEET_ATTR_TYPE    : m_opSheetInfo.btOpSheetType = *((ushort*)pVal);break;
    case OPSHEET_ATTR_STEPS   :	m_opSheetInfo.nOpSheetSteps = *((int*)pVal);break;
    case OPSHEET_ATTR_TITLE   :
        qstrncpy(m_opSheetInfo.szOpSheetTitle,(char*)pVal,OPERASHEETNAMELEN-1);
        m_opSheetInfo.szOpSheetTitle[OPERASHEETNAMELEN-1] = 0;
        break;
    case OPSHEET_ATTR_DESCRIBE:
        qstrncpy(m_opSheetInfo.szOpSheetDescripe,(char*)pVal,OPERASHEETDESCRIBELEN-1);
        m_opSheetInfo.szOpSheetDescripe[OPERASHEETDESCRIBELEN-1] = 0;
        break;
    case OPSHEET_ATTR_TASK    :
        qstrncpy(m_opSheetInfo.szOpSheetTask,(char*)pVal,OPERASHEETTASKLEN-1);
        m_opSheetInfo.szOpSheetDescripe[OPERASHEETTASKLEN-1] = 0;
        break;
    case OPSHEET_ATTR_OPERATOR:
        qstrncpy(m_opSheetInfo.szOperator,(char*)pVal,OPERATORLEN-1);
        m_opSheetInfo.szOpSheetDescripe[OPERATORLEN-1] = 0;
        break;
    case OPSHEET_ATTR_GUARDIAN:
        qstrncpy(m_opSheetInfo.szGuardian,(char*)pVal,OPERATORLEN-1);
        m_opSheetInfo.szOpSheetDescripe[OPERATORLEN-1] = 0;
        break;
    case OPSHEET_ATTR_EDITOR  :
        qstrncpy(m_opSheetInfo.szEditor,(char*)pVal,OPERATORLEN-1);
        m_opSheetInfo.szOpSheetDescripe[OPERATORLEN-1] = 0;
        break;
    case OPSHEET_ATTR_MAKETIME:m_opSheetInfo.tOperTime = *((time_t*)pVal);break;
    default: return false;
    }
    return true;
}

void HOpSheetInfo::copyTo(HOpSheetInfo* info)
{
    if(!info) return;
    memcpy(&m_opSheetInfo,&info->m_opSheetInfo,sizeof(OPSHEETINFO));
}

void HOpSheetInfo::copyFrom(HOpSheetInfo* info)
{
    if(!info) return;
    memcpy(&info->m_opSheetInfo,&m_opSheetInfo,sizeof(OPSHEETINFO));
}

bool HOpSheetInfo::checkExist()
{
    return false;
}

///////////////////////////////////////////////////////////////////////////////////////////
HOpSheetStep::HOpSheetStep()
{
    m_bBreak = false;
    m_bRunning = false;
    memset(&opSheetStep,0,sizeof(OPSHEETSTEP));
    opSheetStep.wOpSheetID = (ushort)-1;
    opSheetStep.nStepIndex = (int)-1;
    opSheetStep.nPreStepIndex = (int)-1;
    opSheetStep.nNextStepIndex = (int)-1;

    opSheetStep.wOpStID = (ushort)-1;
    opSheetStep.wOpPtID = (ushort)-1;
    opSheetStep.btOpType = STEP_TYPE_TISHI;
    opSheetStep.btLockType = (ushort)-1;//锁类型
    opSheetStep.dwMainLockNo = (ulong)-1;
    opSheetStep.dwOpenLockNo = (ulong)-1;
    opSheetStep.dwCloseLockNo = (ulong)-1;
    qstrcpy(opSheetStep.szContent,QStringLiteral("新步骤"));
    qstrcpy(opSheetStep.szRemark,QStringLiteral("操作备注"));
    opSheetStep.wOpFlag = (ushort)-1;
}

HOpSheetStep::HOpSheetStep(ushort wOpSheetID)
{
    m_bBreak = false;
    m_bRunning = false;
    memset(&opSheetStep,0,sizeof(OPSHEETSTEP));
    opSheetStep.wOpSheetID = wOpSheetID;
    opSheetStep.nStepIndex = (int)-1;
    opSheetStep.nPreStepIndex = (int)-1;
    opSheetStep.nNextStepIndex = (int)-1;

    opSheetStep.wOpStID = (ushort)-1;
    opSheetStep.wOpPtID = (ushort)-1;
    opSheetStep.btOpType = STEP_TYPE_TISHI;
    opSheetStep.btLockType = (ushort)-1;//锁类型
    opSheetStep.dwMainLockNo = (ulong)-1;
    opSheetStep.dwOpenLockNo = (ulong)-1;
    opSheetStep.dwCloseLockNo = (ulong)-1;
    qstrcpy(opSheetStep.szContent,QStringLiteral("新步骤"));
    qstrcpy(opSheetStep.szRemark,QStringLiteral("操作备注"));
    opSheetStep.wOpFlag = (ushort)-1;
}

HOpSheetStep::~HOpSheetStep()
{

}

void HOpSheetStep::loadFromDb(int row)
{

}

void HOpSheetStep::saveToDb(int row)
{

}

bool HOpSheetStep::getAttr(ushort wAttr,void* pVal,size_t size)
{
    if(!pVal)
        return false;
    switch(wAttr)
    {
    case STEP_ATTR_OPTABID  : *((ushort*)pVal) = opSheetStep.wOpSheetID;break;
    case STEP_ATTR_INDEX    : *((ushort*)pVal) = opSheetStep.nStepIndex;break;
    case STEP_ATTR_OPSTID   : *((ushort*)pVal) = opSheetStep.wOpStID;break;
    case STEP_ATTR_OPPTID   : *((ushort*)pVal) = opSheetStep.wOpPtID;break;
    case STEP_ATTR_OPTYPE   : *((ushort*)pVal) = opSheetStep.btOpType;break;
    case STEP_ATTR_LOCKTYPE : *((ushort*)pVal) = opSheetStep.btLockType;break;
    case STEP_ATTR_MLOCKNO  : *((int*)pVal) = opSheetStep.dwMainLockNo;break;
    case STEP_ATTR_SENTENCE : qstrcpy((char*)pVal,opSheetStep.szContent);break;
    case STEP_ATTR_OPTIME   : *((time_t*)pVal) = opSheetStep.tOpTime;break;
    case STEP_ATTR_HELOCKNO : *((ushort*)pVal) = opSheetStep.dwOpenLockNo;break;
    case STEP_ATTR_FENLOCKNO: *((ushort*)pVal) = opSheetStep.dwCloseLockNo;break;
    case STEP_ATTR_PRESTEP  : *((ushort*)pVal) = opSheetStep.nPreStepIndex;break;
    case STEP_ATTR_NEXTSTEP : *((ushort*)pVal) = opSheetStep.nNextStepIndex;break;
    case STEP_ATTR_OPFLAG   : *((time_t*)pVal) = opSheetStep.wOpFlag;break;
    default: return false;
    }
    return true;
}

bool HOpSheetStep::setAttr(ushort wAttr,void* pVal,size_t size)
{
    if(!pVal)
        return false;
    switch(wAttr)
    {
    case STEP_ATTR_OPTABID  : opSheetStep.wOpSheetID = *((ushort*)pVal);break;
    case STEP_ATTR_INDEX    : opSheetStep.nStepIndex = *((ushort*)pVal);break;
    case STEP_ATTR_OPSTID   : opSheetStep.wOpStID = *((ushort*)pVal);break;
    case STEP_ATTR_OPPTID   : opSheetStep.wOpPtID = *((ushort*)pVal);break;
    case STEP_ATTR_OPTYPE   : opSheetStep.btOpType = *((ushort*)pVal);break;
    case STEP_ATTR_LOCKTYPE : opSheetStep.btLockType = *((ushort*)pVal);break;
    case STEP_ATTR_MLOCKNO  : opSheetStep.dwMainLockNo = *((int*)pVal);break;
    case STEP_ATTR_SENTENCE :
        qstrncpy(opSheetStep.szContent,(char*)pVal,OPERASHEETCONTENTLEN-1);
        opSheetStep.szContent[OPERASHEETCONTENTLEN-1] = 0;
        break;
    case STEP_ATTR_OPTIME   : opSheetStep.tOpTime = *((time_t*)pVal);break;
    case STEP_ATTR_HELOCKNO : opSheetStep.dwOpenLockNo = *((ushort*)pVal);break;
    case STEP_ATTR_FENLOCKNO: opSheetStep.dwCloseLockNo = *((ushort*)pVal);break;
    case STEP_ATTR_PRESTEP  : opSheetStep.nPreStepIndex = *((ushort*)pVal);break;
    case STEP_ATTR_NEXTSTEP : opSheetStep.nNextStepIndex = *((ushort*)pVal); break;
    case STEP_ATTR_OPFLAG   : opSheetStep.wOpFlag = *((time_t*)pVal) = ;break;
    default: return false;
    }
    return true;
}

void HOpSheetStep::setStepIndex(int step)
{
    opSheetStep.nStepIndex = step;
}

int HOpSheetStep::getStepIndex()
{
    return opSheetStep.nStepIndex;
}

void HOpSheetStep::setOpSheetStep(HOpSheetStep* step)
{
    if(!step) return;
    memcpy(&opSheetStep,step,sizeof(OPSHEETSTEP));
}

void HOpSheetStep::getOpSheetStep(HOpSheetStep* step)
{
    if(!step) return;
    memcpy(step,&opSheetStep,sizeof(OPSHEETSTEP));
}

void HOpSheetStep::start()
{
    m_bRunning = true;
}

void HOpSheetStep::stop()
{
    m_bRunning = false;
}

bool HOpSheetStep::isRunning()
{
    return m_bRunning;
}

void HOpSheetStep::setBreak()
{
    m_bBreak = !m_bBreak;
}

bool HOpSheetStep::isBreak()
{
    return m_bBreak;
}

void HOpSheetStep::clearBreak()
{
    m_bBreak = false;
}

bool HOpSheetStep::isRemoteOp()
{
    if(DIGITAL_OPERAFLAG_REMOTE == opSheetStep.wOpFlag)
        return true;
    return false;
}

bool HOpSheetStep::isLocalOp()
{
    if(DIGITAL_OPERAFLAG_LOCAL == opSheetStep.wOpFlag)
        return true;
    return false;
}

bool HOpSheetStep::isCtrlLock()
{
    return false;
}

///////////////////////////////////////////////////////////////////////
HOpSheet::HOpSheet()
{
    m_pOpSheetInfo = NULL;
    m_bModify = false;
}

HOpSheet::~HOpSheet()
{
    clearOpSheetSteps();
    if(m_pOpSheetInfo)
    {
        delete m_pOpSheetInfo;
        m_pOpSheetInfo = NULL;
    }
}

bool HOpSheet::getAttr(ushort wAttr,void* pVal,size_t size)
{
    if(!pVal || !m_pOpSheetInfo)
        return false;
    return m_pOpSheetInfo->getAttr(wAttr,pVal,size);
    //return true;
}

bool HOpSheet::setAttr(ushort wAttr,void* pVal,size_t size)
{
    if(!pVal || !m_pOpSheetInfo)
        return false;
    return m_pOpSheetInfo->setAttr(wAttr,pVal,size);
    //return true;
}

void HOpSheet::clearOpSheetSteps()
{
    /*
    while(!m_pOpSheetStepList.isEmpty())
        delete (OPSHEETSTEP*)m_pOpSheetStepList.takeFirst();*/
    qDeleteAll(m_pOpSheetStepList.begin(),m_pOpSheetStepList.end());
    m_pOpSheetStepList.clear();
}

//操作票增加步骤
HOpSheetStep* HOpSheet::addOpSheetStep()
{
    if(!m_pOpSheetInfo) return NULL;
    ushort wOpSheetID;
    if(!getAttr(OPSHEET_ATTR_ID,&wOpSheetID) || (ushort)-1 == wOpSheetID)
        return NULL;
    HOpSheetStep* pOpSheetStep = new HOpSheetStep(wOpSheetID);
    if(!pOpSheetStep) return NULL;
    m_pOpSheetStepList.append(pOpSheetStep);
    int nSteps = m_pOpSheetStepList.count();
    pOpSheetStep->setStepIndex(nSteps);
    setAttr(OPSHEET_ATTR_STEPS,nSteps);
    return NULL;
}

HOpSheetStep* HOpSheet::insertOpSheetItem(int step)
{
    if(!m_pOpSheetInfo) return NULL;

    if(m_pOpSheetStepList.isEmpty())
        return addOpSheetStep();
    else
    {
        //1.找到第step步，获取index和pre和next
        HOpSheetStep* pCurSheetStep = m_pOpSheetStepList.value(step);
        if(!pCurSheetStep) return NULL;
        int nCurStepIndex,nPreStepIndex,nNextStepIndex;
        nCurStepIndex = nPreStepIndex = nNextStepIndex = (int)-1;
        pCurSheetStep->getAttr(STEP_ATTR_INDEX,&nCurStepIndex);
        pCurSheetStep->getAttr(STEP_ATTR_PRESTEP,&nPreStepIndex);
        pCurSheetStep->getAttr(STEP_ATTR_NEXTSTEP,&nNextStepIndex);

        //2.新建新的步骤
        ushort wOpSheetID;
        if(!getAttr(OPSHEET_ATTR_ID,&wOpSheetID) || (ushort)-1 == wOpSheetID)
            return NULL;
        ushort wOpSheetID1;
        pCurSheetStep->getAttr(OPSHEET_ATTR_ID,&wOpSheetID1);
        if(wOpSheetID != wOpSheetID1)
            return NULL;
        HOpSheetStep* pNewSheetStep = new HOpSheetStep(wOpSheetID);
        pNewSheetStep->setAttr(STEP_ATTR_INDEX,&nCurStepIndex);
        pNewSheetStep->setAttr(STEP_ATTR_PRESTEP,&nPreStepIndex);
        pNewSheetStep->setAttr(STEP_ATTR_NEXTSTEP,&nNextStepIndex);
        m_pOpSheetStepList.insert(step,pNewSheetStep);

        for(int i = step+1;i < m_pOpSheetStepList.count();i++)
        {
            nCurStepIndex = nPreStepIndex = nNextStepIndex = (int)-1;
            HOpSheetStep* pOpSheetStep = m_pOpSheetStepList[i];
            if(!pOpSheetStep) continue;
            pOpSheetStep->getAttr(STEP_ATTR_INDEX,&nCurStepIndex);
            pOpSheetStep->getAttr(STEP_ATTR_PRESTEP,&nPreStepIndex);
            pOpSheetStep->getAttr(STEP_ATTR_NEXTSTEP,&nNextStepIndex);
            if(nCurStepIndex != (int)-1) nCurStepIndex++;
            if(nPreStepIndex != (int)-1) nPreStepIndex++;
            if(nNextStepIndex != (int)-1) nNextStepIndex++;
            pOpSheetStep->setAttr(STEP_ATTR_INDEX,&nCurStepIndex);
            pOpSheetStep->setAttr(STEP_ATTR_PRESTEP,&nPreStepIndex);
            pOpSheetStep->setAttr(STEP_ATTR_NEXTSTEP,&nNextStepIndex);
        }
        int nSteps;
        getAttr(OPSHEET_ATTR_STEPS,&nSteps);
        nSteps++;
        setAttr(OPSHEET_ATTR_STEPS,&nSteps);
        qDebug()<<(m_pOpSheetStepList.count() - nSteps);

        return pNewSheetStep;
    }
    return NULL;
}

HOpSheetStep* HOpSheet::getOpSheetStep(int index)
{
    return (HOpSheetStep*)m_pOpSheetStepList.value(index);
}

bool HOpSheet::moveOpSheetStep(int index,bool up)//上移还是下移
{
    return false;
}

bool HOpSheet::delOpSheetStep(int index)
{
    HOpSheetStep* pOpSheetStep = m_pOpSheetStepList.value(index);
    if(!pOpSheetStep) return true;

    int nCurStepIndex,nPreStepIndex,nNextStepIndex;
    for(int i = step+1;i < m_pOpSheetStepList.count();i++)
    {
        nCurStepIndex = nPreStepIndex = nNextStepIndex = (int)-1;
        HOpSheetStep* pOpSheetStep = m_pOpSheetStepList[i];
        if(!pOpSheetStep) continue;
        pOpSheetStep->getAttr(STEP_ATTR_INDEX,&nCurStepIndex);
        pOpSheetStep->getAttr(STEP_ATTR_PRESTEP,&nPreStepIndex);
        pOpSheetStep->getAttr(STEP_ATTR_NEXTSTEP,&nNextStepIndex);
        if(nCurStepIndex != (int)-1) nCurStepIndex--;
        if(nPreStepIndex != (int)-1) nPreStepIndex--;
        if(nNextStepIndex != (int)-1) nNextStepIndex--;
        pOpSheetStep->setAttr(STEP_ATTR_INDEX,&nCurStepIndex);
        pOpSheetStep->setAttr(STEP_ATTR_PRESTEP,&nPreStepIndex);
        pOpSheetStep->setAttr(STEP_ATTR_NEXTSTEP,&nNextStepIndex);
    }
    int nSteps;
    getAttr(OPSHEET_ATTR_STEPS,&nSteps);
    nSteps--;
    setAttr(OPSHEET_ATTR_STEPS,&nSteps);

    m_pOpSheetStepList.removeOne(pOpSheetStep);
    delete pOpSheetStep;
    pOpSheetStep = NULL;

    qDebug()<<(m_pOpSheetStepList.count() - nSteps);

}

void HOpSheet::start(int index)
{
    HOpSheetStep* pOpSheetStep = m_pOpSheetStepList.value(index);
    if(!pOpSheetStep) return;
    pOpSheetStep->start();
}

void HOpSheet::stop()
{
    QList<HOpSheetStep*>::iterator it = m_pOpSheetStepList.begin();
    while(it != m_pOpSheetStepList.end())
    {
        HOpSheetStep* pOpSheetStep = *it;
        if(!pOpSheetStep) continue;
        pOpSheetStep->stop();
        it++;
    }
}

bool HOpSheet::isRunning(int index)
{
    HOpSheetStep* pOpSheetStep = m_pOpSheetStepList.value(index);
    if(!pOpSheetStep) return false;
    return pOpSheetStep->isRunning();
}

void HOpSheet::setBreak(int index)
{
    HOpSheetStep* pOpSheetStep = m_pOpSheetStepList.value(index);
    if(!pOpSheetStep) return;
    pOpSheetStep->setBreak();
}

bool HOpSheet::isBreak(int index)
{
    HOpSheetStep* pOpSheetStep = m_pOpSheetStepList.value(index);
    if(!pOpSheetStep) return false;
    return pOpSheetStep->isBreak();
}

void HOpSheet::clearBreak()
{
    QList<HOpSheetStep*>::iterator it = m_pOpSheetStepList.begin();
    while(it != m_pOpSheetStepList.end())
    {
        HOpSheetStep* pOpSheetStep = *it;
        if(!pOpSheetStep) continue;
        pOpSheetStep->clearBreak();
        it++;
    }
}

bool HOpSheet::isModify()
{
    return m_bModify;
}

void HOpSheet::setModify(bool modify)
{
    m_bModify = modify;
}

//数据库部分
bool HOpSheet::loadOpSheet(ushort wOpSheetID)
{
    if((ushort)-1 == wOpSheetID)
        return false;
    HOpSheetInfo* pOpSheetInfo = m_pWfSystemMgr->findOpSheetInfo(wOpSheetID);
    if(!pOpSheetInfo) return false;
    if(NULL == m_pOpSheetInfo)
    {
        m_pOpSheetInfo = new HOpSheetInfo;
        if(!m_pOpSheetInfo) return false;
    }
    m_pOpSheetInfo->copyFrom(pOpSheetInfo);
    //开始读取step
    int nSteps;
    if(!getAttr(OPSHEET_ATTR_STEPS,&nSteps))
        return false;
    clearOpSheetSteps();
    if(nSteps > 0)
    {
        char szFile[256],szPath[256];
        getDataFilePath(DFPATH_OPSHEET,szPath);
        sprintf(szFile,"%s%s%5u%s",szPath,"OPS",wOpSheetID,".OPS");
        int fd = createDBFile(szFile);
        if((int)-1 == fd)
            return false;
        DATAFILEHEADER dataFileHeader;
        loadDataFileHeader(fd,&dataFileHeader);
        for(int i = 0; i < dataFileHeader.wTotal;i++)
        {
            HOpSheetStep* pOpSheetStep = new HOpSheetStep;
            if(false == loadDataFileRecord(fd,++i,&pOpSheetStep->opSheetStep))
            {
                delete pOpSheetStep;
                continue;
            }
            m_pOpSheetStepList.append(pOpSheetStep);
        }
        closeDBFile(fd);
    }
    setModify(false);
    return true;
}

bool HOpSheet::saveOpSheet()
{
    if(NULL == m_pOpSheetInfo)
        return;
    //1.存储OpSheetInfo结构，这个由handle统一处理
    ushort wOpSheetID;
    getAttr(OPSHEET_ATTR_ID,&wOpSheetID);
    if((ushort)-1 == wOpSheetID)
    {
        HOpSheetInfo* pOpSheetInfo = m_pWfSystemMgr->addOpSheet();
        if(!pOpSheetInfo) return false;
        OPSHEETINFO opSheetInfo;
        m_pOpSheetInfo->getOpSheetInfo(&opSheetInfo);
        pOpSheetInfo->setOpSheetInfo(&opSheetInfo);
    }
    HOpSheetInfo* pOpSheetInfo = m_pWfSystemMgr->findOpSheetInfo(wOpSheetID);
    if(!pOpSheetInfo) return false;
    m_pOpSheetInfo->copyTo(pOpSheetInfo);
    m_pWfSystemMgr->saveOpSheetInfo();

    //2.存储步骤操作
    char szFile[256],szPath[256];
    getDataFilePath(DFPATH_OPSHEET,szPath);
    sprintf(szFile,"%s%s%5u%s",szPath,"OPS",wOpSheetID,".OPS");
    int fd = createDBFile(szFile);
    if((int)-1 == fd)
        return false;
    DATAFILEHEADER dataFileHeader;
    loadDataFileHeader(fd,&dataFileHeader);
    int steps;
    getAttr(OPSHEET_ATTR_STEPS,&steps);
    dataFileHeader.wTotal = steps;
    dataFileHeader.btType = FILE_TYPE_OPSHEET;
    dataFileHeader.wTypeLen = sizeof(OPSHEETSTEP);
    saveDataFileHeader(fd,&dataFileHeader);
    HOpSheetStep* pOpSheetStep;
    for(int i = 0; i < m_pOpSheetStepList.count();i++)
    {
        pOpSheetStep = m_pOpSheetStepList[i];
        if(false == saveDataFileRecord(fd,++i,&pOpSheetStep->opSheetStep))
        {
            return false;
        }
    }
    closeDBFile(fd);
    setModify(false);
    return true;
}

void HOpSheet::close()
{
    if(m_pOpSheetInfo)
    {
        delete m_pOpSheetInfo;
        m_pOpSheetInfo = NULL;
    }
    clearOpSheetSteps();
    setModify(false);
}

void HOpSheet::copyTo(HOpSheetInfo* pOpSheetInfo)
{
    if(!m_pOpSheetInfo || !pOpSheetInfo)
        return;
    m_pOpSheetInfo->copyTo(pOpSheetInfo);
}

void HOpSheet::copyFrom(HOpSheetInfo* pOpSheetInfo)
{
    if(!pOpSheetInfo)
        return;
    if(!m_pOpSheetInfo)
    {
        m_pOpSheetInfo = new HOpSheetInfo;
        if(!m_pOpSheetInfo)
             return;
    }
    m_pOpSheetInfo->copyFrom(pOpSheetInfo);
}
