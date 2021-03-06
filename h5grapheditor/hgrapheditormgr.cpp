﻿#include "hgrapheditormgr.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QScrollBar>
#include <QDir>
#include "hgrapheditorview.h"
#include "hgrapheditordoc.h"
#include "hgrapheditorscene.h"
#include "hgrapheditorop.h"
#include "hgraphcommand.h"
#include "hgraph.h"
#include "hselectedmgr.h"
#include "hmakeicon.h"
#include "hgrapheditordrawtoolmgr.h"
#include "hgrapheditorselecttool.h"
//图形文件管理总类
HGraphEditorMgr::HGraphEditorMgr()
    :m_logicRectF(-500,-500,1000,1000)
{
    m_pGraphEditorDoc = new HGraphEditorDoc(this);
    Q_ASSERT(m_pGraphEditorDoc);

    m_pGraphEditorUndoStack = new QUndoStack(this);

    m_pGraphEditorOp = new HGraphEditorOp(this);
    m_pSelectedMgr = new HSelectedMgr;

    m_pGraphEditorScene = new HGraphEditorScene(this);
    m_pGraphEditorView = NULL;

    int width = qApp->desktop()->screen()->width();
    int height = qApp->desktop()->screen()->height();
    m_logicRectF.setX(0-(width-2)/2);
    m_logicRectF.setY(0-(height-100)/2);
    m_logicRectF.setWidth(width-2);
    m_logicRectF.setHeight(height-100);
    m_eDrawShape = No;

    m_pGraphEditorDrawToolMgr = NULL;
    m_pGraphEditorSelectTool = NULL;
    //选择状态下的刷新
    connect(m_pSelectedMgr,SIGNAL(refreshSelect(QRectF)),m_pGraphEditorOp,SLOT(onRefreshSelect(QRectF)));
}

HGraphEditorMgr::~HGraphEditorMgr()
{
    if(m_pGraphEditorOp)
    {
        delete m_pGraphEditorOp;
        m_pGraphEditorOp = NULL;
    }

    if(m_pGraphEditorDoc)
    {
        delete m_pGraphEditorDoc;
        m_pGraphEditorDoc = NULL;
    }

    HMakeIcon::Instance()->Exstance();

}

//启动时加载数据库
void HGraphEditorMgr::loadStation()
{
    if(!m_pGraphEditorDoc)
        return;
    m_pGraphEditorDoc->loadStation();
}

//启动时加载模板信息
void HGraphEditorMgr::loadTemplates()
{
    if(!m_pGraphEditorDoc)
        return;
    m_pGraphEditorDoc->loadIconTemplate();
}

//启动时加载画面信息
void HGraphEditorMgr::loadGraphs()
{
    if(!m_pGraphEditorDoc)
        return;
    m_pGraphEditorDoc->loadAllGraph();
}

HGraphEditorOp* HGraphEditorMgr::graphEditorOp()
{
    return m_pGraphEditorOp;
}

HGraphEditorScene* HGraphEditorMgr::graphEditorScene()
{
    return m_pGraphEditorScene;
}

HGraphEditorView* HGraphEditorMgr::graphEditorView()
{
    return m_pGraphEditorView;
}

HGraphEditorDoc* HGraphEditorMgr::graphEditorDoc()
{
    return m_pGraphEditorDoc;
}

QUndoStack* HGraphEditorMgr::graphEditorStack()
{
    return m_pGraphEditorUndoStack;
}

HSelectedMgr* HGraphEditorMgr::selectedMgr()
{
    return m_pSelectedMgr;
}

HGraphEditorDrawToolMgr* HGraphEditorMgr::graphEditorDrawToolMgr()
{
    return m_pGraphEditorDrawToolMgr;
}

HGraphEditorSelectTool* HGraphEditorMgr::graphEditorSelectTool()
{
    return m_pGraphEditorSelectTool;
}

void HGraphEditorMgr::setGraphEditorView(HGraphEditorView* view)
{
    if(view)
    {
        m_pGraphEditorView = view;
        m_pGraphEditorView->setScene(m_pGraphEditorScene);
        m_pGraphEditorScene->setView(m_pGraphEditorView);
        QRectF rectF(m_logicRectF);
        m_pGraphEditorScene->setSceneRect(rectF);

        QScrollBar* pBar = m_pGraphEditorView->horizontalScrollBar();
        if(pBar && pBar->isHidden() == false)
        {
            pBar->setSliderPosition(pBar->minimum());
        }
        pBar = m_pGraphEditorView->verticalScrollBar();
        if(pBar && pBar->isHidden() == false)
        {
            pBar->setSliderPosition(pBar->minimum());
        }

        if(graphEditorDoc()->getCurGraph())
        {
           graphEditorDoc()->getCurGraph()->m_width = m_logicRectF.width();
           graphEditorDoc()->getCurGraph()->m_height = m_logicRectF.height();
        }

        if(!m_pGraphEditorDrawToolMgr)
        {
            m_pGraphEditorDrawToolMgr = new HGraphEditorDrawToolMgr(this);
            connect(m_pGraphEditorDrawToolMgr,SIGNAL(drawPath(const QList<Path>&)),m_pGraphEditorOp,SLOT(onDrawPath(const QList<Path>)));
            connect(m_pGraphEditorDrawToolMgr,SIGNAL(endDraw()),m_pGraphEditorOp,SLOT(onEndDraw()));
        }
        if(!m_pGraphEditorSelectTool)
        {
            m_pGraphEditorSelectTool =new HGraphEditorSelectTool(this);
            connect(m_pGraphEditorSelectTool,SIGNAL(refreshSelect(QRectF)),m_pGraphEditorOp,SLOT(onRefreshSelect(QRectF)));
            connect(m_pGraphEditorSelectTool,SIGNAL(endDraw()),m_pGraphEditorOp,SLOT(onEndDraw()));
            connect(m_pGraphEditorOp,SIGNAL(selectChanged()),m_pGraphEditorSelectTool,SLOT(onSelectChanged()));
        }
    }

}

//设置逻辑界面大小
void HGraphEditorMgr::setLogicRect(const QRectF& rect)
{
    m_logicRectF = rect;
}

QRectF HGraphEditorMgr::getLogicRect()
{
    return m_logicRectF;
}

//判断graph文件名是否存在
bool HGraphEditorMgr::isExistGraph(const QString& graphName)
{
    if(!m_pGraphEditorDoc)
        return false;
    HGraph* graph = m_pGraphEditorDoc->findGraph(graphName);
    if(!graph)
        return false;
    return true;
}

//判断graph文件是否修改
bool HGraphEditorMgr::isGraphModify()
{
    if(!m_pGraphEditorDoc)
        return false;
    return m_pGraphEditorDoc->isGraphModify();
}

void HGraphEditorMgr::setDrawShape(DrawShape ds)
{
    m_eDrawShape = ds;
}

DrawShape HGraphEditorMgr::getDrawShape()
{
    return m_eDrawShape;
}

void HGraphEditorMgr::reset()
{
    m_pSelectedMgr->clear();
    m_pGraphEditorUndoStack->clear();

    for(int i = 0; i < m_pGraphEditorScene->views().count();i++)
        m_pGraphEditorScene->views().at(i)->setScene(0);

    delete m_pGraphEditorScene;

    m_pGraphEditorScene =  new HGraphEditorScene(this);

    //初始化scene
    m_pGraphEditorView->setScene(m_pGraphEditorScene);
    m_pGraphEditorScene->setView(m_pGraphEditorView);
    int width = qApp->desktop()->screen()->width();
    int height = qApp->desktop()->screen()->height();
    m_logicRectF.setX(0-(width-2)/2);
    m_logicRectF.setY(0-(height-100)/2);
    m_logicRectF.setWidth(width-2);
    m_logicRectF.setHeight(height-100);
    m_pGraphEditorScene->setSceneRect(m_logicRectF);

    QScrollBar* pBar = m_pGraphEditorView->horizontalScrollBar();
    if(pBar && pBar->isHidden() == false)
    {
        pBar->setSliderPosition(pBar->minimum());
    }
    pBar = m_pGraphEditorView->verticalScrollBar();
    if(pBar && pBar->isHidden() == false)
    {
        pBar->setSliderPosition(pBar->minimum());
    }

    if(graphEditorDoc()->getCurGraph())
    {
       graphEditorDoc()->getCurGraph()->m_width = m_logicRectF.width();
       graphEditorDoc()->getCurGraph()->m_height = m_logicRectF.height();
    }
}

//新建文件
void HGraphEditorMgr::New(const QString& graphName)
{
    if(!m_pGraphEditorDoc)
        return;
    m_pGraphEditorDoc->addGraph(graphName);
    m_pGraphEditorOp->setGraphicsView();

    if(!m_pGraphEditorDrawToolMgr)
        return;
    QColor bgColor = QColor(graphEditorDoc()->getCurGraph()->getFillColor());
    m_pGraphEditorDrawToolMgr->m_vDrawAttribute.brush.setColor(bgColor);
    QColor fgColor = QColor(255-bgColor.red(),255-bgColor.green(),255-bgColor.blue());
    m_pGraphEditorDrawToolMgr->m_vDrawAttribute.drawPen.setColor(fgColor);
    m_pGraphEditorDrawToolMgr->m_vDrawAttribute.textPen.setColor(fgColor);
}

bool HGraphEditorMgr::Open(const QString& graphName,int id)
{
    if(!m_pGraphEditorDoc)
        return false;
    if(!m_pGraphEditorDoc->openGraph(graphName,id))
        return false;
    m_pGraphEditorOp->setGraphicsView();

    if(!m_pGraphEditorDoc->getCurGraph())
        return false;
    for(int i = 0; i < m_pGraphEditorDoc->getCurGraph()->size();i++)
    {
        HBaseObj* obj = (HBaseObj*)m_pGraphEditorDoc->getCurGraph()->at(i);
        m_pGraphEditorOp->objCreated(obj);
    }
    if(!m_pGraphEditorDrawToolMgr)
        return false;
    QColor bgColor = QColor(graphEditorDoc()->getCurGraph()->getFillColor());
    m_pGraphEditorDrawToolMgr->m_vDrawAttribute.brush.setColor(bgColor);
    QColor fgColor = QColor(255-bgColor.red(),255-bgColor.green(),255-bgColor.blue());
    m_pGraphEditorDrawToolMgr->m_vDrawAttribute.drawPen.setColor(fgColor);
    m_pGraphEditorDrawToolMgr->m_vDrawAttribute.textPen.setColor(fgColor);
    return true;

}

void HGraphEditorMgr::Save()
{
    if(!m_pGraphEditorDoc)
        return;
    return m_pGraphEditorDoc->saveCurGraph();
}

bool HGraphEditorMgr::Del(const QString& graphName,int id)
{
    if(!m_pGraphEditorDoc)
        return false;
    return m_pGraphEditorDoc->delGraph(graphName,id);
}

int HGraphEditorMgr::ImportFile(const QString& graphName)
{
    if(!m_pGraphEditorDoc)
        return false;
    return m_pGraphEditorDoc->importGraph(graphName);
}

void HGraphEditorMgr::refreshView()
{
    if(!m_pGraphEditorView)
        return;
    m_pGraphEditorView->refresh();
}
