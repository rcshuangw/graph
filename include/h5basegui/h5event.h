#ifndef HEVENT_H
#define HEVENT_H
#include <QEvent>
#include <QMouseEvent>
#include <QVariant>
#include "h5iconguiexport.h"

class H5BASEGUI_EXPORT HEvent
{
public:
    HEvent();
    HEvent(QEvent* event,QVariant data);
    ~HEvent();

public:
    QEvent* event();
    QVariant data();
public:
    QEvent* m_event;
    QVariant m_data;
};


#endif
