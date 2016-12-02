///////////////////////////////////////////////////////////////////////////
//
//  FileName: Factory.h
//  Createor: 柯四海
//  Date:     2016-11-25
//  Comment:  简单工厂类，专门负责产生图形
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
	enum shapeType{m_eShapeNotSure,m_eShapeLine,m_eShapeRect,m_eShapeTriangle};//工厂里面图形的种类,枚举类型
public:
	Shape* createShape(Factory::shapeType type);//产生图形
	Shape* createShape(Factory::shapeType type,const QPointF& start,const QPointF& end);//产生以start为左上角,end为右下角的图形
};

#endif