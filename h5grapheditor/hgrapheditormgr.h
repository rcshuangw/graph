#ifndef HGRAPHEDITORMGR_H
#define HGRAPHEDITORMGR_H

#include <QObject>
#include <QRectF>
#include <QUndoStack>
#include <QUndoCommand>
#include <QFont>
#include <QColor>
#include <QImage>
#include "hiconapi.h"
class HGraphEditorScene;
class HGraphEditorView;
class HGraphEditorDoc;
class HGraphEditorOp;
class HIconGraphicsItem;
class HBaseObj;
class HGraph;
class HSelectedMgr;
class HGraphEditorDrawToolMgr;
class HGraphEditorSelectTool;
class HGraphEditorMgr : public QObject
{
    Q_OBJECT
public:
    HGraphEditorMgr();
    ~HGraphEditorMgr();
public:
    HGraphEditorScene* graphEditorScene();
    HGraphEditorView*  graphEditorView();
    HGraphEditorDoc*   graphEditorDoc();
    HGraphEditorOp*    graphEditorOp();
    QUndoStack*        graphEditorStack();
    HSelectedMgr*      selectedMgr();
    HGraphEditorDrawToolMgr* graphEditorDrawToolMgr();
    HGraphEditorSelectTool* graphEditorSelectTool();
public:
    void setGraphEditorView(HGraphEditorView* view);
    //加载
    void loadStation();
    void loadTemplates();
    void loadGraphs();

    bool findGraphByName(const QString&);
    bool isGraphModify();
public:
    //文件
    void New(const QString&);
    bool Open(const QString&,int);
    void Save();
    bool Del(const QString&,int);
    int ImportFile(const QString&);
public:
    void setDrawShape(DrawShape ds);
    DrawShape getDrawShape();
    void setLogicRect(const QRectF& rect);
    QRectF getLogicRect();

    //属性相关操作
    //void initBaseAttribute();
public:
    //增加command
    void addNewCommand(HBaseObj* pObj);
    void addDelCommand(QList<HBaseObj*> pObjs);
    void addPasteCommand(QList<HBaseObj*> pObjs);
    void addMoveCommand(QList<HBaseObj*> pObjs,qreal dx,qreal dy);
    void addRotateCommand(QList<HBaseObj*> pObjs,float angle);
    void addTurnCommand(QList<HBaseObj*> pObjs,bool bdirection);
    void addResizeCommand(QList<HBaseObj*> pObjs,QList<QPolygonF> oldPts,QList<QPolygonF> newPts);

public:
    //刷新view
    void refreshView();
protected:
    HGraphEditorDoc* m_pGraphEditorDoc;
    HGraphEditorScene* m_pGraphEditorScene;
    HGraphEditorView* m_pGraphEditorView;
    QUndoStack* m_pGraphEditorUndoStack;
    HGraphEditorOp* m_pGraphEditorOp;
    HSelectedMgr* m_pSelectedMgr;
    HGraphEditorDrawToolMgr* m_pGraphEditorDrawToolMgr;
    HGraphEditorSelectTool* m_pGraphEditorSelectTool;
private:
    DrawShape m_eDrawShape;
    QRectF m_logicRectF;  //scene的大小
    HGraph* m_pTempGraph; //临时画面文件
    QString m_strGraphFile;
};

#endif // HGRAPHEDITORMGR_H
