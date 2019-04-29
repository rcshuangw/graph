#include "hiconeditorwidget.h"
#include <QVBoxLayout>
#include <QTabBar>
#include <QInputDialog>
#include <QMenu>
#include <QContextMenuEvent>
#include <QMessageBox>
#include "hiconeditorframe.h"
#include "hiconeditormgr.h"
#include "hicontemplate.h"
#include "hiconsymbol.h"
#include "hiconshowpattern.h"
//#include "hiconobj.h"
//#include "hiconrectobj.h"
//#include "hiconlineitem.h"
HIconEditorWidget::HIconEditorWidget()
{
    m_pTabBar = new QTabBar;
    m_pTabBar->installEventFilter(this);
    connect(m_pTabBar,SIGNAL(currentChanged(int)),this,SLOT(patternChanged(int)));

}

void HIconEditorWidget::setIconEditorMgr(HIconEditorMgr *iconMgr)
{
    m_pIconEditorMgr = iconMgr;
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconEditorFrame())
        return;
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->addWidget(m_pTabBar);
    layout->addWidget(m_pIconEditorMgr->iconEditorFrame());
    setLayout(layout);

    //增加一个刷新函数
    refresh();
}

void HIconEditorWidget::refresh()
{
    if(!m_pIconEditorMgr || !m_pTabBar)
        return;
    if(m_pIconEditorMgr->iconTemplate() || m_pIconEditorMgr->iconTemplate()->getSymbol())
        return;
    while(m_pTabBar->count() > 0)
    {
        m_pTabBar->blockSignals(true);
        m_pTabBar->removeTab(0);
        m_pTabBar->blockSignals(false);
    }
    HIconSymbol* pSymbol = (HIconSymbol*) m_pIconEditorMgr->iconTemplate()->getSymbol();
    if(!pSymbol)
        return;
   for(int i = 0; i < pSymbol->patternCount();i++)
   {
       HIconShowPattern* pattern = (HIconShowPattern*)pSymbol->findPatternById(i);
       if(pattern)
       {
           m_pTabBar->blockSignals(true);
           m_pTabBar->addTab(pattern->strName);
           m_pTabBar->setTabData(i,pattern->nPattern);
           m_pTabBar->blockSignals(false);
       }
   }

   if(m_pTabBar->count() > 0)
   {
       int index = pSymbol->getCurrentPatternIndex() - 1;
       m_pTabBar->blockSignals(true);
       m_pTabBar->setCurrentIndex(index);
       m_pTabBar->blockSignals(false);
       patternChanged(index);
   }

}

void HIconEditorWidget::newIconWidget()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconTemplate())
        return;
    /*HIconSymbol* pSymbol = (HIconSymbol*)(pIconMgr->getIconTemplate()->getSymbol());
    if(!pSymbol)
        return;
    HIconShowPattern* pattern = pSymbol->getCurrentPatternPtr();//(HIconShowPattern*)(pSymbol->newPattern(strName));
    if(!pattern)
        return;
    pTabBar->show();
    int index = pTabBar->addTab(pattern->strName);
    pTabBar->setTabData(index,pSymbol->getCurrentPattern());
    pTabBar->setCurrentIndex(index);
    pIconMgr->getIconFrame()->setShowRuler(true);*/
    QSizeF sizeF = m_pIconEditorMgr->iconTemplate()->getDefaultSize();//获取默认大小
    if(sizeF.width() > 0 && sizeF.height())
    {
        QSizeF nSizeF = sizeF * m_pIconEditorMgr->getRatio();
        QRectF rectF = QRectF(QPointF(-nSizeF.width()/2,-nSizeF.height()/2),sizeF.width(),sizeF.height());
        m_pIconEditorMgr->iconTemplate()->getSymbol()->m_width = nSizeF.width();
        m_pIconEditorMgr->iconTemplate()->getSymbol()->m_height = nSizeF.height();
        m_pIconEditorMgr->setLogicRect(rectF);
    }
    //pIconMgr->getIconFrame()->show();
}


void HIconEditorWidget::openIconWidget()
{
    if(!m_pIconEditorMgr || !m_pIconEditorMgr->iconTemplate())
        return;

    int width = m_pIconEditorMgr->iconTemplate()->getSymbol()->m_width;
    int height = m_pIconEditorMgr->iconTemplate()->getSymbol()->m_height;
    QSizeF sizeF = m_pIconEditorMgr->iconTemplate()->getDefaultSize();//获取默认大小
    if(width > 0 && height > 0 && sizeF.width() > 0 && sizeF.height())
    {
        m_pIconEditorMgr->setRatio(qMin(width/sizeF.width(),height/sizeF.height()));
        QRectF rectF = QRectF(QPointF(-width/2,-height/2),QSizeF(width,height));
        m_pIconEditorMgr->setLogicRect(rectF);
    }

    //所有false
    HIconTemplate* pTemplate = m_pIconEditorMgr->iconTemplate();
    if(!pTemplate) return;
    for(int i = 0; i < pTemplate->getSymbol()->getObjList().count();i++)
    {
        HBaseObj* pObj = pTemplate->getSymbol()->getObjList().at(i);
        if(pObj && pObj->getPattern() != newPatternId)
        {
            H5GraphicsItem* item = (H5GraphicsItem*)pObj->iconGraphicsItem();
            if(item)
                item->setVisible(false);
        }
    }
    //open之后会重新refresh然后触发patternChanged打开对应的pattern
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
    if(m_pIconEditorMgr->iconTemplate() || m_pIconEditorMgr->iconTemplate()->getSymbol())
        return;
    HIconSymbol* pSymbol = (HIconSymbol*)(m_pIconEditorMgr->iconTemplate()->getSymbol());
    if(!pSymbol)
        return;
    bool ok;
    QString strName = QInputDialog::getText(this,QStringLiteral("输入显示方案名称"),QStringLiteral("显示方案名称:"),QLineEdit::Normal,"",&ok);
    if(strName.isEmpty())
        return;
    HIconShowPattern* pattern = (HIconShowPattern*)(pSymbol->newPattern(strName));
    if(!pattern)
        return;
    int index = m_pTabBar->addTab(strName);
    m_pTabBar->setTabData(index,pSymbol->getCurrentPattern());
    m_pTabBar->setCurrentIndex(index);

}

void HIconEditorWidget::delShowPattern()
{
    if(m_pTabBar && m_pIconEditorMgr)
    {
        int curIndex = m_pTabBar->currentIndex();
        if(curIndex == 0)
        {
            QMessageBox::warning(NULL,QStringLiteral("警告"),QStringLiteral("缺省样式不能删除!"),QMessageBox::Ok);
            return;
        }
        else
        {
            QVariant data = m_pTabBar->tabData(curIndex);
            if(!data.isValid())
                return;
            if(!m_pIconEditorMgr->iconEditorFrame()||!m_pIconEditorMgr->iconTemplate()||!m_pIconEditorMgr->iconTemplate()->getSymbol())
                return;
            HIconTemplate* pTemplate = m_pIconEditorMgr->iconTemplate();
            QString strPatternName = pTemplate->getSymbol()->getCurrentPatternPtr()->strName;
            QString strWarning = QString(QStringLiteral("确定删除%1显示方案?")).arg(strPatternName);
            int ret = QMessageBox::warning(NULL,QStringLiteral("警告"),strWarning,QMessageBox::Ok|QMessageBox::Cancel);
            if(QMessageBox::Ok == ret)
            {
                m_pIconEditorMgr->iconTemplate()->clearSceneByPatternId(data.toInt());
                pTemplate->getSymbol()->delPattern(data.toInt());
                m_pTabBar->removeTab(curIndex);
            }
        }
    }
}

void HIconEditorWidget::renameShowPattern()
{
    if(m_pTabBar && m_pIconEditorMgr)
    {
        int curIndex = m_pTabBar->currentIndex();

        QVariant data = m_pTabBar->tabData(curIndex);
        if(!data.isValid())
            return;
        if(!m_pIconEditorMgr->iconEditorFrame()||!m_pIconEditorMgr->iconTemplate()||!m_pIconEditorMgr->iconTemplate()->getSymbol())
            return;

        HIconTemplate* pTemplate = m_pIconEditorMgr->iconTemplate();
        QString strPatternName = pTemplate->getSymbol()->getCurrentPatternPtr()->strName;
        bool ok;
        QString strNewName = QInputDialog::getText(this,QStringLiteral("输入显示方案名称"),QStringLiteral("显示方案名称:"),QLineEdit::Normal,strPatternName,&ok);
        if(ok)
        {
            if(strNewName.isEmpty())
                return;
            pTemplate->getSymbol()->getCurrentPatternPtr()->strName = strNewName;
            m_pTabBar->setTabText(curIndex,strNewName);
        }
    }
}

void HIconEditorWidget::refreshIconWidget()
{

}


void HIconEditorWidget::patternChanged(int index)
{
    if(!m_pTabBar||!m_pIconEditorMgr->iconEditorFrame()||!m_pIconEditorMgr->iconTemplate()||!m_pIconEditorMgr->iconTemplate()->getSymbol())
        return;
    bool ok;
    QVariant data = m_pTabBar->tabData(index);
    if(!data.isValid())
        return;
    int newPatternId = data.toInt(&ok);
    if(!ok)
        return;
    //所有false
    HIconTemplate* pTemplate = m_pIconEditorMgr->iconTemplate();
    for(int i = 0; i < pTemplate->getSymbol()->getObjList().count();i++)
    {
        HBaseObj* pObj = pTemplate->getSymbol()->getObjList().at(i);
        if(pObj && pObj->getPattern() != newPatternId)
        {
            H5GraphicsItem* item = (H5GraphicsItem*)pObj->iconGraphicsItem();
            if(item)
                item->setVisible(false);
        }
    }
    pTemplate->getSymbol()->setCurrentPattern(newPatternId);

   ///显示新的部分
    pTemplate->getSymbol()->setCurrentPattern(newPatternId);
    HIconShowPattern* pattern = pTemplate->getSymbol()->findPatternById(newPatternId);
    if(pattern)
    {
        for(int i = 0; i < pattern->getObjList().count();i++)
        {
            HBaseObj* pObj = (HBaseObj*)pattern->getObjList().at(i);
            if(pObj )
            {
                H5GraphicsItem* item = (H5GraphicsItem*)pObj->iconGraphicsItem();
                if(item)
                    item->setVisible(true);
            }
        }
    }

    //刷新
    if(m_pIconEditorMgr->iconEditorFrame())
    {
        m_pIconEditorMgr->iconEditorFrame()->view()->invalidateScene(m_pIconEditorMgr->iconEditorFrame()->view()->sceneRect());
    }
}

bool HIconEditorWidget::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == m_pTabBar)
    {
        if(event->type() == QEvent::ContextMenu)
        {
            QMenu menu(m_pTabBar);
            menu.addAction(QStringLiteral("增加"),this,SLOT(addShowPattern()));
            menu.addAction(QStringLiteral("删除"),this,SLOT(delShowPattern()));
            menu.addAction(QStringLiteral("改名"),this,SLOT(renameShowPattern()));

            menu.exec(((QContextMenuEvent*)event)->globalPos());
            return true;
        }
    }
    return false;
}
