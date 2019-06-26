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


HOpSheetBaseWnd::HOpSheetBaseWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpSheetBaseWnd)
{
    ui->setupUi(this);
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

    //工具栏以下部分
    verticalLayout = new QVBoxLayout();
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
    //end 操作票步骤

    verticalLayout->addLayout(firstLineLayout);
    verticalLayout->addLayout(secondLineLayout);
    verticalLayout->addWidget(m_sheetStepTable);

    mainLayout->addLayout(m_toolBarLayout);
    mainLayout->addLayout(verticalLayout);
    mainLayout->setStretch(0, 1);
    mainLayout->setStretch(1, 9);

}
