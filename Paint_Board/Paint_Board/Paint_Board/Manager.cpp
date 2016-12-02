//////////////////////////////////////////////////
// 
// FileName: Manager.cpp
// Creator : 柯四海
// Date    : 2016-11-30T13:52:05
// Comment : 主要负责接收并处理画板(PaintBoard)的一些请求，例如画图形，移动，删除的 
//
//////////////////////////////////////////////////

#include "Manager.h"
#include <QQueue>
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

Manager::Manager(void)
{
	m_bCombination=false;
}

Manager::~Manager(void)
{
	int len = m_allShape.size();
	for(int i = len-1;i >= 0; i--)
	{
		Shape* temp = m_allShape[i];
		m_allShape.pop_back();
		delete temp;
	}
}
Shape* Manager::getShapeBeSelected(const QPointF& point)
{
	for (int i = m_allShape.size() - 1; i >= 0; i--) //判断着一个点在哪一个图形上，先判断是不是在边界上
	{
		if (m_allShape[i]->isOnShapeBounder(point)) //如果这个点在边界上
			return m_allShape[i];		//返回这个图形
	}
	for (int i = m_allShape.size() - 1; i >= 0; i--)  //现在判断在不在图形的里面,也就是除开边界的位置
	{
		if (m_allShape[i]->isOnshapeBody(point)) 
			return m_allShape[i];
	}
	return NULL;
}

void Manager::addShape(Shape* shape)
{
	Q_ASSERT(shape);
	m_allShape.push_back(shape);
}

void Manager::readyToDraw(QPainter* painter)
{
	m_shapeCombination.setBoolDrawBounderForCombinetion(true);
	int len=m_allShape.size();
	//对于每一个图形，都是先画Body，再画周围虚线,再画边界矩形属性
	for(int i=0;i < len; i++)	
	{
		m_allShape[i]->readyToDrawing();
		m_allShape[i]->drawing(painter);
	}
	for(int i = 0; i< len; i++)
	{
		if(m_allShape[i]->getBoolDrawBounder())
			m_allShape[i]->drawBounderLine(painter);
	}
	for(int i=0; i < len; i++)
	{
		if(m_allShape[i]->getBoolDrawBounder())
			m_allShape[i]->drawBounder(painter);
	}
}

Shape* Manager::createShape(Factory::shapeType type,const QPointF& start,const QPointF& end)
{
	return m_factory.createShape(type,start,end);
}

void Manager::addCombinationShape(Shape* shape)//每一次添加时，需要看看是不是已经有了，如果已经有了那就删除掉
{
	if(m_shapeCombination.findShape(shape))
	{
		shape->setBoolDrawBounder(false);
		m_shapeCombination.remove(shape);
	}
	else
	{
		shape->setBoolDrawBounder(true);
		m_shapeCombination.addShape(shape);
	}
}

void Manager::clearCombinationShape()
{
	m_shapeCombination.removeAll();
}

void Manager::setBoolDrawBounderForCombination(bool status)
{
	m_shapeCombination.setBoolDrawBounderForCombinetion(status);
}

void Manager::setBoolNeedCombination(bool status)
{
	m_bCombination=status;
	if(status==false)
	{
		m_shapeCombination.setBoolDrawBounderForCombinetion(false);//选中的不是Combination里面的图形时，我们应该讲Combination里面的图形的边界设为不可见
		m_shapeCombination.removeAll();//并且清空vector
	}
}

bool Manager::isCombination()
{
	return m_bCombination;
}

void Manager::move(Shape* shape,const QPointF& from,const QPointF& to)
{
	Q_ASSERT(shape);
	if(m_bCombination)//如果是组合状态下的移动，那么久调用组合类的移动
	{
		m_shapeCombination.move(shape,from,to);
	}
	else 
	{
		shape->move(from,to);//否则就是单个对象的移动
	}
}

int Manager::getKeyStatus(Shape* shape,const QPointF& point)
{
	Q_ASSERT(shape);
	return shape->getKeyStatus(point);
}

void Manager::deleteCombination()
{
	int len = m_shapeCombination.getSize();
	for(int i = len-1; i >= 0; i--) //依次取出 组合在一起的图形，并且去掉
	{
		Shape* temp = m_shapeCombination.getShapeAt(i);
		m_shapeCombination.removeAt(i);
		this->deleteShape(temp);
	}
}

void Manager::deleteShape(Shape* shape)
{
	if(!shape) 
		return;

	for(int i = 0; i <= m_allShape.size(); i++)
	{
		if(m_allShape[i] == shape)
		{
			Shape* temp = m_allShape[i];
			m_allShape.remove(i);
			delete temp;
			return ;
		}
	}
}

void Manager::upperShape(Shape* shape,Manager::shapeUpOrDown tyte)//1 代表上移一位，-1代表下移一位
{
	int len = m_allShape.size();
	int pos;
	for(pos = 0;pos < len; pos++)
	{
		if(m_allShape[pos] == shape) break;
	}
	if (pos >= len)
		return;		//没有这个图形

	if(tyte == Manager::m_eUp)
	{
		if(pos < len-1 && pos >= 0 )
		{
			swap(m_allShape[pos],m_allShape[pos+1]);
		}
	}
	else if(tyte == Manager::m_eDown)
	{
		if(pos > 0 && pos < len)
		{
			swap(m_allShape[pos],m_allShape[pos-1]);
		}
	}
}

void Manager::upperCombination(Manager::shapeUpOrDown type)//操作整个组合:  1 代表上移一位，-1代表下移一位
{
	if( !m_bCombination) 
		return;

	if(type == Manager::m_eUp) //如果是上移
	{
		int len = m_allShape.size();
		for(int i= len - 1; i >= 0; i--) //那么从反向移动
		{
			if(m_shapeCombination.findShape(m_allShape[i]))
			{
				 if(i == len-1)
					 continue; //最后一个没有必要移动
				 if(m_shapeCombination.findShape(m_allShape[i+1]))
					 continue;//如果要移动的那一个后面也是要移动的，那就没有必要移动
				 swap(m_allShape[i],m_allShape[i+1]);
			}
		}
	}
	else if(type == m_eDown)//向下移动
	{
		int len = m_allShape.size();
		for(int i = 0; i < len; i++)
		{
			if(m_shapeCombination.findShape(m_allShape[i]))
			{
				if(i == 0)
					continue; //第一个没有必要下移
				if(m_shapeCombination.findShape(m_allShape[i-1])) 
					continue;//如果下一个也是要下移的，那么没有必要下移
				swap(m_allShape[i], m_allShape[i-1]); 
			}
		}
	}
}