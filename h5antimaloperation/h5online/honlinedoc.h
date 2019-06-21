#ifndef HONLINEDOC_H
#define HONLINEDOC_H

#include <QObject>
#include <QList>
class HStation;
class HBaseObj;
class HIconTemplate;
class HStation;
class HGraph;
class HOnlineMgr;

/*
 * 初始化 加载所有厂站的信息，所有画面的信息，所有模板的信息(考虑启动画面)
 * 初始化临时HGraph
 * 当新建一个新画面时，提供HGraph对象，初始化这个HGraph对象(包含背景等信息)，返回给HGraph
 *临时HGraph的内容提供给view/scene,供显示。
 * 打开画面，删除都是如此，代码此处实现，可以供其他对象调用对应接口
*/
class HOnlineDoc : QObject
{
    Q_OBJECT
public:
    HOnlineDoc(HOnlineMgr* mgr);
    virtual ~HOnlineDoc();

public:
    //加载模板列表 ?
    //void loadIconTemplate();

    //加载画面信息
    void loadAllGraph();

    //查找根画面
    HGraph* getRootGraph();

    //寻找模板 uuid ?
    //HIconTemplate* findIconTemplate(const QString& uuid);

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
    //厂站列表
    //QList<HStation*> m_pStationList;

    //图形文件列表
    QList<HGraph*> m_pGraphList;

    //模板列表
    //QList<HIconTemplate*> m_pIconTemplateList;

protected:

    HOnlineMgr* m_pOnlineMgr;

    //当前文件
    HGraph* m_pCurGraph;

};

#endif // HONLINEDOC_H
