#ifndef HANALOGUEPAGE_H
#define HANALOGUEPAGE_H

#include <QDialog>
#include "h5basehelpexport.h"
class HBaseObj;
class HIconObj;
class HAnalogue;
class QListWidgetItem;
namespace Ui {
class analoguePage;
}

class H5BASEHELP_EXPORT HAnaloguePage : public QDialog
{
    Q_OBJECT

public:
    explicit HAnaloguePage(QWidget *parent = 0);
    HAnaloguePage(HBaseObj* pObj,QWidget *parent = 0);
    ~HAnaloguePage();

public:
    void setIconComplexObj(HBaseObj*pObj);
    void initDataProperty();
    void initBaseProperty();
    void setAnaAttrib(HAnalogue* pAna);


public slots:
    void onStationCurrentIndexChanged(int index);
    void onIntervalCurrentIndexChanged(int index);
    void onListWidgetItemDoubleClicked(QListWidgetItem*);
    void fontBtn_clicked();
    void textClrBtn_clicked();
    void bgClrBtn_clicked();
    void formatCombo_clicked();
    void onOk();
    void onCancel();
private:
    Ui::analoguePage *ui;
    HIconObj* pCurObj;
    QFont font;
    QString strTextColor;
    QString strBgColor;

    ushort wStation;//厂站
    ushort wPoint;//测点
    ushort wAttrib;//属性
};

#endif // HANALOGUEPAGE_H
