//////////////////////////////////////////////////
// 
// FileName: BounderType.h
// Creator : 柯四海
// Date    : 2016-11-30 11:20:44
// Comment : 将一些继承 Bounder 的派生类 写到这里，相当于图形边界属性类的集合
//
//////////////////////////////////////////////////

#ifndef _BOUNDERTYPE_H_
#define _BOUNDERTYPE_H_

#include "Bounder.h"

//-----------------------------------------------------------------------------------------
class BounderCicle :
	public Bounder
{
public:
	BounderCicle(void);
	~BounderCicle(void);

public:
	virtual void drawing(QPainter* painter) override;//画自己的函数
	virtual void move(Shape* shape, const QPointF& from, const QPointF& to) override;//当这个图形被选中时，并且被鼠标从 from拖动到to应该改变主要物体的哪一些属性
	virtual void setCenterPointFromShape(Shape* shape) override;//自己根据Shape提供的信息来设置自己的信息

public:
	double changeAngle(Shape* shape, QPointF from, QPointF to);//当从from 移动到to 这个属性应该改变Shape图形的哪一些属性(例如这个应该是改变了图形的旋转角度，相应的四个点的坐标也会改变)
	double disBetweenTwoPoint(const QPointF& from, const QPointF& to); //得到两个点之间的距离

private:
	const static int ms_nStartAngle = 30*16; 
	const static int ms_nEndAngle = 300*16;
	const static double ms_feps /* = 1e-8   小于这个数就当做0 */ ;
};


//-----------------------------------------------------------------------------------------
class BounderDown :public Bounder
{
public:
	BounderDown(void);
	~BounderDown(void);
public:
	virtual void move(Shape* shape,const QPointF& from, const QPointF& to) override;
	virtual void setCenterPointFromShape(Shape* shape) override;
};


//-----------------------------------------------------------------------------------------
class BounderDownLeft :public Bounder
{
public:
	BounderDownLeft(void);
	~BounderDownLeft(void);
public:
	virtual void move(Shape* shape,const QPointF& from, const QPointF& to) override;
	virtual void setCenterPointFromShape(Shape* shape) override;
};


//-----------------------------------------------------------------------------------------
class BounderDownRight :public Bounder{
public:
	BounderDownRight(void);
	~BounderDownRight(void);
public:
	virtual void move(Shape* shape,const QPointF& from,const QPointF& to) override;
	virtual void setCenterPointFromShape(Shape* shape) override;
};


//-----------------------------------------------------------------------------------------
class BounderLeft :
	public Bounder
{
public:
	BounderLeft(void);
	~BounderLeft(void);
public:
	virtual void move(Shape* shape,const QPointF& from,const QPointF& to) override;
	virtual void setCenterPointFromShape(Shape* shape) override;
};

//-----------------------------------------------------------------------------------------
class BounderRight :
	public Bounder
{
public:
	BounderRight(void);
	~BounderRight(void);
public:
	virtual void move(Shape* shape,const QPointF& from, const QPointF& to) override;
	virtual void setCenterPointFromShape(Shape* shape) override;
};


//-----------------------------------------------------------------------------------------
class BounderUp :
	public Bounder
{
public:
	BounderUp(void);
	~BounderUp(void);
public:
	virtual void move(Shape* shape,const QPointF& from, const QPointF& to) override;
	virtual void setCenterPointFromShape(Shape* shape) override;
};


//-----------------------------------------------------------------------------------------
class BounderUpLeft :
	public Bounder
{
public:
	BounderUpLeft(void);
	~BounderUpLeft(void);
public:
	virtual void move(Shape* shape,const QPointF& from, const QPointF& to) override;
	virtual void setCenterPointFromShape(Shape* shape) override;
};


//----------------------------------------------------------------------------------------------
class BounderUpRight : public Bounder
{
public:
	BounderUpRight(void);
	~BounderUpRight(void);
public:
	virtual void move(Shape* shape,const QPointF& from,const QPointF& to) override;
	virtual void setCenterPointFromShape(Shape* shape) override;
};

#endif