
//////////////////////////////////////////////////
// 
// FileName: Rect.cpp
// Creator : ���ĺ�
// Date    : 2016-11-30 13:57:35
// Comment : �����࣬�̳�Shape�����ڻ�һ������
//
//////////////////////////////////////////////////

#include "Manager.h"
#include "Rect.h"

void Rect::inint()
{
	//����˳ʱ��ķ������ɶ�������϶������ƶ��кܴ�ı���
	Bounder* bounder;
	bounder = new BounderUp;
	addBounder(bounder);
	bounder = new BounderUpRight;
	addBounder(bounder);
	bounder = new BounderRight;
	addBounder(bounder);
	bounder = new BounderDownRight;
	addBounder(bounder);
	bounder = new BounderDown;
	addBounder(bounder);
	bounder = new BounderDownLeft;
	addBounder(bounder);
	bounder = new BounderLeft;
	addBounder(bounder);
	bounder = new BounderUpLeft;
	addBounder(bounder);
	bounder = new BounderCicle;
	addBounder(bounder);
}
Rect::Rect(void)
{
	inint();
}

Rect::Rect(const QPointF& start,const QPointF& end):Shape(start,end)
{
	inint();
}

Rect::~Rect(void)
{
#if DEBUG
	--m_debugShapeNumber;
#endif
}

void Rect::drawing(QPainter* painter)
{
	painter->save();
	painter->setBrush(Qt::white);
	QPainterPath path;
	path.moveTo(getLeftTopPoint());
	path.lineTo(getLeftBottomPoint());
	path.lineTo(getRightBottomPoint());
	path.lineTo(getRightTopPoint());
	path.lineTo(getLeftTopPoint());
	painter->drawPath(path);
	painter->restore();
}

void Rect::drawBounderLine(QPainter* painter)
{
	painter->save();
	painter->setPen(Qt::DotLine);
	painter->drawLine(getLeftTopPoint(),getLeftBottomPoint());
	painter->drawLine(getLeftBottomPoint(),getRightBottomPoint());
	painter->drawLine(getRightBottomPoint(),getRightTopPoint());
	painter->drawLine(getRightTopPoint(),getLeftTopPoint());
	painter->restore();
}

bool Rect::isOnshapeBody(const QPointF& point)
{
	QPainterPath path;
	path.moveTo(m_leftTopPoint);
	path.lineTo(m_leftBottomPoint);
	path.lineTo(m_rightBottomPoint);
	path.lineTo(m_rightTopPoint);
	path.lineTo(m_leftTopPoint);
	return path.contains(point);
}