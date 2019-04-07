#include "hselectmanager.h"S

HSelectManager::HSelectManager()
{

}

HSelectManager::~HSelectManager()
{

}


void HSelectManager::draw(QPainter* painter, const QRectF& rect, const QRectF &selectRect = QRectF())
{

}

void HSelectManager::addObj(HBaseObj* obj)
{

}

void HSelectManager::removeObj(HBaseObj* obj)
{

}

void HSelectManager::setSelectObj(QList<HBaseObj*> objs)
{

}

void HSelectManager::selectChanged(HBaseObj* obj, bool isSelect)
{

}

void HSelectManager::clear()
{

}

bool HSelectManager::isSelected(HBaseObj* obj)
{

}

int HSelectManager::isOnPoint(const QPointF& point, QPointF& selectPoint)
{

}

bool HSelectManager::isOnObj(const QPointF& point)//在point点上是否选中obj
{

}

void HSelectManager::recalcSelect()
{

}

void HSelectManager::calcPoints()
{

}