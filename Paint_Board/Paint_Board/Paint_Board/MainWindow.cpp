//////////////////////////////////////////////////
// 
// FileName: MainWindow.cpp
// Creator : ���ĺ�
// Date    : 2016-11-30 12:12:09
// Comment : �����ڣ����𴴽�������ͼ�εĴ�����ť�������û����������û��ĵ���¼����ݵ�����(PaintBoard)�д���
//
//////////////////////////////////////////////////

#include "MainWindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget* parent):QMainWindow(parent)
{
	m_group=new QActionGroup(this);
	m_rectAction = new QAction("Rect",NULL);
	m_lineAction = new QAction("Line",NULL);
	m_triangleAction = new QAction("Triangle",NULL);
	m_deleteAction = new QAction("Delete",NULL);
	m_upperAction = new QAction("upper",NULL);
	m_downAction = new QAction("Down",NULL);
	m_toolBar = addToolBar("tool");

	m_group->addAction(m_lineAction);
	m_group->addAction(m_rectAction);
	m_group->addAction(m_triangleAction);
	m_group->addAction(m_upperAction);
	m_group->addAction(m_downAction);
	m_group->addAction(m_deleteAction);

	m_toolBar->addAction(m_lineAction);
	m_toolBar->addAction(m_rectAction);
	m_toolBar->addAction(m_triangleAction);
	m_toolBar->addAction(m_deleteAction);
	m_toolBar->addAction(m_upperAction);
	m_toolBar->addAction(m_downAction);

	m_paintBoard = new PaintBoard;
	setCentralWidget(m_paintBoard);
	connect(m_rectAction, SIGNAL(triggered()), this, SLOT(rectActionTriggered()));
	connect(m_lineAction, SIGNAL(triggered()), this, SLOT(lineActionTriggered()));
	connect(m_triangleAction, SIGNAL(triggered()), this, SLOT(triangleActionTriggered()));

	connect(m_upperAction,SIGNAL(triggered()),this, SLOT(upperActionTriggered()));
	connect(m_downAction,SIGNAL(triggered()),this, SLOT(downActionTriggered()));
	connect(this,SIGNAL(upperOrDownActionTriggered(Manager::shapeUpOrDown)), m_paintBoard, SLOT(upperShape(Manager::shapeUpOrDown)));

	connect(m_deleteAction, SIGNAL(triggered()), m_paintBoard, SLOT(deledeShape()));
	connect(this, SIGNAL(changeShape(Factory::shapeType)), m_paintBoard, SLOT(setShapeType(Factory::shapeType)));
	resize(800, 800);
}

MainWindow::~MainWindow(void)
{

}
void MainWindow::rectActionTriggered()
{
	emit changeShape(Factory::m_eShapeRect);
}
void MainWindow::lineActionTriggered()
{
	emit changeShape(Factory::m_eShapeLine);
}
void MainWindow::triangleActionTriggered()
{
	emit changeShape(Factory::m_eShapeTriangle);
}
void MainWindow::upperActionTriggered()
{
	emit upperOrDownActionTriggered(Manager::m_eUp);
}
void MainWindow::downActionTriggered()
{
	emit upperOrDownActionTriggered(Manager::m_eDown);
}