#ifndef HONLINEDOC_H
#define HONLINEDOC_H
#include <QObject>
#include <QList>
class HStation;
class HBaseObj;
class HIconTemplate;
class HStation;
class HGraph;
class HAntiMalopMgr;

class HAntiMalopDoc : QObject
{
    Q_OBJECT
public:
    HAntiMalopDoc(HAntiMalopMgr* mgr);
    virtual ~HAntiMalopDoc();

public:
    //加载画面信息
    void loadAllGraph();

    //查找根画面
    HGraph* getRootGraph();

    //查找画面
    HGraph* findGraph(int graphID);

    //
    HGraph* findGraph(const QString& graphName);

    //打开画面
    bool openGraph(const QString& name,const int id);

    //获取当前画面
    HGraph* getCurGraph();

    //刷新模板列表
    void updateGraphList();

public:

    //图形文件列表
    QList<HGraph*> m_pGraphList;

protected:
    HAntiMalopMgr* m_pAntiMalopMgr;
    HGraph* m_pCurGraph;

};

#endif // HONLINEDOC_H
