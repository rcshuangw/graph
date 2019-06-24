#ifndef HONLINEMGR_H
#define HONLINEMGR_H
#include <QObject>
#include <QRectF>
class HAntiMalopDoc;
class HGraphFrame;
class HPreviewGraphFrame;
class HEditGraphFrame;
class HGraph;
class HAntiMalopMgr : public QObject
{
    Q_OBJECT
public:
    explicit HAntiMalopMgr(QObject *parent = nullptr);
public:
    HGraphFrame*        graphFrame();
    HPreviewGraphFrame* previewGraphFrame();
    HEditGraphFrame*    editGraphFrame();
    HAntiMalopDoc*    antiMalopDoc();
public:
    void reset();
    //void setGraphEditorView(HOnlineView* view);
    void loadGraphs();
    bool openGraph(const QString&,int);
public:

    void setLogicRect(const QRectF& rect);
    QRectF getLogicRect();
    void refreshView();

protected:
    HGraphFrame* m_pGraphFrame;
    HPreviewGraphFrame* m_pPreviewGraphFrame;
    HEditGraphFrame* m_pEditGraphFrame;
    HAntiMalopDoc* m_pAntiMalopDoc;
private:
    QRectF m_logicRectF;  //scene的大小
    HGraph* m_pTempGraph; //临时画面文件
    QString m_strGraphFile;

    //还有牌的一些定义
};

#endif // HONLINEMGR_H
