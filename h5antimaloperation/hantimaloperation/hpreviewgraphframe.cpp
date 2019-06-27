#include "hpreviewgraphframe.h"
HPreviewGraphFrame::HPreviewGraphFrame(quint8 btGraphType,HAntiMalopMgr* mgr,HGraphFrame *parent)
    :HGraphFrame(mgr,parent)
{
    m_btGraphType = btGraphType;
}

HPreviewGraphFrame::~HPreviewGraphFrame()
{

}



void HPreviewGraphFrame::getOperatorSentence( OPERATORSHEETSTEP* pStep )
{

}

void HPreviewGraphFrame::getOperatorRemark( OPERATORSHEETSTEP* pStep )
{

}

QString HPreviewGraphFrame::makeOpSentence( QString szString, quint16 wOpSTID, quint16 wOpPTID )
{
    return QString();
}

QString HPreviewGraphFrame::makeOpSentence( QString szString, QString szChar, quint16 wOpSTID, quint16 wOpPTID )
{
    return QString();
}

QString HPreviewGraphFrame::makeCheckOpSentence( QString szString )
{
    return QString();
}

void HPreviewGraphFrame::onPreviewCheckOp( const int nCheckType )
{

}

void HPreviewGraphFrame::onManualSetValue( quint8 btValue )
{

}

void HPreviewGraphFrame::onClearManualSet()
{

}

bool HPreviewGraphFrame::isPreviewing()
{
    return false;
}

int  HPreviewGraphFrame::databaseID()
{
    return 0;
}

bool HPreviewGraphFrame::onMousePressEvent(QObject *obj, QEvent *event)
{
    return false;
}

bool HPreviewGraphFrame::onContextMenuEvent(QObject *obj, QEvent *event)
{
    return false;
}

void HPreviewGraphFrame::onPreviewStart()
{

}

void HPreviewGraphFrame::onPreviewStop()
{

}

void HPreviewGraphFrame::onPreviewCancel()
{

}

void HPreviewGraphFrame::onPreviewOpen()
{

}

void HPreviewGraphFrame::onPreviewClose()
{

}

void HPreviewGraphFrame::onPreviewCancelLast()
{

}

void HPreviewGraphFrame::onPreviewTishi()
{

}

void HPreviewGraphFrame::onPreviewCheckSwitchOpen()
{

}

void HPreviewGraphFrame::onPreviewCheckSwitchClose()
{

}

void HPreviewGraphFrame::onPreviewCheckBreakOpen()
{

}

void HPreviewGraphFrame::onPreviewCheckBreakClose()
{

}

void HPreviewGraphFrame::onPreviewCheckEBIOpen()
{

}

void HPreviewGraphFrame::onPreviewCheckEBIClose()
{

}

void HPreviewGraphFrame::onPreviewCheckLive()
{

}

void HPreviewGraphFrame::onPreviewManualSetOpen()
{

}

void HPreviewGraphFrame::onPreviewManualSetClose()
{

}

void HPreviewGraphFrame::onPreviewManualSetXOpen()
{

}

void HPreviewGraphFrame::onPreviewManualSetXClose()
{

}

void HPreviewGraphFrame::onPreviewClearManualSet()
{

}
