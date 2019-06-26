#ifndef HOPSHEETBASEWND_H
#define HOPSHEETBASEWND_H
#include <QWidget>
//每个工具栏都在子窗口创建
namespace Ui {
class OpSheetBaseWnd;
}
class QHBoxLayout;
class QLineEdit;
class QPushButton;
class QTableWidget;
class HOpSheetBaseWnd : public QWidget
{
    Q_OBJECT

public:
    explicit HOpSheetBaseWnd(QWidget *parent = 0);
    ~HOpSheetBaseWnd();

public:
    void createOpSheetBaseWnd();

public:
    QHBoxLayout *m_toolBarLayout;
    QLineEdit *m_sheetNoLineEdit;
    QLineEdit *m_sheetTitleLineEdit;
    QLineEdit *m_sheetTaskLineEdit;
    QPushButton *m_sheetNoBtn;
    QTableWidget *m_sheetStepTable;
private:
    Ui::OpSheetBaseWnd *ui;
};

#endif // HOPSHEETBASEWND_H
