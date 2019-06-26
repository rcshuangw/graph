#ifndef HOPSHEETPREVIEWWND_H
#define HOPSHEETPREVIEWWND_H
#include "hopsheetbasewnd.h"

class HOpSheetPreviewWnd : public HOpSheetBaseWnd
{
public:
    HOpSheetPreviewWnd(QWidget *parent = 0);

public:
    void createToolBar();
};

#endif // HOPSHEETPREVIEWWND_H
