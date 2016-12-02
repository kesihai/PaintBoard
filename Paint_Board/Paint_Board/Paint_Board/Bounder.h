
//////////////////////////////////////////////////
// 
// FileName: Bounder.h
// Creator : 柯四海
// Date    : 2016-11-30 11:54:31
// Comment : 图形边界属性的基类,用来装饰 Shape 图形,装饰Shape图形的边界图形可以由此派生
//
//////////////////////////////////////////////////


#pragma once
#ifndef _BOUNDER_H_
#define _BOUNDER_H_

#include <QtGui>
class Shape;
#define Pi acos(-1.0)

class Bounder{
public:
	Bounder(const QPointF& point);
	Bounder();
	virtual ~Bounder();

public:
	virtual void drawing(QPainter* painter); //边界属性 画自己的方法
	virtual void move(Shape* shape, const QPointF& from, const QPointF& to) = 0; //当鼠标选中边界属性时，应该让边界属性来改变图形的特征
	virtual void setCenterPointFromShape(Shape* shape) = 0;  //边界属性应该通过 boss图形的信息设置自己的信息
	virtual bool isOnShape(const QPointF& point);	//判断自己有没有被鼠标选中

public:
	void	setAngle(const double& angle)			{ m_angle = angle;} //设置角度
	void	setCenterPoint(const QPointF& point)	{ m_centerPoint = point;}//设置中心点
	double	getAngle()								{ return m_angle;} //得到旋转角度
	int		getBounderId()							{ return m_bounderId;} //得到ID (后面有有图形继承这个类，就会有自己的Id)
	QPointF getCenterPoint()						{ return m_centerPoint;} //得到中心点
	//已经派生出图形的类别
	enum BOUNDERTYPE{m_eBounderUp, m_eBounderUpRight, m_eBounderRight, m_eBounderDownRight,
					m_eBounderDown, m_eBounderDownLeft, m_eBounderLeft, m_eBounderUpLeft,m_eBounderCicle};

public:
	double	disBetweenTwoPoint(const QPointF& from, const QPointF& to);//两个点之间的距离
protected:
	QPointF m_centerPoint; //中心的点
	double m_angle; //角度
	int m_bounderId;//被选中边界的Id
protected:
	const static int ms_bounderSize = 10;//边界图形的大小
};
#endif 