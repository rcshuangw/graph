#ifndef HGRAPHEDITORDOC_H
#define HGRAPHEDITORDOC_H

#include <QObject>
class HBaseObj;
class HIconGraphicsItem;
class HIconTemplate;
class QDomElement;
class HStation;
class HGraph;
class HGraphEditorMgr;

class HGraphEditorDoc : QObject
{
public:
    HGraphEditorDoc(HGraphEditorMgr* mgr);
    virtual ~HGraphEditorDoc();

public:
    //加载厂站信息
    void loadStation();

    //厂站ID获取厂站
    HStation* getStation(quint16 wStationID);

    //厂站地址获取厂站
    HStation* getRtu(quint16 wStationAddress);

    //索引厂站
    HStation* findStation(int nIndex);

    //加载模板信息
    void loadIconTemplate();

    //寻找模板 uuid
    HIconTemplate* findIconTemplate(const QString& uuid);

    //加载画面信息
    void loadAllGraph();

    //保存画面信息
    void saveAllGraph();

    //或者画面ID
    int getGraphID();

    //查找画面
    HGraph* findGraph(int graphID);

    //
    HGraph* findGraph(const QString& graphName);

    //新建画面
    HGraph* addGraph(const QString& name);

    //删除画面
    bool delGraph(const QString& name,const int id);

    //打开画面
    bool openGraph(const QString& name,const int id);

    //拷贝画面
    void copyGraph(HGraph* graph);

    //保存画面
    void saveCurGraph();

    //导入画面
    int importGraph(const QString& name);

    //更新所有画面里面的模板信息
    void updateGraphList();

    //获取模板对象列表
    QList<HIconTemplate*> getIconTemplateList();

    //获取画面列表
    QList<HGraph*> getGraphList();

    //获取当前画面
    HGraph* getCurGraph();

    //判断graph文件是否修改
    bool isGraphModify();

public:
    //厂站列表
    QList<HStation*> pStationList;

    //模板列表 读取模板信息后保存的
    QList<HIconTemplate*> pIconTemplateList;

    //图形文件列表
    QList<HGraph*> pGraphList;

protected:

    HGraphEditorMgr* pGraphEditorMgr;

    //当前文件
    HGraph* pCurGraph;

};

#endif // HGRAPHEDITORDOC_H
