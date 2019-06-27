#ifndef HOPSHEETPREVIEWWND_H
#define HOPSHEETPREVIEWWND_H
#include "hopsheetbasewnd.h"
class QWidget;
class QObject;
class QEvent;
class QMouseEvent;
class HOpSheetBaseWnd;
class HOpSheetPreviewWnd : public HOpSheetBaseWnd
{
public:
    HOpSheetPreviewWnd(QWidget *parent = 0);

 public:
    void createActions();

public slots:
    void onOpeartorStepChanged(int nType,OPERATORSHEETSTEP*& step);

protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void procContextMenu(QMouseEvent* event);

};

#endif // HOPSHEETPREVIEWWND_H
