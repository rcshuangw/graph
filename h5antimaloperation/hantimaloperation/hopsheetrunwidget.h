#ifndef HOPSHEETRUNWIDGET_H
#define HOPSHEETRUNWIDGET_H

#include "hframe.h"
//工具栏
//操作票浏览、预演、执行票窗口
class HOpSheetPreviewWnd;
class HPreviewGraphFrame;
class QTabWidget;
class HAntiMalopMgr;
class HOpSheetRunWidget : public HFrame
{
    Q_OBJECT
public:
    HOpSheetRunWidget(HAntiMalopMgr *mgr,HFrame* parent = 0);
    ~HOpSheetRunWidget();

    void createOpSheetRunWidget();
signals:

public slots:

private:
    QTabWidget* m_pRunWndTab;
    HOpSheetPreviewWnd* m_pOpSheetPreviewWnd;
    HPreviewGraphFrame* m_pPreviewGraphFrame;

private:
    HAntiMalopMgr* m_pAntiMalpoMgr;
};

#endif // HOPSHEETRUNWIDGET_H
