#ifndef HICONMGR_H
#define HICONMGR_H
#include "hiconscene.h"
#include "hiconeditorframe.h"
#include "hicondocument.h"
#include "hiconstate.h"
#include "hiconeditorop.h"
#include <QUndoStack>
class HIconEditorFrame;
class HIconDocument;
class HIconDrawManager;
class HIconEditorOp;
class HIconEditorMgr
{
public:
    HIconEditorMgr();
    HIconDocument* getIconDocument();
    HIconTemplate* getIconTemplate();
    HIconEditorFrame* getIconFrame();
    QUndoStack* getIconUndoStack();
    HIconOp* getIconOp();

    void setBackgroundColor(QString clrName);
    QString getBackgroundColor();
    void setShowGrid(bool show);
    bool getShowGrid();
    void setShowCenterLine(bool show);
    bool getShowCenterLine();

    void setDrawShape(DRAWSHAPE ds);
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
    HIconDrawManager* m_pIconState;
    HIconEditorOp* m_pIconOp;
    QUndoStack* m_pIconUndoStack;
};

#endif // HICONMGR_H
