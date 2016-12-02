
///////////////////////////////////////////////////////////////////////////
//
//  FileName: Factory.cpp
//  Createor: 柯四海
//  Date:     2016-11-25
//  Comment:  简单工厂类，专门负责产生图形
//
//
///////////////////////////////////////////////////////////////////////////

#include "Factory.h"
#include "Rect.h"
#include "Line.h"
#include "Triangle.h"

Factory::Factory(void)
{
}


Factory::~Factory(void)
{

}

Shape* Factory::createShape(Factory::shapeType type)
{
	switch(type)
	{
	case m_eShapeNotSure:
		return NULL;
	case m_eShapeLine:
		return new Line;
	case m_eShapeRect:
		return new Rect;
	case m_eShapeTriangle:
		return new Triangle;
	default:
		return NULL;
	}
}
Shape* Factory::createShape(Factory::shapeType type,const QPointF& start,const QPointF& end)
{
	switch (type)
	{ 
	case m_eShapeNotSure:
		return NULL;
	case m_eShapeLine:
		return new Line(start,end);
	case m_eShapeRect:
		return new Rect(start,end);
	case m_eShapeTriangle:
		return new Triangle(start,end);
	default:
		return NULL;
	}
}