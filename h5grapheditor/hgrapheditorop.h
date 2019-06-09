#ifndef HGRAPHEDITOROP_H
#define HGRAPHEDITOROP_H

#include <QObject>
#include "hiconapi.h"
#include "hdrawmanager.h"
#define ICON_DRAW_TOOL   0x01
#define ICON_SELECT_TOOL 0x02
class HGraphEditorMgr;
class HBaseObj;
class HGraphEditorOp : public QObject
{
    Q_OBJECT
public:
    HGraphEditorOp(HGraphEditorMgr* mgr);
    ~HGraphEditorOp();
public:
    void setGraphicsView();

public:
    void cut();
    void copy();
    void paste();
    void del();
    QString getClipboardFile();
    bool isClipboardAvailable();

    void bringToTop();
    void bringToBottom();

    void groupObj();
    void ungroupObj();

public:
    //颜色部分
    QColor getPenColor();
    QColor getFillColor();
    void setPicture();

    //线型填充等部分
    void setLineStyle(int style);
    void setLineWidth(int width);
    void setFillBrush(int brushStyle);

    //字体
    void setFontFamily(const QString& family);
    void setFontSize(int size);
    void setBold(bool b);
    void setItalic(bool b);
    void setUnderline(bool b);
public:
    void alignLeft();
    void alignRight();
    void alignHCenter();
    void alignTop();
    void alignBottom();
    void alignVCenter();
    void alignAlgorithm();
public: //等宽
    void sizeEqualWidth();
    void sizeEqualHeight();
    void sizeEqualComplete();
    void sizeHEqualSpace();
    void sizeVEqualSpace();
    bool getbenchMarkSize(QPointF& pt);
    void equalAlgorithm();
public: //旋转
    void flipLeft90();
    void flipRight90();
    void flipHorizon();
    void flipVertical();
    void flipAlgorithm();
public:
    void zoomIn();
    void zoomOut();
    void zoom();
    void zoomSame();
    void setupMatrix();
public:
    int toolType() {return m_nToolType;}
    void drawTool(DrawShape drawShape);
    void selectTool(SelectMode select);
    void switchSelectTool();

public:
    void createIconObj(const QString&,const QString&,int shape,QPointF,QList<H5GraphicsItem*> &items);
    void ObjCreated(HBaseObj* pObj,bool bPaste = false);
    void addIconObj(HBaseObj* pObj,bool bPaste = false);

    void objSelectChanged(HBaseObj *obj, bool isSelected);
    void onUpdateStatus(const QString& text);
    void setObjAttribute();
public slots:
    void onRefreshSelect(const QRectF&);
    void onDrawPath(const QList<Path>& path);
    void onEndDraw();
signals:
    void selectChanged();
    void setSelectTool();
    void updateStatus(const QString& text);
    void updateBaseAction();
    void attributeChanged();
private:
    HGraphEditorMgr* m_pGraphEditorMgr;
    Qt::Alignment m_Alignment;
    IconSize m_Equalway;
    IconFlip m_Flipway;
    qreal m_scale;
    int m_nToolType;

};

#endif // HGRAPHEDITOROP_H
