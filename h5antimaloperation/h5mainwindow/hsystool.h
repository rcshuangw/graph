#ifndef HSYSTOOL_H
#define HSYSTOOL_H
#include "h5mainwindowexport.h"
#include <QFrame>
class QToolButton;
class QPushButton;
class QLabel;
class HClock;
class H5MAINWINDOW_EXPORT HSysTool : public QFrame
{
    Q_OBJECT
public:
    HSysTool(QWidget* parent = 0);
    ~HSysTool();
public:
    void init();
    void createMenu();
public:
    int m_nWidth;
    int m_nHeight;
    int win_width;
    int win_height;
signals:

public slots:
private:
    QToolButton* m_pStartBtn;
    QPushButton* m_pOnlineBtn;
    QPushButton* m_pPreviewBtn;
    QPushButton* m_pTypicalBtn;

    //
    QLabel* m_pMovie;
    HClock* m_pClock;
};

#endif // HSYSTOOL_H
