
//////////////////////////////////////////////////
// 
// FileName: MainWindow.h
// Creator : 柯四海
// Date    : 2016-11-30 12:12:09
// Comment : 主窗口，负责创建画基本图形的触发按钮，方便用户操作，将用户的点击事件传递到画板(PaintBoard)中处理
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
		void rectActionTriggered();//画矩形的按钮被触发
		void lineActionTriggered();//画线 的按钮被触发
		void triangleActionTriggered();//画三角形的按钮被触发
		void upperActionTriggered(); //将图形上调一个的按钮被触发
		void downActionTriggered(); //将图形下调一个的按钮被触发
signals:
		void changeShape(Factory::shapeType type);//改变即将要画的矩形的种类
		void upperOrDownActionTriggered(Manager::shapeUpOrDown type);//上调或下调矩形的方法
private:
	QAction* m_rectAction;//画矩形的Action
	QAction* m_lineAction;//画Line的Action
	QAction* m_triangleAction;//画三角形的Action
	QAction* m_deleteAction;//删除的按钮
	QAction* m_upperAction;//上调一层的按钮
	QAction* m_downAction; //下调一层的按钮
	QToolBar* m_toolBar;  // 
	PaintBoard* m_paintBoard;
	QActionGroup* m_group;
};
#endif