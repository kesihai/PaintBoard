
//////////////////////////////////////////////////
// 
// FileName: Manager.h
// Creator : ���ĺ�
// Date    : 2016-11-30T13:52:05
// Comment : ��Ҫ������ղ�������(PaintBoard)��һЩ�������续ͼ�Σ��ƶ���ɾ���� 
//
//////////////////////////////////////////////////

#ifndef _MANAGER_H_
#define _MANAGER_H_

#pragma once
#include "Shape.h"
#include "Factory.h"
#include "Combination.h"
#include <QVector>

class Manager
{
public:
	Manager(void);
	~Manager(void);

public:
	void addShape(Shape* shape); //����µ�ͼ��
	void readyToDraw(QPainter* painter); //׼����ͼ��
	void move(Shape* shape,const QPointF& from,const QPointF& to); //�ƶ���������ô�ƶ�������Ƿ񴥷����������ԣ��������ϣ���ô�ƶ����ͼ�Σ������ƶ���ǰ��ѡ�е�ͼ��
	void setBoolDrawBounderForCombination(bool status);//�Ƿ�Ϊ����໭�߽�
	void setBoolNeedCombination(bool status); //�����Ƿ�����ϵ����֮��
	int  getKeyStatus(Shape* shape,const QPointF& point); //����ƶ�ʱ������������õ�����״̬
	bool isCombination(); //�õ��Ƿ�����ϵ�״̬
	Shape* getShapeBeSelected(const QPointF& point);//�õ���ѡ�е�ͼ�Σ��ȿ��ɼ��߽�ͼ�εı߽��ǲ��Ǳ�ѡ��
	Shape* createShape(Factory::shapeType type,const QPointF& start,const QPointF& end);//����һ��ͼ��

public:
	enum keyStatus{ m_eKeyStatusEmpty =-2,m_eKeyStatusBody =-1,m_eKeyStatusUp, m_eKeyStatusUpRight,m_eKeyStatusRight,m_eKeyStatusDownRight,
					m_eKeyStatusDown,m_eKeyStatusDownLeft,m_eKeyStatusLeft,m_eKeyStatusUpLeft,m_eKeyStatusCicle};
	enum shapeUpOrDown{m_eDown,m_eUp};

public:
	void addCombinationShape(Shape* shape);//Ϊ��������һ��ͼ�� 
	void clearCombinationShape();//��������
	void deleteCombination();//ɾ������࣬���ɾ������������ͼ�α�ɾ��
	void deleteShape(Shape* shape);//ɾ��һ��ͼ�Σ����ͼ�λᱻ����
	void upperShape(Shape* shape,Manager::shapeUpOrDown tyte);//���ƻ�����һ��ͼ�Σ����ݺ���Ĳ���   1 ��������һλ��-1��������һλ
	void upperCombination(Manager::shapeUpOrDown type);//���ƻ����������������  1 ��������һλ��-1��������һλ
	Combination m_shapeCombination;

private:
	QVector<Shape*> m_allShape;//���б�������ͼ�ζ����������
	Factory m_factory; //�򵥹����࣬��Ҫ�������ͼ��
	bool m_bCombination;//Ŀǰ�ǲ��Ǵ������״̬
};

#endif