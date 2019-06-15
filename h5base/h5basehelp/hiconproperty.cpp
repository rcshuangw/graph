#include "hiconproperty.h"
#include "ui_iconproperty.h"
#include "hiconapi.h"
#include <QColorDialog>
#include <QFontDialog>
#include <QVariant>
#include <QFile>
#include <QFileDialog>
#include <math.h>
#include "hline.h"
#include "hrectangle.h"
#include "hellipse.h"
#include "hcircle.h"
#include "htext.h"
#include "harc.h"
#include "hpolygon.h"
#include "hpolyline.h"
#include "hgroup.h"
#include "hiconhelper.h"
HPropertyDlg::HPropertyDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IconProperty)
{
    ui->setupUi(this);

    /*QFile qss(":/qss/propertystylesheet.qss");
    if( qss.open(QFile::ReadOnly))
    {
       qDebug("open success");
       QString style = QLatin1String(qss.readAll());
       setStyleSheet(style);
       qss.close();
    }*/
    //setStyleSheet();
    setWindowTitle(QStringLiteral("test1"));

}

HPropertyDlg::HPropertyDlg(HBaseObj* pObj,QWidget *parent):
    QDialog(parent),ui(new Ui::IconProperty)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    btnGroup = new QButtonGroup;
    pCurObj = pObj;
    connect(ui->okBtn,SIGNAL(clicked(bool)),this,SLOT(ok_clicked()));
    connect(ui->noBtn,SIGNAL(clicked(bool)),this,SLOT(no_clicked()));
    initTab();

//
}


HPropertyDlg::~HPropertyDlg()
{
    delete ui;
}

void HPropertyDlg::setIconObj(HBaseObj* obj)
{
    btnGroup = new QButtonGroup;
    pCurObj = obj;
    connect(ui->okBtn,SIGNAL(clicked(bool)),this,SLOT(ok_clicked()));
    connect(ui->noBtn,SIGNAL(clicked(bool)),this,SLOT(no_clicked()));
    initTab();
}


void HPropertyDlg::initTab()
{
    ui->propertyTab->setMovable(false);
    initTextTab();
    initBaseTab();
    initLineTab();
    initShapeTab();
    DrawShape drawShape = pCurObj->getShapeType();
    ui->verticalLayout_18->setStretch(0,3);
    ui->verticalLayout_18->setStretch(1,3);
    ui->verticalLayout_18->setStretch(2,3);
    ui->verticalLayout_18->setStretch(3,3);
    ui->verticalLayout_18->setStretch(4,1);
    if(drawShape == Text)
    {
        ui->groupBox_2->hide();
        ui->groupBox_8->hide();
        ui->verticalLayout_18->setStretch(0,3);
        ui->verticalLayout_18->setStretch(1,3);
        ui->verticalLayout_18->setStretch(4,7);
    }
    if(drawShape == Line)
    {
        ui->propertyTab->removeTab(1);//文字
        //虽然形状在tab3,但removeTab1之后，tab3就变成tab2
        ui->propertyTab->removeTab(2);//形状
        ui->xCoord_width->setEnabled(false);
        ui->yCoord_height->setEnabled(false);
        ui->groupBox_8->hide();
        ui->groupBox_10->hide();
        ui->verticalLayout_18->setStretch(0,3);
        ui->verticalLayout_18->setStretch(1,3);
        ui->verticalLayout_18->setStretch(4,7);
    }
    else if(drawShape == Rectangle)
    {
        ui->propertyTab->removeTab(1);//文字
        ui->groupBox_2->hide();
        ui->groupBox_8->hide();
        ui->verticalLayout_18->setStretch(0,3);
        ui->verticalLayout_18->setStretch(3,3);
        ui->verticalLayout_18->setStretch(4,7);
    }
    else if(drawShape == Ellipse ||drawShape == Circle || drawShape == Polyline || drawShape == Polygon)
    {
        ui->propertyTab->removeTab(1);//文字
        ui->groupBox_2->hide();
        ui->groupBox_8->hide();
        ui->groupBox_10->hide();
        ui->verticalLayout_18->setStretch(0,3);
        ui->verticalLayout_18->setStretch(4,10);
        //ui->verticalLayout_18->setStretch(4,7);
    }
    else if(drawShape ==Arc )
    {
       ui->propertyTab->removeTab(1);//文字
       ui->groupBox_2->hide();
       ui->groupBox_10->hide();
       ui->verticalLayout_18->setStretch(0,3);
       ui->verticalLayout_18->setStretch(2,3);
       ui->verticalLayout_18->setStretch(4,7);
    }
    else if(drawShape == Group)
    {
        ui->propertyTab->removeTab(3);
        ui->propertyTab->removeTab(2);
        ui->propertyTab->removeTab(1);
    }
}

void HPropertyDlg::initBaseTab()
{

    if(!pCurObj)
        return;
    ui->xCoord->setDecimals(2);
    ui->xCoord->setMinimum(-9999.99);
    ui->xCoord->setMaximum(9999.99);
    ui->yCoord->setDecimals(2);
    ui->yCoord->setMinimum(-9999.99);
    ui->yCoord->setMaximum(9999.99);
    ui->xCoord_width->setMaximum(9999.99);
    ui->yCoord_height->setMaximum(9999.99);

    //角度
    ui->x_rotate->setMinimum(-360);
    ui->x_rotate->setMaximum(360);
    ui->x_rotate->setSuffix(QStringLiteral("°"));
    ui->x_rotate->setValue(0);
    ui->objName->setText("");
    ui->objType->setText("无");

    if(pCurObj)
    {
        QString strObjName = pCurObj->getObjName();
        ui->objName->setText(strObjName);
        ui->x_rotate->setValue(pCurObj->rotateAngle());
        ui->xCoord->setValue(pCurObj->getOX());
        ui->yCoord->setValue(pCurObj->getOY());
        ui->horizontalFlip->setChecked(pCurObj->isHorizonTurn());
        ui->verticalFlip->setChecked(pCurObj->isVerticalTurn());

        if(pCurObj->getShapeType() == Line)
        {
            ui->objType->setText(QStringLiteral("直线"));
            //HLine* pObj = (HLine*)pCurObj;
        }
        else if(pCurObj->getShapeType() == Rectangle)
        {
            ui->objType->setText(QStringLiteral("矩形"));
            HRectangle* pObj = (HRectangle*)pCurObj;

            ui->xCoord_width->setValue(pObj->m_width);
            ui->yCoord_height->setValue(pObj->m_height);
        }
        else if(pCurObj->getShapeType() == Ellipse)
        {
            ui->objType->setText(QStringLiteral("椭圆"));
            HEllipse* pObj = (HEllipse*)pCurObj;

            ui->xCoord_width->setValue(pObj->m_width);
            ui->yCoord_height->setValue(pObj->m_height);
        }
        else if(pCurObj->getShapeType() == Circle)
        {
            ui->objType->setText(QStringLiteral("圆"));
            HCircle* pObj = (HCircle*)pCurObj;

            ui->xCoord_width->setValue(pObj->m_width);
            ui->yCoord_height->setValue(pObj->m_height);
        }
        else if(pCurObj->getShapeType() == Polygon)
        {
            ui->objType->setText(QStringLiteral("多边形"));
            //HPolygon* pObj = (HPolygon*)pCurObj;

            //ui->xCoord_width->setValue(pObj->width);
            //ui->yCoord_height->setValue(pObj->height);
        }
        else if(pCurObj->getShapeType() == Polyline)
        {
            ui->objType->setText(QStringLiteral("折线"));
            //HPolyline* pObj = (HPolyline*)pCurObj;

            //ui->xCoord_width->setValue(pObj->width);
            //ui->yCoord_height->setValue(pObj->height);
        }
        else if(pCurObj->getShapeType() == Arc)
        {
            ui->objType->setText(QStringLiteral("弧线"));
            //HArc* pObj = (HArc*)pCurObj;

            //ui->xCoord_width->setValue(pObj->getRectWidth());
            //ui->yCoord_height->setValue(pObj->getRectHeight());
        }
        else if(pCurObj->getShapeType() == Text)
        {
            ui->objType->setText(QStringLiteral("文字"));
            HText* pObj = (HText*)pCurObj;

            ui->xCoord_width->setValue(pObj->m_width);
            ui->yCoord_height->setValue(pObj->m_height);
        }
        else if(pCurObj->getShapeType() == Group)
        {
            ui->objType->setText(QStringLiteral("组合"));
            HGroup* pObj = (HGroup*)pCurObj;

            ui->xCoord_width->setValue(pObj->m_width);
            ui->yCoord_height->setValue(pObj->m_height);
        }
    }
}

void HPropertyDlg::initTextTab()
{
    connect(ui->textFontBtn,SIGNAL(clicked(bool)),this,SLOT(textFont_clicked()));
    connect(ui->textColorBtn,SIGNAL(clicked(bool)),this,SLOT(textColor_clicked()));

    ui->horizAlignComboBox->clear();
    ui->horizAlignComboBox->addItem(QStringLiteral("左对齐"),Qt::AlignLeft);
    ui->horizAlignComboBox->addItem(QStringLiteral("居中对齐"),Qt::AlignHCenter);
    ui->horizAlignComboBox->addItem(QStringLiteral("右对齐"),Qt::AlignRight);

    ui->vertiAlignComboBox->addItem(QStringLiteral("顶端对齐"),Qt::AlignTop);
    ui->vertiAlignComboBox->addItem(QStringLiteral("垂直居中"),Qt::AlignVCenter);
    ui->vertiAlignComboBox->addItem(QStringLiteral("底部对齐"),Qt::AlignBottom);

    ui->directComboBox->addItem(QStringLiteral("不调整"),0);

    ui->layoutComboBox->addItem(QStringLiteral("空"),LAYOUT_TEXT_NULL);
    ui->layoutComboBox->addItem(QStringLiteral("充满"),LAYOUT_TEXT_FULL);
    //ui->layoutComboBox->addItem(QStringLiteral("横向"),LAYOUT_TEXT_HORIZON);
    //ui->layoutComboBox->addItem(QStringLiteral("纵向"),LAYOUT_TEXT_VERTICAL);

    font.setFamily(QStringLiteral("微软雅黑"));
    font.setPointSize(12);
    ui->textFontBtn->setFont(font);
    ui->textFontBtn->setText(QStringLiteral("示范"));

    strTextColor = "#000000";
    QString strbkColor = QString("background-color:")+ strTextColor;
    ui->textColorBtn->setStyleSheet(strbkColor);

    if(pCurObj)
    {
        DrawShape drawShape = pCurObj->getShapeType();
        if(drawShape == Text)
        {
            HText* pTextObj = (HText*)pCurObj;
            ui->horizAlignComboBox->setCurrentIndex(ui->horizAlignComboBox->findData(pTextObj->horizontalAlign()));
            ui->vertiAlignComboBox->setCurrentIndex(ui->vertiAlignComboBox->findData(pTextObj->verticalAlign()));
            ui->layoutComboBox->setCurrentIndex(ui->layoutComboBox->findData(pTextObj->layout()));
            QString strFontName = pTextObj->fontFamily();
            int pointSize = pTextObj->fontSize();
            int weight = pTextObj->fontWeight();
            bool italic = pTextObj->fontItalic();
            QFont font1(strFontName,pointSize,weight,italic);
            font.setFamily(strFontName);
            font.setPointSize(pointSize);
            font.setWeight(weight);
            font.setItalic(italic);
            ui->textFontBtn->setFont(font);
            ui->textFontBtn->setText(QStringLiteral("示范"));
            strTextColor = pTextObj->getTextColor();
            QString textClr = QString("background-color:")+ strTextColor;
            ui->textColorBtn->setStyleSheet(textClr);

            ui->textEdit->setText(pTextObj->text());
        }
    }
}

void HPropertyDlg::initLineTab()
{
    connect(ui->lineColor,SIGNAL(clicked(bool)),this,SLOT(lineColor_clicked()));
    connect(ui->lineWidth,SIGNAL(currentIndexChanged(int)),this,SLOT(lineWidth_clicked()));
    connect(ui->lineStyle,SIGNAL(currentIndexChanged(int)),this,SLOT(lineStyle_clicked()));
    connect(ui->lineCapStyle,SIGNAL(currentIndexChanged(int)),this,SLOT(lineJoinStyle_clicked()));
    connect(ui->lineStartArrow,SIGNAL(currentIndexChanged(int)),this,SLOT(arrowHead_clicked()));
    connect(ui->lineTailArrow,SIGNAL(currentIndexChanged(int)),this,SLOT(arrowTail_clicked()));
    connect(ui->rectRound,SIGNAL(stateChanged(int)),this,SLOT(round_clicked()));
    //线条颜色
    //QString strLineColor;
    strLineColor = "#FF0000";
    if(pCurObj)
        strLineColor = pCurObj->getLineColor();
    QString strbkColor = QString("background-color:")+ strLineColor;
    ui->lineColor->setStyleSheet(strbkColor);

    //线宽
    HIconHelper::Instance()->InitPenWidthComboBox(ui->lineWidth);
    ui->lineWidth->setCurrentIndex(0);
    if(pCurObj)
    {
        int nLineWidthIndex = ui->lineWidth->findData(pCurObj->getLineWidth());
        ui->lineWidth->setCurrentIndex(nLineWidthIndex);
    }

    //线型
    HIconHelper::Instance()->InitPenStyleComboBox(ui->lineStyle);
    ui->lineStyle->setCurrentIndex(0);
    if(pCurObj)
    {
        int nLineStyleIndex = ui->lineStyle->findData((quint8)pCurObj->getLineStyle());
        ui->lineStyle->setCurrentIndex(nLineStyleIndex);
    }

    //线角
    HIconHelper::Instance()->InitPenCapStyleComboBox(ui->lineCapStyle);
    ui->lineCapStyle->setCurrentIndex(0);

    //箭头部分
    HIconHelper::Instance()->InitArrowStyleComboBox(ui->lineStartArrow,false);
    ui->lineStartArrow->setCurrentIndex(0);

    //尾部箭头部分
    HIconHelper::Instance()->InitArrowStyleComboBox(ui->lineTailArrow,true);
    ui->lineTailArrow->setCurrentIndex(0);

    //角度部分
    ui->startAngle->setMinimum(0);
    ui->startAngle->setMaximum(360);
    ui->startAngle->setSuffix(QStringLiteral("°"));
    ui->startAngle->setValue(30);

    ui->spanAngle->setMinimum(0);
    ui->spanAngle->setMaximum(360);
    ui->spanAngle->setSuffix(QStringLiteral("°"));
    ui->spanAngle->setValue(240);

    //弯曲度
    ui->rectRound->setChecked(false);
    ui->xAxis->setMinimum(0);
    ui->xAxis->setMaximum(100);
    ui->yAxis->setMinimum(0);
    ui->yAxis->setMaximum(100);
    ui->xAxis->setEnabled(false);
    ui->yAxis->setEnabled(false);
    if(pCurObj)
    {
        DrawShape drawShape = pCurObj->getShapeType();
        if(drawShape == Line)
        {
            HLine* pLineObj = (HLine*)pCurObj;
            int curIndex = ui->lineStartArrow->findData(pLineObj->getStartArrowType());
            ui->lineStartArrow->setCurrentIndex(curIndex);
            curIndex = ui->lineTailArrow->findData(pLineObj->getEndArrowType());
            ui->lineTailArrow->setCurrentIndex(curIndex);
            int w = pLineObj->getArrowWidth();
            int h = pLineObj->getArrowHeight();
            ui->arrowWidth->setValue(w);
            ui->arrowHeight->setValue(h);
        }
        else if(drawShape == Arc)
        {
            HArc* pArcObj = (HArc*)pCurObj;
            ui->startAngle->setValue(pArcObj->startAngle());
            ui->spanAngle->setValue(pArcObj->sweepLength());
        }
        else if(Rectangle == drawShape || Ellipse == drawShape || Circle == drawShape || Text == drawShape )
        {
            HRectangle* pRectObj = (HRectangle*)pCurObj;
            bool bRound = pRectObj->isRound();
            ui->rectRound->setChecked(bRound);
            if(bRound)
            {
                ui->xAxis->setEnabled(true);
                ui->yAxis->setEnabled(true);
                ui->xAxis->setValue(pRectObj->getXAxis());
                ui->yAxis->setValue(pRectObj->getYAxis());
            }
        }
    }
}

void HPropertyDlg::initShapeTab()
{
    connect(ui->transSlider,SIGNAL(valueChanged(int)),ui->transSpix,SLOT(setValue(int)));
    connect(ui->transSpix,SIGNAL(valueChanged(int)),ui->transSlider,SLOT(setValue(int)));
    connect(ui->fillStyle,SIGNAL(currentIndexChanged(int)),this,SLOT(fillStyle_clicked()));
    connect(ui->fillColor,SIGNAL(clicked(bool)),this,SLOT(fillColor_clicked()));
    connect(ui->fillDirection,SIGNAL(currentIndexChanged(int)),this,SLOT(fillDirection_clicked()));
    connect(ui->fillPercentage,SIGNAL(valueChanged(int)),this,SLOT(fillPercentage_clicked()));
    connect(btnGroup,SIGNAL(buttonClicked(int)),this,SLOT(btnGroup_clicked(int)));
    connect(ui->picBtn,SIGNAL(clicked(bool)),this,SLOT(picBtn_clicked()));
    //边框可见
    ui->frameSee->setChecked(true);

    //填充方式
    btnGroup->addButton(ui->noFill,0);
    btnGroup->addButton(ui->colorFill,1);
    btnGroup->addButton(ui->imageFill,2);
    ui->noFill->setChecked(true);

    //透明度
    ui->transSlider->setMinimum(0);
    ui->transSlider->setMaximum(100);
    ui->transSpix->setSuffix("%");
    ui->transSpix->setMinimum(0);
    ui->transSpix->setMaximum(100);
    ui->transSlider->setValue(0);

    //填充方式
    HIconHelper::Instance()->InitBrushStyleComboBox(ui->fillStyle);

    //填充颜色
    //QString strFillColor;
    strFillColor = "#FF0000";

    //填充比例
    ui->fillPercentage->setSuffix("%");
    ui->fillPercentage->setMinimum(0);
    ui->fillPercentage->setMaximum(100);
    ui->fillPercentage->setValue(100);

    //填充方向
    //ui->fillDirection->addItem(QStringLiteral("无方向"),0);
    ui->fillDirection->addItem(QStringLiteral("由底到顶"),DIRECT_BOTTOM_TO_TOP);
    ui->fillDirection->addItem(QStringLiteral("由顶到底"),DIRECT_TOP_TO_BOTTOM);
    ui->fillDirection->addItem(QStringLiteral("由左到右"),DIRECT_LEFT_TO_RIGHT);
    ui->fillDirection->addItem(QStringLiteral("由右到左"),DIRECT_RIGHT_TO_LEFT);
    ui->fillDirection->addItem(QStringLiteral("垂直到外"),DIRECT_VER_TO_OUT);
    ui->fillDirection->addItem(QStringLiteral("水平到外"),DIRECT_HORi_TO_OUT);
    ui->fillDirection->addItem(QStringLiteral("垂直到里"),DIRECT_VER_TO_IN);
    ui->fillDirection->addItem(QStringLiteral("水平到里"),DIRECT_HORI_TO_IN);
    ui->fillDirection->setEnabled(false);

    ui->alignPicCombo->addItem(QStringLiteral("左"),0);
    ui->alignPicCombo->addItem(QStringLiteral("中"),1);
    ui->alignPicCombo->addItem(QStringLiteral("右"),2);
    ui->keepPicCheck->setChecked(false);
    ui->alignPicCombo->setEnabled(false);
    //实际显示
    if(pCurObj)
    {
        DrawShape drawShape = pCurObj->getShapeType();
        if(Rectangle == drawShape || Ellipse == drawShape || Circle == drawShape || Polygon == drawShape || Text == drawShape)
        {
            HShapeObj* pObj = (HShapeObj*)pCurObj;
            ui->frameSee->setChecked(pObj->getFrameSee());
            quint8 id = pObj->getFillWay();
            if(id == 0)
                ui->noFill->setChecked(true);
            else if(id == 1)
                ui->colorFill->setChecked(true);
            else if(id == 2)
                ui->imageFill->setChecked(true);
            emit btnGroup->buttonClicked(id);

            ui->transSlider->setValue(pObj->getTransparency());
            int nFillStyle = ui->fillStyle->findData(int(pObj->getFillStyle()));
            ui->fillStyle->setCurrentIndex(nFillStyle);

            strFillColor = pObj->getFillColor();
            QString strbgColor = QString("background-color:")+ strFillColor;
            ui->fillColor->setStyleSheet(strbgColor);
            ui->fillPercentage->setValue(pObj->getFillPercentage());
            if(nFillStyle == Qt::LinearGradientPattern)
            {
                ui->fillDirection->setEnabled(true);
                int nFillDirect = ui->fillDirection->findData(pObj->getFillDirection());
                ui->fillDirection->setCurrentIndex(nFillDirect);
            }

            //图片部分
            ui->picLineEdit->setText(pObj->getBkImagePath());
            ui->keepPicCheck->setChecked(pObj->getKeepImageRatio());
            if(pObj->getKeepImageRatio())
            {
                ui->alignPicCombo->setEnabled(true);
                ui->alignPicCombo->setCurrentIndex(ui->alignPicCombo->findData(pObj->getImageDirect()));
            }
        }
    }
}




//线条颜色
void HPropertyDlg::lineColor_clicked()
{
    QColor curColor = QColor(Qt::white);
    if(pCurObj)
    {
        strLineColor = pCurObj->getLineColor();
        curColor = QColor(strLineColor);
    }
    const QColor color = QColorDialog::getColor(curColor, this, QStringLiteral("选择颜色"));
    if(!color.isValid()) return;
    strLineColor = color.name(QColor::HexRgb);
    ui->lineColor->setStyleSheet(QString("background-color:")+strLineColor);
}

void HPropertyDlg::ok_clicked()
{
    DrawShape drawShape = pCurObj->getShapeType();
    pCurObj->setLineColor(strLineColor);
    pCurObj->setLineWidth(ui->lineWidth->currentData().toUInt());
    pCurObj->setLineStyle(Qt::PenStyle(ui->lineStyle->currentData().toInt()));
    pCurObj->setLineCapStyle(Qt::PenCapStyle(ui->lineCapStyle->currentData().toInt()));
    bool bHTurn = false;
    bool bVTurn = false;
    if(ui->verticalFlip->checkState() == Qt::Checked)
    {
        bVTurn = true;
    }
    if(ui->horizontalFlip->checkState() == Qt::Checked)
    {
        bHTurn = true;
    }
    pCurObj->turn(bHTurn,bVTurn);
    bool bFrameSee = false;
    if(ui->frameSee->checkState() == Qt::Checked)
        bFrameSee = true;

    if(drawShape == Line)
    {
        HLine* pLineObj = (HLine*)pCurObj;
        pLineObj->setOX(ui->xCoord->value());
        pLineObj->setOY(ui->yCoord->value());
        pLineObj->setStartArrowType(ui->lineStartArrow->currentData().toUInt());
        pLineObj->setEndArrowType(ui->lineTailArrow->currentData().toUInt());
        pLineObj->setArrowWidth(ui->arrowWidth->value());
        pLineObj->setArrowHeight(ui->arrowHeight->value());
    }
    else if(drawShape == Arc)
    {
        HArc* pArcObj = (HArc*)pCurObj;
        pArcObj->setStartAngle(ui->startAngle->value());
        pArcObj->setSweepLength(ui->spanAngle->value());
    }
    else if(drawShape == Polyline)
    {

    }
    else
    {
        HShapeObj* pShapeObj = (HShapeObj*)pCurObj;
        pShapeObj->setOX(ui->xCoord->value());
        pShapeObj->setOY(ui->yCoord->value());
        pShapeObj->resize(ui->xCoord_width->value(),ui->yCoord_height->value());
        pShapeObj->setFrameSee(bFrameSee);
        pShapeObj->setFillWay(btnGroup->checkedId());
        pShapeObj->setTransparency(ui->transSlider->value());
        pShapeObj->setFillPercentage(ui->fillPercentage->value());
        pShapeObj->setFillStyle((Qt::BrushStyle)ui->fillStyle->currentData().toUInt());
        pShapeObj->setFillColor(strFillColor);
        pShapeObj->setFillDirection(ui->fillDirection->currentData().toUInt());
        pShapeObj->rotate(ui->x_rotate->value());
        bool bRound = false;
        if(ui->rectRound->checkState() == Qt::Checked)
            bRound = true;
        if(btnGroup->checkedId() == 1)//当前是颜色填充就不能用画面填充，当前是图片填充且如果两种填充都有画面填充优于颜色填充
            pShapeObj->setBkImagePath("");
        else
            pShapeObj->setBkImagePath(ui->picLineEdit->text());
        bool bKeep = false;
        if(ui->keepPicCheck->checkState() == Qt::Checked)
            bKeep = true;
        pShapeObj->setKeepImageRatio(bKeep);
        pShapeObj->setImageDirect(ui->alignPicCombo->currentData().toUInt());
        if(drawShape == Rectangle || drawShape == Circle || drawShape == Ellipse || drawShape == Polygon)
        {
            HRectangle* pObj = (HRectangle*)pCurObj;
            pObj->setRound(bRound);
            pObj->setXAxis(ui->xAxis->value());
            pObj->setYAxis(ui->yAxis->value());
        }
        else if(drawShape == Text)
        {
            HText *pTextObj = (HText*)pCurObj;
            pTextObj->setRound(bRound);
            pTextObj->setXAxis(ui->xAxis->value());
            pTextObj->setYAxis(ui->yAxis->value());
            pTextObj->setHorizontalAlign(ui->horizAlignComboBox->currentData().toInt());
            pTextObj->setVerticalAlign(ui->vertiAlignComboBox->currentData().toInt());
            pTextObj->setLayout(ui->layoutComboBox->currentData().toUInt());
            pTextObj->setFontFamily(font.family());
            pTextObj->setFontSize(font.pointSize());
            pTextObj->setFontWeight(font.weight());
            pTextObj->setFontItalic(font.italic());
           pTextObj->setTextColor(strTextColor);
            pTextObj->setText(ui->textEdit->text());
        }
    }
    pCurObj->setModify(true);

    QDialog::accept();
}

void HPropertyDlg::no_clicked()
{
    QDialog::reject();
}

void HPropertyDlg::btnGroup_clicked(int id)
{
    ui->verticalLayout_18->setStretch(0,3);
    ui->verticalLayout_18->setStretch(1,2);
    ui->verticalLayout_18->setStretch(2,3);
    ui->verticalLayout_18->setStretch(3,3);
    ui->verticalLayout_18->setStretch(4,1);
    if(id == 0)
    {
        ui->groupBox_6->setVisible(false);
        ui->groupBox_7->setVisible(false);
        ui->groupBox_12->setVisible(false);
        ui->verticalLayout_18->setStretch(0,3);
        ui->verticalLayout_18->setStretch(4,9);
    }
    else if(id == 1)//图片填充
    {
        ui->groupBox_6->setVisible(true);
        ui->groupBox_7->setVisible(true);
        ui->groupBox_12->setVisible(false);
        ui->verticalLayout_18->setStretch(0,3);
        ui->verticalLayout_18->setStretch(1,2);
        ui->verticalLayout_18->setStretch(2,3);
        ui->verticalLayout_18->setStretch(4,4);
    }
    else if(id == 2)
    {
        ui->groupBox_6->setVisible(true);
        ui->groupBox_7->setVisible(false);
        ui->groupBox_12->setVisible(true);
        ui->verticalLayout_18->setStretch(0,3);
        ui->verticalLayout_18->setStretch(1,2);
        ui->verticalLayout_18->setStretch(3,3);
        ui->verticalLayout_18->setStretch(4,4);
    }
}

void HPropertyDlg::lineWidth_clicked()
{

}

void HPropertyDlg::lineStyle_clicked()
{

}

void HPropertyDlg::lineJoinStyle_clicked()
{

}

void HPropertyDlg::frameSee_clicked()
{

}

void HPropertyDlg::fillWay_clicked()
{
    if(ui->noFill->isChecked())
    {
        ui->groupBox_6->setVisible(false);
        ui->groupBox_7->setVisible(false);
        ui->groupBox_12->setVisible(false);
    }
}

void HPropertyDlg::fillStyle_clicked()
{
    int nCurrentIndex = ui->fillStyle->currentIndex();
    int nFillStyle = ui->fillStyle->itemData(nCurrentIndex).toInt();
    if(nFillStyle == Qt::LinearGradientPattern)
    {
        HShapeObj* pObj = (HShapeObj*)pCurObj;
        ui->fillDirection->setEnabled(true);
        int nFillDirect = ui->fillDirection->findData(pObj->getFillDirection());
        ui->fillDirection->setCurrentIndex(nFillDirect);
    }
    else
    {
        ui->fillDirection->setCurrentIndex(0);
        ui->fillDirection->setEnabled(false);
    }
}

void HPropertyDlg::fillColor_clicked()
{
    QColor curColor = QColor(Qt::white);
    if(pCurObj)
    {
        HShapeObj* pObj = (HShapeObj*)pCurObj;
        strFillColor = pObj->getFillColor();
        curColor = QColor(strFillColor);
    }
    const QColor color = QColorDialog::getColor(curColor, this, QStringLiteral("选择颜色"));
    if(!color.isValid()) return;
    strFillColor = color.name(QColor::HexRgb);
    ui->fillColor->setStyleSheet(QString("background-color:")+strFillColor);
}

void HPropertyDlg::fillDirection_clicked()
{

}

void HPropertyDlg::fillPercentage_clicked()
{

}

void HPropertyDlg::transSlider_clicked()
{

}

void HPropertyDlg::transSpix_clicked()
{

}

void HPropertyDlg::arrowHead_clicked()
{
    int nStartIndex = ui->lineStartArrow->currentIndex();
    int nEndIndex = ui->lineTailArrow->currentIndex();
    if(nStartIndex == 0 && nEndIndex == 0)
    {
        ui->arrowWidth->setEnabled(false);
        ui->arrowHeight->setEnabled(false);
    }
    else
    {
        ui->arrowWidth->setEnabled(true);
        ui->arrowHeight->setEnabled(true);
    }
}

void HPropertyDlg::arrowTail_clicked()
{
    int nStartIndex = ui->lineStartArrow->currentIndex();
    int nEndIndex = ui->lineTailArrow->currentIndex();
    if(nStartIndex == 0 && nEndIndex == 0)
    {
        ui->arrowWidth->setEnabled(false);
        ui->arrowHeight->setEnabled(false);
    }
    else
    {
        ui->arrowWidth->setEnabled(true);
        ui->arrowHeight->setEnabled(true);
    }
}

void HPropertyDlg::textColor_clicked()
{
    QColor curColor = QColor(strTextColor);
    const QColor color = QColorDialog::getColor(curColor, this, QStringLiteral("选择颜色"));
    if(!color.isValid()) return;
    strTextColor = color.name(QColor::HexRgb);
    ui->textColorBtn->setStyleSheet(QString("background-color:")+strTextColor);
}

void HPropertyDlg::textFont_clicked()
{
    bool ok;
    QFont newFont = QFontDialog::getFont(&ok,font,this,QStringLiteral("选择字体"));
    if(ok)
    {
        font = newFont;
        ui->textFontBtn->setFont(font);
        ui->textFontBtn->setText(QStringLiteral("示范"));
    }
}

void HPropertyDlg::round_clicked()
{
    if(!ui->rectRound->isChecked())
    {
        ui->xAxis->setEnabled(false);
        ui->yAxis->setEnabled(false);
    }
    else
    {
        ui->xAxis->setEnabled(true);
        ui->yAxis->setEnabled(true);
    }
}

void HPropertyDlg::xAxis_clicked()
{

}

void HPropertyDlg::yAxis_clicked()
{

}

void HPropertyDlg::picBtn_clicked()
{
    static QString path;

    QString fileName = QFileDialog::getOpenFileName(this,QStringLiteral("打开图片"),path,"Images(*.png *.jpg *.bmp)",NULL,    QFileDialog::DontUseNativeDialog);
    if(!fileName.isEmpty() || !fileName.isNull())
    {
        ui->picLineEdit->setText(fileName);
        //画面路径要保存
    }
}
