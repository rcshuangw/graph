#include "hframe.h"
#include <QScrollBar>
/*
 * HFrame的坐标是主要在QMainWindow里面的中心区域，不包含左边框，上边菜单等状态的位置，最左边就是(0,0)
 * HGraphicsView的逻辑坐标则是包含在
*/
HFrame::HFrame(QWidget* parent, Qt::WindowFlags f):QFrame(parent,f)
{
    m_nHRulerHeight = 25;
    m_nVRulerWidth = 25;
    m_bIsShowRuler = true;
    m_fScale = 0.6;
    m_pView = new QGraphicsView(this);
    m_pView->setBackgroundRole(QPalette::Dark);
    m_pView->setCacheMode(QGraphicsView::CacheBackground);
    m_pView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    m_pView->setRubberBandSelectionMode(Qt::ContainsItemShape);
    m_pView->installEventFilter(this);
    m_pView->scale(m_fScale,m_fScale);
    m_pView->viewport()->setMouseTracking(true);
    m_pView->viewport()->installEventFilter(this);
    connect(m_pView->horizontalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(onHScrollBarChanged(int)));
    connect(m_pView->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(onVScrollBarChanded(int)));
    drawBox();

}

HFrame::~HFrame()
{

}

//设置显示标尺线
void HFrame::setShowRuler(bool bShow)
{
    if(bShow == m_bIsShowRuler)
        return;
    m_bIsShowRuler = bShow;
    if(bShow)
    {
        m_pView->move(m_nVRulerWidth,m_nHRulerHeight);
        m_pView->resize(width()-m_nVRulerWidth,height()-m_nHRulerHeight);
    }
    else
    {
        m_pView->move(0,0);
        m_pView->resize(width(),height());
    }
    update();
}

//获取显示标尺线
bool HFrame::isShowRuler()
{
    return m_bIsShowRuler;
}

//设置水平标尺线高度
void HFrame::setHRulerHeight(int height)
{

}

//获取水平标尺线高度
int  HFrame::hRulerHeight() const
{
    return m_nHRulerHeight;
}

//设置垂直标尺线宽度
void HFrame::setVRulerWidth(int width)
{

}

//获取垂直标尺线宽度
int  HFrame::vRulerWidth() const
{
    return m_nVRulerWidth;
}

//获取当前view
QGraphicsView* HFrame::view()
{
    return m_pView;
}

//获取比例
double HFrame::scale()
{
    return m_fScale;
}

//缩放到
void HFrame::scaleChangedTo(double scale)
{
    double ratio = scale/m_fScale;
    scaleChanged(ratio);

}

//缩放比例
void HFrame::scaleChanged(double ratio)
{
    if(ratio<0 || qFuzzyCompare(ratio,1))
        return;

    m_fScale *= ratio;
    m_pView->scale(ratio,ratio);
    drawHRuler();
    drawVRuler();
    update();
}

//移动中心点到view中间
void HFrame::centerOn(const QPointF& pos)
{

}

//水平滚动条改变
void HFrame::onHScrollBarChanged(int value)
{
    drawHRuler();
    QRect rect(m_nVRulerWidth,0,m_vHRuler.width(),m_vHRuler.height());
    update(rect);
}

//垂直滚动条改变
void HFrame::onVScrollBarChanded(int value)
{
    drawVRuler();
    QRect rect(0,m_nHRulerHeight,m_vVRuler.width(),m_vVRuler.height());
    update(rect);
}

//对象事件过滤
bool HFrame::eventFilter(QObject* obj,QEvent* event)
{
    if(obj == m_pView->viewport())
    {
        switch(((QMouseEvent*)event)->type())
        {
        case QEvent::MouseButtonDblClick:
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseMove:
            mouseMoved(((QMouseEvent*)event)->pos());
            return false;
        case QEvent::Resize:
            drawHRuler();
            drawVRuler();
            update();
            return false;
        }
    }
    return false;
}

//绘制事件过滤
void HFrame::paintEvent(QPaintEvent* painterEvent)
{
    if(m_bIsShowRuler)
    {
        QPainter painter(this);
        painter.setBackground(QBrush(Qt::white));
        if(!m_vHRuler.isNull())
            painter.drawPixmap(m_nVRulerWidth,0,m_vHRuler.width(),m_vHRuler.height(),m_vHRuler);
        if(!m_vVRuler.isNull())
            painter.drawPixmap(0,m_nHRulerHeight,m_vVRuler.width(),m_vVRuler.height(),m_vVRuler);
        if(!m_vBox.isNull())
            painter.drawPixmap(0,0,m_nVRulerWidth,m_nHRulerHeight,m_vBox);
    }

}

//大小改变事件过滤
void HFrame::resizeEvent(QResizeEvent* event)
{
    m_pView->move(m_nVRulerWidth,m_nHRulerHeight);
    int w = width() - m_nVRulerWidth;
    int h = height() - m_nHRulerHeight;
    m_pView->resize(w-1,h-1);
    m_pView->resize(w,h);
}

//绘制水平标尺
void HFrame::drawHRuler()
{
    //m_vHRuler
    QRectF rectF = m_pView->sceneRect();
    QPointF startPoint = m_pView->mapToScene(m_pView->viewport()->rect().topLeft());
    startPoint.setX(qMax(startPoint.x(),rectF.topLeft().x()));
    if(m_pView->horizontalScrollBar()->value() == 0)
        startPoint.setX(rectF.topLeft().x());

    QPointF endPoint = m_pView->mapToScene(m_pView->viewport()->rect().topRight());
    endPoint.setX(qMin(endPoint.x(),rectF.topRight().x()));
    if(m_pView->horizontalScrollBar()->value() ==  m_pView->horizontalScrollBar()->maximum())
        endPoint.setX(rectF.topRight().x());

    QFont f;
    f.setPointSize(8);
    QFontMetrics fontMetrics(f);
    int maxFontWidth = fontMetrics.width(QString::number((int)rectF.topRight().x()));
    int textMargin = 8;
    int devWidth = m_pView->width();
    m_vHRuler = QPixmap(devWidth+maxFontWidth,m_nHRulerHeight);
    m_vHRuler.fill();
    QPainter painter(&m_vHRuler);
    painter.translate(1,1);
    painter.setFont(f);
    painter.save();

    QPen pen(Qt::red);
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawLine(QPoint(0,m_nHRulerHeight),QPoint(m_pView->viewport()->width(),m_nHRulerHeight));
    painter.restore();
    int logSpan = 1;
    int devSpan = logSpan*m_fScale;
    bool flag = true;
    while(devSpan<5){
        if(flag){
            logSpan *= 5;
        }
        else{
            logSpan *= 2;
        }
        devSpan = logSpan*m_fScale;
        flag = !flag;
    }
    QPointF logPoint = startPoint;
    QPoint devPoint = m_pView->mapFromScene(logPoint);
    painter.drawLine(QPoint(devPoint.x(),0),QPoint(devPoint.x(),m_nHRulerHeight));
    painter.drawText(devPoint.x()+1,textMargin,QString::number((int)logPoint.x()));
    logPoint.setX((int)logPoint.x()/logSpan*logSpan+logSpan);
    while(logPoint.x()<endPoint.x()+logSpan){
        devPoint = m_pView->mapFromScene(logPoint);
        if((int)logPoint.x()%(10*logSpan)==0){
            painter.drawLine(QPoint(devPoint.x(),0),QPoint(devPoint.x(),m_nHRulerHeight));
            painter.drawText(devPoint.x()+1,textMargin,QString::number((int)logPoint.x()));
        }
        else if((int)logPoint.x()%(5*logSpan)==0){
            painter.drawLine(QPoint(devPoint.x(),m_nHRulerHeight/2),QPoint(devPoint.x(),m_nHRulerHeight));
            painter.drawText(devPoint.x()+1,textMargin,QString::number((int)logPoint.x()));
        }
        else{
            painter.drawLine(QPoint(devPoint.x(),m_nHRulerHeight*3/4),QPoint(devPoint.x(),m_nHRulerHeight));
        }
        logPoint.setX(logPoint.x()+logSpan);
    }
    devPoint = m_pView->mapFromScene(endPoint);
    painter.drawLine(QPoint(devPoint.x(),0),QPoint(devPoint.x(),m_nHRulerHeight));
    painter.drawText(devPoint.x()+1,textMargin,QString::number((int)endPoint.x()));
}

//绘制垂直标尺
void HFrame::drawVRuler()
{
    //m_vVRuler
    QRectF rectF = m_pView->sceneRect();
    QPointF startPoint = m_pView->mapToScene(m_pView->viewport()->rect().topLeft());
    startPoint.setY(qMax(startPoint.y(),rectF.topLeft().y()));
    if(m_pView->verticalScrollBar()->value() == 0)
        startPoint.setY(rectF.topLeft().y());

    QPointF endPoint = m_pView->mapToScene(m_pView->viewport()->rect().bottomLeft());
    endPoint.setY(qMin(endPoint.y(),rectF.bottomLeft().y()));
    if(m_pView->verticalScrollBar()->value() == m_pView->verticalScrollBar()->maximum())
        endPoint.setY(rectF.bottomLeft().y());

    QFont f;
    f.setPointSize(8);
    QFontMetrics fontMetrics(f);
    int maxFontHeight = fontMetrics.height();
    int textMargin = 1;
    int devWidth = m_pView->height();
    m_vVRuler = QPixmap(m_nVRulerWidth,devWidth+maxFontHeight);
    m_vVRuler.fill();
    QPainter painter(&m_vVRuler);
    painter.translate(1,1);
    painter.setFont(f);
    painter.save();

    QPen pen(Qt::red);
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawLine(QPoint(m_nVRulerWidth,0),QPoint(m_nVRulerWidth,m_pView->viewport()->height()));
    painter.restore();
    int logSpan = 1;
    int devSpan = logSpan*m_fScale;
    bool flag = true;
    while(devSpan<5){
        if(flag){
            logSpan *= 5;
        }
        else{
            logSpan *= 2;
        }
        devSpan = logSpan*m_fScale;
        flag = !flag;
    }
    QPointF logPoint = startPoint;
    QPoint devPoint = m_pView->mapFromScene(logPoint);
    painter.drawLine(QPoint(0,devPoint.y()),QPoint(m_nVRulerWidth,devPoint.y()));
    painter.drawText(textMargin,devPoint.y()+maxFontHeight,QString::number((int)logPoint.y()));
    logPoint.setY((int)logPoint.y()/logSpan*logSpan+logSpan);
    while(logPoint.y()<endPoint.y()){
        devPoint = m_pView->mapFromScene(logPoint);
        if((int)logPoint.y()%(10*logSpan)==0){
            painter.drawLine(QPoint(0,devPoint.y()),QPoint(m_nVRulerWidth,devPoint.y()));
            painter.drawText(textMargin,devPoint.y()+maxFontHeight,QString::number((int)logPoint.y()));
        }
        else if((int)logPoint.y()%(5*logSpan)==0){
            painter.drawLine(QPoint(m_nHRulerHeight/2,devPoint.y()),QPoint(m_nVRulerWidth,devPoint.y()));
            painter.drawText(textMargin,devPoint.y()+maxFontHeight,QString::number((int)logPoint.y()));
        }
        else{
            painter.drawLine(QPoint(m_nHRulerHeight*3/4,devPoint.y()),QPoint(m_nVRulerWidth,devPoint.y()));
            //painter.drawLine(QPoint(devPoint.x(),m_nHRulerHeight*3/4),QPoint(devPoint.x(),m_nHRulerHeight));
        }
        logPoint.setY(logPoint.y()+logSpan);
    }
    devPoint = m_pView->mapFromScene(endPoint);
    painter.drawLine(QPoint(0,devPoint.y()),QPoint(m_nVRulerWidth,devPoint.y()));
    painter.drawText(textMargin,devPoint.y()+maxFontHeight,QString::number((int)endPoint.y()));
}

//绘制左上角
void HFrame::drawBox()
{
    m_vBox = QPixmap(m_nVRulerWidth,m_nHRulerHeight);
    m_vBox.fill();
    QPainter painter(&m_vBox);
    painter.save();
    painter.setPen(Qt::DashLine);
    painter.drawLine(m_nVRulerWidth/2-1,0,m_nVRulerWidth/2-1,m_nHRulerHeight);
    painter.drawLine(0,m_nHRulerHeight/2-1,m_nVRulerWidth,m_nHRulerHeight/2-1);

    painter.setPen(Qt::white);
    painter.drawLine(0,1,0,m_nHRulerHeight+1);
    painter.drawLine(1,0,m_nVRulerWidth,0);

    painter.setPen(Qt::darkGray);
    painter.drawLine(0,m_nHRulerHeight-1,m_nVRulerWidth,m_nHRulerHeight-1);
    painter.drawLine(m_nVRulerWidth-1,0,m_nVRulerWidth-1,m_nHRulerHeight);
    painter.restore();

}

//鼠标位置改变
void HFrame:: mouseMoved(const QPoint& pos)
{
    //pos的位置就是Frame的坐标，也就是pView的坐标系统
    //Scene的坐标就是(500,500)起始点
    m_vCurpos = pos;
    QPointF logPos = m_pView->mapToScene(pos);//转换成Secne的坐标系统
    emit mousePosChanged(pos,logPos);
}
