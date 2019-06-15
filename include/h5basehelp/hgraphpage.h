#ifndef HGRAPHPAGE_H
#define HGRAPHPAGE_H

#include <QDialog>
#include "h5basehelpexport.h"
namespace Ui {
class graphPage;
}
class HGraph;
class H5BASEHELP_EXPORT HGraphPage : public QDialog
{
    Q_OBJECT

public:
    explicit HGraphPage(QWidget *parent = 0);
    HGraphPage(HGraph* pGraph,QWidget *parent = 0);
    ~HGraphPage();

    //void copyGraphInfo(GRAPHINFO* pGraphInfo);
    void initGraphInfo();

public slots:
    void onBgColorBtn_clicked();
    void onPicPathBtn_clicked();
    void onOk();
    void onCancle();
private:
    Ui::graphPage *ui;
    HGraph *pGraph;
    QString strFillColor;
};

#endif // HGRAPHPAGE_H
