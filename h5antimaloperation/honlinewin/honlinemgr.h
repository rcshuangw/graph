#ifndef HONLINEMGR_H
#define HONLINEMGR_H
#include <QObject>
class HOnlineScene;
class HOnlineView;
class HOnlineDoc;
class HOnlineOp;
class HGraph;
class HSelectedMgr;
class HOnlineMgr : public QObject
{
    Q_OBJECT
public:
    explicit HOnlineMgr(QObject *parent = nullptr);
public:
    HOnlineScene*  onlineScene();
    HOnlineView*   onlineView();
    HOnlineDoc*    onlineDoc();
    HOnlineOp*     onlineOp();
    HSelectedMgr*  selectedMgr();
public:
    void reset();
    void setGraphEditorView(HOnlineView* view);
    void loadGraphs();
    void openGraph(const QString&,int);
public:

    void setLogicRect(const QRectF& rect);
    QRectF getLogicRect();
    void refreshView();

protected:
    HOnlineDoc* m_pOnlineDoc;
    HOnlineScene* m_pOnlineScene;
    HOnlineView* m_pOnlineView;
    HOnlineOp* m_pOnlineOp;
    HSelectedMgr* m_pSelectedMgr;
private:
    QRectF m_logicRectF;  //scene的大小
    HGraph* m_pTempGraph; //临时画面文件
    QString m_strGraphFile;

    //还有牌的一些定义
};

#endif // HONLINEMGR_H
