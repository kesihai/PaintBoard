
//////////////////////////////////////////////////
// 
// FileName: Bounder.h
// Creator : 柯四海
// Date    : 2016-11-30 11:54:31
// Comment : 图形边界属性的基类,用来装饰 Shape 图形,装饰Shape图形的边界图形可以由此派生
//
//////////////////////////////////////////////////

#include "Bounder.h"
#include "Shape.h"

Bounder::Bounder(const QPointF& point):m_centerPoint(point),m_angle(0)
{
}

Bounder::~Bounder(void)
{

}

Bounder::Bounder():m_centerPoint(QPointF(-10,-10))
{
}
	
void Bounder::drawing(QPainter* painter)
{
	Q_ASSERT(painter);
	QRectF r(QPointF(-ms_bounderSize / 2, -ms_bounderSize / 2), QPointF(ms_bounderSize / 2, ms_bounderSize / 2));
	painter->save();
	painter->setBrush(Qt::gray);
	painter->translate(m_centerPoint);
	painter->rotate(m_angle);
	painter->drawRect(r);
	painter->restore();
}


double Bounder::disBetweenTwoPoint(const QPointF& from,const QPointF& to)
{
	return sqrt((from.x() - to.x()) * (from.x() - to.x()) + (from.y() - to.y()) * (from.y() - to.y()));
}

bool Bounder::isOnShape(const QPointF& point)
{
	QPointF f(ms_bounderSize/2, ms_bounderSize/2);
	QRectF ff(m_centerPoint-f, m_centerPoint+f);
	return ff.contains(point);
}
