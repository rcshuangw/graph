#ifndef HICONOP_H
#define HICONOP_H
#include "hiconapi.h"
#include "hbaseobj.h"
#include "hiconeditormgr.h"
#include "hdrawmanager.h"

#define ICON_DRAW_TOOL  0x01
#define ICON_SELECT_TOOL 0x02
class HIconEditorMgr;
class HIconEditorOp : public QObject
{
	Q_OBJECT
public:
    HIconEditorOp(HIconEditorMgr* mgr);
    ~HIconEditorOp();
public:
    //画面
    void New(const QString& strTemplateName,const QString& strCatalogName,const int& nCatalogType);
    void Open(const QString &strTemplateName, int nTemplateType, const QString &strUuid);

    void fitWidth();

    void fitHeight();

    void cut();

    void copy();

    void paste();

    void del();

    QString getClipboardFile();

    bool isClipboardAvailable();

    //移动到顶层
    void bringToTop();

    //移动到底层
    void bringToBottom();

    //组合
    void groupObj();

    //取消组合
    void ungroupObj();

    //增加对象到scene
    //void addIconGraphicsItem(HBaseObj* pObj);
    /*
    //左对齐
    void alignLeft();

    //右对齐
    void alignRight();

    //水平居中
    void alignHCenter();

    //上对齐
    void alignTop();

    //下对齐
    void alignBottom();

    //垂直居中
    void alignVCenter();

    //不同对齐方式不同点
    bool getbenchMarkPoint(QPointF& pt);

    //对齐
    void alignAlgorithm();

    //等宽
    void sizeEqualWidth();

    //等高
    void sizeEqualHeight();

    //完全相等
    void sizeEqualComplete();

    //横向等间距
    void sizeHEqualSpace();

    //纵向等间距
    void sizeVEqualSpace();

    //相等数据获取
    bool getbenchMarkSize(QPointF& pt);

    //相等关系算法
    void equalAlgorithm();

    //逆时针翻转90
    void flipLeft90();

    //顺时针翻转90
    void flipRight90();

    //水平翻转
    void flipHorizon();

    //垂直翻转
    void flipVertical();

    //旋转算法
    void flipAlgorithm();
    */
    //放大
    void zoomIn();

    //缩小
    void zoomOut();

    //自由缩放
    void zoom();

    //原始大小
    void zoomSame();

    void setupMatrix();

    int toolType() {return m_nToolType;}

    void drawTool(DrawShape drawShape);

    void selectTool(SelectMode select);

    void switchSelectTool();

signals:
    void selectChanged();
    void setSelectTool();
public slots:

    //图符创建、删除
    void onCreateObj(HBaseObj* pObj,bool isPaste );
    void onRemoveObj(HBaseObj* pObj);

    void onRefreshSelect(const QRectF& rect);
    void onDrawPath(const QList<Path>& path);
    void onEndDraw();

    void onSelectChanged(HBaseObj *obj, bool isSelected);

private:
    HIconEditorMgr* m_pIconEditorMgr;
    Qt::Alignment m_Alignment;
    IconSize m_Equalway;
    IconFlip m_Flipway;
    double m_scale;
    int m_nToolType;

};
#endif // HICONOP_H
