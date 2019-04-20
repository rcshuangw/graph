#ifndef HICONMGR_H
#define HICONMGR_H
#include "hiconeditorscene.h"
#include "hiconeditorframe.h"
#include "hiconeditordoc.h"
#include "hiconeditorop.h"
#include <QUndoStack>
/*
 * 绘制图符管理类
 * 主要管理各种对象指针，以及背景相关设置，如颜色、中心线、网格线等
 * 以及对图符的基本操作
*/
class HIconEditorFrame;
class HIconEditorDoc;
class HIconEditorSelectMgr;
class HIconEditorOp;
class HIconTemplate;


class HIconEditorMgr
{
public:
    HIconEditorMgr();
    ~HIconEditorMgr();
public:
    //指针
	HIconEditorDoc* iconEditorDocument();
	HIconTemplate* iconTemplate();
    HIconEditorFrame* iconEditorFrame();
	void setIconEditorFrame(HIconEditorFrame* frame);
	//HIconEditorSelectMgr iconEditorSelectMgr();
	QUndoStack* iconEditorUndoStack();
	HIconEditorOp* iconEditorOp();

public:
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

	//
	void setLogicRect(QRectF& rectF);
	QRectF getLogicRect();
public:
    void New(const QString& strTemplateName,const QString& strCatalogName,const int& nCatalogType);
    void Del(const QString &strTemplateName, int nTemplateType, const QString &strUuid);
    void Open(const QString &strTemplateName, int nTemplateType, const QString &strUuid);
    bool Save(bool savefile=false);
private:
    DrawShape m_drawShape;
    bool m_bShowGrid;
    bool m_bShowCenterLine;
    QString m_strBgClr;

	QRectF m_sceneRect;

    HIconEditorFrame* m_pIconEditorFrame;
    HIconEditorDoc* m_pIconEditorDoc;
	HIconEditorSelectMgr* m_pIconEditorSelectMgr;
	HIconTemplate* m_pIconTemplate;
    HIconEditorOp* m_pIconEditorOp;
	QUndoStack* m_pIconUndoStack;
};

#endif // HICONMGR_H
