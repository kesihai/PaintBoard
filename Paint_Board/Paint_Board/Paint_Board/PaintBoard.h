
//////////////////////////////////////////////////
// 
// FileName: PaintBoard.h
// Creator : ���ĺ�
// Date    : 2016-11-30 13:55:04
// Comment : ���壬�����滭ͼ�μ�������¼���Ȼ����Ϣ����Manager����
//
//////////////////////////////////////////////////

#ifndef _PAINTBOARD_H
#define _PAINTBOARD_H

#include <QtGui/QMainWindow>
#include "Manager.h"

class PaintBoard : public QWidget{
	Q_OBJECT
public:
	PaintBoard(QWidget *parent = 0);
	~PaintBoard();

public slots:
	void setShapeType(Factory::shapeType type); //���ý������ᱻ����ͼ������
	void deledeShape(); //��Ӧɾ����ť��������źţ����ʱ��ظ�Manager�෢��ɾ��ͼ�ε��ź�
	void upperShape(Manager::shapeUpOrDown type); //���ϵ� ���� �µ��İ�ť����� ����Manager����  ��ͬ��type��Maneger������Ӧ���ϵ����µ�

protected:
	void mousePressEvent(QMouseEvent *event) override;//��д��갴���¼�
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void paintEvent(QPaintEvent *event) override;

protected:
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;

private: 
	Manager m_maneger; //������
	QPointF m_pointPrePress; //��һ�������������
	Shape*  m_pActiveShape; //�����������������е�ͼ��ָ�룬���û��ͼ�α����У���ΪNULL
	bool	m_bKeyCtrlBePress; //CTRL���ǲ����Ѿ�����
	bool	m_bMousePress; //Ϊ�˼�������ƶ�״̬�����õ�����
	Shape*  m_pShapeBelowMouse; //������ƶ�ʱ,����λ������µ�ͼ��
	Factory:: shapeType m_eShapeTypeWillBeDraw;// (enum)�������ᱻ��ͼ�ε�����
};
#endif

