#include "h5event.h"
HEvent::HEvent()
{
    m_event = 0;
}

HEvent::HEvent(QEvent* event,QVariant data)
    :m_event(event),m_data(data)
{

}

HEvent::~HEvent()
{

}


QEvent* HEvent::event()
{
    return m_event;
}

QVariant HEvent::data()
{
    return m_data;
}
