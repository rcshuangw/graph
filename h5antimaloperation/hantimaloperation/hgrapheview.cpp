#include "hgraphview.h"
#include <QScrollBar>
HGraphView::HGraphView(QWidget *parent)
    :QGraphicsView (parent)
{
    setAcceptDrops(false);
    //setDragMode(QGraphicsView::ScrollHandDrag);
    setCacheMode(QGraphicsView::CacheBackground);//背景缓存渲染时间
    setRubberBandSelectionMode(Qt::ContainsItemShape);//选择拖拽部分
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    viewport()->setMouseTracking(true);
    m_pAntiMalopMgr = NULL;
}

HGraphView::~HGraphView()
{

}

void HGraphView::setAntiMalopMgr(HAntiMalopMgr* mgr)
{
    m_pAntiMalopMgr = mgr;
}

HAntiMalopMgr* HGraphView::antiMalopMgr()
{
    return m_pAntiMalopMgr;
}

void HGraphView::refresh()
{
    QScrollBar* pBar = horizontalScrollBar();
    int hBar = 0;
    int vBar = 0;
    if(pBar && pBar->isHidden() == false )
    {
        hBar = pBar->height();//水平滚动条的高度
    }
    pBar =verticalScrollBar();
    if(pBar && pBar->isHidden() == false)
    {
        vBar = pBar->width();//垂直滚动条的宽度
    }
    int width = viewport()->width() + hBar;
    int height = viewport()->height() + vBar;
    resize(width-1,height-1);
    resize(width,height);

}


bool HGraphView::eventFilter(QObject *o, QEvent *e)
{
    return false;
}
