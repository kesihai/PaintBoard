//////////////////////////////////////////////////
// 
// FileName: Line.cpp
// Creator : 柯四海
// Date    : 2016-11-30 12:10:17
// Comment : 继承自 Shape ，功能是画出一条线
//
//////////////////////////////////////////////////


#include "Line.h"
#include <QMessageBox>
#include "Manager.h"

const double Line :: ms_fUsefulDis = 10;


void Line::inint()
{
	Bounder* bounder;
	bounder = new BounderUpLeft;
	addBounder(bounder);
	bounder = new BounderDownRight;
	addBounder(bounder);
}

Line::Line(void)
{
	inint();
}

Line::Line(const QPointF& start, const QPointF& end) : Shape(start,end)
{
	inint();
}

Line::~Line(void)
{
#if DEBUG
	--m_debugShapeNumber;
#endif
}

void Line::setInintPointDuringMove(const QPointF& point)
{
	m_rightBottomPoint = point;
	m_leftBottomPoint = QPointF(m_leftTopPoint.x(), m_rightBottomPoint.y());
	m_rightTopPoint = QPointF(m_rightBottomPoint.x(), m_leftTopPoint.y());
}

void Line::drawing(QPainter* painter)
{
	QLineF line(m_leftTopPoint, m_rightBottomPoint);
	painter->drawLine(line);
}

void Line::drawBounderLine(QPainter* painter)
{
	QLineF line(m_leftTopPoint, m_rightBottomPoint);
	painter->save();
	painter->setPen(Qt::DotLine);
	painter->drawLine(line);
	painter->restore();
}

bool Line::isOnshapeBody(const QPointF& point)
{
	QPointF startPoint = m_leftTopPoint;
	QPointF endPoint = m_rightBottomPoint;
	QPointF realPoint = point;
	//下面是判断点在不在线段上
	double eps;
	eps = fabs(startPoint.x()-endPoint.x()); //如果线的起点和终点的x距离很近
	if(eps < ms_fUsefulDis) 
	{
		return (fabs(realPoint.x() - startPoint.x()) < ms_fUsefulDis && (realPoint.y() - startPoint.y()) * (realPoint.y() - endPoint.y()) <= 0);
	}
	eps = fabs(startPoint.y() - endPoint.y()); //如果线的y很近
	if(eps < ms_fUsefulDis)
	{
		return (fabs(realPoint.y() - startPoint.y()) < ms_fUsefulDis && (realPoint.x()-startPoint.x())*(realPoint.x()-endPoint.x()) <= 0);
	}

	QRectF f(startPoint,endPoint);
	if(!f.contains(realPoint)) 
	{
		return false;
	}
	double k = (startPoint.y() - endPoint.y()) / (startPoint.x() - endPoint.x());
	double b = startPoint.y() - startPoint.x() * k;
	double len = fabs((-point.y() + b + k * point.x())) / sqrt(1+k*k);
	return (len < ms_fUsefulDis);
	/*
	因为没有为Line设置 旋转属性，所以这里没有判断选中旋转的情况
	*/
}