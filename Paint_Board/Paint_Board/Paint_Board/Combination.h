
//////////////////////////////////////////////////
// 
// FileName: Combination.h
// Creator : 柯四海
// Date    : 2016-11-30 12:05:32
// Comment : 为实现图形间组合添加的类
//
//////////////////////////////////////////////////

#ifndef _COMBINATION_H_
#define _COMBINATION_H_

#pragma once
#include "Shape.h"
#include "Bounder.h"
#include <QVector>

class Combination{
public:
	Combination(void);
	~Combination(void);

public:
	bool findShape(Shape* shape);//查找一个图形在不在组合图形中
	void addShape(Shape* shape);//为组合图形添加一个图形
	void remove(Shape* shape);//去掉一个组合图形，这个时候这个图形还在Manager类里面，只是失去了组合的信息，没有被析构
	void removeAt(int pos); //去掉一个位置的图形
	void removeAll();//去掉所有组合的图形
	int getSize();//得到组合图形的图形个数
	Shape* getShapeAt(int pos);//得到一个位置的图形
	Shape* isOnShape(const QPointF& point);//看看一个点在不在一个图形
	void setSelectedShape(Shape* shape);//因为组合图形中也是有一个被鼠标选中的
	void move(Shape* shape,const QPointF& from,const QPointF& to);//移动，传进来组合图形中那一个被选中的图形
	void setSelectedPointForBrotherShape(); //为别的组合图形选中哪一个部位被选中
	int  getPosFromSelectedShape(Shape* from,Shape* to);//根据from (shape)被选中的位置得到to(shape)被选中图形的哪一个部位的标号，具体标号是 上为0，然后顺时针，一共有8个边界为  0~7，还有一个旋转为8
	void setBoolDrawBounderForCombinetion(bool status); //为组合类设置表是否画边界
	double getDisFromOnePoint(Shape* shape,Bounder* bounder); //根据这个图形和这个图形的一个属性，得到这个属性到这个图形中心的单位向量的长度
	void setLenForBrotherShape(); //因为组合图形拉伸是按照比例的，所以提前为他们设置比例
	void setPointFForBrotherShape(); //这个为为其他的图形设置相应需要改变的点到中心距离的单位向量

private:
	QVector<Shape*> m_shapeConbine; //组合类用vector记录所有的组合在一起的图形
	QVector<int>m_bounderId; //记录每一个组合类需要改变的部位的坐标
	QVector<double>m_bounderLen; //记录每一个组合类应该按照上面比例改变
	QVector<QPointF>m_PointCombination;//看看别的图形对应哪一个点被选中，body,Cicle或周围的矩形

private:
	Bounder* bounder[9]; //用到享元模式的思想,只构建9个对象，为所有的类服务
	Shape* m_shapeBeSelected; //组合图形里面被选中的图形
};
#endif