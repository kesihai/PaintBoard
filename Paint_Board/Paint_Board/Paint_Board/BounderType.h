//////////////////////////////////////////////////
// 
// FileName: BounderType.h
// Creator : ���ĺ�
// Date    : 2016-11-30 11:20:44
// Comment : ��һЩ�̳� Bounder �������� д������൱��ͼ�α߽�������ļ���
//
//////////////////////////////////////////////////

#ifndef _BOUNDERTYPE_H_
#define _BOUNDERTYPE_H_

#include "Bounder.h"

//-----------------------------------------------------------------------------------------
class BounderCicle :
	public Bounder
{
public:
	BounderCicle(void);
	~BounderCicle(void);

public:
	virtual void drawing(QPainter* painter) override;//���Լ��ĺ���
	virtual void move(Shape* shape, const QPointF& from, const QPointF& to) override;//�����ͼ�α�ѡ��ʱ�����ұ����� from�϶���toӦ�øı���Ҫ�������һЩ����
	virtual void setCenterPointFromShape(Shape* shape) override;//�Լ�����Shape�ṩ����Ϣ�������Լ�����Ϣ

public:
	double changeAngle(Shape* shape, QPointF from, QPointF to);//����from �ƶ���to �������Ӧ�øı�Shapeͼ�ε���һЩ����(�������Ӧ���Ǹı���ͼ�ε���ת�Ƕȣ���Ӧ���ĸ��������Ҳ��ı�)
	double disBetweenTwoPoint(const QPointF& from, const QPointF& to); //�õ�������֮��ľ���

private:
	const static int ms_nStartAngle = 30*16; 
	const static int ms_nEndAngle = 300*16;
	const static double ms_feps /* = 1e-8   С��������͵���0 */ ;
};


//-----------------------------------------------------------------------------------------
class BounderDown :public Bounder
{
public:
	BounderDown(void);
	~BounderDown(void);
public:
	virtual void move(Shape* shape,const QPointF& from, const QPointF& to) override;
	virtual void setCenterPointFromShape(Shape* shape) override;
};


//-----------------------------------------------------------------------------------------
class BounderDownLeft :public Bounder
{
public:
	BounderDownLeft(void);
	~BounderDownLeft(void);
public:
	virtual void move(Shape* shape,const QPointF& from, const QPointF& to) override;
	virtual void setCenterPointFromShape(Shape* shape) override;
};


//-----------------------------------------------------------------------------------------
class BounderDownRight :public Bounder{
public:
	BounderDownRight(void);
	~BounderDownRight(void);
public:
	virtual void move(Shape* shape,const QPointF& from,const QPointF& to) override;
	virtual void setCenterPointFromShape(Shape* shape) override;
};


//-----------------------------------------------------------------------------------------
class BounderLeft :
	public Bounder
{
public:
	BounderLeft(void);
	~BounderLeft(void);
public:
	virtual void move(Shape* shape,const QPointF& from,const QPointF& to) override;
	virtual void setCenterPointFromShape(Shape* shape) override;
};

//-----------------------------------------------------------------------------------------
class BounderRight :
	public Bounder
{
public:
	BounderRight(void);
	~BounderRight(void);
public:
	virtual void move(Shape* shape,const QPointF& from, const QPointF& to) override;
	virtual void setCenterPointFromShape(Shape* shape) override;
};


//-----------------------------------------------------------------------------------------
class BounderUp :
	public Bounder
{
public:
	BounderUp(void);
	~BounderUp(void);
public:
	virtual void move(Shape* shape,const QPointF& from, const QPointF& to) override;
	virtual void setCenterPointFromShape(Shape* shape) override;
};


//-----------------------------------------------------------------------------------------
class BounderUpLeft :
	public Bounder
{
public:
	BounderUpLeft(void);
	~BounderUpLeft(void);
public:
	virtual void move(Shape* shape,const QPointF& from, const QPointF& to) override;
	virtual void setCenterPointFromShape(Shape* shape) override;
};


//----------------------------------------------------------------------------------------------
class BounderUpRight : public Bounder
{
public:
	BounderUpRight(void);
	~BounderUpRight(void);
public:
	virtual void move(Shape* shape,const QPointF& from,const QPointF& to) override;
	virtual void setCenterPointFromShape(Shape* shape) override;
};

#endif