#ifndef HICONSCENE_H
#define HICONSCENE_H

#include <QGraphicsScene>
#include <QGraphicsPathItem>
class HIconEditorMgr;
class HIconEditorScene : public QGraphicsScene
{
    Q_OBJECT
public:
    HIconEditorScene(HIconEditorMgr* iconMgr);

public:
	//绘制
    void drawPath(const QList<Path>& pathList);
    void endDraw();

public:
	virtual void drawBackground(QPainter *painter, const QRectF &rect);//绘制背景
	virtual void drawForeground(QPainter *painter, const QRectF &rect);//绘制选择的图元

	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
   
    HIconEditorMgr* m_pIconEditorMgr;
	QList< QGraphicsPathItem*> m_pGraphicsPathItems;
};

#endif // HGRAPHICSSCENE_H
