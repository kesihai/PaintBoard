//////////////////////////////////////////////////
// 
// FileName: Manager.cpp
// Creator : ���ĺ�
// Date    : 2016-11-30T13:52:05
// Comment : ��Ҫ������ղ�������(PaintBoard)��һЩ�������续ͼ�Σ��ƶ���ɾ���� 
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
	for (int i = m_allShape.size() - 1; i >= 0; i--) //�ж���һ��������һ��ͼ���ϣ����ж��ǲ����ڱ߽���
	{
		if (m_allShape[i]->isOnShapeBounder(point)) //���������ڱ߽���
			return m_allShape[i];		//�������ͼ��
	}
	for (int i = m_allShape.size() - 1; i >= 0; i--)  //�����ж��ڲ���ͼ�ε�����,Ҳ���ǳ����߽��λ��
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
	//����ÿһ��ͼ�Σ������Ȼ�Body���ٻ���Χ����,�ٻ��߽��������
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

void Manager::addCombinationShape(Shape* shape)//ÿһ�����ʱ����Ҫ�����ǲ����Ѿ����ˣ�����Ѿ������Ǿ�ɾ����
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
		m_shapeCombination.setBoolDrawBounderForCombinetion(false);//ѡ�еĲ���Combination�����ͼ��ʱ������Ӧ�ý�Combination�����ͼ�εı߽���Ϊ���ɼ�
		m_shapeCombination.removeAll();//�������vector
	}
}

bool Manager::isCombination()
{
	return m_bCombination;
}

void Manager::move(Shape* shape,const QPointF& from,const QPointF& to)
{
	Q_ASSERT(shape);
	if(m_bCombination)//��������״̬�µ��ƶ�����ô�õ����������ƶ�
	{
		m_shapeCombination.move(shape,from,to);
	}
	else 
	{
		shape->move(from,to);//������ǵ���������ƶ�
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
	for(int i = len-1; i >= 0; i--) //����ȡ�� �����һ���ͼ�Σ�����ȥ��
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

void Manager::upperShape(Shape* shape,Manager::shapeUpOrDown tyte)//1 ��������һλ��-1��������һλ
{
	int len = m_allShape.size();
	int pos;
	for(pos = 0;pos < len; pos++)
	{
		if(m_allShape[pos] == shape) break;
	}
	if (pos >= len)
		return;		//û�����ͼ��

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

void Manager::upperCombination(Manager::shapeUpOrDown type)//�����������:  1 ��������һλ��-1��������һλ
{
	if( !m_bCombination) 
		return;

	if(type == Manager::m_eUp) //���������
	{
		int len = m_allShape.size();
		for(int i= len - 1; i >= 0; i--) //��ô�ӷ����ƶ�
		{
			if(m_shapeCombination.findShape(m_allShape[i]))
			{
				 if(i == len-1)
					 continue; //���һ��û�б�Ҫ�ƶ�
				 if(m_shapeCombination.findShape(m_allShape[i+1]))
					 continue;//���Ҫ�ƶ�����һ������Ҳ��Ҫ�ƶ��ģ��Ǿ�û�б�Ҫ�ƶ�
				 swap(m_allShape[i],m_allShape[i+1]);
			}
		}
	}
	else if(type == m_eDown)//�����ƶ�
	{
		int len = m_allShape.size();
		for(int i = 0; i < len; i++)
		{
			if(m_shapeCombination.findShape(m_allShape[i]))
			{
				if(i == 0)
					continue; //��һ��û�б�Ҫ����
				if(m_shapeCombination.findShape(m_allShape[i-1])) 
					continue;//�����һ��Ҳ��Ҫ���Ƶģ���ôû�б�Ҫ����
				swap(m_allShape[i], m_allShape[i-1]); 
			}
		}
	}
}