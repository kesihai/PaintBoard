

//////////////////////////////////////////////////
// 
// FileName: PaintBoard.h
// Creator : ���ĺ�
// Date    : 2016-11-30 13:55:04
// Comment : ���壬�����滭ͼ�μ�������¼���Ȼ����Ϣ����Manager����
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
	if(m_eShapeTypeWillBeDraw != Factory::m_eShapeNotSure) //��Ȼ֪��Ҫ��ʲôͼ�Σ����ǻ��µ�ͼ��
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
	else	//��Ȼ���ǻ��µ�ͼ�Σ���ô��Ҫ����û��ѡ����ǰ��ͼ�Σ�
	{
		//����ѡ����ǰ��ͼ�Σ�Ҫ���ǲ��ǰ����� CTRL ������ϣ� ���
		if(m_bKeyCtrlBePress)//���ǰ�������ϼ�
		{
			m_pActiveShape=m_maneger.getShapeBeSelected(event->pos());
			if(m_pActiveShape)
			{
				m_pActiveShape->setBoolDrawBounder(true);
				m_maneger.addCombinationShape(m_pActiveShape);//��Ϊ����û�е���ͼ�Σ�������Ҫ��һ���ж�
			}
		}
		else
		{
			//��Ȼ�ſ��� CTRL ���������ͼ�εİ�ť����ô�������ж��ǲ��ǵ�����ԭ��ѡ�е����ͼ������
			Shape* temp_activeShape= m_maneger.getShapeBeSelected(event->posF());////�õ������е�ͼ��
			if(temp_activeShape) //��һ���ǵõ���һ��ͼ�α�ѡ�У���һ�����������ͼ�εĲ���
			{
				temp_activeShape->isOnShape(event->posF());
			}
			if(temp_activeShape != m_pActiveShape)  //�������ѡ�е�ͼ�κ���һ��ѡ�е�ͼ�β�һ��,���ʱ������Ӧ�ñ������ѡ�е�ͼ��
			{
				if(m_pActiveShape)
				{
					m_pActiveShape->setBoolDrawBounder(false);
					m_pActiveShape->setBoolBounderBeSelected(false);
				}
				m_pActiveShape=temp_activeShape;  //����ڱ������ѡ�е�ͼ��
			}
			if(temp_activeShape && !m_maneger.m_shapeCombination.findShape(temp_activeShape))//������ͼ�β�����ϵ�ͼ�����棬��ô����ѡ���˱��ͼ�λ���û��ѡ��ͼ�� 
			{
				temp_activeShape=NULL;
			}
			if(temp_activeShape!=NULL)//�ſ���ϼ�CTRL �������µ��������ͼ�����棬��ôӦ�����������Ļͼ��ʱ��һ��
			{
				m_maneger.m_shapeCombination.setSelectedShape(temp_activeShape);
			}
			else  //��û�а�����ϼ�����û�е������ͼ�����棬����Ӧ��ȥ��������ϵı�־
			{
				m_maneger.setBoolNeedCombination(false);//��һ���Ὣ�������ͼ�εı߽���Ϊ���ɼ�
				if(m_pActiveShape != NULL) //����л���ڣ����� �� �ڲ��ڻ���ڵı߽�
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
	if (!m_bMousePress) //���������û�е��ж����϶��ƶ���Ҫ�ı�����״̬
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

	if (m_pActiveShape)//��Ȼ�л��
	{
		if (m_eShapeTypeWillBeDraw == Factory::m_eShapeNotSure) //���ƶ���ʱ��,���ͼ�β�֪������ô����ѡ��ԭ����ͼ����
		{
			m_maneger.move(m_pActiveShape,m_pointPrePress,event->posF());
			m_pointPrePress = event->posF();
		}
		else	// �����ǻ��µ�ͼ�Σ�Ϊ�˱�֤���ƶ�ʱʼ�ձ�֤ͼ��ԭ������״�����ʱ���ǲ���Ҫ�ı� m_pointPrePress��
		{
			m_pActiveShape->setInintPointDuringMove(event->posF()); //ֻ��Ҫ�����һ��������ĵ�Ϳ���ȷ��һ����ת�Ƕ�Ϊ0�ȵľ���
		}
	}
	update();
	QWidget::mouseMoveEvent(event);
}

void PaintBoard::mouseReleaseEvent(QMouseEvent *event)
{
	if (m_eShapeTypeWillBeDraw != Factory::m_eShapeNotSure)//����һ��ͼ�θոջ���
	{
		if (m_pActiveShape)
			m_pActiveShape->adjustIfUserPressAndFastReleaseDuringCreateNewShape();//�ոջ����ͼ��Ϊ��ֹ�û���һ�¾����Ϸſ�
		update();
		m_pActiveShape=NULL;//�ոջ����ͼ�β������ǻ��ͼ�Σ�ֻ�б�ѡ�е�ͼ�β���m_pActiveShape
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
		if(m_pActiveShape && (!m_maneger.m_shapeCombination.findShape(m_pActiveShape)))//��Ϊ�û���ѡ��һ��ͼ�κ󾭳���CTRL��,�������ú����
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
		m_maneger.deleteShape(m_pActiveShape);//ɾ��m_pActiveShape;
	}
	m_pActiveShape = NULL;
	update();
}

void PaintBoard::upperShape(Manager::shapeUpOrDown type)
{
	//���û������Ǿ��Ǻܺô�����������������ϣ�������ϵ�����£�ʲô�Ž�������һ���أ�
	//�������WPS�����ƹ��ܣ���ʵ���ǽ����ͼ������һ�������ܺ�����һ����û�н���
	if(m_maneger.isCombination())//����������״̬����ô�����״̬��ͼ��ȫ������һ��
	{
		m_maneger.upperCombination(type);
	}
	else
	{
		m_maneger.upperShape(m_pActiveShape,type);
	}
	update();
}