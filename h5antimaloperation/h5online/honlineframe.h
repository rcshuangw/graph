#ifndef HONLINEFRAME1_H
#define HONLINEFRAME1_H

#include <QFrame>

namespace Ui {
class onlineframe;
}

class honlineframe : public QFrame
{
    Q_OBJECT

public:
    explicit honlineframe(QWidget *parent = 0);
    ~honlineframe();

public:
    void initOnlineFrame();
private:
    Ui::onlineframe *ui;
};

#endif // HONLINEFRAME1_H
