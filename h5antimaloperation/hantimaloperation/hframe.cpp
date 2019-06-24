#include "hframe.h"
HFrame::HFrame(QWidget* parent):QFrame(parent)
{
    centerLayout = new QVBoxLayout();
    setLayout(centerLayout);
}
