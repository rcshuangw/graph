#ifndef HICONMGR_H
#define HICONMGR_H
#include "hiconeditorscene.h"
#include "hiconeditorframe.h"
#include "hicondocument.h"
#include "hiconeditorop.h"
#include <QUndoStack>
/*
 * 绘制图符管理类
 * 主要管理各种对象指针，以及背景相关设置，如颜色、中心线、网格线等
 * 以及对图符的基本操作
*/
class HIconEditorFrame;
class HIconDocument;
class HIconDrawManager;
class HIconSelectManager;//将selectMgr和selectTool结合
class HIconEditorOp;
class HIconTemplate;
class HIconEditorMgr
{
public:
    HIconEditorMgr();
    ~HIconEditorMgr();

    //文档指针
    HIconDocument* getIconDocument();

    //图标模板文件
    HIconTemplate* getIconTemplate();

    //图符绘制widget
    HIconEditorFrame* getIconFrame();

    //undo redo
    QUndoStack* getIconUndoStack();

    //图符操作类
    HIconEditorOp* getIconeditorOp();

    //背景颜色
    void setBackgroundColor(QString clrName);
    QString getBackgroundColor();

    //网格
    void setShowGrid(bool show);
    bool getShowGrid();

    //中心线
    void setShowCenterLine(bool show);
    bool getShowCenterLine();

    void setDrawShape(DrawShape ds);
    DrawShape getDrawShape();

    void setSelectMode(SELECTMODE ds);
    SELECTMODE getSelectMode();

public:
    void New(const QString& strTemplateName,const QString& strCatalogName,const int& nCatalogType);
    void Del(const QString &strTemplateName, int nTemplateType, const QString &strUuid);
    void Open(const QString &strTemplateName, int nTemplateType, const QString &strUuid);
    bool Save(bool savefile=false);
private:
    DrawShape m_drawShape;
    SELECTMODE m_selectMode;
    bool m_bShowGrid;
    bool m_bShowCenterLine;
    QString m_strBgClr;

    HIconEditorFrame* m_pIconFrame;
    HIconDocument* m_pIconDocument;
    HIconDrawManager* m_pIconDrawMgr;
    HIconSelectManager* m_pIconSelectMgr;

    HIconEditorOp* m_pIconOp;
    QUndoStack* m_pIconUndoStack;
};

#endif // HICONMGR_H
