#include "hopsheetbasewnd.h"
#include "ui_opsheetbasewnd.h"

#include <QtWidgets/QWidget>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QToolBar>
#include <QMouseEvent>
#include <QMenu>
HOpSheetBaseWnd::HOpSheetBaseWnd(quint8 btOpenType,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpSheetBaseWnd)
{
    //ui->setupUi(this);
    createOpSheetBaseWnd();
}

HOpSheetBaseWnd::~HOpSheetBaseWnd()
{
    delete ui;
}

void HOpSheetBaseWnd::createOpSheetBaseWnd()
{
    QVBoxLayout *mainLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *firstLineLayout;
    QHBoxLayout *sheetNoLayout;
    QHBoxLayout *sheetTitleLayout;
    QHBoxLayout *secondLineLayout;
    QHBoxLayout *sheetTaskLayout;
    QLabel *sheetTitleLabel;
    QLabel *sheetNoLabel;
    QLabel *sheetTaskLabel;

    //窗口属性设置
    if (this->objectName().isEmpty())
        this->setObjectName("OpSheetBaseWnd");
    this->resize(748, 502);
    QFont font;
    font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));//宋体
    font.setPointSize(10);
    this->setFont(font);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(4);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(2, 2, 2, 2);

     //工具栏layout
    m_toolBarLayout = new QHBoxLayout();
    m_toolBar = new QToolBar(this);
    m_toolBar->setIconSize(QSize(26,21));
    m_toolBarLayout->addWidget(m_toolBar);

    //工具栏以下部分
    verticalLayout = new QVBoxLayout();
    //QLabel 操作票说明
    m_sheetLabel = new QLabel(this);
    m_sheetLabel->setText(QStringLiteral("正在......"));
    //m_sheetLabel->setFrameShape(QFrame::Box);
    m_sheetLabel->setMinimumSize(QSize(0, 28));
    QFont font1 = font;
    font1.setPointSize(15);
    font1.setBold(true);
    m_sheetLabel->setFont(font1);

    //以下第一行
    firstLineLayout = new QHBoxLayout();

    //票号
    sheetNoLayout = new QHBoxLayout();
    sheetNoLabel = new QLabel(this);
    sheetNoLabel->setText(QStringLiteral("票号"));
    sheetNoLabel->setFont(font);
    sheetNoLayout->addWidget(sheetNoLabel);
    m_sheetNoLineEdit = new QLineEdit(this);
    m_sheetNoLineEdit->setMinimumSize(QSize(0, 23));
    sheetNoLayout->addWidget(m_sheetNoLineEdit);
    //end 票号

    //标题
    sheetTitleLayout = new QHBoxLayout();
    sheetTitleLabel = new QLabel(this);
    sheetTitleLabel->setText(QStringLiteral("标题"));
    sheetTitleLayout->addWidget(sheetTitleLabel);
    m_sheetTitleLineEdit = new QLineEdit(this);
    m_sheetTitleLineEdit->setMinimumSize(QSize(0, 23));
    sheetTitleLayout->addWidget(m_sheetTitleLineEdit);
    //end 标题

    firstLineLayout->addLayout(sheetNoLayout);
    firstLineLayout->addLayout(sheetTitleLayout);
    firstLineLayout->setStretch(0, 2);
    firstLineLayout->setStretch(1, 8);
    //以上第一行

    //以下第二行
    secondLineLayout = new QHBoxLayout();
    //以下操作任务
    sheetTaskLayout = new QHBoxLayout();
    sheetTaskLabel = new QLabel(this);
    sheetTaskLabel->setText(QStringLiteral("操作任务"));
    sheetTaskLayout->addWidget(sheetTaskLabel);
    m_sheetTaskLineEdit = new QLineEdit(this);
    m_sheetTaskLineEdit->setMinimumSize(QSize(0, 23));
    sheetTaskLayout->addWidget(m_sheetTaskLineEdit);

    //设置按钮
    m_sheetNoBtn = new QPushButton(this);
    m_sheetNoBtn->setText(QStringLiteral("设置"));
    m_sheetNoBtn->setMinimumSize(QSize(0, 23));

    secondLineLayout->addLayout(sheetTaskLayout);
    secondLineLayout->addWidget(m_sheetNoBtn);
    //以上第二行

    //操作票步骤Table
    m_sheetStepTable = new QTableWidget(this);
    m_sheetStepTable->setColumnCount(4);
    QTableWidgetItem *item = new QTableWidgetItem();
    m_sheetStepTable->setHorizontalHeaderItem(0, item);
    item->setText(QStringLiteral("步骤"));
    QTableWidgetItem *item1 = new QTableWidgetItem();
    m_sheetStepTable->setHorizontalHeaderItem(1, item1);
    item1->setText(QStringLiteral("操作内容"));
    QTableWidgetItem *item2 = new QTableWidgetItem();
    m_sheetStepTable->setHorizontalHeaderItem(2, item2);
    item2->setText(QStringLiteral("操作时间"));
    QTableWidgetItem *item3 = new QTableWidgetItem();
    m_sheetStepTable->setHorizontalHeaderItem(3, item3);
    item3->setText(QStringLiteral("备注"));


    m_sheetStepTable->setColumnWidth(0,60);
   /* m_sheetStepTable->setColumnWidth(1,600);*/
    m_sheetStepTable->setColumnWidth(2,150);
    m_sheetStepTable->setColumnWidth(3,100);
    m_sheetStepTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    m_sheetStepTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    m_sheetStepTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    m_sheetStepTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
   // m_sheetStepTable->horizontalHeader()->setStretchLastSection(true);//
    m_sheetStepTable->setObjectName(QStringLiteral("sheetStepTable"));
    //end 操作票步骤
    verticalLayout->addWidget(m_sheetLabel);
    verticalLayout->addLayout(firstLineLayout);
    verticalLayout->addLayout(secondLineLayout);
    verticalLayout->addWidget(m_sheetStepTable);

    mainLayout->addLayout(m_toolBarLayout);
    mainLayout->addLayout(verticalLayout);
    mainLayout->setStretch(0, 2);
    mainLayout->setStretch(1, 8);
}

bool HOpSheetBaseWnd::eventFilter(QObject *watched, QEvent *event)
{
    //创建右键菜单

    if(watched == m_sheetStepTable)
    {
        if(event->type() == QEvent::ContextMenu)
        {
            QMouseEvent* e = static_cast<QMouseEvent*>(event);
            if(m_btOpenType == 0)
                procPreviewContextMenu(e);
        }
    }
    return false;
}

void HOpSheetBaseWnd::procPreviewContextMenu(QMouseEvent *event)
{
    QPointF pt = event->pos();

    QMenu* menu = new QMenu;
    QAction* editStepAct = new QAction(QStringLiteral("预演增加一步"));
    QAction* delStepAct = new QAction(QStringLiteral("预演删除一步"));
    menu->addAction(editStepAct);
    menu->addAction(delStepAct);
    menu->popup(pt);
}

//处理浏览框的右键
void HOpSheetBaseWnd::procBrowserContextMenu(QMouseEvent *event)
{

}

