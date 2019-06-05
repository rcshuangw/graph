#ifndef HGRAPHEDITORVIEW_H
#define HGRAPHEDITORVIEW_H

#include <QGraphicsView>
class HGraphEditorView : public QGraphicsView
{
    Q_OBJECT
public:
    HGraphEditorView(QWidget *parent = Q_NULLPTR);

public:
    //目前只刷新界面
    void refresh();
    bool graphicsEditorViewPortEvent(QEvent* event);
public:
    virtual bool viewportEvent(QEvent* event);

    //virtual void dragEnterEvent(QDragEnterEvent *event);


};

#endif // HGRAPHEDITORVIEW_H
