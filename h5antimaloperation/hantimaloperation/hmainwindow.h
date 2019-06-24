#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "h5mainwindowexport.h"
#include <QWidget>
#include "hsystool.h"
#include "hclient.h"
class H5MAINWINDOW_EXPORT MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    HSysTool* m_pSysTool;
    HClient* m_pClient;
private:
    //Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
