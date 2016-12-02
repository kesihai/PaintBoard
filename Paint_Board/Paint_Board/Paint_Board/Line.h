
//////////////////////////////////////////////////
// 
// FileName: Line.h
// Creator : 柯四海
// Date    : 2016-11-30 12:10:17
// Comment : 继承自 Shape ，功能是画出一条线
//
//////////////////////////////////////////////////

#ifndef _LINE_H_
#define _LINE_H_

#pragma once
#include "shape.h"
class Line :
	public Shape
{
public:
	Line(void);
	Line(const QPointF& start, const QPointF& end);//产生以start为左上,end为右下的图形
	~Line(void);
public:
			void inint();
	virtual void drawing(QPainter* painter) override; //画主要身体的方法
	virtual void drawBounderLine(QPainter* painter) override; //画一些辅助的线，例如被拦着时应该画的线
	virtual void setInintPointDuringMove(const QPointF& point) override;//用户刚开始画图形时，应该生成什么样的图形
	virtual bool isOnshapeBody(const QPointF& point) override;//点在不在body上
private:
	const static double ms_fUsefulDis /* =10 */; // 当鼠标要选中线段，可接受最远的距离
};

#endif