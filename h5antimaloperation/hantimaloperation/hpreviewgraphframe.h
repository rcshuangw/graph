#ifndef HPREVIEWGRAPHFRAME_H
#define HPREVIEWGRAPHFRAME_H
#include "hgraphframe.h"
#include "hfileapi.h"
class HGraphView;
class HAntiMalopMgr;
class HIconObj;
/*
 * HPreviewFrame 包含HPreviewGraphFrame(画面)、HOpSheetPreviewWnd(预演窗口)、HOpSheetBrowserWnd(浏览窗口)、HOpSheetExecuteWnd(执行窗口)
*/
//浏览(编辑)\预演画面窗口
class HPreviewGraphFrame : public HGraphFrame
{
    Q_OBJECT
public:
    HPreviewGraphFrame(quint8 btGraphType);//编辑票/预演票
    ~HPreviewGraphFrame();

public:
    void getOperatorSentence( OPERATORSHEETSTEP* pStep );
    void getOperatorRemark( OPERATORSHEETSTEP* pStep );
    QString makeOpSentence( QString szString, quint16 wOpSTID, quint16 wOpPTID );
    QString makeOpSentence( QString szString, QString szChar, quint16 wOpSTID, quint16 wOpPTID );
    QString makeCheckOpSentence( QString szString );

    void onPreviewCheckOp( const int nCheckType );
    void onManualSetValue( quint8 btValue );
    void onClearManualSet();
    bool isPreviewing();
    int  databaseID();
public:
    virtual bool onMousePressEvent(QObject *obj, QEvent *event);
    virtual bool onContextMenuEvent(QObject *obj, QEvent *event);
public slots:
    //主要是菜单 注意开票操作过程需要connect到左边的操作票框

    //检查操作
    void onPreviewStart();
    void onPreviewStop();
    void onPreviewCancel();

    //预演
    void onPreviewOpen();
    void onPreviewClose();
    void onPreviewCancelLast();

    //检查提示操作
    void onPreviewTishi();//自定义
    void onPreviewCheckSwitchOpen();
    void onPreviewCheckSwitchClose();
    void onPreviewCheckBreakOpen();
    void onPreviewCheckBreakClose();
    void onPreviewCheckEBIOpen();//EBI--压板
    void onPreviewCheckEBIClose();
    void onPreviewCheckLive();//带电
    void onPreviewManualSetOpen();
    void onPreviewManualSetClose();
    void onPreviewManualSetXOpen();//4态分错
    void onPreviewManualSetXClose(); //4态合错
    void onPreviewClearManualSet();

    //主要是点击完成后向左边操作票框发送操作票信息
signals:
    //nType--预演步骤、编辑步骤
    void sendOpeartorStep(int nType,OPERATORSHEETSTEP*& step);
};

#endif // HPREVIEWGRAPHFRAME_H
