﻿#ifndef HFONTHELPER_H
#define HFONTHELPER_H

#include <QStringList>
#include <QFont>
#include <QFontInfo>
#include <QFontDatabase>
#include <QComboBox>
#include "h5basehelpexport.h"
class H5BASEHELP_EXPORT HFontHelper
{
public:
    HFontHelper();
    ~HFontHelper();

public:
    static HFontHelper* m_pInstance;
    static HFontHelper* Instance();

public:
    QStringList fontFamilies() const;
    bool bold(const QString &family, const QString &style) const;
    QFont font(const QString &family, const QString &style, int pointSize) const;
    bool italic(const QString &family, const QString &style) const;
    QList<int> pointSizes(const QString &family, const QString &styleName = QString());
    QList<int> smoothSizes(const QString &family, const QString &styleName);
    QString styleString(const QFont &font);
    QString styleString(const QFontInfo &fontInfo);
    QStringList styles(const QString &family) const;
    int weight(const QString &family, const QString &style) const;
public:
    void initFontFamilyComboBox(QComboBox* comboBox);
    void initFontSizeComboBox(QComboBox* comboBox,QString strFamily);
private:
    QFontDatabase fontDatabase;
};

#endif // HFONTHELPER_H
