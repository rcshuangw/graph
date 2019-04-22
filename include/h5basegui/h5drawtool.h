#ifndef H5DRAWTOOL_H
#define H5DRAWTOOL_H
#include <QObject>
#include "h5iconguiexport.h"
#include "h5event.h"
#include "hdrawmanager.h"
#include "h5baselib/hbaseobj.h"

//class HDrawManager; //绘制管理
class H5BASEGUI_EXPORT HDrawTool : public QObject
{
	Q_OBJECT
public:
    HDrawTool(HDrawManager* manager,DrawShape drawShape,const QString& name,const QString& uuid);
    virtual ~HDrawTool();

public:
    virtual void clear();
    virtual void onEvent(HEvent& event);

    virtual void onMousePressEvent(QMouseEvent* event,QVariant &data) = 0;
    virtual void onMouseMoveEvent(QMouseEvent* event,QVariant &data) = 0;
    virtual void onMouseReleaseEvent(QMouseEvent* event,QVariant &data) = 0;
public:
    DrawShape drawShape() {return m_edrawShape;}
    QString objTypeName(){ return m_strObjName;}
    QString templateUuid() {return m_strObjUuid;}
	HDrawManager* toolManager(){return m_pToolManager;}

protected:
	HDrawManager* m_pToolManager;
    DrawShape m_edrawShape;
    QString m_strObjName;
    QString m_strObjUuid;
};
#endif

