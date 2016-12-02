
//////////////////////////////////////////////////
// 
// FileName: Shape.h
// Creator : ���ĺ�
// Date    : 2016-11-18 11:50:56
// Comment : ����ͼ�εĻ��࣬������һЩ�����ķ���������
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
	void setLeftTopPoint(const QPointF& point)		{ m_leftTopPoint = point;}//�������Ͻ�����
	void setLeftBottomPoint(const QPointF& point)	{ m_leftBottomPoint = point;} //�������½�����
	void setRightTopPoint(const QPointF& point)		{ m_rightTopPoint = point;}  //�������Ͻ�����
	void setRightBottomPoint(const QPointF& point)	{ m_rightBottomPoint = point;}//�������½�����
	void setBoolDrawBounder(bool status)			{ m_bDrawBounder = status;} //�����Ƿ񻭱߽������
	void setBoolBounderBeSelected(bool status)		{ m_bBounderBeSelected = status;} //���ñ߽��ǲ��Ǳ�ѡ�е�����
	void setAngle(const double& angle);  //������ת�Ƕ�
	QPointF getLeftTopPoint()		{ return m_leftTopPoint;} //�õ����Ͻ�����
	QPointF getLeftBottomPoint()	{ return m_leftBottomPoint;} //�õ����½�����
	QPointF getRightTopPoint()		{ return m_rightTopPoint;}//�õ����Ͻ�����
	QPointF getRightBottomPoint()	{ return m_rightBottomPoint;} //�õ����½�����
	bool getBoolDrawBounder()		{ return m_bDrawBounder;}   //�õ��Ƿ񻭱߽������
	bool getBoolBounderBeSelected()	{ return m_bBounderBeSelected;}//�õ��߽�ͼ���ǲ��Ǳ�ѡ�е�����
	double getAngle()				{ return m_angle;}//�õ���ת�Ƕ�
	Bounder* getSelectedBounder()	{ return m_pBounderBeSelected;}//�õ�
	
public:
	QPointF getCenterPointFromLeftTopAndRightBottom();
	QPointF getCenterPointFromLeftBottomAndRightTop();
	QPointF PointAfterRotation(const QPointF& center,const QPointF& target,double angle);
	void  rebuildRectFromLeftTopAndRightBottom(const QPointF& left_top,const QPointF& right_bottom,double angle);
	void  rebuildRectFromLeftBottomAndRightTop(const QPointF& left_bottom,const QPointF& right_top,double angle);
	void  adjustIfUserPressAndFastReleaseDuringCreateNewShape(); //���տ�ʼ��ͼ��ʱ�������û���һ�¾ͷſ������

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
	virtual void setInintPointDuringMove(const QPointF& point); //�ڸտ�ʼ��ͼ�ε�ʱ��Ϊ�˱�֤ͼ��һֱΪԭ�������ӣ�������������������Ǹ�����Ϊ�������������
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
	bool m_bDrawBounder;	//�����ѡ���ˣ�����Ҫ���ߵ�
	QPointF m_firstPressPoint;
	Bounder* m_pBounderBeSelected;
	QVector<Bounder*> m_pBounderCollection;//�߽�����Щͼ�εļ���

private:
	const static double ms_fSmallEnough  /* = 0.5 */;//���û��տ�ʼ����ͼ�ε������յ�ľ���С�����ֵ�����ȡ��ʩ��ʼ��ͼ�εĴ�С
	const static int	ms_nInintSize = 100; //����û���ͼʱ�͵���һ�£���ô��ʼ��ͼ��Ϊ�����С
};

#endif