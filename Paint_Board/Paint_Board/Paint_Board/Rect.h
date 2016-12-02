
//////////////////////////////////////////////////
// 
// FileName: Rect.h
// Creator : 柯四海
// Date    : 2016-11-30 13:57:35
// Comment : 矩形类，继承Shape，用于画一个矩形
//
//////////////////////////////////////////////////

#ifndef _RECT_H_
#define _RECT_H_

#pragma once
#include "shape.h"
class Rect :public Shape
{
public:
	Rect(void);
	Rect(const QPointF& start, const QPointF& end);
	~Rect(void);

public:
			void inint();
	virtual void drawing(QPainter* painter) override; //画自己的Body的函数
	virtual void drawBounderLine(QPainter* painter) override; //画边界线的函数
	virtual bool isOnshapeBody(const QPointF& point) override; //有没有被body选中
};
#endif