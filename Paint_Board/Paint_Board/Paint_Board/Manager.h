
//////////////////////////////////////////////////
// 
// FileName: Manager.h
// Creator : 柯四海
// Date    : 2016-11-30T13:52:05
// Comment : 主要负责接收并处理画板(PaintBoard)的一些请求，例如画图形，移动，删除的 
//
//////////////////////////////////////////////////

#ifndef _MANAGER_H_
#define _MANAGER_H_

#pragma once
#include "Shape.h"
#include "Factory.h"
#include "Combination.h"
#include <QVector>

class Manager
{
public:
	Manager(void);
	~Manager(void);

public:
	void addShape(Shape* shape); //添加新的图形
	void readyToDraw(QPainter* painter); //准备画图形
	void move(Shape* shape,const QPointF& from,const QPointF& to); //移动，至于这么移动会根据是否触发组合这个属性，如果有组合，那么移动组合图形，否则移动当前被选中的图形
	void setBoolDrawBounderForCombination(bool status);//是否为组合类画边界
	void setBoolNeedCombination(bool status); //设置是否处于组合的情况之下
	int  getKeyStatus(Shape* shape,const QPointF& point); //鼠标移动时调用这个方法得到鼠标的状态
	bool isCombination(); //得到是否处于组合的状态
	Shape* getShapeBeSelected(const QPointF& point);//得到被选中的图形，先看可见边界图形的边界是不是被选中
	Shape* createShape(Factory::shapeType type,const QPointF& start,const QPointF& end);//画出一个图形

public:
	enum keyStatus{ m_eKeyStatusEmpty =-2,m_eKeyStatusBody =-1,m_eKeyStatusUp, m_eKeyStatusUpRight,m_eKeyStatusRight,m_eKeyStatusDownRight,
					m_eKeyStatusDown,m_eKeyStatusDownLeft,m_eKeyStatusLeft,m_eKeyStatusUpLeft,m_eKeyStatusCicle};
	enum shapeUpOrDown{m_eDown,m_eUp};

public:
	void addCombinationShape(Shape* shape);//为组合类添加一个图形 
	void clearCombinationShape();//清楚组合类
	void deleteCombination();//删除组合类，这个删除会让组合类的图形被删除
	void deleteShape(Shape* shape);//删除一个图形，这个图形会被析构
	void upperShape(Shape* shape,Manager::shapeUpOrDown tyte);//上移或下移一个图形，根据后面的参数   1 代表上移一位，-1代表下移一位
	void upperCombination(Manager::shapeUpOrDown type);//上移或者下移整个组合类  1 代表上移一位，-1代表下移一位
	Combination m_shapeCombination;

private:
	QVector<Shape*> m_allShape;//所有被创建的图形都在这个里面
	Factory m_factory; //简单工厂类，主要负责产生图形
	bool m_bCombination;//目前是不是处于组合状态
};

#endif