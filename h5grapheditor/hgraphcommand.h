#ifndef HGRAPHUNDOCOMMAND_H
#define HGRAPHUNDOCOMMAND_H
/*
 * 撤销、删除类
*/
#include <QUndoCommand>
#include <QPolygonF>

class HGraphEditorMgr;
class HBaseObj;
class HTempContainer;
class HGroup;
class HGraphCommand : public QUndoCommand
{
public:
    enum Type{
        New = 0,            //新建
        Delete = 1,         //删除
        Paste = 2,          //粘贴
        Move = 3,           //移动
        Group = 4,          //组合
        UnGroup = 5,        //解除
        Rotate = 6,         //旋转
        Turn = 7,           //翻转
        Resize = 8,         //改变大小(包含手动改变大小，对齐，相等)
    };

    HGraphCommand(HGraphEditorMgr* graphEditorMgr);
    ~HGraphCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
protected:
    HGraphEditorMgr* m_pGraphEditorMgr;
    bool bFirstTime;
};


//新建
class HGraphNewCommand : public HGraphCommand
{
public:
    HGraphNewCommand(HGraphEditorMgr* graphEditorMgr,HBaseObj* pObj);
    ~HGraphNewCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
protected:
    HBaseObj* pObj;
};

//删除
class HGraphDelCommand : public HGraphCommand
{
public:
    HGraphDelCommand(HGraphEditorMgr* graphEditorMgr,QList<HBaseObj*> pObjs);
    ~HGraphDelCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
protected:
    QList<HBaseObj*> pObjList;
};

//粘贴
class HGraphPasteCommand : public HGraphCommand
{
public:
    HGraphPasteCommand(HGraphEditorMgr* graphEditorMgr,QList<HBaseObj*> pObjs);
    ~HGraphPasteCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
protected:
    QList<HBaseObj*> pObjList;
};

//移动
class HGraphMoveCommand : public HGraphCommand
{
public:
    HGraphMoveCommand(HGraphEditorMgr* graphEditorMgr,QList<HBaseObj*> pObjs,qreal dx,qreal dy);
    HGraphMoveCommand(HGraphEditorMgr* graphEditorMgr,QList<HBaseObj*> pObjs,QList<qreal> dxs,QList<qreal> dys);
    HGraphMoveCommand(HGraphEditorMgr* graphEditorMgr,QList<HBaseObj*> pObjs,QList<QPointF> oldPt,QList<QPointF> newPt);
    ~HGraphMoveCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
protected:
    QList<HBaseObj*> pObjList;
    QList<qreal> dxList;
    QList<qreal> dyList;
};

//旋转
class HGraphRotateCommand : public HGraphCommand
{
public:
    HGraphRotateCommand(HGraphEditorMgr* graphEditorMgr,QList<HBaseObj*> pObjs,float angle);
    HGraphRotateCommand(HGraphEditorMgr* graphEditorMgr,QList<HBaseObj*> pObjs,QList<float> angles);
    ~HGraphRotateCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
protected:
    QList<HBaseObj*> pObjList;
    QList<float> angleList;

};

//翻转
class HGraphTurnCommand : public HGraphCommand
{
public:
    HGraphTurnCommand(HGraphEditorMgr* graphEditorMgr,QList<HBaseObj*> pObjs,bool direction);
    ~HGraphTurnCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
protected:
    QList<HBaseObj*> pObjList;
    bool bDirection;

};

//改变大小
class HGraphResizeCommand : public HGraphCommand
{
public:
    HGraphResizeCommand(HGraphEditorMgr* graphEditorMgr,QList<HBaseObj*> pObjs,QList<QPolygonF> oldPts,QList<QPolygonF> newPts);
    ~HGraphResizeCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
protected:
    QList<HBaseObj*> pObjList;
    QList<QPolygonF> oldPtList;
    QList<QPolygonF> newPtList;

};

class HGraphGroupCommand : public HGraphCommand
{
public:
    HGraphGroupCommand(HGraphEditorMgr* graphEditorMgr,HTempContainer* temp,HGroup* group,bool changed);
    ~HGraphGroupCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
    void group();
    void unGroup();
protected:
    HTempContainer* m_pTempContainer;
    HGroup* m_pGroup;
    bool m_bChanged;

};
#endif // HGRAPHUNDOCOMMAND_H
