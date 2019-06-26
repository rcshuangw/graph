#ifndef HOPTERM_H
#define HOPTERM_H

#include <QObject>
#include "publicdata.h"
//操作术语 测点术语
/*
 * ushort wOpTermGroupID;
    ushort wOpTermID;
    uchar  btOpTermType;//合、分、提示
    char   szOpTerm[OPTERMLEN];//具体术语
*/
class HOpTerm : public QObject
{
    Q_OBJECT
public:
    explicit HOpTerm(QObject *parent = 0);
    ushort getOpTermID();
    ushort getOpTermGroupID();
    uchar getOpTermType();
    QString getOpTermName();
private:
    OPTERM opTerm;
signals:

public slots:
};

/*
 * ushort  wOpTermGroupID;
    char    szOpTermGroup[OPTERMLEN];
    uchar   btOpTermGroupType;//开关、刀闸等类型
    ushort  wOpTermCounts; //管理的操作术语的个数
*/
class HOpTermGroup : public QObject
{
    Q_OBJECT
public:
    HOpTermGroup(QObject *parent = 0);
    ~HOpTermGroup();
public:
    ushort getOpTermGroupID();
    QString getOpTermGroupName();
    HOpTerm* opTermFen(); //每个测点术语组合只有一组分合语句
    HOpTerm* opTermHe();
    HOpTerm* findOpTerm(ushort wTermID); //找到对象，一般采用回复对象，而不是用真假来作为返回值----设计方面的
    bool loadData(FILEHANDLE &fileHandle);
public:
    OPTERMGROUP opTermGroup;//groupID是唯一标识
    QList<HOpTerm*> m_pOpTermList;
};

//测点类型
class HPointTerm : public QObject
{
    Q_OBJECT
public:
    HPointTerm(QObject* parent);
    ushort getPointTermID();
    QString getPointTermName();
private:
    POINTTERM pointTerm;
};

#endif // HOPTERM_H
