
//////////////////////////////////////////////////
// 
// FileName: MainWindow.h
// Creator : ���ĺ�
// Date    : 2016-11-30 12:12:09
// Comment : �����ڣ����𴴽�������ͼ�εĴ�����ť�������û����������û��ĵ���¼����ݵ�����(PaintBoard)�д���
//
//////////////////////////////////////////////////

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#pragma once
#include <QtGui/QMainWindow>
#include "Factory.h"
#include "PaintBoard.h"
class MainWindow :public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent=0);
	~MainWindow();
	public slots:
		void rectActionTriggered();//�����εİ�ť������
		void lineActionTriggered();//���� �İ�ť������
		void triangleActionTriggered();//�������εİ�ť������
		void upperActionTriggered(); //��ͼ���ϵ�һ���İ�ť������
		void downActionTriggered(); //��ͼ���µ�һ���İ�ť������
signals:
		void changeShape(Factory::shapeType type);//�ı伴��Ҫ���ľ��ε�����
		void upperOrDownActionTriggered(Manager::shapeUpOrDown type);//�ϵ����µ����εķ���
private:
	QAction* m_rectAction;//�����ε�Action
	QAction* m_lineAction;//��Line��Action
	QAction* m_triangleAction;//�������ε�Action
	QAction* m_deleteAction;//ɾ���İ�ť
	QAction* m_upperAction;//�ϵ�һ��İ�ť
	QAction* m_downAction; //�µ�һ��İ�ť
	QToolBar* m_toolBar;  // 
	PaintBoard* m_paintBoard;
	QActionGroup* m_group;
};
#endif