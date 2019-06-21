#include "honlineframe.h"
#include "ui_onlineframe.h"

honlineframe::honlineframe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::onlineframe)
{
    ui->setupUi(this);
}

honlineframe::~honlineframe()
{
    delete ui;
}
