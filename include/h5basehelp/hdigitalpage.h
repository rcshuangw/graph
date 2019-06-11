#ifndef HDATAPROPERTYDLG_H
#define HDATAPROPERTYDLG_H

#include <QDialog>
#include "h5basehelpexport.h"
class HBaseObj;
class HIconObj;
class HDigital;
namespace Ui {
class digitalPage;
}

class H5BASEHELP_EXPORT HDigitalPage : public QDialog
{
    Q_OBJECT

public:
    explicit HDigitalPage(QWidget *parent = 0);
    HDigitalPage(HBaseObj* pObj,QWidget *parent = 0);
    ~HDigitalPage();
public:
    void initDataProper();
    void initBaseProper();
    void setDigitalAttr(HDigital* pDigital);

public slots:
    void onStationCurrentIndexChanged(int index);
    void onIntervalCurrentIndexChanged(int index);
    void onPointList_clicked();
    void onOk();
    void onCancel();
private:
    Ui::digitalPage *ui;
    HIconObj* pCurObj;
    ushort wStation;//厂站
    ushort wPoint;//测点
    ushort wAttrib;//属性
};

#endif // HDATAPROPERTYDLG_H
