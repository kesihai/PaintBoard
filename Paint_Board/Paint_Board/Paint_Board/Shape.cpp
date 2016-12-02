
//////////////////////////////////////////////////
// 
// FileName: Shape.cpp
// Creator : ���ĺ�
// Date    : 2016-11-18 11:50:56
// Comment : ����ͼ�εĻ��࣬������һЩ�����ķ���������
//
//////////////////////////////////////////////////

#include "Shape.h"
#include "BounderType.h"
#include "Manager.h"

#if DEBUG
int Shape::m_debugShapeNumber = 0;
#endif

const double Shape::ms_fSmallEnough = 0.5;

Shape::Shape(void):m_angle(0)
{
	QPointF s(-4,-4);
	m_leftTopPoint = s;
	m_leftBottomPoint = s;
	m_rightTopPoint = s;

	m_bDrawBounder = false;
	m_pBounderBeSelected = NULL;
	m_bBounderBeSelected = false;
	m_firstPressPoint = s;
}

Shape::~Shape(void)
{
	Bounder* bounder;
	int len = m_pBounderCollection.size();
	for (int i = len-1; i >= 0; i--)
	{
		bounder = m_pBounderCollection[i];
		m_pBounderCollection.pop_back();
		delete bounder;
	}
}

Shape::Shape(const QPointF& leftTopPoint, const QPointF& rigthBottomPoint) : m_angle(0)
{
	m_leftTopPoint = leftTopPoint;
	m_rightBottomPoint = rigthBottomPoint;
	m_leftBottomPoint.setX(m_leftTopPoint.x());
	m_leftBottomPoint.setY(m_rightBottomPoint.y());
	m_rightTopPoint.setX(m_rightBottomPoint.x());
	m_rightTopPoint.setY(m_leftTopPoint.y());

	m_bDrawBounder = false;
	m_pBounderBeSelected = NULL;
	m_bBounderBeSelected = false;
	m_firstPressPoint = leftTopPoint;
}

void Shape::setAngle(const double& angle)
{
	m_angle=angle;
	while(m_angle>360) m_angle-=360;
	while(m_angle<0) m_angle+=360;
}

void Shape::move(const QPointF& from, const QPointF& to)
{
	if (m_bBounderBeSelected && m_pBounderBeSelected)
	{
		m_pBounderBeSelected->move(this, from, to);
		return ;
	}
	QPointF temp = to - from;
	m_leftTopPoint += temp;
	m_leftBottomPoint += temp;
	m_rightTopPoint += temp;
	m_rightBottomPoint += temp;
}

void Shape::drawBounder(QPainter* painter)
{
	Q_ASSERT(painter);
	if (!m_bDrawBounder)
		return ;
	setBounder();
	int len = m_pBounderCollection.size();
	for(int i = 0; i < len; i++)
	{
		m_pBounderCollection[i]->drawing(painter);
	}
}

void Shape::drawBounderLine(QPainter* painter)
{
	return ;
}

void Shape::readyToDrawing()
{
	setBounder();
}

bool Shape::isOnShape(const QPointF& point)
{
	if(isOnShapeBounder(point))
	{
		m_bBounderBeSelected = true;
		m_bDrawBounder = true;
		return true;
	}
	m_bBounderBeSelected = false;
	if(isOnshapeBody(point))
	{
		m_bDrawBounder = true;
		return true;
	}
	m_bDrawBounder = false;
	return false;
}

QPointF Shape::PointAfterRotation(const QPointF& center,const QPointF& target,double angle)
{
	angle = angle * acos(-1.0) / 180;
	QPointF ans;
	ans.setX((target.x() - center.x()) * cos(angle) - (target.y() - center.y()) * sin(angle) + center.x());
	ans.setY((target.x() - center.x()) * sin(angle) + (target.y() - center.y()) * cos(angle) + center.y());
	return ans;
}

QPointF Shape::getCenterPointFromLeftTopAndRightBottom()
{
	return (m_leftTopPoint + m_rightBottomPoint)/2;
}

QPointF Shape::getCenterPointFromLeftBottomAndRightTop()
{
	return (m_leftBottomPoint + m_rightTopPoint) / 2;
}

void Shape::rebuildRectFromLeftTopAndRightBottom(const QPointF& leftTop, const QPointF& rightBottom, double angle)
{
	m_leftTopPoint = leftTop;
	m_rightBottomPoint = rightBottom;
	m_angle = angle;
	QPointF cenPoint = getCenterPointFromLeftTopAndRightBottom();
	QPointF realLeftTop = PointAfterRotation(cenPoint,leftTop,-angle);
	QPointF realRightBottom = PointAfterRotation(cenPoint,rightBottom,-angle);

	QPointF realLeftBottom(realLeftTop.x(),realRightBottom.y());
	QPointF realRightTop(realRightBottom.x(),realLeftTop.y());
	m_leftBottomPoint = PointAfterRotation(cenPoint,realLeftBottom,angle);
	m_rightTopPoint = PointAfterRotation(cenPoint,realRightTop,angle);
}

void Shape::rebuildRectFromLeftBottomAndRightTop(const QPointF& leftBottom, const QPointF& rightTop, double angle)
{
	m_leftBottomPoint = leftBottom;
	m_rightTopPoint = rightTop;
	m_angle = angle;
	QPointF cenPoint = getCenterPointFromLeftBottomAndRightTop();
	QPointF realLeftBottom=PointAfterRotation(cenPoint, leftBottom, -angle);
	QPointF realRightTop=PointAfterRotation(cenPoint, rightTop, -angle);

	QPointF realLeftTop(realLeftBottom.x(), realRightTop.y());
	QPointF realRightBottom(realRightTop.x(), realLeftBottom.y());
	m_leftTopPoint = PointAfterRotation(cenPoint, realLeftTop, angle);
	m_rightBottomPoint = PointAfterRotation(cenPoint, realRightBottom, angle);
}

void Shape::setInintPointDuringMove(const QPointF& point)
{
	//�ڻ�ͼ�ĳ��ڣ�ֻ֪��������Ϳ����ؽ���������ˣ���һ���㣬�������ƶ����ĵ�
	if(m_firstPressPoint.x() <= point.x() && m_firstPressPoint.y() <= point.y())  //
	{
		m_leftTopPoint = m_firstPressPoint;
		m_rightBottomPoint = point;
		m_leftBottomPoint = QPointF(m_leftTopPoint.x(), m_rightBottomPoint.y());
		m_rightTopPoint = QPointF(m_rightBottomPoint.x(),m_leftTopPoint.y());
	}
	else if(m_firstPressPoint.x()>= point.x() && m_firstPressPoint.y() >= point.y())
	{
		m_leftTopPoint = point;
		m_rightBottomPoint = m_firstPressPoint;
		m_leftBottomPoint = QPointF(m_leftTopPoint.x(),m_rightBottomPoint.y());
		m_rightTopPoint = QPointF(m_rightBottomPoint.x(),m_leftTopPoint.y());
	}
	else if(m_firstPressPoint.x() < point.x() && m_firstPressPoint.y() >= point.y())
	{
		m_leftBottomPoint = m_firstPressPoint;
		m_rightTopPoint = point;
		m_leftTopPoint = QPointF(m_leftBottomPoint.x(),m_rightTopPoint.y());
		m_rightBottomPoint = QPointF(m_rightTopPoint.x(),m_leftBottomPoint.y());
	}
	else if (m_firstPressPoint.x() > point.x() && m_firstPressPoint.y() < point.y())
	{
		m_leftBottomPoint = point;
		m_rightTopPoint = m_firstPressPoint;
		m_leftTopPoint = QPointF(m_leftBottomPoint.x(), m_rightTopPoint.y());
		m_rightBottomPoint = QPointF(m_rightTopPoint.x(), m_leftBottomPoint.y());
	}
}

bool Shape::isOnShapeBounder(const QPointF& point)
{
	if (!m_bDrawBounder)
		return false;

	int len = m_pBounderCollection.size();
	for (int i = 0; i < len; i++)
	{
		if (m_pBounderCollection[i]->isOnShape(point))
		{
			m_pBounderBeSelected = m_pBounderCollection[i];
			return true;
		}
	}
	return false;
}

bool Shape::isOnshapeBody(const QPointF& point)
{
	return false;
}

void Shape::adjustIfUserPressAndFastReleaseDuringCreateNewShape()
{
	double xx = m_leftTopPoint.x() - m_rightBottomPoint.x();
	double yy = m_leftTopPoint.y() - m_rightBottomPoint.y();
	double dis = sqrt(xx * xx + yy * yy);
	if(dis < ms_fSmallEnough)
	{
		m_rightBottomPoint.setX(m_leftTopPoint.x() + ms_nInintSize);
		m_rightBottomPoint.setY(m_leftTopPoint.y() + ms_nInintSize);
		m_leftBottomPoint = QPointF(m_leftTopPoint.x(), m_rightBottomPoint.y());
		m_rightTopPoint = QPointF(m_rightBottomPoint.x(), m_leftTopPoint.y());
	}
}

void Shape:: addBounder(Bounder* bounder)
{
	Q_ASSERT(bounder);
	m_pBounderCollection.push_back(bounder);
}

void Shape::setBounder()
{
	int len = m_pBounderCollection.size();
	for (int i = 0; i < len; i++)
	{
		m_pBounderCollection[i]->setCenterPointFromShape(this);
	}
}

int getKeyDirBetweenTwoKeyDir(int kir1,int dir2)
{
	return (kir1 + dir2) / 2;
}

int Shape::getKeyStatus(const QPointF& point)
{
	if (isOnShapeBounder(point))
	{
		if (m_pBounderBeSelected->getBounderId() == Bounder::m_eBounderCicle)
			return Manager::m_eKeyStatusCicle;
		
		BounderCicle cicle;
		cicle.setCenterPointFromShape(this);
		cicle.setAngle(this->getAngle());
		double angle = cicle.changeAngle(this,QPointF(0,-4)+this->getCenterPointFromLeftBottomAndRightTop(),point);
		if(angle < 0)
			angle += 360;
		if(angle > 360)
			angle -= 360;
		int bounderBeSelectedId = m_pBounderBeSelected->getBounderId();
		/**
		*  ������ �ж�������״�ķ���,�Ƚ��鷳
		*  ˼·�������ж�һ��������ĵ��γɵ������ĽǶ�����bug�ģ���Ϊ�����κ�խʱ���õ���������״��׼ȷ
		*  ����: ��Ϊ���������ĸ����εıߵ����Ļ��ǱȽϺ��жϵģ���ô���ǿ��Է�������(��Ȼ���ϲ������)
		*		 1�������ѡ�е����ĸ��߽���αߵ����ĵ�λ�� ��ôֱ�ӷ��صõ��������״
		*		 2�������ѡ�е����ĸ������λ�ã���ô��������ʱ�����һ�����α����ı�ѡ��ʱ��ʲô���ͼ�Σ�Ȼ�����
		*			�õ��������״ ���� ˳ʱ����ת45�ȵ� �����״
		*/
		int keydir = getKeyDir(point);
		QPointF temp;
		int realKeyDir;
		int seconeKeyDir;
		switch (bounderBeSelectedId)
		{
		case Bounder::m_eBounderUp:
			return keydir;
		case Bounder::m_eBounderRight:
			return keydir;
		case Bounder::m_eBounderDown:
			return keydir;
		case Bounder::m_eBounderLeft:
			return keydir;
		case Bounder::m_eBounderUpRight:
			temp = (m_rightTopPoint + m_leftTopPoint) / 2;
			realKeyDir = getKeyDir(temp);
			temp = (m_rightTopPoint + m_rightBottomPoint) / 2;
			seconeKeyDir =getKeyDir(temp);
			return getKeyDirBetweenTwoKeyDir(realKeyDir,seconeKeyDir);//����������õ��м�ķ���
		case Bounder::m_eBounderDownRight:
			temp = (m_rightTopPoint + m_rightBottomPoint) / 2;
			realKeyDir = getKeyDir(temp);
			temp = (m_leftBottomPoint + m_rightBottomPoint) / 2;
			seconeKeyDir = getKeyDir(temp);
			return getKeyDirBetweenTwoKeyDir(realKeyDir,seconeKeyDir);
		case Bounder::m_eBounderDownLeft:
			temp = (m_leftBottomPoint + m_rightBottomPoint) / 2;
			realKeyDir = getKeyDir(temp);
			temp = (m_leftTopPoint + m_leftBottomPoint) / 2;
			seconeKeyDir = getKeyDir(temp);
			return getKeyDirBetweenTwoKeyDir(realKeyDir,seconeKeyDir);
		case Bounder::m_eBounderUpLeft:
			temp = (m_leftTopPoint + m_leftBottomPoint) / 2;
			realKeyDir = getKeyDir(temp);
			temp = (m_leftTopPoint + m_rightTopPoint) / 2;
			seconeKeyDir = getKeyDir(temp);
			return getKeyDirBetweenTwoKeyDir(realKeyDir,seconeKeyDir);
		default:
			return keydir;
		}
		return keydir;
	}
	else if(isOnshapeBody(point))
	{
		return Manager::m_eKeyStatusBody;
	}
	else
	{
		return Manager::m_eKeyStatusEmpty;
	}
	return Manager::m_eKeyStatusEmpty;
}
 
/**
* @param	point  ������һ����
* @brief	��������� getKeyStatus  ����ȷ��������״
* @return	�������������㣬��Ӧ�÷������������״
*/
int Shape::getKeyDir(const QPointF& point)
{
	BounderCicle cicle;
	cicle.setCenterPointFromShape(this);
	cicle.setAngle(this->getAngle());
	double angle = cicle.changeAngle(this,QPointF(0,-4) + this->getCenterPointFromLeftBottomAndRightTop(),point);
	
	if(angle < 0)
		angle += 360;

	if(angle > 360)
		angle -= 360;
	
	if(angle > 337.5 || angle <= 22.5)
		return Manager::m_eKeyStatusUp;
	else if(angle >= 22.5 && angle <= 67.5)
		return Manager::m_eKeyStatusUpRight;
	else if(angle >= 67.5 && angle <= 112.5)
		return Manager::m_eKeyStatusRight;
	else if(angle >= 112.5 && angle <= 157.5)
		return Manager::m_eKeyStatusDownRight;
	else if(angle >= 157.5 && angle <= 202.5)
		return Manager::m_eKeyStatusDown;
	else if(angle >= 202.5 && angle <= 247.5)
		return Manager::m_eKeyStatusDownLeft;
	else if(angle >= 247.5 && angle <= 292.5)
		return Manager::m_eKeyStatusLeft;
	else if(angle >= 292.5 && angle <= 337.5)
		return Manager::m_eKeyStatusUpLeft;
	return Manager::m_eKeyStatusUp;
}