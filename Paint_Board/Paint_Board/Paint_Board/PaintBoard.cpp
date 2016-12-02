

//////////////////////////////////////////////////
// 
// FileName: PaintBoard.h
// Creator : 柯四海
// Date    : 2016-11-30 13:55:04
// Comment : 画板，在上面画图形监听鼠标事件，然后信息交给Manager处理
//
//////////////////////////////////////////////////

#include "PaintBoard.h"

PaintBoard::PaintBoard(QWidget *parent)
	:QWidget(parent)
{
	setFocusPolicy(Qt::ClickFocus);
	setMouseTracking(true);
	m_eShapeTypeWillBeDraw = Factory::m_eShapeNotSure;
	m_pActiveShape = NULL;
	m_pShapeBelowMouse  = NULL;
	m_bKeyCtrlBePress = false;
	m_bMousePress = false;
	resize(300,300);
}

PaintBoard::~PaintBoard()
{

}

void PaintBoard::setShapeType(Factory::shapeType type)
{
	m_eShapeTypeWillBeDraw = type;
}

void PaintBoard::mousePressEvent(QMouseEvent *event)
{
	if(m_eShapeTypeWillBeDraw != Factory::m_eShapeNotSure) //既然知道要画什么图形，就是画新的图形
	{
		if(m_pActiveShape)
		{
			m_pActiveShape->setBoolDrawBounder(false);
			m_pActiveShape->setBoolBounderBeSelected(false);
		}
		m_pActiveShape = m_maneger.createShape(m_eShapeTypeWillBeDraw,event->posF(),event->posF());
		if(m_pActiveShape)
			m_maneger.addShape(m_pActiveShape);
	}
	else	//既然不是画新的图形，那么就要看有没有选中以前的图形，
	{
		//对于选中以前的图形，要分是不是按下了 CTRL 键（组合） 情况
		if(m_bKeyCtrlBePress)//这是按下了组合键
		{
			m_pActiveShape=m_maneger.getShapeBeSelected(event->pos());
			if(m_pActiveShape)
			{
				m_pActiveShape->setBoolDrawBounder(true);
				m_maneger.addCombinationShape(m_pActiveShape);//因为可能没有点中图形，所以需要加一个判断
			}
		}
		else
		{
			//既然放开了 CTRL 这个添加组合图形的按钮，那么接下来判断是不是点在了原来选中的组合图形上面
			Shape* temp_activeShape= m_maneger.getShapeBeSelected(event->posF());////得到被点中的图形
			if(temp_activeShape) //上一步是得到哪一个图形被选中，下一步是设置这个图形的参数
			{
				temp_activeShape->isOnShape(event->posF());
			}
			if(temp_activeShape != m_pActiveShape)  //如果现在选中的图形和上一次选中的图形不一样,这个时候活动窗口应该变成现在选中的图形
			{
				if(m_pActiveShape)
				{
					m_pActiveShape->setBoolDrawBounder(false);
					m_pActiveShape->setBoolBounderBeSelected(false);
				}
				m_pActiveShape=temp_activeShape;  //活动窗口变成了新选中的图形
			}
			if(temp_activeShape && !m_maneger.m_shapeCombination.findShape(temp_activeShape))//如果这个图形不在组合的图形里面，那么就是选中了别的图形或者没有选中图形 
			{
				temp_activeShape=NULL;
			}
			if(temp_activeShape!=NULL)//放开组合键CTRL 并且重新点在了组合图形上面，那么应该组合类里面的活动图形时哪一个
			{
				m_maneger.m_shapeCombination.setSelectedShape(temp_activeShape);
			}
			else  //在没有按着组合键并且没有点在组合图形上面，首先应该去掉所以组合的标志
			{
				m_maneger.setBoolNeedCombination(false);//这一步会将所有组合图形的边界设为不可见
				if(m_pActiveShape != NULL) //如果有活动窗口，现在 点 在不在活动窗口的边界
				{
					m_pActiveShape->setBoolDrawBounder(true);
					if(m_pActiveShape->isOnShapeBounder(event->posF()))
					{
						m_pActiveShape->setBoolBounderBeSelected(true);
					}
					else
					{
						m_pActiveShape->setBoolBounderBeSelected(false);
						m_pActiveShape=m_maneger.getShapeBeSelected(event->posF());
						m_pActiveShape->isOnShape(event->posF());
					}
				}
			}
		}
	}
	m_pointPrePress=event->posF();
	update();
	m_bMousePress=true;
	QWidget::mousePressEvent(event);
}

void PaintBoard::mouseMoveEvent(QMouseEvent *event)
{
	if (!m_bMousePress) //这里是鼠标没有点中东西拖动移动需要改变鼠标的状态
	{
		m_pShapeBelowMouse=m_maneger.getShapeBeSelected(event->posF());
		if(m_pShapeBelowMouse)
		{
			int keyStatus=m_maneger.getKeyStatus(m_pShapeBelowMouse,event->posF());
			switch (keyStatus)
			{
			case Manager::m_eKeyStatusEmpty:
				setCursor(Qt::ArrowCursor);
				break;
			case Manager::m_eKeyStatusBody:
				setCursor(Qt::SizeAllCursor);
				break;
			case Manager::m_eKeyStatusUp:
			case Manager::m_eKeyStatusDown:
				setCursor(Qt::SizeVerCursor);
				break;
			case Manager::m_eKeyStatusLeft:
			case Manager::m_eKeyStatusRight:
				setCursor(Qt::SizeHorCursor);
				break;
			case Manager::m_eKeyStatusUpLeft:
			case Manager::m_eKeyStatusDownRight:
				setCursor(Qt::SizeFDiagCursor);
				break;
			case Manager::m_eKeyStatusUpRight:
			case Manager::m_eKeyStatusDownLeft:
				setCursor(Qt::SizeBDiagCursor);
				break;
			case Manager::m_eKeyStatusCicle:
				setCursor(Qt::OpenHandCursor);
				break;
			default:
				setCursor(Qt::ArrowCursor);
				break;
			}
		}
		else
		{
			setCursor(Qt::ArrowCursor);
		}
		update();
		QWidget::mouseMoveEvent(event);
		return ;
	}

	if (m_pActiveShape)//既然有活动的
	{
		if (m_eShapeTypeWillBeDraw == Factory::m_eShapeNotSure) //当移动的时候,如果图形不知道，那么就是选中原来的图形了
		{
			m_maneger.move(m_pActiveShape,m_pointPrePress,event->posF());
			m_pointPrePress = event->posF();
		}
		else	// 这里是画新的图形，为了保证在移动时始终保证图形原来的形状，这个时候是不需要改变 m_pointPrePress点
		{
			m_pActiveShape->setInintPointDuringMove(event->posF()); //只需要根距第一个点后后面的点就可以确定一个旋转角度为0度的矩形
		}
	}
	update();
	QWidget::mouseMoveEvent(event);
}

void PaintBoard::mouseReleaseEvent(QMouseEvent *event)
{
	if (m_eShapeTypeWillBeDraw != Factory::m_eShapeNotSure)//这是一个图形刚刚画完
	{
		if (m_pActiveShape)
			m_pActiveShape->adjustIfUserPressAndFastReleaseDuringCreateNewShape();//刚刚画完的图形为防止用户点一下就马上放开
		update();
		m_pActiveShape=NULL;//刚刚画完的图形不能算是活动的图形，只有被选中的图形才是m_pActiveShape
	}
	m_eShapeTypeWillBeDraw = Factory::m_eShapeNotSure;
	m_bMousePress=false;
	QWidget::mouseReleaseEvent(event);
}

void PaintBoard::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setBrush(Qt::white);
	painter.setRenderHint(QPainter::Antialiasing,true);
	m_maneger.readyToDraw(&painter);
	QWidget::paintEvent(event);
#if DEBUG
	qDebug()<<Shape::m_debugShapeNumber;
#endif
}

void PaintBoard::keyPressEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Control)  
	{
		m_bKeyCtrlBePress = true;
		m_maneger.setBoolNeedCombination(true);
		if(m_pActiveShape && (!m_maneger.m_shapeCombination.findShape(m_pActiveShape)))//因为用户会选中一个图形后经常按CTRL键,所以设置后面的
			m_maneger.m_shapeCombination.addShape(m_pActiveShape);
	}
	QWidget::keyPressEvent(event);
}

void PaintBoard::keyReleaseEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Control)
	{
		m_bKeyCtrlBePress = false;
	}
	QWidget::keyReleaseEvent(event);
}

void PaintBoard::deledeShape()
{
	if(m_maneger.isCombination())
	{
		m_maneger.deleteCombination();
		m_maneger.setBoolNeedCombination(false);
	}
	else
	{
		m_maneger.deleteShape(m_pActiveShape);//删除m_pActiveShape;
	}
	m_pActiveShape = NULL;
	update();
}

void PaintBoard::upperShape(Manager::shapeUpOrDown type)
{
	//如果没有组合那就是很好处理的情况，但是有组合，在有组合的情况下，什么才叫做向上一层呢？
	//经过检测WPS的上移功能，其实就是将这个图形上移一个，不管和上面一个有没有交集
	if(m_maneger.isCombination())//如果处于组合状态，那么将组合状态的图形全部上移一个
	{
		m_maneger.upperCombination(type);
	}
	else
	{
		m_maneger.upperShape(m_pActiveShape,type);
	}
	update();
}