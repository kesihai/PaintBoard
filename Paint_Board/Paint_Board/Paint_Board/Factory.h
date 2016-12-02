///////////////////////////////////////////////////////////////////////////
//
//  FileName: Factory.h
//  Createor: ���ĺ�
//  Date:     2016-11-25
//  Comment:  �򵥹����࣬ר�Ÿ������ͼ��
//
//
///////////////////////////////////////////////////////////////////////////

#ifndef _FACTORY_H_
#define _FACTORY_H_

#pragma once
#include "Shape.h"

class Factory
{
public:
	Factory(void);
	~Factory(void);
public:
	enum shapeType{m_eShapeNotSure,m_eShapeLine,m_eShapeRect,m_eShapeTriangle};//��������ͼ�ε�����,ö������
public:
	Shape* createShape(Factory::shapeType type);//����ͼ��
	Shape* createShape(Factory::shapeType type,const QPointF& start,const QPointF& end);//������startΪ���Ͻ�,endΪ���½ǵ�ͼ��
};

#endif