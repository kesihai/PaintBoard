
//////////////////////////////////////////////////
// 
// FileName: Combination.h
// Creator : ���ĺ�
// Date    : 2016-11-30 12:05:32
// Comment : Ϊʵ��ͼ�μ������ӵ���
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
	bool findShape(Shape* shape);//����һ��ͼ���ڲ������ͼ����
	void addShape(Shape* shape);//Ϊ���ͼ�����һ��ͼ��
	void remove(Shape* shape);//ȥ��һ�����ͼ�Σ����ʱ�����ͼ�λ���Manager�����棬ֻ��ʧȥ����ϵ���Ϣ��û�б�����
	void removeAt(int pos); //ȥ��һ��λ�õ�ͼ��
	void removeAll();//ȥ��������ϵ�ͼ��
	int getSize();//�õ����ͼ�ε�ͼ�θ���
	Shape* getShapeAt(int pos);//�õ�һ��λ�õ�ͼ��
	Shape* isOnShape(const QPointF& point);//����һ�����ڲ���һ��ͼ��
	void setSelectedShape(Shape* shape);//��Ϊ���ͼ����Ҳ����һ�������ѡ�е�
	void move(Shape* shape,const QPointF& from,const QPointF& to);//�ƶ������������ͼ������һ����ѡ�е�ͼ��
	void setSelectedPointForBrotherShape(); //Ϊ������ͼ��ѡ����һ����λ��ѡ��
	int  getPosFromSelectedShape(Shape* from,Shape* to);//����from (shape)��ѡ�е�λ�õõ�to(shape)��ѡ��ͼ�ε���һ����λ�ı�ţ��������� ��Ϊ0��Ȼ��˳ʱ�룬һ����8���߽�Ϊ  0~7������һ����תΪ8
	void setBoolDrawBounderForCombinetion(bool status); //Ϊ��������ñ��Ƿ񻭱߽�
	double getDisFromOnePoint(Shape* shape,Bounder* bounder); //�������ͼ�κ����ͼ�ε�һ�����ԣ��õ�������Ե����ͼ�����ĵĵ�λ�����ĳ���
	void setLenForBrotherShape(); //��Ϊ���ͼ�������ǰ��ձ����ģ�������ǰΪ�������ñ���
	void setPointFForBrotherShape(); //���ΪΪ������ͼ��������Ӧ��Ҫ�ı�ĵ㵽���ľ���ĵ�λ����

private:
	QVector<Shape*> m_shapeConbine; //�������vector��¼���е������һ���ͼ��
	QVector<int>m_bounderId; //��¼ÿһ���������Ҫ�ı�Ĳ�λ������
	QVector<double>m_bounderLen; //��¼ÿһ�������Ӧ�ð�����������ı�
	QVector<QPointF>m_PointCombination;//�������ͼ�ζ�Ӧ��һ���㱻ѡ�У�body,Cicle����Χ�ľ���

private:
	Bounder* bounder[9]; //�õ���Ԫģʽ��˼��,ֻ����9������Ϊ���е������
	Shape* m_shapeBeSelected; //���ͼ�����汻ѡ�е�ͼ��
};
#endif