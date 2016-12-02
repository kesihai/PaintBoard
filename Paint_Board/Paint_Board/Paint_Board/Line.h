
//////////////////////////////////////////////////
// 
// FileName: Line.h
// Creator : ���ĺ�
// Date    : 2016-11-30 12:10:17
// Comment : �̳��� Shape �������ǻ���һ����
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
	Line(const QPointF& start, const QPointF& end);//������startΪ����,endΪ���µ�ͼ��
	~Line(void);
public:
			void inint();
	virtual void drawing(QPainter* painter) override; //����Ҫ����ķ���
	virtual void drawBounderLine(QPainter* painter) override; //��һЩ�������ߣ����类����ʱӦ�û�����
	virtual void setInintPointDuringMove(const QPointF& point) override;//�û��տ�ʼ��ͼ��ʱ��Ӧ������ʲô����ͼ��
	virtual bool isOnshapeBody(const QPointF& point) override;//���ڲ���body��
private:
	const static double ms_fUsefulDis /* =10 */; // �����Ҫѡ���߶Σ��ɽ�����Զ�ľ���
};

#endif