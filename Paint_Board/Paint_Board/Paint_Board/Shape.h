
//////////////////////////////////////////////////
// 
// FileName: Shape.h
// Creator : 柯四海
// Date    : 2016-11-18 11:50:56
// Comment : 所有图形的基类，定义了一些基本的方法和属性
//
//////////////////////////////////////////////////

#ifndef _SHAPE_H_
#define _SHAPE_H_

#pragma once
#include <QtGui>
#include <QtGui>
#include <QWidget>
#include "BounderType.h"

class Shape
{
public:
	Shape();
	Shape(const QPointF& leftTopPoint,const QPointF& rigthBottomPoint);
	virtual ~Shape(void);

public:
	void setLeftTopPoint(const QPointF& point)		{ m_leftTopPoint = point;}//设置左上角坐标
	void setLeftBottomPoint(const QPointF& point)	{ m_leftBottomPoint = point;} //设置左下角坐标
	void setRightTopPoint(const QPointF& point)		{ m_rightTopPoint = point;}  //设置右上角坐标
	void setRightBottomPoint(const QPointF& point)	{ m_rightBottomPoint = point;}//设置右下角坐标
	void setBoolDrawBounder(bool status)			{ m_bDrawBounder = status;} //设置是否画边界的属性
	void setBoolBounderBeSelected(bool status)		{ m_bBounderBeSelected = status;} //设置边界是不是被选中的属性
	void setAngle(const double& angle);  //设置旋转角度
	QPointF getLeftTopPoint()		{ return m_leftTopPoint;} //得到左上角坐标
	QPointF getLeftBottomPoint()	{ return m_leftBottomPoint;} //得到左下角坐标
	QPointF getRightTopPoint()		{ return m_rightTopPoint;}//得到右上角坐标
	QPointF getRightBottomPoint()	{ return m_rightBottomPoint;} //得到右下角坐标
	bool getBoolDrawBounder()		{ return m_bDrawBounder;}   //得到是否画边界的属性
	bool getBoolBounderBeSelected()	{ return m_bBounderBeSelected;}//得到边界图形是不是被选中的属性
	double getAngle()				{ return m_angle;}//得到旋转角度
	Bounder* getSelectedBounder()	{ return m_pBounderBeSelected;}//得到
	
public:
	QPointF getCenterPointFromLeftTopAndRightBottom();
	QPointF getCenterPointFromLeftBottomAndRightTop();
	QPointF PointAfterRotation(const QPointF& center,const QPointF& target,double angle);
	void  rebuildRectFromLeftTopAndRightBottom(const QPointF& left_top,const QPointF& right_bottom,double angle);
	void  rebuildRectFromLeftBottomAndRightTop(const QPointF& left_bottom,const QPointF& right_top,double angle);
	void  adjustIfUserPressAndFastReleaseDuringCreateNewShape(); //当刚开始画图形时，避免用户点一下就放开的情况

public:
	virtual void move(const QPointF& from,const QPointF& to);
	virtual void drawBounder(QPainter* painter);
	virtual void drawBounderLine(QPainter* painter);
	virtual void drawing(QPainter* painter)=0;
	virtual void setBounder();
			void readyToDrawing();
	virtual bool isOnShape(const QPointF& point);
	virtual bool isOnShapeBounder(const QPointF& point);
	virtual bool isOnshapeBody(const QPointF& point);
	virtual void setInintPointDuringMove(const QPointF& point); //在刚开始画图形的时候为了保证图形一直为原来的样子，设置这个函数，下面那个变量为辅助这个函数的
	virtual void addBounder(Bounder* bounder);

public:
	int getKeyStatus(const QPointF& point);
	int getKeyDir(const QPointF& point);

public:
#if DEBUG
public:
	static  int m_debugShapeNumber;
#endif

protected:
	QPointF m_leftTopPoint;
	QPointF m_leftBottomPoint;
	QPointF m_rightTopPoint;
	QPointF m_rightBottomPoint;
	double m_angle;

protected:
	bool m_bBounderBeSelected;
	bool m_bDrawBounder;	//如果被选中了，那是要画边的
	QPointF m_firstPressPoint;
	Bounder* m_pBounderBeSelected;
	QVector<Bounder*> m_pBounderCollection;//边界有哪些图形的集合

private:
	const static double ms_fSmallEnough  /* = 0.5 */;//当用户刚开始画的图形的起点和终点的距离小于这个值，则采取措施初始化图形的大小
	const static int	ms_nInintSize = 100; //如果用户画图时就点了一下，那么初始化图形为这个大小
};

#endif