#ifndef HFRAME_H
#define HFRAME_H
#include <QFrame>
#include <QVBoxLayout>
//每个窗口都至少有1张操作票
class HFrame : public QFrame
{
public:
    HFrame(QWidget* parent = 0);

protected:
    QVBoxLayout *frameLayout;
    QVBoxLayout *centerLayout;
};

#endif // HFRAME_H
