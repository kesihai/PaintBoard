
//////////////////////////////////////////////////
// 
// FileName: PaintBoard.h
// Creator : 柯四海
// Date    : 2016-11-30 13:55:04
// Comment : 画板，在上面画图形监听鼠标事件，然后信息交给Manager处理
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
	void setShapeType(Factory::shapeType type); //设置接下来会被画的图形种类
	void deledeShape(); //响应删除按钮被点击的信号，这个时候回给Manager类发送删除图形的信号
	void upperShape(Manager::shapeUpOrDown type); //当上调 或者 下调的按钮被点击 ，给Manager发送  不同的type让Maneger进行相应的上调或下调

protected:
	void mousePressEvent(QMouseEvent *event) override;//重写鼠标按下事件
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void paintEvent(QPaintEvent *event) override;

protected:
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;

private: 
	Manager m_maneger; //管理类
	QPointF m_pointPrePress; //上一次鼠标点击的坐标
	Shape*  m_pActiveShape; //整个窗口中呗鼠标点中的图形指针，如果没有图形被点中，则为NULL
	bool	m_bKeyCtrlBePress; //CTRL键是不是已经按下
	bool	m_bMousePress; //为了监听鼠标移动状态而设置的属性
	Shape*  m_pShapeBelowMouse; //当鼠标移动时,正好位于鼠标下的图形
	Factory:: shapeType m_eShapeTypeWillBeDraw;// (enum)接下来会被画图形的种类
};
#endif

