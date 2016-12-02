//////////////////////////////////////////////////
// 
// FileName: BounderType.cpp
// Creator : 柯四海
// Date    : 2016-11-30 11:20:44
// Comment : 将一些继承 Bounder 的派生类 定义 写到这里，相当于边界属性类的集合
//
//////////////////////////////////////////////////

#include "BounderType.h"
#include "Shape.h"

//-----------------------------------------------------------------------------------------
const double BounderCicle:: ms_feps = 1e-8;

BounderCicle::BounderCicle(void)
{
	m_bounderId = Bounder::m_eBounderCicle;
}

BounderCicle::~BounderCicle(void)
{
}

void BounderCicle::drawing(QPainter* painter)
{
	Q_ASSERT(painter);
	painter->save();
	QRectF R(-ms_bounderSize/2,-ms_bounderSize/2,ms_bounderSize,ms_bounderSize);
	painter->translate(m_centerPoint);
	painter->rotate(m_angle);
	painter->setBrush(Qt::red);
	painter->drawArc(R,ms_nStartAngle,ms_nEndAngle);
	painter->restore();
}

void BounderCicle::move(Shape* shape,const QPointF& from,const QPointF& to)
{
	Q_ASSERT(shape);
	double angleChanged = changeAngle(shape,from,to);
	shape->setAngle(shape->getAngle() + angleChanged);
	QPointF cenPoint = shape->getCenterPointFromLeftBottomAndRightTop();	
	shape->setLeftTopPoint(shape->PointAfterRotation(cenPoint, shape->getLeftTopPoint(), angleChanged));
	shape->setLeftBottomPoint(shape->PointAfterRotation(cenPoint, shape->getLeftBottomPoint(), angleChanged));
	shape->setRightTopPoint(shape->PointAfterRotation(cenPoint, shape->getRightTopPoint(), angleChanged));
	shape->setRightBottomPoint(shape->PointAfterRotation(cenPoint, shape->getRightBottomPoint(), angleChanged));
}

void BounderCicle::setCenterPointFromShape(Shape* shape)
{
	Q_ASSERT(shape);
	QPointF closeTopCen = (shape->getLeftTopPoint() + shape->getRightTopPoint()) / 2;
	QPointF dir = closeTopCen - shape->getCenterPointFromLeftBottomAndRightTop();
	double temp = disBetweenTwoPoint(dir, QPointF(0,0));
	if(temp < ms_feps)
	{
		QPointF cenPoint=closeTopCen - QPointF(7,7);
		cenPoint = shape->PointAfterRotation(closeTopCen, cenPoint, getAngle());
		m_centerPoint = cenPoint;
	}
	else
	{
		while(temp < 1)
		{
			temp = temp * 2;
			dir = dir * 2;
		}
		dir.setX(dir.x()/temp);
		dir.setY(dir.y()/temp);
		m_centerPoint = closeTopCen + 15 * dir;
	}
}

double BounderCicle::disBetweenTwoPoint(const QPointF& from, const QPointF& to)
{
	return sqrt((from.x() - to.x()) * (from.x() - to.x()) + (from.y() - to.y()) * (from.y() - to.y()));
}

double BounderCicle::changeAngle(Shape* shape, QPointF from, QPointF to)
{
	Q_ASSERT(shape);
	QPointF cenPoint = shape->getCenterPointFromLeftBottomAndRightTop();
	QPointF From = from;
	QPointF To = to;
	from -= cenPoint;
	to -= cenPoint;
	double a = sqrt(from.x() * from.x() + from.y() * from.y());
	double b = sqrt(to.x() * to.x() + to.y() * to.y());
	double c = sqrt((from.x() - to.x()) * (from.x() - to.x()) + (from.y() - to.y()) * (from.y() - to.y()));
	double temp = (a * a + b * b - c * c) / ( 2 * a * b);
	double ans = acos(temp) / acos(-1.0) * 180;
	/*
		前面ans是得到旋转的绝对值，那么下面的就是决定方向问题
		方法：将From分别照 ans 和 -ans旋转，看哪一个更加接近 to,那么就好得到角度的问题了
	*/
	QPointF yesPoint = shape->PointAfterRotation(cenPoint,From,-ans);
	QPointF noPoint=shape->PointAfterRotation(cenPoint,From,ans);
	double yesDis=disBetweenTwoPoint(yesPoint,To);
	double noDis=disBetweenTwoPoint(noPoint,To);
	if(yesDis<noDis)  return -ans;
	return ans;
}


//-----------------------------------------------------------------------------------------
BounderDown::BounderDown(void)
{
	m_bounderId = m_eBounderDown;
}
BounderDown::~BounderDown(void)
{

}
void BounderDown::move(Shape* shape,const QPointF& from, const QPointF& to)
{
	Q_ASSERT(shape);
	double dis = disBetweenTwoPoint(from, to);
	double realAngle = m_angle - 90;
	QPointF dir(cos(realAngle*Pi/180),sin(realAngle*Pi/180));
	QPointF moveDir = to - from;
	double temp = (dir.x() * moveDir.x() + dir.y() * moveDir.y()) / (dis); //算出两个向量的夹角
	dir = temp * dis * dir; //dis* temp 就是这个移动的向量在真正需要移动的坐标的长度
	shape->setLeftBottomPoint(shape->getLeftBottomPoint() + dir);
	shape->setRightBottomPoint(shape->getRightBottomPoint() + dir);
}
void BounderDown::setCenterPointFromShape(Shape* shape)
{
	m_centerPoint = (shape->getLeftBottomPoint() + shape->getRightBottomPoint()) / 2;
	m_angle=shape->getAngle();
}

//-----------------------------------------------------------------------------------------

BounderDownLeft::BounderDownLeft(void)
{
	m_bounderId = Bounder::m_eBounderDownLeft;
}

BounderDownLeft::~BounderDownLeft(void)
{
}

void BounderDownLeft::setCenterPointFromShape(Shape* shape)
{
	Q_ASSERT(shape);
	m_centerPoint = shape->getLeftBottomPoint();
	m_angle = shape->getAngle();
}

void BounderDownLeft::move(Shape* shape, const QPointF& from, const QPointF& to)
{
	Q_ASSERT(shape);
	shape->rebuildRectFromLeftBottomAndRightTop(to, shape->getRightTopPoint(), shape->getAngle());
}

//-----------------------------------------------------------------------------------------

BounderDownRight::BounderDownRight(void)
{
	m_bounderId = Bounder::m_eBounderDownRight;
}

BounderDownRight::~BounderDownRight(void)
{
}

void BounderDownRight::setCenterPointFromShape(Shape* shape)
{
	Q_ASSERT(shape);
	m_centerPoint = shape->getRightBottomPoint();
	m_angle = shape->getAngle();
}

void BounderDownRight::move(Shape* shape,const QPointF& from,const QPointF& to)
{
	Q_ASSERT(shape);
	shape->rebuildRectFromLeftTopAndRightBottom(shape->getLeftTopPoint(),to,shape->getAngle());
}


//-----------------------------------------------------------------------------------------

BounderLeft::BounderLeft(void)
{
	m_bounderId = Bounder::m_eBounderLeft;
}

BounderLeft::~BounderLeft(void)
{
}

void BounderLeft::setCenterPointFromShape(Shape* shape)
{
	Q_ASSERT(shape);
	m_centerPoint = (shape->getLeftBottomPoint() + shape->getLeftTopPoint())/2;
	m_angle = shape->getAngle();
}

void BounderLeft::move(Shape* shape,const QPointF& from,const QPointF& to)
{
	Q_ASSERT(shape);
	double dis = disBetweenTwoPoint(from,to);
	double realAngle = m_angle - 180;
	QPointF dir(cos(realAngle * Pi / 180), sin(realAngle * Pi / 180));
	QPointF moveDir = to - from;
	double temp = (dir.x() * moveDir.x() + dir.y() * moveDir.y()) / (dis); //算出两个向量的夹角
	dir = temp * dis * dir; //dis* temp 就是这个移动的向量在真正需要移动的坐标的长度
	shape->setLeftTopPoint(shape->getLeftTopPoint() + dir);
	shape->setLeftBottomPoint(shape->getLeftBottomPoint() + dir);
}

//-----------------------------------------------------------------------------------------

BounderRight::BounderRight(void)
{
	m_bounderId = Bounder::m_eBounderRight;
}

BounderRight::~BounderRight(void)
{
}

void BounderRight::setCenterPointFromShape(Shape* shape)
{
	Q_ASSERT(shape);
	m_centerPoint = (shape->getRightBottomPoint()+shape->getRightTopPoint())/2;
	m_angle = shape->getAngle();
}

void BounderRight::move(Shape* shape,const QPointF& from, const QPointF& to)
{
	Q_ASSERT(shape);
	double dis = disBetweenTwoPoint(from,to);
	double realAngle = m_angle;
	QPointF dir(cos(realAngle * Pi / 180), sin(realAngle * Pi / 180));
	QPointF moveDir = to-from;
	double temp = (dir.x()*moveDir.x() + dir.y() * moveDir.y())/ (dis); //算出两个向量的夹角
	dir = temp * dis * dir; //dis* temp 就是这个移动的向量在真正需要移动的坐标的长度
	shape->setRightTopPoint(shape->getRightTopPoint() + dir);
	shape->setRightBottomPoint(shape->getRightBottomPoint() + dir);
}


//-----------------------------------------------------------------------------------------

BounderUp::BounderUp(void)
{
	m_bounderId = Bounder::m_eBounderUp;
}

BounderUp::~BounderUp(void)
{

}

void BounderUp::setCenterPointFromShape(Shape* shape)
{
	Q_ASSERT(shape);
	m_centerPoint = (shape->getLeftTopPoint() + shape->getRightTopPoint()) / 2;
	m_angle = shape->getAngle();
}

void BounderUp::move(Shape* shape, const QPointF& from, const QPointF& to)
{
	Q_ASSERT(shape);
	double dis = disBetweenTwoPoint(from,to);
	double realAngle = m_angle - 90;
	QPointF dir(cos(realAngle * Pi / 180), sin(realAngle * Pi / 180));
	QPointF move_dir = to - from;
	double temp = (dir.x() * move_dir.x() + dir.y() * move_dir.y()) / (dis); //算出两个向量的夹角
	dir = temp * dis * dir; //dis* temp 就是这个移动的向量在真正需要移动的坐标的长度
	shape->setLeftTopPoint(shape->getLeftTopPoint() + dir);
	shape->setRightTopPoint(shape->getRightTopPoint() + dir);
}

//-----------------------------------------------------------------------------------------

BounderUpLeft::BounderUpLeft(void)
{
	m_bounderId = Bounder::m_eBounderUpLeft;
}

BounderUpLeft::~BounderUpLeft(void)
{
}

void BounderUpLeft::setCenterPointFromShape(Shape* shape)
{
	Q_ASSERT(shape);
	m_centerPoint = shape->getLeftTopPoint();
	m_angle = shape->getAngle();
}

void BounderUpLeft::move(Shape* shape, const QPointF& from, const QPointF& to)
{
	Q_ASSERT(shape);
	shape->rebuildRectFromLeftTopAndRightBottom(to, shape->getRightBottomPoint(), shape->getAngle());
}

//-----------------------------------------------------------------------------------------

BounderUpRight::BounderUpRight(void)
{
	m_bounderId = Bounder::m_eBounderUpRight;
}

BounderUpRight::~BounderUpRight(void)
{
}
void BounderUpRight::move(Shape* shape,const QPointF& from,const QPointF& to)
{
	Q_ASSERT(shape);
	shape->rebuildRectFromLeftBottomAndRightTop(shape->getLeftBottomPoint(), to, shape->getAngle());
}
void BounderUpRight::setCenterPointFromShape(Shape* shape)
{
	Q_ASSERT(shape);
	m_centerPoint = shape->getRightTopPoint();
	m_angle = shape->getAngle();
}
//-----------------------------------------------------------------------------------------