//////////////////////////////////////////////////
// 
// FileName: Combination.cpp
// Creator : ���ĺ�
// Date    : 2016-11-30T12:05:32
// Comment : Ϊʵ��ͼ�μ������ӵ���
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
	setBoolDrawBounderForCombinetion(false);//���Ƴ����е�ͼ��֮ǰ�������ǵı߽���Ϊ���ɼ�
	m_shapeConbine.clear();
}


/* ����ĺ���������һ����ϵ�ͼ�Σ���һ����㵽���棬�ȼ���ǲ��ǵ㵽�˱߽�����������棬
*  ������ǵ㵽�߽�������Σ���ô����ǲ��ǵ㵽body���棬������ڱ߽��������λ�body�ϣ�
*  ��ôֱ�ӷ���true�����򷵻�false;

*  ����һ����ϵ�ͼ�Σ������ǵ���һ��ͼ���ϣ����Ǻܷ���ı����ͼ�ε���״������������ͼ��
*  ��״�ĸı���Ҫ������ȷ�������Ե������ҵ����ͼ�κ�Ӧ������Ϊ������ͼ���ҵ���Ӧ�߽������
*/
Shape* Combination::isOnShape(const QPointF& point)
{
	m_shapeBeSelected = NULL;//û�б�ѡ��
	for(int i=0; i < m_shapeConbine.size();i++)//�ȼ��ÿһ�����εı߿��Ƿ�ѡ��
	{
		if(m_shapeConbine[i]->isOnShapeBounder(point)) //���ʱ��m_shapeConbine[i]�ѽ�����ȫ�����ú�
		{
			m_shapeBeSelected = m_shapeConbine[i];//���ʱ�����ѡ�е�ͼ����Ϣ�Ѿ�֪�������Ǳ���������һ���ͼ�ε���Ϣ����֪�����������ͼ�ε����������α�ѡ�У�Ӧ�ö�Ӧ���ͼ�ε���һ���������α�ѡ�� 
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
			m_shapeBeSelected = m_shapeConbine[i]; //�Լ���ѡ�У�ͬʱ����Ӧ��ҪΪͬ��ѡ����һ�����ֱ�ѡ��
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
	m_shapeBeSelected = shape;//��Ȼ���ͼ�α�ѡ�У���ô�������߽类ѡ�л���Body��ѡ��Ϊ������ͼ��������Ӧ��ѡ�в�λ
	if(m_shapeBeSelected->getBoolBounderBeSelected()) //����Ǳ߽����Ա�ѡ����
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
		return ;//û��ѡ��
	
	if(!m_shapeBeSelected->getBoolBounderBeSelected())
		return ; //ѡ�е���body 
	
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

	if(m_shapeBeSelected && !m_shapeBeSelected->getBoolBounderBeSelected()) //��Ȼ��ѡ�е�body����ôÿһ��ֱ���ƶ�
	{
		for(int i = 0;i < m_shapeConbine.size(); i++)
		{
			m_shapeConbine[i]->move(from, to);
		}
		return ;
	}
	else if(m_shapeBeSelected && m_shapeBeSelected->getSelectedBounder()->getBounderId() == Bounder::m_eBounderCicle)//��Ȼѡ�Ĳ������壬��ô���ǿ�������ľ��Σ�Ҳ������ѡ�е���ת�� ==8������ѡ����Բ
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
	else  //�������ѡ�����Աߵ������,���ʱ����Ҫ�������ۣ�����ѡ���ĸ��ǻ��Ǳ߽�
	{
		int id = shape->getSelectedBounder()->getBounderId();
		//��������� %2���жϣ����ǵ����Ժ����Ա߽���������⣬�������������ķ�ʽ,�����Ǵ���ѡ���ĸ���������
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
		else//���Ǵ���߽���α�ѡ�е����
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
		return Bounder::m_eBounderCicle;		//�����ѡ����ת�ľ��Σ���ôֱ�ӿ���ȷ�����������Ҳ��ѡ�о���

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
	else if(bounder->getBounderId() == Bounder::m_eBounderUp || bounder->getBounderId() == Bounder::m_eBounderDown)//����
	{
		QPointF a = (shape->getLeftTopPoint() + shape->getRightTopPoint())/2;
		QPointF b = (shape->getLeftBottomPoint() + shape->getRightBottomPoint())/2;
		double x = a.x() - b.x();
		double y = a.y() - b.y();
		return sqrt(x * x + y * y);
	}
	else  //����
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