
//////////////////////////////////////////////////
// 
// FileName: Rect.h
// Creator : ���ĺ�
// Date    : 2016-11-30 13:57:35
// Comment : �����࣬�̳�Shape�����ڻ�һ������
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
	virtual void drawing(QPainter* painter) override; //���Լ���Body�ĺ���
	virtual void drawBounderLine(QPainter* painter) override; //���߽��ߵĺ���
	virtual bool isOnshapeBody(const QPointF& point) override; //��û�б�bodyѡ��
};
#endif