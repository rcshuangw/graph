#include "hiconhelper.h"
#include <QProcessEnvironment>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include "hbaseobj.h"
#include "hicontemplate.h"
#include "hiconobj.h"
#include "hline.h"
#include "hrectangle.h"
#include "hellipse.h"
#include "hcircle.h"
#include "htext.h"
#include "hpolygon.h"
#include "hpolyline.h"
#include "hgroup.h"
#include "htempcontainer.h"
#include "../../include/hfileapi.h"
HIconHelper::HIconHelper()
{

}

HIconHelper* HIconHelper::m_pInstance = NULL;

HIconHelper* HIconHelper::Instance()
{
    if(!m_pInstance)
    {
        m_pInstance = new HIconHelper();
    }
    return m_pInstance;
}

//根据uuid找到template,然后根据nCurPattern找到对应的icon
//注意此种方式不能立即刷新
QPixmap HIconHelper::iconPixmap(const QString& strType,const QString& uuid,const QSizeF& ratioSizeF,int nCurPattern)
{
    HIconTemplate* pIconTemplate = new HIconTemplate(QString());
    Q_ASSERT( pIconTemplate );

    char szIconPath[128];
    getDataFilePath(DFPATH_ICON,szIconPath);
    QString iconsPath = QString(szIconPath);
    //QString iconsPath = getenv("wfsystem_dir");
    // iconsPath = iconsPath + "/" + "icon";//QString(szIconPath);
    QString path = iconsPath +"/" + strType + "/" + uuid + ".xic";
    if ( uuid.isEmpty() && strType.contains(".xic") )
    {
        path = strType;
    }
    pIconTemplate->readXml(path);

    QSizeF defalultSize = QSizeF(50,50);//pIconTemplate->getDefaultSize();
    QImage image(defalultSize.width()+1,defalultSize.height(),QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    //painter设置
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing,true);

    //创建iconObj
    HIconObj* pObj = new HIconObj(pIconTemplate);
    if(!pObj->iconSymbol() || pObj->iconSymbol()->getMaxPattern() <= nCurPattern)
        return QPixmap();
    pObj->iconSymbol()->setCurrentPattern(0);

    //设置图符大小和绘制信息
    QPolygonF points;
    points<<QPointF(0,0)<<QPointF(defalultSize.width(),defalultSize.height());
    //pObj->setPointList(points);
    pObj->resize(defalultSize.width(),defalultSize.height());
    pObj->move(points.boundingRect().width()/2,points.boundingRect().height()/2);
    painter.translate(defalultSize.width()/2,defalultSize.height()/2);
    pObj->paint(&painter);
    delete pObj;
    if(!pIconTemplate)
    {
        delete pIconTemplate;
        pIconTemplate = NULL;
    }

    return QPixmap().fromImage(image);
}


void HIconHelper::loadIconDoucument(QList<HIconTemplate*> *pIconTemplateList)
{
    //先找路径，在找文件夹，然后文件夹里面搜索添加完成
    if(NULL == pIconTemplateList)
        return;
    char szIconPath[128];
    memset(szIconPath,0,128);
    getDataFilePath(DFPATH_ICON,szIconPath);
    QString iconsPath = QString(szIconPath);
    //QString iconsPath = getenv("wfsystem_dir");
    // iconsPath = iconsPath + "/" + "icon";//QString(szIconPath);

    QDir dirIconsPath(iconsPath);
    if(!dirIconsPath.exists())
        return;
    QFileInfoList iconsFileInfoList = dirIconsPath.entryInfoList(QDir::Dirs  | QDir::NoDotAndDotDot);
    foreach(QFileInfo info,iconsFileInfoList)
    {
        if(info.isFile())continue;
        QString strChildFilePath = iconsPath + "/" + info.fileName();
        loadIconTemplateFile(pIconTemplateList,strChildFilePath);
    }
}

void HIconHelper::loadIconTemplateFile(QList<HIconTemplate*> *pIconTemplateList,QString strIconsPath)//加载所有的模板文件
{
    //先找路径，在找文件夹，然后文件夹里面搜索添加完成
    QDir dirIconsFilePath(strIconsPath);
    if(!dirIconsFilePath.exists())
        return;
    QStringList filters;
    filters<<"*.xic";
    dirIconsFilePath.setNameFilters(filters);
    QFileInfoList iconsFileInfoList = dirIconsFilePath.entryInfoList(QDir::Files);
    foreach(QFileInfo info,iconsFileInfoList)
    {
        if(!info.isFile())continue;
        QString strIconTemplateFile = strIconsPath + "/" + info.fileName();
        QUuid uuid = QUuid(info.fileName());
        HIconTemplate *pIconTemplate = new HIconTemplate(uuid);
        if(!pIconTemplate) continue;
        pIconTemplate->readXml(strIconTemplateFile);
        pIconTemplateList->append(pIconTemplate);
    }
}


void HIconHelper::saveIconDoucument(QList<HIconTemplate*> *pIconTemplateList)
{
    if(NULL == pIconTemplateList)
        return;

    char szIconPath[128];
    memset(szIconPath,0,128);
    getDataFilePath(DFPATH_ICON,szIconPath);
    QString iconsPath = QString(szIconPath);
    //QString iconsPath = getenv("wfsystem_dir");
    // iconsPath = iconsPath + "/" + "icon";//QString(szIconPath);
    QDir dirIconsPath(iconsPath);
    if(!dirIconsPath.exists())
        dirIconsPath.mkdir(iconsPath);
    //获取遥信，遥测，遥调等文件夹
    QFileInfoList iconsFileInfoList = dirIconsPath.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    foreach(QFileInfo info,iconsFileInfoList)
    {
        if(info.isFile())continue;
        saveIconTemplateFile(pIconTemplateList,iconsPath,info.fileName());
    }
}

void HIconHelper::saveIconTemplateFile(QList<HIconTemplate*> *pIconTemplateList,const QString& strIconsPath,const QString& strFolderName)//保存所有的模板文件
{
    QDir dirIconsFilePath(strIconsPath);
    if(!dirIconsFilePath.exists())
        return;

    QString strIconsFolderPath = strIconsPath + "/" + strFolderName;
    for(int i = 0; i < pIconTemplateList->count();i++)
    {
        HIconTemplate* iconTemplate = pIconTemplateList->at(i);
        if(!iconTemplate || !iconTemplate->isModify()) continue;
        if(IsIconInFolder(strFolderName,iconTemplate->getCatalogType()))
        {
            QString strFileName = strIconsFolderPath + "/" + iconTemplate->getUuid().toString() + ".xic";
            //如果有文件存在 就删除
            if(QFile::exists(strFileName))
            {
                QFile::remove(strFileName);
            }
            iconTemplate->writeXml(strFileName);

        }
        else
        {
           // QString strWarning = QStringLiteral("没有找到")+iconTemplate->getCatalogName()+QStringLiteral("文件夹!");
           // QMessageBox::warning(NULL,"warning",strWarning);
        }
    }
}


bool HIconHelper::IsIconInFolder(const QString& strFolderName,const int nIconType)
{
    bool bIn = false;
    if((strFolderName == "digital"||strFolderName == QStringLiteral("遥信")) && nIconType == TEMPLATE_TYPE_DIGITAL)
        bIn = true;
    else if((strFolderName == "analogue"||strFolderName == QStringLiteral("遥测")) && nIconType == TEMPLATE_TYPE_ANALOGUE)
        bIn = true;
    else if((strFolderName == "relay"||strFolderName == QStringLiteral("遥控")) && nIconType == TEMPLATE_TYPE_RELAY)
        bIn = true;
    else if((strFolderName == "pluse"||strFolderName == QStringLiteral("遥脉")) && nIconType == TEMPLATE_TYPE_PLUSE)
        bIn = true;
    else if((strFolderName == "tap"||strFolderName == QStringLiteral("档位")) && nIconType == TEMPLATE_TYPE_TAP)
        bIn = true;
    else if((strFolderName == "light"||strFolderName == QStringLiteral("光字牌")) && nIconType == TEMPLATE_TYPE_LIGHT)
        bIn = true;
    else if((strFolderName == "jdpai"||strFolderName == QStringLiteral("接地牌")) && nIconType == TEMPLATE_TYPE_JDPAI)
        bIn = true;
    else if((strFolderName == "control"||strFolderName == QStringLiteral("控制点")) && nIconType == TEMPLATE_TYPE_CONTROL)
        bIn = true;
    else if((strFolderName == "transform2"||strFolderName == QStringLiteral("两卷变")) && nIconType == TEMPLATE_TYPE_TRANSFORMER2)
        bIn = true;
    else if((strFolderName == "transform3"||strFolderName == QStringLiteral("三卷变")) && nIconType == TEMPLATE_TYPE_TRANSFORMER3)
        bIn = true;
    else if((strFolderName == "generator"||strFolderName == QStringLiteral("发电机")) && nIconType == TEMPLATE_TYPE_GENERATOR)
        bIn = true;
    else if((strFolderName == "capacitor"||strFolderName == QStringLiteral("电容器")) && nIconType == TEMPLATE_TYPE_CAPACITOR)
        bIn = true;
    else if((strFolderName == "otherdevice"||strFolderName == QStringLiteral("其他设备")) && nIconType == TEMPLATE_TYPE_OTHERDEVICE)
        bIn = true;
    else if((strFolderName == "pt"||strFolderName == QStringLiteral("电压互感器")) && nIconType == TEMPLATE_TYPE_PT)
        bIn = true;
    else if((strFolderName == "ct"||strFolderName == QStringLiteral("电流互感器")) && nIconType == TEMPLATE_TYPE_CT)
        bIn = true;
    else if((strFolderName == "arrester"||strFolderName == QStringLiteral("避雷器")) && nIconType == TEMPLATE_TYPE_ARRESTER)
        bIn = true;
    else if((strFolderName == "reactor"||strFolderName == QStringLiteral("容抗器")) && nIconType == TEMPLATE_TYPE_REACTOR)
        bIn = true;
    else if((strFolderName == "other"||strFolderName == QStringLiteral("其他")) && nIconType == TEMPLATE_TYPE_OTHER)
        bIn = true;
    return bIn;
}

QString HIconHelper::getIconFolder(int nType)
{
    QString strFolderName;
    if(nType == TEMPLATE_TYPE_DIGITAL)
        strFolderName = QStringLiteral("遥信");
    else if(nType == TEMPLATE_TYPE_ANALOGUE)
        strFolderName = QStringLiteral("遥测");
    else if(nType == TEMPLATE_TYPE_RELAY)
        strFolderName =QStringLiteral("遥控");
    else if( nType == TEMPLATE_TYPE_PLUSE)
        strFolderName = QStringLiteral("遥脉");
    else if(nType == TEMPLATE_TYPE_TAP)
        strFolderName = QStringLiteral("档位");
    else if(nType == TEMPLATE_TYPE_LIGHT)
        strFolderName = QStringLiteral("光字牌");
    else if(nType == TEMPLATE_TYPE_JDPAI)
        strFolderName = QStringLiteral("接地牌");
    else if(nType == TEMPLATE_TYPE_CONTROL)
        strFolderName = QStringLiteral("控制点");
    else if(nType == TEMPLATE_TYPE_TRANSFORMER2)
        strFolderName = QStringLiteral("两卷变");
    else if(nType == TEMPLATE_TYPE_TRANSFORMER3)
        strFolderName = QStringLiteral("三卷变");
    else if(nType == TEMPLATE_TYPE_GENERATOR)
        strFolderName = QStringLiteral("发电机");
    else if(nType == TEMPLATE_TYPE_CAPACITOR)
        strFolderName = QStringLiteral("电容器");
    else if(nType == TEMPLATE_TYPE_OTHERDEVICE)
        strFolderName = QStringLiteral("其他设备");
    else if(nType == TEMPLATE_TYPE_PT)
        strFolderName = QStringLiteral("电压互感器");
    else if(nType == TEMPLATE_TYPE_CT)
        strFolderName = QStringLiteral("电流互感器");
    else if(nType == TEMPLATE_TYPE_ARRESTER)
        strFolderName = QStringLiteral("避雷器");
    else if(nType == TEMPLATE_TYPE_REACTOR)
        strFolderName = QStringLiteral("容抗器");
    else if(nType == TEMPLATE_TYPE_OTHER)
        strFolderName = QStringLiteral("其他");
    return strFolderName;
}


QIcon HIconHelper::createPenorBrushColorIcon(const QIcon& icon,const QColor& clr)
{
    QPixmap pix = icon.pixmap(icon.actualSize(QSize(32, 32)));
    QPainter p(&pix);
    p.setPen(Qt::NoPen);
    p.setBrush(clr);
    p.drawRect(0, 22, 32, 9);
    return QIcon(pix);
}

void HIconHelper::InitPenWidthComboBox(QComboBox* comboBox)
{
    if(!comboBox)
        return;
    comboBox->clear();
    comboBox->setIconSize(QSize(32,16));
    QStringList strLineWidthList;
    strLineWidthList<<"0"<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10"<<"11"<<"12";
    for(int i = 0; i < strLineWidthList.count();i++)
        comboBox->addItem(createPenWidthIcon(strLineWidthList[i].toInt()),strLineWidthList[i],strLineWidthList[i].toInt());
}

void HIconHelper::InitPenStyleComboBox(QComboBox* comboBox)
{
    if(!comboBox)
        return;
    comboBox->clear();
    comboBox->setIconSize(QSize(30,16));
    QStringList strLineStyleList;
    strLineStyleList<<QStringLiteral("实线")<<QStringLiteral("虚线")<<QStringLiteral("点线")
                   <<QStringLiteral("点-虚线")<<QStringLiteral("点-点-虚线");
    for(int i = 0; i < strLineStyleList.count();i++)
    {
        int penStyle = Qt::PenStyle(i+1);
        comboBox->addItem(createPenStyleIcon(Qt::PenStyle(i+1)),strLineStyleList[i],penStyle);
    }
}

void HIconHelper::InitPenCapStyleComboBox(QComboBox* comboBox)
{
    if(!comboBox)
        return;
    comboBox->addItem(createPenCapStyleIcon(Qt::FlatCap),QStringLiteral("平角"),Qt::FlatCap);
    comboBox->addItem(createPenCapStyleIcon(Qt::SquareCap),QStringLiteral("方角"),Qt::SquareCap);
    comboBox->addItem(createPenCapStyleIcon(Qt::RoundCap),QStringLiteral("圆角"),Qt::RoundCap);
}

void HIconHelper::InitBrushStyleComboBox(QComboBox* comboBox)
{
    if(!comboBox)
        return;
    comboBox->clear();
    comboBox->setIconSize(QSize(30,16));
    QStringList fillStyleList;
    fillStyleList<<QStringLiteral("无填充")<<QStringLiteral("实填充")<<QStringLiteral("密度1")<<QStringLiteral("密度2")
                 <<QStringLiteral("密度3")<<QStringLiteral("密度4")<<QStringLiteral("密度5")<<QStringLiteral("密度6")
                 <<QStringLiteral("密度7")<<QStringLiteral("水平线")<<QStringLiteral("垂直线")<<QStringLiteral("横平竖直线")
                 <<QStringLiteral("斜线")<<QStringLiteral("反斜线")<<QStringLiteral("交叉斜线")<<QStringLiteral("线性渐变")
                 <<QStringLiteral("径向渐变")<<QStringLiteral("锥形渐变");

    for(int i = 0; i < fillStyleList.count();i++)
    {
        int brushStyle = Qt::BrushStyle(i);
        comboBox->addItem(createBrushStyleIcon(Qt::BrushStyle(i)),fillStyleList[i],brushStyle);
    }
}

void HIconHelper::InitArrowStyleComboBox(QComboBox* comboBox,bool head)
{
    if(!comboBox)
        return;
    comboBox->addItem(createArrowIcon(0,head),QStringLiteral("无箭头"),0);
    comboBox->addItem(createArrowIcon(1,head),QStringLiteral("箭头"),1);
    comboBox->addItem(createArrowIcon(2,head),QStringLiteral("空心三角"),2);
    comboBox->addItem(createArrowIcon(3,head),QStringLiteral("实心三角"),3);
}

QIcon HIconHelper::createPenWidthIcon(int width)
{
    QPixmap pixmap(30,16);
    QPainter painter(&pixmap);
    painter.fillRect(QRect(0,0,30,16),Qt::white);
    QPen pen;
    pen.setWidthF(width);
    painter.setPen(pen);
    painter.drawLine(0,8,30,8);
    return QIcon(pixmap);
}

QIcon HIconHelper::createPenStyleIcon(Qt::PenStyle style)
{
    QPixmap pixmap(30,16);
    QPainter painter(&pixmap);
    painter.fillRect(QRect(0,0,30,16),Qt::white);
    QPen pen;
    pen.setStyle(style);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawLine(0,8,30,8);

    return QIcon(pixmap);
}


QIcon HIconHelper::createPenCapStyleIcon(Qt::PenCapStyle capStyle)
{
    QPixmap pixmap(30,16);
    QPainter painter(&pixmap);
    painter.fillRect(QRect(0,0,30,16),Qt::white);
    QPen pen(capStyle);
    pen.setWidth(5);
    pen.setCapStyle(capStyle);
    painter.setPen(pen);
    painter.drawLine(5,8,25,8);

    return QIcon(pixmap);
}

QIcon HIconHelper::createBrushStyleIcon(Qt::BrushStyle brushStyle)
{
    QPixmap pixmap(30,16);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);
    if(brushStyle == Qt::LinearGradientPattern)
    {
        QLinearGradient linearGradient(0,0,30,16);
        linearGradient.setColorAt(0.0,Qt::white);
        linearGradient.setColorAt(1.0,Qt::black);
        painter.setBrush(linearGradient);
    }
    else if(brushStyle == Qt::RadialGradientPattern)
    {
        QRadialGradient radialGradient(15,8,30,15,8);
        radialGradient.setColorAt(0.0,Qt::white);
        radialGradient.setColorAt(1.0,Qt::black);
        painter.setBrush(radialGradient);
    }
    else if(brushStyle == Qt::ConicalGradientPattern)
    {
        QConicalGradient conicalGradient(15,8,0);
        conicalGradient.setColorAt(0.0,Qt::white);
        conicalGradient.setColorAt(1.0,Qt::black);
        painter.setBrush(conicalGradient);
    }
    else
        painter.setBrush(brushStyle);
    painter.drawRect(0,0,29,15);
    return QIcon(pixmap);
}

//箭头
QIcon HIconHelper::createArrowIcon(quint8 style,bool head)
{
    QPixmap pixmap(30,16);
    QPainter painter(&pixmap);
    painter.fillRect(QRect(0,0,30,16),Qt::white);
    painter.setRenderHint(QPainter::Antialiasing,true);
    QPoint arrowStart(2,8);
    QPoint arrowEnd(28,8);
    QLine line(arrowStart,arrowEnd);
    int len = 5;
    switch(style)
    {
    case 0:
     {
        painter.drawLine(line);
        break;
     }
    case 1: //单箭头
     {
        painter.drawLine(arrowStart,arrowEnd);
        painter.drawLine(arrowStart,QPoint(arrowStart.x()+2*len,arrowStart.y()-len));
        painter.drawLine(arrowStart,QPoint(arrowStart.x()+2*len,arrowStart.y()+len));
        break;
     }
    case 2: //空心箭头
     {
        painter.drawLine(QPoint(arrowStart.x()+2*len,arrowStart.y()),arrowEnd);
        painter.drawLine(arrowStart,QPoint(arrowStart.x()+2*len,arrowStart.y()-len));
        painter.drawLine(arrowStart,QPoint(arrowStart.x()+2*len,arrowStart.y()+len));
        painter.drawLine(QPoint(arrowStart.x()+2*len,arrowStart.y()-len),QPoint(arrowStart.x()+2*len,arrowStart.y()+len));
        break;
     }
    case 3: //实心箭头
     {
        painter.drawLine(arrowStart,arrowEnd);
        QPolygon points;
        points.append(arrowStart);
        points.append(QPoint(arrowStart.x()+2*len,arrowStart.y()-len));
        points.append(QPoint(arrowStart.x()+2*len,arrowStart.y()+len));
        painter.save();
        painter.setBrush(Qt::black);
        painter.drawPolygon(points);
        painter.restore();
        break;
     }
    }
    if(head)
    {
        QTransform matrix;
        matrix.scale(-1,1);
        QPixmap pix = pixmap.transformed(matrix);
        return QIcon(pix);
    }
    return QIcon(pixmap);
}
