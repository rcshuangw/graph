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
HIconEditorPreview::HIconEditorPreview(QWidget *parent) :
    QDialog(parent),ui(new Ui::IconPreview)
{
    ui->setupUi(this);

    ui->widget->installEventFilter(this);
    ui->widthSpinBox->setRange(0,100);
    ui->heightSpinBox->setRange(0,100);

    connect(ui->widthSpinBox,SIGNAL(editingFinished()),this,SLOT(onDefaultSizeChanged()));
    connect(ui->heightSpinBox,SIGNAL(editingFinished()),this,SLOT(onDefaultSizeChanged()));
    connect(ui->refreshBtn,SIGNAL(clicked(bool)),this,SLOT(onRefreshChanged()));
}

HIconEditorPreview::~HIconEditorPreview()
{
    delete ui;
}

void HIconEditorPreview::clear()
{
    m_pixmap = QPixmap();
    ui->widget->repaint();
}

void HIconEditorPreview::setIconEditorMgr(HIconEditorMgr* mgr)
{
    clear();
    pIconMgr = mgr;
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
    refresh();
}

void HIconEditorPreview::refresh()
{
    if(!pIconMgr || !pIconMgr->iconTemplate())
        return;

    QSizeF tempSize = pIconMgr->iconTemplate()->getDefaultSize();
    m_boundingRect = QRectF(QPointF(0,0),tempSize);
    m_boundingRect.moveCenter(QPointF(ui->widget->size().width()/2,ui->widget->size().height()/2));
    m_pixmap = QPixmap(ui->widget->size());
    QPainter painter(&m_pixmap);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.fillRect(QRectF(QPointF(0,0),ui->widget->size()),Qt::white);
    drawIcon(&painter);
    ui->widget->update();
}

void HIconEditorPreview::onDefaultSizeChanged()
{
    int width = ui->widthSpinBox->value();
    int height = ui->heightSpinBox->value();
    if(!pIconMgr || !pIconMgr->iconTemplate())
        return;
    pIconMgr->iconTemplate()->setDefaultSize(QSizeF(width,height));
    QSizeF sizeF = QSizeF(width,height);//获取默认大小
    if(sizeF.width() > 0 && sizeF.height())
    {
        QSizeF nSizeF = sizeF * pIconMgr->getRatio();
        QRectF rectF = QRectF(QPointF(-nSizeF.width()/2,-nSizeF.height()/2),QSizeF(nSizeF.width(),nSizeF.height()));
        pIconMgr->iconTemplate()->getSymbol()->m_width = nSizeF.width();
        pIconMgr->iconTemplate()->getSymbol()->m_height = nSizeF.height();
        pIconMgr->setLogicRect(rectF);
        pIconMgr->iconTemplate()->setModify(true);
    }
    refresh();
}

void HIconEditorPreview::onRefreshChanged()
{
    refresh();
}

void HIconEditorPreview::drawIcon(QPainter *p)
{
    if(!pIconMgr)
        return;
    HIconTemplate* pTemplate = pIconMgr->iconTemplate();
    if(!pTemplate) return;
    HIconObj* obj = new HIconObj(pTemplate);
    if(!obj)return;
    //obj->initIconTemplate();
    obj->resize(m_boundingRect.width(),m_boundingRect.height());
    p->save();
    p->setPen(Qt::DotLine);
    p->drawRect(m_boundingRect);
    p->restore();
    p->save();
    p->translate(ui->widget->width()/2,ui->widget->height()/2);
    obj->paint(p);
    p->restore();
    if(obj)
    {
        delete obj;
        obj = NULL;
    }

}

bool HIconEditorPreview::eventFilter(QObject *obj, QEvent *event)
{
    //return false;
    if(obj == ui->widget)
    {
        if(event->type() == QEvent::Paint)
        {
            if(!m_pixmap.isNull())
            {
                QPainter p(ui->widget);
                p.drawPixmap(QPointF(0,0),m_pixmap);
            }
            return true;
        }
    }
    return false;
}



