
//////////////////////////////////////////////////
// 
// FileName: Triangle.h
// Creator : 柯四海
// Date    : 2016-11-30T14:03:35
// Comment : 三角形类，继承于Shape,作用是画一个三角形
//
//////////////////////////////////////////////////

#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Shape.h"
#pragma once
class Triangle :
	public Shape
{
public:
	Triangle(void);
	Triangle(const QPointF& start, const QPointF& end);
	~Triangle(void);
	void inint();
public:	
	virtual void drawing(QPainter* painter) override;
	virtual void drawBounderLine(QPainter* painter) override;
	virtual bool isOnshapeBody(const QPointF& point) override;
};
#endif