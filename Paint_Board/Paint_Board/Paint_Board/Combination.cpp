//////////////////////////////////////////////////
// 
// FileName: Combination.cpp
// Creator : 柯四海
// Date    : 2016-11-30T12:05:32
// Comment : 为实现图形间组合添加的类
//
//////////////////////////////////////////////////

#include "Combination.h"
#include "BounderType.h"

#if DEBUG
#define bug(msg) qDebug()<<msg;
#endif

Combination::Combination(void)
{
	m_shapeConbine.clear();
	bounder[0] = new BounderUp;
	bounder[1] = new BounderUpRight;
	bounder[2] = new BounderRight;
	bounder[3] = new BounderDownRight;
	bounder[4] = new BounderDown;
	bounder[5] = new BounderDownLeft;
	bounder[6] = new BounderLeft;
	bounder[7] = new BounderUpLeft;
	bounder[8] = new BounderCicle;
	m_shapeBeSelected = NULL;
}

Combination::~Combination(void)
{
	for(int i = 0; i < 9; i++)
	{	
		delete bounder[i];
		bounder[i] = NULL;
	}
}

bool Combination::findShape(Shape* shape)
{
	return m_shapeConbine.contains(shape);
}

void Combination::addShape(Shape* shape)
{
	Q_ASSERT(shape);
	shape->setBoolDrawBounder(true);
	m_shapeConbine.push_back(shape);
}

void Combination::remove(Shape* shape)
{
	if (!shape)
		return;

	int len = m_shapeConbine.size();
	for(int i = 0; i < len; i++)
	{
		if(m_shapeConbine[i] == shape) 
		{
			m_shapeConbine[i]->setBoolDrawBounder(false);
			m_shapeConbine.remove(i);
			return ;
		}
	}
}

void Combination::removeAll()
{
	setBoolDrawBounderForCombinetion(false);//在移除所有的图形之前，将他们的边界置为不可见
	m_shapeConbine.clear();
}


/* 下面的函数，对于一个组合的图形，当一个点点到上面，先检测是不是点到了边界拉伸矩形上面，
*  如果不是点到边界拉伸矩形，那么检查是不是点到body上面，如果点在边界的拉伸矩形或body上，
*  那么直接返回true，否则返回false;

*  对于一个组合的图形，当我们点在一个图形上，我们很方便改变这个图形的形状，可是其他的图形
*  形状的改变需要有它来确定，所以当我们找到这个图形后，应该马上为其他的图形找到对应边界拉伸框
*/
Shape* Combination::isOnShape(const QPointF& point)
{
	m_shapeBeSelected = NULL;//没有被选中
	for(int i=0; i < m_shapeConbine.size();i++)//先检查每一个矩形的边框是否被选中
	{
		if(m_shapeConbine[i]->isOnShapeBounder(point)) //这个时候m_shapeConbine[i]已将参数全部设置好
		{
			m_shapeBeSelected = m_shapeConbine[i];//这个时候这个选中的图形信息已经知道，可是别和它组合在一起的图形的信息还不知道，例如这个图形的上拉动矩形被选中，应该对应别的图形的哪一个拉动矩形被选中 
			m_shapeConbine[i]->setBoolBounderBeSelected(true);
			setSelectedPointForBrotherShape();
			setLenForBrotherShape();
			return m_shapeConbine[i];
		}
	}
	for(int i = 0; i < m_shapeConbine.size(); i++)
	{
		if(m_shapeConbine[i]->isOnshapeBody(point))
		{
			m_shapeBeSelected = m_shapeConbine[i]; //自己被选中，同时后面应该要为同伴选出哪一个部分被选中
			setSelectedPointForBrotherShape();
			return m_shapeConbine[i];
		}
	}
	return NULL;
}

void Combination::setSelectedShape(Shape* shape)
{
	if(!shape)
	{
		m_shapeBeSelected=NULL;
		this->removeAll();//
		return ;
	}
	m_shapeBeSelected = shape;//既然这个图形被选中，那么根据他边界被选中还是Body被选中为别的组合图形设置相应的选中部位
	if(m_shapeBeSelected->getBoolBounderBeSelected()) //如果是边界属性被选中了
	{
		setSelectedPointForBrotherShape();
		setLenForBrotherShape();
	}
	else
	{
		setSelectedPointForBrotherShape();
	}
}

void Combination::setSelectedPointForBrotherShape()
{
	if(!m_shapeBeSelected) 
		return ;//没有选中
	
	if(!m_shapeBeSelected->getBoolBounderBeSelected())
		return ; //选中的是body 
	
	m_bounderId.clear();
	for(int i = 0;i < m_shapeConbine.size(); i++)
	{
		m_bounderId.push_back(getPosFromSelectedShape(m_shapeBeSelected,m_shapeConbine[i]));
	}
}

void Combination::move(Shape* shape,const QPointF& from,const QPointF& to)
{
	if(!m_shapeBeSelected) 
		return;

	if(m_shapeBeSelected && !m_shapeBeSelected->getBoolBounderBeSelected()) //既然是选中的body，那么每一个直接移动
	{
		for(int i = 0;i < m_shapeConbine.size(); i++)
		{
			m_shapeConbine[i]->move(from, to);
		}
		return ;
	}
	else if(m_shapeBeSelected && m_shapeBeSelected->getSelectedBounder()->getBounderId() == Bounder::m_eBounderCicle)//既然选的不是身体，那么就是可以拉伸的矩形，也可能是选中的旋转的 ==8代表是选中了圆
	{
		BounderCicle* temp = (BounderCicle*)(m_shapeBeSelected->getSelectedBounder());
		double angle = temp->changeAngle(m_shapeBeSelected,from,to);
		for(int i=0;i<m_shapeConbine.size();i++)
		{
			QPointF cen=m_shapeConbine[i]->getCenterPointFromLeftBottomAndRightTop();
			m_shapeConbine[i]->setLeftTopPoint(m_shapeBeSelected->PointAfterRotation(cen,m_shapeConbine[i]->getLeftTopPoint(),angle));
			m_shapeConbine[i]->setLeftBottomPoint(m_shapeBeSelected->PointAfterRotation(cen,m_shapeConbine[i]->getLeftBottomPoint(),angle));
			m_shapeConbine[i]->setRightTopPoint(m_shapeBeSelected->PointAfterRotation(cen,m_shapeConbine[i]->getRightTopPoint(),angle));
			m_shapeConbine[i]->setRightBottomPoint(m_shapeBeSelected->PointAfterRotation(cen,m_shapeConbine[i]->getRightBottomPoint(),angle));
			m_shapeConbine[i]->setAngle(m_shapeConbine[i]->getAngle()+angle);
		}
	}
	else  //这个代表选中了旁边的拉伸框,这个时候需要分类讨论，看是选中四个角还是边界
	{
		int id = shape->getSelectedBounder()->getBounderId();
		//这里可以用 %2来判断，可是担心以后属性边界变多出现问题，就用这样暴力的方式,下面是处理选中四个顶点的情况
		if(id == Bounder::m_eBounderUpRight ||  id == Bounder::m_eBounderDownRight || id == Bounder::m_eBounderDownLeft || id == Bounder::m_eBounderUpLeft) 
		{
			Bounder* temp;
			QPointF point = shape->getSelectedBounder()->getCenterPoint();
			for(int i = 0;i < m_shapeConbine.size(); i++)
			{
				temp = bounder[m_bounderId[i]];
				temp->setCenterPointFromShape(m_shapeConbine[i]);
				temp->setAngle(m_shapeConbine[i]->getAngle());  
				QPointF _from = from-point+temp->getCenterPoint();
				QPointF _to = to-point+temp->getCenterPoint();
				temp->move(m_shapeConbine[i],_from,_to);
			}
		}
		else//这是处理边界矩形被选中的情况
		{  
			int pos=0;
			for(int i = 0; i < m_shapeConbine.size(); i++)
			{
				if(m_shapeConbine[i] == shape) 
				{
					pos=i;
					break;
				}
			}
			Bounder* temp;
			for(int i = 0;i < m_shapeConbine.size(); i++)
			{
				temp = bounder[m_bounderId[i]];
				temp->setCenterPointFromShape(m_shapeConbine[i]);
				temp->setAngle(m_shapeConbine[i]->getAngle());
				QPointF _to = to-from;
				temp->move(m_shapeConbine[i],QPointF(0,0),_to*m_bounderLen[i]/m_bounderLen[pos]);
			}
		}
	}
}

int Combination::getPosFromSelectedShape(Shape* from,Shape* to)
{
	Q_ASSERT(from && to);
	if(from->getSelectedBounder()->getBounderId() == Bounder::m_eBounderCicle)
		return Bounder::m_eBounderCicle;		//如果是选的旋转的矩形，那么直接可以确定组合里面别的也是选中矩形

	double toAngle = to->getAngle();
	double fromAngle = from->getAngle();
	toAngle = toAngle - fromAngle;
	
	while(toAngle<0) toAngle+=360;
	while(toAngle>=360) toAngle-=360;
	int ans = from->getSelectedBounder()->getBounderId();
	if(toAngle >= 0 && toAngle < 45)
		return (ans);
	if(toAngle >= 45 && toAngle < 135)
		return (ans-2+8)%8;
	if(toAngle >= 135 && toAngle < 225)
		return (ans-4+8)%8;
	if(toAngle >= 225 && toAngle < 315)
		return (ans-6+8)%8;
	return ans;
}

void Combination::setBoolDrawBounderForCombinetion(bool status)
{
	for(int i = 0;i < m_shapeConbine.size(); i++)
	{
		m_shapeConbine[i]->setBoolDrawBounder(status);
	}
}

double Combination::getDisFromOnePoint(Shape* shape,Bounder* bounder)
{
	if(bounder->getBounderId() == Bounder::m_eBounderUpLeft || bounder->getBounderId() == Bounder::m_eBounderDownRight)//Left_top   Right_bottom   
	{
		QPointF a = shape->getLeftTopPoint();
		QPointF b = shape->getRightBottomPoint();
		double x = a.x() - b.x();
		double y = a.y() - b.y();
		return sqrt(x * x + y * y);
	}
	else if(bounder->getBounderId() == Bounder::m_eBounderUpRight || bounder->getBounderId() == Bounder::m_eBounderDownLeft) //left_bottom,right_top
	{
		QPointF a = shape->getLeftBottomPoint();
		QPointF b = shape->getRightTopPoint();
		double x = a.x() - b.x();
		double y = a.y() - b.y();
		return sqrt(x * x + y * y);
	}
	else if(bounder->getBounderId() == Bounder::m_eBounderUp || bounder->getBounderId() == Bounder::m_eBounderDown)//上下
	{
		QPointF a = (shape->getLeftTopPoint() + shape->getRightTopPoint())/2;
		QPointF b = (shape->getLeftBottomPoint() + shape->getRightBottomPoint())/2;
		double x = a.x() - b.x();
		double y = a.y() - b.y();
		return sqrt(x * x + y * y);
	}
	else  //左右
	{
		QPointF a = (shape->getLeftBottomPoint() + shape->getLeftTopPoint())/2;
		QPointF b = (shape->getRightTopPoint() + shape->getRightBottomPoint())/2;
		double x = a.x() - b.x();
		double y = a.y() - b.y();
		return sqrt(x * x + y * y);
	}
}
void Combination::setLenForBrotherShape()
{
	m_bounderLen.clear();
	for(int i = 0; i < m_shapeConbine.size(); i++)
	{
		m_bounderLen.push_back(getDisFromOnePoint(m_shapeConbine[i],bounder[m_bounderId[i]]));
	}
}

void Combination::setPointFForBrotherShape()
{
	m_PointCombination.clear();
	Bounder* temp;
	for(int i = 0; i<m_shapeConbine.size(); i++)
	{
		temp = bounder[m_bounderId[i]];
		temp->setCenterPointFromShape(m_shapeConbine[i]);
		QPointF s = temp->getCenterPoint()-m_shapeConbine[i]->getCenterPointFromLeftBottomAndRightTop();
		double len = temp->disBetweenTwoPoint(QPointF(0,0),s);
		s = s / len;
		m_PointCombination.push_back(s);
	}
}

int Combination::getSize()
{
	return m_shapeConbine.size();
}
Shape* Combination::getShapeAt(int pos)
{
	return m_shapeConbine[pos];
}

void Combination::removeAt(int pos)
{
	if(pos < 0 || pos >= m_shapeConbine.size()) 
		return ;
	m_shapeConbine[pos]->setBoolDrawBounder(false);
	m_shapeConbine[pos]->setBoolBounderBeSelected(false);
	m_shapeConbine.remove(pos);
}