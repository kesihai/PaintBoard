//////////////////////////////////////////////////
// 
// FileName: Triangle.cpp
// Creator : 柯四海
// Date    : 2016-11-30T14:03:35
// Comment : 三角形类，继承于Shape,作用是画一个三角形
//
//////////////////////////////////////////////////

#include "Triangle.h"
#include "Manager.h"

void Triangle:: inint()
{
	Bounder* bounder;
	bounder = new BounderUp;
	addBounder(bounder);
	bounder = new BounderUpRight;
	addBounder(bounder);
	bounder = new BounderRight;
	addBounder(bounder);
	bounder = new BounderDownRight;
	addBounder(bounder);
	bounder = new BounderDown;
	addBounder(bounder);
	bounder = new BounderDownLeft;
	addBounder(bounder);
	bounder = new BounderLeft;
	addBounder(bounder);
	bounder = new BounderUpLeft;
	addBounder(bounder);
	bounder = new BounderCicle;
	addBounder(bounder);
}

Triangle::Triangle(void)
{
	inint();
}
Triangle::Triangle(const QPointF& start,const QPointF& end) : Shape(start, end)
{
	inint();
}
Triangle::~Triangle(void)
{
#if DEBUG
	--m_debugShapeNumber;
#endif
}


void Triangle::drawing(QPainter* painter)
{
	QPainterPath path;
	path.moveTo(m_pBounderCollection[7]->getCenterPoint());
	path.lineTo(m_pBounderCollection[5]->getCenterPoint());
	path.lineTo(m_pBounderCollection[3]->getCenterPoint());
	path.lineTo(m_pBounderCollection[7]->getCenterPoint());
	painter->drawPath(path);
}

void Triangle::drawBounderLine(QPainter* painter)
{
	painter->save();
	painter->setPen(Qt::DotLine);
	painter->drawLine(m_pBounderCollection[1]->getCenterPoint(),m_pBounderCollection[3]->getCenterPoint());
	painter->drawLine(m_pBounderCollection[3]->getCenterPoint(),m_pBounderCollection[5]->getCenterPoint());
	painter->drawLine(m_pBounderCollection[5]->getCenterPoint(),m_pBounderCollection[7]->getCenterPoint());
	painter->drawLine(m_pBounderCollection[7]->getCenterPoint(),m_pBounderCollection[1]->getCenterPoint());
	painter->restore();
}

bool Triangle::isOnshapeBody(const QPointF& point)
{
	QPainterPath path;
	path.moveTo(m_leftTopPoint);
	path.lineTo(m_leftBottomPoint);
	path.lineTo(m_rightBottomPoint);
	path.lineTo(m_leftTopPoint);
	return path.contains(point);
}