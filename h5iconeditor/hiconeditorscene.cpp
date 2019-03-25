#include "hiconeditorscene.h"
#include "hiconeditorframe.h"
#include <cmath>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QMenu>
#include <QMessageBox>
#include <QDebug>
HIconEditorScene::HIconEditorScene(HIconEditorMgr* iconMgr)
    :pIconMgr(iconMgr)
{

}

void HIconScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if(!pIconMgr && !pIconMgr->getIconFrame())
        return;
    QRectF rectLogic = pIconMgr->getIconFrame()->getLogicRect();
    QRectF finalRect = rectLogic;//rect.intersected(rectLogic);
    painter->save();
    QColor bgclr = QColor(pIconMgr->getBackgroundColor());
    painter->fillRect(finalRect,bgclr);


    bool bShowGrid = pIconMgr->getShowGrid();
    if(bShowGrid)
    {
        for(qreal x=finalRect.left();x < finalRect.right()+25;x+=25)
            for(qreal y=finalRect.top();y<finalRect.bottom()+25;y+=25)
                painter->drawPoint(x,y);
    }

    bool bShowCenterLine = pIconMgr->getShowCenterLine();
    if(bShowCenterLine)
    {
        QPointF p1(rectLogic.left()+5,(rectLogic.topLeft().y()+rectLogic.bottomLeft().y())/2);
        QPointF p2(rectLogic.right()-5,(rectLogic.topLeft().y()+rectLogic.bottomLeft().y())/2);
        QPointF p3((rectLogic.topLeft().x()+rectLogic.topRight().x())/2,rectLogic.top()+5);
        QPointF p4((rectLogic.topLeft().x()+rectLogic.topRight().x())/2,rectLogic.bottom()-5);
        QPen pen(Qt::lightGray);
        pen.setWidth(1);
        painter->setPen(pen);
        painter->drawLine(p1,p2);
        painter->drawLine(p3,p4);
    }
    painter->restore();
}


void HIconScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button() != Qt::LeftButton)
        return;

    bLeftShift = true;
    prePoint = mouseEvent->scenePos();
    DRAWSHAPE drawShape = pIconMgr->getDrawShape();
    nSelectMode = pIconMgr->getSelectMode();
    //处于选择状态同时没有选到任何item,就是多选状态
    if(nSelectMode == enumSelect)
    {
        //如果选择到东西 先把选择到的取消掉 就可以了
        QPointF pt = mouseEvent->scenePos();
        if(!getItemAt(pt))
        {
            //drawShape = enumSelection;
            pIconMgr->setDrawShape(enumSelection);
            nSelectMode = enumDraw;;
        }
        else
        {
            nSelectMode = enumSelect;
        }
        if(nSelectMode == enumSelect)
        {
            if(pointInRect(pt) != 0)
                nSelectMode = enumSize;
            else
                nSelectMode = enumMove;
        }
    }
    if(nSelectMode == enumDraw)
    {
        switch (drawShape) {
        case enumLine:
        {
            HBaseObj *pObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(enumLine);
            HLine* pObj1 = (HLine*)pObj;
            pObj1->setHeadPoint(prePoint);
            pObj1->setTailPoint(prePoint);
            line = new HIconLineItem(pObj1);
            line->setItemObj(pObj);
            pIconMgr->getIconTemplate()->getSymbol()->addObj(pObj);

            addItem(line);
            addNewIconCommand(pObj);
        }
            break;
        case enumRectangle:
        {
            HBaseObj *pObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(enumRectangle);
            QRectF tempF = QRectF(prePoint,prePoint).normalized();
            ((HRectangle*)pObj)->setObjRect(tempF);
            rectangle = new HIconRectangleItem(pObj);
            rectangle->setItemObj(pObj);
            pIconMgr->getIconTemplate()->getSymbol()->addObj(pObj);
            addItem(rectangle);
            addNewIconCommand(pObj);
        }
            break;
        case enumEllipse:
        {
            HBaseObj *pObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(enumEllipse);
            QRectF tempF = QRectF(prePoint,prePoint).normalized();
            ((HEllipse*)pObj)->setObjRect(tempF);
            ellipse = new HIconEllipseItem(pObj);
            ellipse->setItemObj(pObj);
            pIconMgr->getIconTemplate()->getSymbol()->addObj(pObj);
            addItem(ellipse);
            addNewIconCommand(pObj);
        }
            break;
        case enumCircle:
        {
            HBaseObj *pObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(enumCircle);
            QRectF tempF = QRectF(prePoint,prePoint).normalized();
            ((HCircle*)pObj)->setObjRect(tempF);
            circle = new HIconCircleItem(pObj);
            circle->setItemObj(pObj);
            pIconMgr->getIconTemplate()->getSymbol()->addObj(pObj);
            addItem(circle);
            addNewIconCommand(pObj);
        }
            break;
        case enumPolygon:
        {
            if(polygon == 0)
            {
                HBaseObj *pObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(enumPolygon);
                ((HPolygon*) pObj)->pylist<<prePoint<<prePoint;
                polygon = new HIconPolygonItem(pObj);
                polygon->setItemObj(pObj);
                pIconMgr->getIconTemplate()->getSymbol()->addObj(pObj);
                addItem(polygon);
                addNewIconCommand(polygon->getItemObj());
            }
            else
            {
                QPolygonF tempF = polygon->polygon();
                tempF.replace(tempF.length()-1,prePoint);
                tempF.append(prePoint);
                polygon->setPolygon(tempF);
                //addNewIconCommand(polygon->getItemObj());
            }
        }
            break;
        case enumPolyline:
        {
            if(polyline == 0)
            {
                HBaseObj *pObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(enumPolyline);
                ((HPolyline*) pObj)->pylist<<prePoint<<prePoint;
                polyline = new HIconPolylineItem(pObj);
                polyline->setItemObj(pObj);
                pIconMgr->getIconTemplate()->getSymbol()->addObj(pObj);
                addItem(polyline);
                addNewIconCommand(polyline->getItemObj());
            }
            else
            {
                QPolygonF tempF = polyline->polygon();
                tempF.replace(tempF.length()-1,prePoint);
                tempF.append(prePoint);
                polyline->setPolygon(tempF);
                //addNewIconCommand(polygon->getItemObj());
            }
        }
            break;
        case enumArc:
        {
            HBaseObj *pObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(enumArc);
            QRectF tempF = QRectF(prePoint,prePoint).normalized();
            ((HArc*)pObj)->setObjRect(tempF);
            arc = new HIconArcItem(pObj);
            arc->setItemObj(pObj);
            pIconMgr->getIconTemplate()->getSymbol()->addObj(pObj);
            addItem(arc);
            addNewIconCommand(pObj);
        }
            break;
        case enumPie:
        {
            HBaseObj *pObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(enumPie);
            QRectF tempF = QRectF(prePoint,prePoint).normalized();
            ((HPie*)pObj)->setObjRect(tempF);
            pie = new HIconPieItem(pObj);
            pie->setItemObj(pObj);
            pIconMgr->getIconTemplate()->getSymbol()->addObj(pObj);
            addItem(pie);
            addNewIconCommand(pObj);
        }
            break;
        case enumText:
        {
            HBaseObj *pObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(enumText);
            QRectF tempF = QRectF(prePoint,prePoint).normalized();
            ((HText*)pObj)->setObjRect(tempF);
            text = new HIconTextItem(pObj);
            text->setItemObj(pObj);
            pIconMgr->getIconTemplate()->getSymbol()->addObj(pObj);
            addItem(text);
            addNewIconCommand(pObj);
        }
            break;
        case enumSelection:
        {
            QRectF tempF = QRectF(prePoint,prePoint).normalized();
            select = new HIconSelectionItem(tempF);
            addItem(select);
            break;
        }
        default:
            break;
        }
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void HIconScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    DRAWSHAPE drawShape = pIconMgr->getDrawShape();
    curPoint = mouseEvent->scenePos();
    if(drawShape == enumLine && line != 0)
    {
        QLineF newline = QLineF(prePoint,curPoint);
        line->setLine(newline);
    }
    else if(drawShape == enumRectangle && rectangle != 0)
    {
        QRectF newRect = QRectF(prePoint,curPoint).normalized();
        rectangle->setRect(newRect);
    }
    else if(drawShape == enumEllipse && ellipse != 0)
    {
        QRectF newRect = QRectF(prePoint,curPoint).normalized();
        ellipse->setRect(newRect);
    }
    else if(drawShape == enumCircle && circle != 0)
    {
        qreal dx = qAbs(curPoint.x() - prePoint.x());
        qreal dy = qAbs(curPoint.y() - prePoint.x());
        QRectF newRect = QRectF(prePoint,QSize(qMin(dx,dy),qMin(dx,dy)));
        circle->setRect(newRect);
    }
    else if(drawShape == enumPolygon && polygon != 0)
    {
        QPolygonF tempF = polygon->polygon();
        tempF.replace(tempF.length()-1,curPoint);
        polygon->setPolygon(tempF);
    }
    else if(drawShape == enumPolyline && polyline != 0)
    {
        QPolygonF tempF = polyline->polygon();
        tempF.replace(tempF.length()-1,curPoint);
        polyline->setPolygon(tempF);
    }
    else if(drawShape == enumArc && arc != 0)
    {
        QRectF newRect = QRectF(prePoint,curPoint).normalized();
        arc->setRect(newRect);
    }
    else if(drawShape == enumPie && pie != 0)
    {
        QRectF newRect = QRectF(prePoint,curPoint).normalized();
        pie->setRect(newRect);
    }
    else if(drawShape == enumText && text != 0)
    {
        QRectF newRect = QRectF(prePoint,curPoint).normalized();
        text->setRect(newRect);
    }
    else if(drawShape == enumSelection && select != 0)
    {
        QRectF newRect = QRectF(prePoint,curPoint).normalized();
        select->setRect(newRect.normalized());
    }
    //判断当前是否处于选择状态
    if(pIconMgr->getSelectMode() == enumSelect)
    {
        setItemCursor(mouseEvent);
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void HIconScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{   
    DRAWSHAPE drawShape = pIconMgr->getDrawShape();
    if(drawShape == enumLine && line != 0)
    {
        line->getItemObj()->setModify(true);
        line->setFlag(QGraphicsItem::ItemIsSelectable,true);
        emit itemInserted(line->type());
        line = 0;
    }
    else if(drawShape == enumRectangle && rectangle != 0)
    {
        rectangle->getItemObj()->setModify(true);
        rectangle->setFlag(QGraphicsItem::ItemIsSelectable,true);
        emit itemInserted(rectangle->type());
        rectangle = 0;        
    }
    else if(drawShape == enumEllipse && ellipse != 0)
    {
        ellipse->getItemObj()->setModify(true);
        ellipse->setFlag(QGraphicsItem::ItemIsSelectable,true);
        emit itemInserted(ellipse->type());
        ellipse = 0;
    }
    else if(drawShape == enumCircle && circle != 0)
    {
        circle->getItemObj()->setModify(true);
        circle->setFlag(QGraphicsItem::ItemIsSelectable,true);
        emit itemInserted(circle->type());
        circle = 0;
    }
    else if(drawShape == enumArc && arc !=0)
    {
        arc->getItemObj()->setModify(true);
        arc->setFlag(QGraphicsItem::ItemIsSelectable,true);
        emit itemInserted(arc->type());
        arc = 0;
    }
    else if(drawShape == enumPie && pie !=0)
    {
        pie->getItemObj()->setModify(true);
        pie->setFlag(QGraphicsItem::ItemIsSelectable,true);
        emit itemInserted(pie->type());
        pie = 0;
    }
    else if(drawShape == enumText && text != 0)
    {
        text->getItemObj()->setModify(true);
        text->setFlag(QGraphicsItem::ItemIsSelectable,true);
        emit itemInserted(text->type());
        text = 0;
    }
    else if(drawShape == enumPolygon && polygon != 0)
    {
        return QGraphicsScene::mouseReleaseEvent(mouseEvent);;
    }
    else if(drawShape == enumPolyline && polyline !=0)
    {
        return QGraphicsScene::mouseReleaseEvent(mouseEvent);;
    }
    else if(drawShape == enumSelection && select != 0)
    {
        //计算选择点
        QRectF rectF = select->rect();
        calcSelectedItem(rectF);//判断item是否选到 选到就是enumSelect否则enumNo
        removeItem(select);
        delete select;
        select = 0;
    }

    //要检查是不是移动过
    if(nSelectMode == enumMove && bLeftShift)
    {
        prepareMoveItem(mouseEvent);
    }
    if(nSelectMode == enumSize && bLeftShift)
    {
        prepareRezieItem(mouseEvent);
    }
    bLeftShift = false;
    pIconMgr->setDrawShape(enumNo);
    pIconMgr->setSelectMode(enumSelect);
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void HIconScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QList<QGraphicsItem*> itemList = selectedItems();
    if(itemList.size()== 1)
    {
        QGraphicsItem* pItem = itemList.first();
        setItemProperty(pItem);
    }
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void HIconScene::keyPressEvent(QKeyEvent *event)
{
    //解决多个item同时移动的问题
    QList<QGraphicsItem*> itemList = selectedItems();
    foreach(QGraphicsItem* item,itemList)
    {
        sendEvent(item,event);
    }
}

void HIconScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    DRAWSHAPE drawShape = pIconMgr->getDrawShape();
    if(drawShape == enumPolygon && polygon != 0)
    {
        if(polygon->polygon().size()<=2)
        {
            HBaseObj* pObj = polygon->getItemObj();
            pObj->setDeleted(true);
            polygon->setVisible(false);
        }
        else
        {
            QPolygonF tempF = polygon->polygon();
            tempF.replace(tempF.size()-1,event->scenePos());
            tempF.append(tempF.at(0));
            polygon->setPolygon(tempF);
        }
        polygon->getItemObj()->setModify(true);
        polygon->setFlag(QGraphicsItem::ItemIsSelectable,true);
        emit itemInserted(polygon->type());
        polygon = 0;
        return;
    }
    else if(drawShape == enumPolyline && polyline != 0)
    {

        if(polyline->polygon().size()<=2)
        {
            HBaseObj* pObj = polyline->getItemObj();
            pObj->setDeleted(true);
            polyline->setVisible(false);
        }
        else
        {
            QPolygonF tempF = polyline->polygon();
            tempF.replace(tempF.size()-1,event->scenePos());

            polyline->setPolygon(tempF);
        }
        polyline->getItemObj()->setModify(true);
        polyline->setFlag(QGraphicsItem::ItemIsSelectable,true);
        emit itemInserted(polyline->type());
        polyline = 0;
        return;
    }

    QList<QGraphicsItem*> itemList = selectedItems();
    if(itemList.size() > 0)
    {
        QMenu menu;
        menu.addAction(QStringLiteral("剪切"),this,SLOT(cutItem()));
        menu.addAction(QStringLiteral("复制"),this,SLOT(copyItem()));
        menu.addAction(QStringLiteral("删除"),this,SLOT(delItem()));
        menu.addAction(QStringLiteral("粘贴"),this,SLOT(pasteItem()));
        menu.addAction(QStringLiteral("属性"),this,SLOT(showProperty()));
        menu.exec(event->screenPos());
    }
    else
    {
        if(!pIconMgr || !pIconMgr->getIconFrame())
            return;

        QFile strFile(pIconMgr->getIconOp()->getClipboardFile());
        if(strFile.exists())
        {
            QMenu menu;
            menu.addAction(QStringLiteral("粘贴"),this,SLOT(pasteItem()));
            menu.exec(event->screenPos());
        }
    }
}

bool HIconScene::getItemAt(const QPointF &pos)
{
    //判断当前点位置是否有item被选择
    QTransform transform;
    QGraphicsItem* item = itemAt(pos,transform);
    if(item)
    {
        return true;
    }
    return false;
}

//如果任一选择对象处于resize状态就返回对应位置,注意每次只能改变一个对象的size
int HIconScene::pointInRect(QPointF& pointF)
{
    QList<QGraphicsItem*> itemList = selectedItems();
    foreach(QGraphicsItem*item,itemList)
    {
        int location = ((HIconGraphicsItem*)item)->pointInRect(pointF);
        if(location != 0)
        {
            oldPolygonF.clear();
            getIconGraphicsItemPointList((HIconGraphicsItem*)item,oldPolygonF);
            return location;
        }
    }
    return 0;
}

void HIconScene::setItemProperty(QGraphicsItem* item)
{
    if(!item) return;
    HIconGraphicsItem* pItem = qgraphicsitem_cast<HIconGraphicsItem*>(item);
    HBaseObj* pObj = pItem->getItemObj();
    HPropertyDlg dlg(pObj);
    dlg.exec();

}

void HIconScene::setItemCursor(QGraphicsSceneMouseEvent *mouseEvent)
{
    QList<QGraphicsItem*> itemList = selectedItems();
    //获取所在item，只要item选择到即可
    //这个地方要改，只要获取当前选择那个，如果是多个选择则返回
    QPointF pointF = mouseEvent->scenePos();
    if(itemList.count()>=2 || itemList.count() == 0) return;
    QGraphicsItem* item = itemList.at(0);
    if(!item) return;
    HIconGraphicsItem* pItem = qgraphicsitem_cast<HIconGraphicsItem*>(item);
    int location = pItem->pointInRect(pointF);
    pItem->setItemCursor(location);
}

void HIconScene::setItemVisible(int nPatternId)
{
    bool bVisible = false;
    foreach (QGraphicsItem *item, items())
    {
        bVisible = false;
        HIconGraphicsItem* pItem = qgraphicsitem_cast<HIconGraphicsItem*>(item);
        if(pItem->getItemObj()->contains(nPatternId) && false == pItem->getItemObj()->isDeleted() )
            bVisible = true;
        item->setVisible(bVisible);
     }
}

//增加图元的显示方案
void HIconScene::refreshItemByPatternId(int nPatternId)
{
    if(!pIconMgr && !pIconMgr->getIconTemplate() &&!pIconMgr->getIconTemplate()->getSymbol())
        return;
    HIconSymbol *pSymbol = pIconMgr->getIconTemplate()->getSymbol();
    HIconShowPattern* pattern = pSymbol->findPatternById(nPatternId);
    if(!pattern) return;
    foreach(HBaseObj* pObj,pattern->pObjList)
    {
        if(!pObj) continue;
        addItemByIconObj(pObj);
    }
}


//删除图元的显示方案
void HIconScene::clearItemByPatternId(int nPatternId)
{
    if(!pIconMgr || !pIconMgr->getIconTemplate() || !pIconMgr->getIconTemplate()->getSymbol())
        return;
    foreach (QGraphicsItem *item, items())
    {
        HIconGraphicsItem* pItem = qgraphicsitem_cast<HIconGraphicsItem*>(item);
        if(!pItem) continue;
        HBaseObj *pObj = pItem->getItemObj();
        if(pObj->contains(nPatternId))
        {
            pIconMgr->getIconTemplate()->getSymbol()->takeObj(pObj);
            removeItem(item);
            delete item;
        }
     }
}

void HIconScene::cutItem()
{
    if(!pIconMgr || !pIconMgr->getIconOp())
        return;
    pIconMgr->getIconOp()->cut();
}

void HIconScene::copyItem()
{
    if(!pIconMgr || !pIconMgr->getIconOp())
        return;
     pIconMgr->getIconOp()->copy();
}

void HIconScene::pasteItem()
{
    if(!pIconMgr || !pIconMgr->getIconOp())
        return;
    pIconMgr->getIconOp()->paste();
}

//右键删除已经选择的图元元素
void HIconScene::delItem()
{
    if(!pIconMgr || !pIconMgr->getIconFrame())
        return;
    if(QMessageBox::Cancel == QMessageBox::information(NULL,QStringLiteral("警告"),QStringLiteral("确认删除该图符吗？"),QMessageBox::Ok|QMessageBox::Cancel))
        return;
    pIconMgr->getIconOp()->del();
}

void HIconScene::showProperty()
{
    QList<QGraphicsItem*> itemList = selectedItems();
    if(itemList.size()== 1)
    {
        QGraphicsItem* pItem = itemList.first();
        setItemProperty(pItem);
    }
}

void HIconScene::calcSelectedItem(const QRectF &rectF)
{
    QPainterPath path;
    path.addRect(rectF);
    QTransform transform;
    setSelectionArea(path,transform);
}

HIconGraphicsItem* HIconScene::addItemByIconObj(HBaseObj* pObj)
{
    if(!pObj) return NULL;
    quint8 drawShape = pObj->getShapeType();
    HIconGraphicsItem* item = NULL;
    if(drawShape == enumLine)
    {
        HLine* pObj1 = (HLine*)pObj;
        line = new HIconLineItem(pObj1);
        line->setItemObj(pObj1);
        line->setFlag(QGraphicsItem::ItemIsSelectable,true);
        addItem(line);
    }
    else if(drawShape == enumRectangle)
    {
        HRectangle* pObj1 = (HRectangle*)pObj;
        rectangle = new HIconRectangleItem(pObj1);
        rectangle->setItemObj(pObj1);
        rectangle->setFlag(QGraphicsItem::ItemIsSelectable,true);
        addItem(rectangle);
    }
    else if(drawShape == enumEllipse)
    {
        HEllipse* pObj1 = (HEllipse*)pObj;
        ellipse = new HIconEllipseItem(pObj1);
        ellipse->setItemObj(pObj1);
        ellipse->setFlag(QGraphicsItem::ItemIsSelectable,true);
        addItem(ellipse);
    }
    else if(drawShape == enumCircle)
    {
        HCircle* pObj1 = (HCircle*)pObj;
        circle = new HIconCircleItem(pObj1);
        circle->setItemObj(pObj1);
        circle->setFlag(QGraphicsItem::ItemIsSelectable,true);
        addItem(circle);
    }
    else if(drawShape == enumPolygon)
    {
        HPolygon* pObj1 = (HPolygon*)pObj;
        polygon = new HIconPolygonItem(pObj1);
        polygon->setItemObj(pObj1);
        polygon->setFlag(QGraphicsItem::ItemIsSelectable,true);
        addItem(polygon);
    }
    else if(drawShape == enumPolyline)
    {
        HPolyline* pObj1 = (HPolyline*)pObj;
        polyline = new HIconPolylineItem(pObj1);
        polyline->setItemObj(pObj1);
        polyline->setFlag(QGraphicsItem::ItemIsSelectable,true);
        addItem(polyline);
    }
    else if(drawShape == enumArc)
    {
        HArc* pObj1 = (HArc*)pObj;
        arc = new HIconArcItem(pObj1);
        arc->setItemObj(pObj1);
        arc->setFlag(QGraphicsItem::ItemIsSelectable,true);
        addItem(arc);
    }
    else if(drawShape == enumPie)
    {
        HPie* pObj1 = (HPie*)pObj;
        pie = new HIconPieItem(pObj1);
        pie->setItemObj(pObj1);
        pie->setFlag(QGraphicsItem::ItemIsSelectable,true);
        addItem(pie);
    }
    else if(drawShape == enumText)
    {
        HText* pObj1 = (HText*)pObj;
        text = new HIconTextItem(pObj1);
        text->setItemObj(pObj1);
        text->setFlag(QGraphicsItem::ItemIsSelectable,true);
        addItem(text);
    }

    if(drawShape == enumLine && line != 0)
    {
        item = line;
        line = 0;
    }
    else if(drawShape == enumRectangle && rectangle != 0)
    {
        item = rectangle;
        rectangle = 0;
    }
    else if(drawShape == enumEllipse && ellipse != 0)
    {
        item = ellipse;
        ellipse = 0;
    }
    else if(drawShape == enumCircle && circle != 0)
    {
        item = circle;
        circle = 0;
    }
    else if(drawShape == enumPolyline && polyline !=0 )
    {
        item = polyline;
        polyline = 0;
    }
    else if(drawShape == enumPolygon && polygon !=0)
    {
        item = polygon;
        polygon = 0;
    }
    else if(drawShape == enumArc && arc !=0)
    {
        item = arc;
        arc = 0;
    }
    else if(drawShape == enumPie && pie !=0)
    {
        item = pie;
        pie = 0;
    }
    else if(drawShape == enumText && text != 0)
    {
        item = text;
        text = 0;
    }

    return item;
}

void HIconScene::addNewIconCommand(HBaseObj *pObj)
{
    if(!pIconMgr || !pIconMgr->getIconUndoStack())
        return;
    HNewIconCommand* newIconCommand = new HNewIconCommand(pIconMgr,pObj);
    pIconMgr->getIconUndoStack()->push(newIconCommand);
}

void HIconScene::prepareMoveItem(QGraphicsSceneMouseEvent *mouseEvent)
{
    QList<QGraphicsItem*> selectedItemList = selectedItems();
    if(selectedItemList.count() == 0) return;
    QPointF pt = mouseEvent->scenePos();
    if(fabs(pt.x()-prePoint.x()) < 0.0001 && fabs(pt.y() - prePoint.y()) < 0.0001)
        return;
    qreal dx = pt.x() - prePoint.x();
    qreal dy = pt.y() - prePoint.y();
    QList<HBaseObj*> objList;
    for(int i = 0; i < selectedItemList.count();i++)
    {
        HIconGraphicsItem* item = (HIconGraphicsItem*)selectedItemList.at(i);
        if(!item) continue;
        objList.append(item->getItemObj());
    }
    HMoveIconCommand* moveIconCommand = new HMoveIconCommand(pIconMgr,objList,dx,dy);
    pIconMgr->getIconUndoStack()->push(moveIconCommand);
}

void HIconScene::prepareRezieItem(QGraphicsSceneMouseEvent *mouseEvent)
{
    QList<QGraphicsItem*> itemList = selectedItems();
    //获取所在item，只要item选择到即可
    QTransform transform;
    QPointF pt = mouseEvent->scenePos();
    QGraphicsItem* item = itemAt(pt,transform);
    if(itemList.indexOf(item) == -1)
        return;
    if(fabs(pt.x()-prePoint.x()) < 0.0001 && fabs(pt.y() - prePoint.y()) < 0.0001)
        return;
    newPolygonF.clear();
    getIconGraphicsItemPointList((HIconGraphicsItem*)item,newPolygonF);
    HIconGraphicsItem* iconItem = (HIconGraphicsItem*)item;
    QList<HBaseObj*> objList;
    objList.append(iconItem->getItemObj());
    //每次只能改变一个
    HResizeIconCommand* resizeIconCommand = new HResizeIconCommand(pIconMgr,objList,oldPolygonF,newPolygonF);
    pIconMgr->getIconUndoStack()->push(resizeIconCommand);

}

void HIconScene::getIconGraphicsItemPointList(HIconGraphicsItem* item,QList<QPolygonF>& pfList)
{
    if(item == NULL) return;
    pfList.clear();
    int nDrawShape = item->type();
    QPolygonF pf;
    pf.clear();
    if(nDrawShape == enumLine)
    {
        HIconLineItem* pItem = (HIconLineItem*)item;
        QLineF lineF = pItem->line();
        pf<<lineF.p1()<<lineF.p2();
    }
    else if(nDrawShape == enumRectangle)
    {
        HIconRectangleItem* pItem = (HIconRectangleItem*)item;
        QRectF rectF = pItem->rect();
        pf<<rectF.topLeft()<<rectF.topRight()<<rectF.bottomLeft()<<rectF.bottomRight();
    }
    else if(nDrawShape == enumEllipse)
    {
        HIconEllipseItem* pItem = (HIconEllipseItem*)item;
        QRectF rectF = pItem->rect();
        pf<<rectF.topLeft()<<rectF.topRight()<<rectF.bottomLeft()<<rectF.bottomRight();
    }
    else if(nDrawShape == enumCircle)
    {
        HIconCircleItem* pItem = (HIconCircleItem*)item;
        QRectF rectF = pItem->rect();
        pf<<rectF.topLeft()<<rectF.topRight()<<rectF.bottomLeft()<<rectF.bottomRight();
    }
    else if(nDrawShape == enumPolyline)
    {
        HIconPolylineItem* pItem = (HIconPolylineItem*)item;
        pf = pItem->polygon();
    }
    else if(nDrawShape == enumPolygon)
    {
        HIconPolygonItem* pItem = (HIconPolygonItem*)item;
        pf = pItem->polygon();
    }
    else if(nDrawShape == enumArc)
    {
        HIconArcItem* pItem = (HIconArcItem*)item;
        QRectF rectF = pItem->rect();
        pf<<rectF.topLeft()<<rectF.topRight()<<rectF.bottomLeft()<<rectF.bottomRight();
    }
    else if(nDrawShape == enumPie)
    {
        HIconPieItem* pItem = (HIconPieItem*)item;
        QRectF rectF = pItem->rect();
        pf<<rectF.topLeft()<<rectF.topRight()<<rectF.bottomLeft()<<rectF.bottomRight();
    }
    else if(nDrawShape == enumText)
    {
        HIconTextItem* pItem = (HIconTextItem*)item;
        QRectF rectF = pItem->rect();
        pf<<rectF.topLeft()<<rectF.topRight()<<rectF.bottomLeft()<<rectF.bottomRight();
    }
    pfList.append(pf);
}

