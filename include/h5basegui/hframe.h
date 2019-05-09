#ifndef HFRAME_H
#define HFRAME_H
#include "h5iconguiexport.h"
#include <QFrame>
#include <QGraphicsView>
#include <QPaintEvent>
#include <QEvent>
#include <QPixmap>
//该类主要是图形编辑的基类

class QGraphicsView;

class H5BASEGUI_EXPORT HFrame : public QFrame
{
    Q_OBJECT
public:
    HFrame(QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~HFrame();

    //设置显示标尺线
    void setShowRuler(bool bShow);

    //获取显示标尺线
    bool isShowRuler();

    //设置水平标尺线高度
    void setHRulerHeight(int height);

    //获取水平标尺线高度
    int  hRulerHeight() const;

    //设置垂直标尺线宽度
    void setVRulerWidth(int width);

    //获取垂直标尺线宽度
    int  vRulerWidth() const;

    //获取当前view
    QGraphicsView* view();

    //获取比例
    double scale();

    //缩放到
    void scaleChangedTo(double scale);

    //缩放比例
    void scaleChanged(double ratio);

    //移动中心点到view中间
    void centerOn(const QPointF& pos);

public slots:
    //水平滚动条改变
    virtual void onHScrollBarChanged(int value);

    //垂直滚动条改变
    virtual void onVScrollBarChanded(int value);

protected:
    //对象事件过滤
    virtual bool eventFilter(QObject* obj,QEvent* event);

    //绘制事件过滤
    virtual void paintEvent(QPaintEvent* painterEvent);

    //大小改变事件过滤
    virtual void resizeEvent(QResizeEvent* event);

    //绘制水平标尺
    void drawHRuler();

    //绘制垂直标尺
    void drawVRuler();

    //绘制左上角
    void drawBox();

    //鼠标位置改变
    void mouseMoved(const QPoint& pos);

signals:
    //鼠标位置改变
    void mousePosChanged(const QPoint&,const QPointF&);

    //画面比例改变
    void scaleHasChanged(double scale);
protected:
    //视图类
    QGraphicsView* m_pView;

    //比例
    double m_fScale;

    //水平标尺的高度
    int m_nHRulerHeight;

    //垂直标尺的宽度
    int m_nVRulerWidth;

    //是否显示标尺
    bool m_bIsShowRuler;

    //水平标尺的小图标
    QPixmap m_vHRuler;

    //垂直标尺的小图标
    QPixmap m_vVRuler;

    //左上角的小图标
    QPixmap m_vBox;

    //是否绘制鼠标指示线
    bool m_bIsDrawIndicator;

    //鼠标指示线位置
    QPoint m_vCurpos;

};

#endif // HFRAME_H
