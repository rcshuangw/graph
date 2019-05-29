#ifndef HICONPREVIEW_H
#define HICONPREVIEW_H

#include <QDialog>
namespace Ui {
class IconPreview;
}
class HIconEditorMgr;
class HIconEditorPreview : public QDialog
{
    Q_OBJECT

public:
    explicit HIconEditorPreview(HIconEditorMgr* iconMgr,QWidget *parent = 0);
    ~HIconEditorPreview();
public:
    void init();
protected:
    bool eventFilter(QObject *, QEvent *);
public slots:
    void refresh();

    void onDefaultSizeChanged();
    void onRefreshChanged();
    void drawIcon(QPainter* p);
private:
    Ui::IconPreview *ui;
    HIconEditorMgr* pIconMgr;
    QRectF  pixRect;
    QPixmap pixMap;
};

#endif // HICONPREVIEW_H
