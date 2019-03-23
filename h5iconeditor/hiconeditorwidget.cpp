#include "hiconeditorwidget.h"
#include <QVBoxLayout>
#include <QTabBar>
#include <QInputDialog>
#include <QMenu>
#include <QContextMenuEvent>
#include <QMessageBox>
#include "hiconeditorframe.h"
#include "hiconmgr.h"
#include "hicontemplate.h"
#include "hiconsymbol.h"
#include "hiconshowpattern.h"
//#include "hiconobj.h"
//#include "hiconrectobj.h"
//#include "hiconlineitem.h"
HIconEditorWidget::HIconEditorWidget()
{
    pTabBar = new QTabBar;
    pTabBar->installEventFilter(this);
    connect(pTabBar,SIGNAL(currentChanged(int)),this,SLOT(patternChanged(int)));

}

void HIconEditorWidget::setIconMgr(HIconMgr *iconMgr)
{
    pIconMgr = iconMgr;
    if(!pIconMgr || !pIconMgr->getIconFrame())
        return;
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->addWidget(pTabBar);
    layout->addWidget(pIconMgr->getIconFrame());
    setLayout(layout);
}

void HIconEditorWidget::newIconWidget()
{
    if(!pIconMgr || !pIconMgr->getIconTemplate())
        return;
    HIconSymbol* pSymbol = (HIconSymbol*)(pIconMgr->getIconTemplate()->getSymbol());
    if(!pSymbol)
        return;
    HIconShowPattern* pattern = pSymbol->getCurrentPatternPtr();//(HIconShowPattern*)(pSymbol->newPattern(strName));
    if(!pattern)
        return;
    pTabBar->show();
    int index = pTabBar->addTab(pattern->strName);
    pTabBar->setTabData(index,pSymbol->getCurrentPattern());
    pTabBar->setCurrentIndex(index);
    pIconMgr->getIconFrame()->setShowRuler(true);
    QSizeF sizeF = pIconMgr->getIconTemplate()->getDefaultSize();//获取默认大小
    if(sizeF.width() > 0 && sizeF.height())
    {
        QRectF rectF = QRectF(-sizeF.width()*10,-sizeF.height()*10,sizeF.width()*20,sizeF.height()*20);
        pIconMgr->getIconFrame()->setLogicRect(rectF);
    }
    pIconMgr->getIconFrame()->show();
}


void HIconEditorWidget::openIconWidget()
{
    if(!pIconMgr || !pIconMgr->getIconTemplate())
        return;
    HIconSymbol* pSymbol = (HIconSymbol*)(pIconMgr->getIconTemplate()->getSymbol());
    if(!pSymbol)
        return;
    for(int i = 0; i < pSymbol->pShowPatternVector.count();i++)
    {
        HIconShowPattern* pattern = (HIconShowPattern*)(pSymbol->pShowPatternVector[i]);
        if(!pattern)
            return;
        int index = pTabBar->addTab(pattern->strName);
        pTabBar->setTabData(index,pattern->nPattern);
        pIconMgr->getIconFrame()->refreshSceneByPatternId(pattern->nPattern);
    }

    QSizeF sizeF = pIconMgr->getIconTemplate()->getDefaultSize();//获取默认大小
    if(sizeF.width() > 0 && sizeF.height()>0)
    {
        QRectF rectF = QRectF(-sizeF.width()*10,-sizeF.height()*10,sizeF.width()*20,sizeF.height()*20);
        pIconMgr->getIconFrame()->setLogicRect(rectF);
    }
    emit pTabBar->currentChanged(0);
    pTabBar->show();
    pIconMgr->getIconFrame()->show();
    pIconMgr->getIconFrame()->setShowRuler(true);
}

void HIconEditorWidget::delIconWidget()
{
    int index = pTabBar->count();
    if(index == 0) return;
    while(index)
    {
        QVariant data = pTabBar->tabData(index-1);
        pIconMgr->getIconTemplate()->getSymbol()->setCurrentPattern(data.toInt());
        pIconMgr->getIconFrame()->clearSceneByPatternId(data.toInt());
        pTabBar->removeTab(index-1);
        index--;
    }
    pIconMgr->getIconFrame()->setShowRuler(false);
    //QRectF rectF = QRectF(0,0,0,0);
    //pIconMgr->getIconFrame()->setLogicRect(rectF);
    pTabBar->hide();
    pIconMgr->getIconFrame()->hide();
    QVBoxLayout* vBoxLayout = (QVBoxLayout*)layout();
    if(vBoxLayout)
    {
        vBoxLayout->removeWidget(pTabBar);
        vBoxLayout->removeWidget(pIconMgr->getIconFrame());
        delete vBoxLayout;
    }
}

void HIconEditorWidget::addShowPattern()
{
    HIconSymbol* pSymbol = (HIconSymbol*)(pIconMgr->getIconTemplate()->getSymbol());
    if(!pSymbol)
        return;
    bool ok;
    QString strName = QInputDialog::getText(this,QStringLiteral("输入显示方案名称"),QStringLiteral("显示方案名称:"),QLineEdit::Normal,"",&ok);
    if(strName.isEmpty())
        return;
    HIconShowPattern* pattern = (HIconShowPattern*)(pSymbol->newPattern(strName));
    if(!pattern)
        return;
    int index = pTabBar->addTab(strName);
    pTabBar->setTabData(index,pSymbol->getCurrentPattern());
    pTabBar->setCurrentIndex(index);

}

void HIconEditorWidget::delShowPattern()
{
    if(pTabBar)
    {
        int curIndex = pTabBar->currentIndex();
        if(curIndex == 0)
        {
            QMessageBox::warning(NULL,QStringLiteral("警告"),QStringLiteral("缺省样式不能删除!"),QMessageBox::Ok);
            return;
        }
        else
        {
            QVariant data = pTabBar->tabData(curIndex);
            if(!data.isValid())
                return;
            if(!pIconMgr->getIconFrame()||!pIconMgr->getIconTemplate()||!pIconMgr->getIconTemplate()->getSymbol())
                return;
            HIconTemplate* pTemplate = pIconMgr->getIconTemplate();
            QString strPatternName = pTemplate->getSymbol()->getCurrentPatternPtr()->strName;
            QString strWarning = QString(QStringLiteral("确定删除%1显示方案?")).arg(strPatternName);
            int ret = QMessageBox::warning(NULL,QStringLiteral("警告"),strWarning,QMessageBox::Ok|QMessageBox::Cancel);
            if(QMessageBox::Ok == ret)
            {
                pIconMgr->getIconFrame()->clearSceneByPatternId(data.toInt());
                pTemplate->getSymbol()->delPattern(data.toInt());
                pTabBar->removeTab(curIndex);
            }
        }
    }
}

void HIconEditorWidget::renameShowPattern()
{
    if(pTabBar)
    {
        int curIndex = pTabBar->currentIndex();

        QVariant data = pTabBar->tabData(curIndex);
        if(!data.isValid())
            return;
        if(!pIconMgr->getIconFrame()||!pIconMgr->getIconTemplate()||!pIconMgr->getIconTemplate()->getSymbol())
            return;

        HIconTemplate* pTemplate = pIconMgr->getIconTemplate();
        QString strPatternName = pTemplate->getSymbol()->getCurrentPatternPtr()->strName;
        bool ok;
        QString strNewName = QInputDialog::getText(this,QStringLiteral("输入显示方案名称"),QStringLiteral("显示方案名称:"),QLineEdit::Normal,strPatternName,&ok);
        if(ok)
        {
            if(strNewName.isEmpty())
                return;
            pTemplate->getSymbol()->getCurrentPatternPtr()->strName = strNewName;
            pTabBar->setTabText(curIndex,strNewName);
        }
    }
}

void HIconEditorWidget::refreshIconWidget()
{

}


void HIconEditorWidget::patternChanged(int index)
{
    if(!pTabBar||!pIconMgr->getIconFrame()||!pIconMgr->getIconTemplate()||!pIconMgr->getIconTemplate()->getSymbol())
        return;
    bool ok;
    QVariant data = pTabBar->tabData(index);
    if(!data.isValid())
        return;
    int newPatternId = data.toInt(&ok);
    if(!ok)
        return;
    HIconTemplate* pTemplate = pIconMgr->getIconTemplate();
    if(!pTemplate || !pTemplate->getSymbol())
        return;
    for(int i = 0; i < pTemplate->getSymbol()->pShowPatternVector.count();i++)
    {
        HIconShowPattern* pattern = (HIconShowPattern*)pTemplate->getSymbol()->pShowPatternVector[i];
        if(pattern)
        {
            pIconMgr->getIconFrame()->setItemVisible(newPatternId);

        }
    }
    pTemplate->getSymbol()->setCurrentPattern(newPatternId);

   /* //显示新的部分
    pTemplate->getSymbol()->setCurrentPattern(newPatternId);
    HIconShowPattern* pattern = pTemplate->getSymbol()->findPatternById(newPatternId);
    if(pattern)
    {
        for(int i = 0; i < pattern->pObjList.count();i++)
        {
            HBaseObj* pObj = (HBaseObj*)pattern->pObjList.at(i);
            if(pObj )
            {
                if(pObj->getShapeType() == enumLine)
                {
                    HLineObj* pLineObj = (HLineObj*)pObj;
                    HIconLineItem* pItem = (HIconLineItem*)(pLineObj->getIconLineItem());
                    if(pItem)
                    {
                        pItem->setVisible(true);
                    }
                }
            }
        }
    }*/

    //刷新
    if(pIconMgr->getIconFrame())
    {
        pIconMgr->getIconFrame()->view()->invalidateScene(pIconMgr->getIconFrame()->view()->sceneRect());
    }
}

bool HIconEditorWidget::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == pTabBar)
    {
        if(event->type() == QEvent::ContextMenu)
        {
            QMenu menu(pTabBar);
            menu.addAction(QStringLiteral("增加"),this,SLOT(addShowPattern()));
            menu.addAction(QStringLiteral("删除"),this,SLOT(delShowPattern()));
            menu.addAction(QStringLiteral("改名"),this,SLOT(renameShowPattern()));

            menu.exec(((QContextMenuEvent*)event)->globalPos());
            return true;
        }
    }
    return false;
}
