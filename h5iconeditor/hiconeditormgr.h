#ifndef HICONEDITORMGR_H
#define HICONEDITORMGR_H
#include "hiconapi.h"
#include <QUndoStack>
/*
 * 绘制图符管理类
*/
class HIconEditorFrame;
class HIconEditorDoc;
class HIconEditorSelectMgr;
class HIconEditorOp;
class HIconTemplate;
class HSelectedMgr;
class HIconEditorDrawToolMgr;
class HIconEditorSelectToolMgr;
class HIconEditorMgr : public QObject
{
    Q_OBJECT
public:
    HIconEditorMgr();
    ~HIconEditorMgr();
public:
    //指针
	HIconEditorDoc* iconEditorDocument();
	HIconTemplate* iconTemplate();
    HIconEditorFrame* iconEditorFrame();

	QUndoStack* iconEditorUndoStack();
	HIconEditorOp* iconEditorOp();
    HSelectedMgr* selectedMgr();
    HIconEditorDrawToolMgr* iconEditorDrawToolMgr();
    HIconEditorSelectToolMgr* iconEditorSelectToolMgr();

public:
    bool initIconEditorMgr();
    void setIconEditorFrame(HIconEditorFrame* frame);

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
    bool m_bModify;

	QRectF m_sceneRect;

    HIconEditorFrame* m_pIconEditorFrame;
    HIconEditorDoc* m_pIconEditorDoc;
	HIconEditorSelectMgr* m_pIconEditorSelectMgr;
	HIconTemplate* m_pIconTemplate;
    HIconEditorOp* m_pIconEditorOp;
	QUndoStack* m_pIconUndoStack;
    HSelectedMgr* m_pSelectedMgr;
    HIconEditorDrawToolMgr* m_pIconEditorDrawToolMgr;
    HIconEditorSelectToolMgr* m_pIconEditorSelectToolMgr;
};

#endif // HICONMGR_H
