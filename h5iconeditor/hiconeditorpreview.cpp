#include "hiconeditorpreview.h"
#include "ui_iconpreview.h"
#include "hiconeditormgr.h"
#include "hiconeditorframe.h"
#include "hicontemplate.h"
#include "hiconshowpattern.h"
#include "hbaseobj.h"
#include "hiconobj.h"
#include "hiconhelper.h"
#include <QIntValidator>
HIconEditorPreview::HIconEditorPreview(HIconEditorMgr* iconMgr,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IconPreview),pIconMgr(iconMgr)
{
    ui->setupUi(this);

    ui->widget->installEventFilter(this);
    ui->widthSpinBox->setRange(0,50);
    ui->heightSpinBox->setRange(0,50);

    connect(ui->widthSpinBox,SIGNAL(editingFinished()),this,SLOT(onDefaultSizeChanged()));
    connect(ui->heightSpinBox,SIGNAL(editingFinished()),this,SLOT(onDefaultSizeChanged()));
    connect(ui->refreshBtn,SIGNAL(clicked(bool)),this,SLOT(onRefreshChanged()));
}

HIconEditorPreview::~HIconEditorPreview()
{
    delete ui;
}

void HIconEditorPreview::init()
{
    if(pIconMgr && pIconMgr->iconTemplate())
    {
        QSizeF sizeF = pIconMgr->iconTemplate()->getDefaultSize();
        ui->widthSpinBox->setValue(sizeF.width());
        ui->heightSpinBox->setValue(sizeF.height());
    }
    else
    {
        ui->widthSpinBox->setValue(0);
        ui->heightSpinBox->setValue(0);
    }
}

void HIconEditorPreview::refresh()
{

    //p.drawLine(QPointF(0,0),QPoint(5,5));
    //drawIcon(&p);

}

void HIconEditorPreview::onDefaultSizeChanged()
{
    int width = ui->widthSpinBox->value();
    int height = ui->heightSpinBox->value();
    if(pIconMgr && pIconMgr->iconTemplate())
    {
        pIconMgr->iconTemplate()->setDefaultSize(QSizeF(width,height));
        QSizeF sizeF = QSizeF(width,height);//获取默认大小
        if(sizeF.width() > 0 && sizeF.height())
        {
            QSizeF nSizeF = sizeF * pIconMgr->getRatio();
            QRectF rectF = QRectF(QPointF(-nSizeF.width()/2,-nSizeF.height()/2),QSizeF(nSizeF.width(),nSizeF.height()));
            pIconMgr->iconTemplate()->getSymbol()->m_width = nSizeF.width();
            pIconMgr->iconTemplate()->getSymbol()->m_height = nSizeF.height();
            pIconMgr->setLogicRect(rectF);
        }
        onRefreshChanged();
    }
}

void HIconEditorPreview::onRefreshChanged()
{
    if(!pIconMgr) return;
    HIconTemplate* pTemplate = pIconMgr->iconTemplate();
    if(!pTemplate) return;
    //绘制区域
    QSizeF tempSize = pTemplate->getDefaultSize();
    pixRect = QRectF(QPointF(0,0),tempSize);

    //获取绘制图形
    QSizeF ratioSizeF= QSizeF(pIconMgr->iconTemplate()->getSymbol()->m_width,pIconMgr->iconTemplate()->getSymbol()->m_height);
    int nCurPattern = pTemplate->getSymbol()->getCurrentPattern();
    pixMap = HIconHelper::Instance()->iconPixmap(pTemplate->getCatalogName(),pTemplate->getUuid().toString(),ratioSizeF,nCurPattern);
    ui->widget->update();//重绘操作
}

void HIconEditorPreview::drawIcon(QPainter *p)
{
    HIconTemplate* pTemplate = pIconMgr->iconTemplate();
    if(!pTemplate) return;
    pixMap = HIconHelper::Instance()->iconPixmap(pTemplate->getCatalogName(),pTemplate->getUuid().toString());
}

bool HIconEditorPreview::eventFilter(QObject *obj, QEvent *event)
{
    //return false;
    if(obj == ui->widget)
    {
        if(event->type() == QEvent::Paint)
        {
            if(!pixMap.isNull())
            {
                QPainter p(ui->widget);
                QPen pen(Qt::red);
                pen.setStyle(Qt::DotLine);
                p.setPen(pen);
                pixRect.moveCenter(QPointF(ui->widget->size().width()/2,ui->widget->size().height()/2));
                p.drawRect(pixRect);
                p.drawPixmap(pixRect.topLeft(),pixMap);

            }
            return true;
        }
    }

    return false;
}



