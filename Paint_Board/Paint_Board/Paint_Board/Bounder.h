
//////////////////////////////////////////////////
// 
// FileName: Bounder.h
// Creator : ���ĺ�
// Date    : 2016-11-30 11:54:31
// Comment : ͼ�α߽����ԵĻ���,����װ�� Shape ͼ��,װ��Shapeͼ�εı߽�ͼ�ο����ɴ�����
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
	virtual void drawing(QPainter* painter); //�߽����� ���Լ��ķ���
	virtual void move(Shape* shape, const QPointF& from, const QPointF& to) = 0; //�����ѡ�б߽�����ʱ��Ӧ���ñ߽��������ı�ͼ�ε�����
	virtual void setCenterPointFromShape(Shape* shape) = 0;  //�߽�����Ӧ��ͨ�� bossͼ�ε���Ϣ�����Լ�����Ϣ
	virtual bool isOnShape(const QPointF& point);	//�ж��Լ���û�б����ѡ��

public:
	void	setAngle(const double& angle)			{ m_angle = angle;} //���ýǶ�
	void	setCenterPoint(const QPointF& point)	{ m_centerPoint = point;}//�������ĵ�
	double	getAngle()								{ return m_angle;} //�õ���ת�Ƕ�
	int		getBounderId()							{ return m_bounderId;} //�õ�ID (��������ͼ�μ̳�����࣬�ͻ����Լ���Id)
	QPointF getCenterPoint()						{ return m_centerPoint;} //�õ����ĵ�
	//�Ѿ�������ͼ�ε����
	enum BOUNDERTYPE{m_eBounderUp, m_eBounderUpRight, m_eBounderRight, m_eBounderDownRight,
					m_eBounderDown, m_eBounderDownLeft, m_eBounderLeft, m_eBounderUpLeft,m_eBounderCicle};

public:
	double	disBetweenTwoPoint(const QPointF& from, const QPointF& to);//������֮��ľ���
protected:
	QPointF m_centerPoint; //���ĵĵ�
	double m_angle; //�Ƕ�
	int m_bounderId;//��ѡ�б߽��Id
protected:
	const static int ms_bounderSize = 10;//�߽�ͼ�εĴ�С
};
#endif 