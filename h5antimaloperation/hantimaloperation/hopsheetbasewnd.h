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
class QLabel;
class QToolBar;
class HOpSheetBaseWnd : public QWidget
{
    Q_OBJECT

public:
    explicit HOpSheetBaseWnd(quint8 btOpenType,QWidget *parent = 0);
    ~HOpSheetBaseWnd();

public:
    void createOpSheetBaseWnd();

    //操作票相关操作
    void newOpSheet();
    void openOpSheet(quint8 btOpenType);
    void loadOpSheet(quint16 wOpSheetID);
    void saveOpSheet();
    void saveAsTemplate();

protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void onMousePressEvent(QMouseEvent* event);//左键
    void onMouseDoubleClickEvent(QMouseEvent *event);//双击
    void onContextMenuEvent(QMouseEvent* event);//右键
    void procPreviewContextMenu(QMouseEvent* event);//右键
    void procBrowserContextMenu(QMouseEvent* event);

public slots:

public:
    QHBoxLayout *m_toolBarLayout;
    QLabel* m_sheetLabel;
    QLineEdit *m_sheetNoLineEdit;
    QLineEdit *m_sheetTitleLineEdit;
    QLineEdit *m_sheetTaskLineEdit;
    QPushButton *m_sheetNoBtn;
    QTableWidget *m_sheetStepTable;
    QToolBar* m_toolBar;

    QAction* m_fileOpenAct;
    QAction* m_fileCloseAct;
    QAction* m_filePrintAct;
    QAction* m_toExecuteAct;
    QAction* m_fileAbolishAct;
    QAction* m_fileSaveAct;
protected:
    quint8 m_btOpenType;      //操作框类型
    quint8 m_btOpSheetType;   //操作票类型
private:
    Ui::OpSheetBaseWnd *ui;
};

#endif // HOPSHEETBASEWND_H
