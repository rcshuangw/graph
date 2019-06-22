#ifndef HONLINEFRAME1_H
#define HONLINEFRAME1_H

#include <QFrame>

namespace Ui {
class onlineframe;
}
class HOnlineView;
class HOnlineMgr;
class HOnlineFrame : public QFrame
{
    Q_OBJECT

public:
    explicit HOnlineFrame(QWidget *parent = 0);
    ~HOnlineFrame();

public:
    void initOnlineFrame();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
private:
    Ui::onlineframe *ui;
    HOnlineView* m_pOnlineView;
    HOnlineMgr* m_pOnlineMgr;
};

#endif // HONLINEFRAME1_H
