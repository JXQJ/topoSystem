#include "cgepublicmath.h"

PublicMath::PublicMath()
{

}

PublicMath::~PublicMath()
{

}


//��_x1<=_x0<=_x2 or _x2<=_x0<=_x1, ���� true, ���򷵻� false
bool PublicMath::between(double _x0, double _x1, double _x2)
{
	double temp1,temp2;
	temp1 = _x0 - _x1;
	temp2 = _x0 - _x2;

  	if ((temp1 < EPSILON && temp2 > -EPSILON) || (temp2 < EPSILON && temp1 > -EPSILON))
	{
		return true;
	}
	else 
	{
		return false;
	}
}


//�������֮��ľ���
double PublicMath::getDistance(PlanePoint _p1,PlanePoint _p2)
{
	double temp1,temp2;
	temp1 = (_p1.x - _p2.x) * (_p1.x - _p2.x);
	temp2 = (_p1.y - _p2.y) * (_p1.y - _p2.y);
	return(sqrt (temp1 + temp2));
}

//�����ֵ(a-b)/(c-b)
double PublicMath::delta(double _a, double _b, double _c)
{
	double temp;

	if (_b == _c)
	{
		temp = 1.0;
	}
	else
	{
		temp = (_a - _b) / (_c - _b);
	}

	return temp;
}

//�ж����߶�֮����ཻ��ϵ
//�����߶��ص�,�򷵻ص���ĳһ�߶εĶ˵�����
bool PublicMath::lineSegmRelation(PlanePoint _p1, PlanePoint _p2,PlanePoint _p3, PlanePoint _p4, PlanePoint &_intersectPoint)
{
	if ((fabs(_p1.x - _p2.x) < EPSILON) && (fabs(_p3.x - _p4.x) < EPSILON))
	 {
		 return false;
	 }
	 //���ֱ�߶�_p1_p2��ֱ��y��
	 else if ((fabs (_p1.x - _p2.x) < EPSILON))
	 {
		 if (between(_p1.x, _p3.x, _p4.x))
		 {
			 double k = (_p4.y - _p3.y) / (_p4.x - _p3.x);
			 _intersectPoint.x = _p1.x;
			 _intersectPoint.y = k * (_intersectPoint.x - _p3.x) + _p3.y;

			 if (between(_intersectPoint.y, _p1.y, _p2.y))
			 {
				 return true;
			 }
			 else
			 {
				 return false;
			 }
		 }
		 else 
		 {
			 return false;
		 }
	 }
	 //���ֱ�߶�_p3_p4��ֱ��y��
	 else if ((fabs(_p3.x - _p4.x) < EPSILON))
	 {
		 if (between(_p3.x, _p1.x, _p2.x))
		 {
			 double k = (_p2.y - _p1.y) / (_p2.x - _p1.x);
			 _intersectPoint.x = _p3.x;
			 _intersectPoint.y = k * (_intersectPoint.x - _p2.x) + _p2.y;

			 if (between(_intersectPoint.y, _p3.y, _p4.y))
			 {
				 return true;
			 }
			 else
			 {
				 return false;
			 }
		 }
		 else 
		 {
			 return false;
		 }
	 }
	 else
     {
		 double k1 = (_p2.y - _p1.y) / (_p2.x - _p1.x); 
	     double k2 = (_p4.y - _p3.y) / (_p4.x - _p3.x);

		 //���߶�ƽ��
    	 if (fabs(k1 - k2) < EPSILON)
		 {
			 _intersectPoint.x = _p3.x; 
			 _intersectPoint.y = k1 * (_intersectPoint.x - _p1.x) + _p1.y;

			 if (fabs(_intersectPoint.y - _p3.y) < EPSILON)
			 {
				 //���߶���ͬһֱ����
				 if (between(_p3.x, _p1.x, _p2.x))
				 {
					 //���߶β����ص�,_p3��_p1_p2��
					 _intersectPoint.x = _p3.x; 
					 _intersectPoint.y = _p3.y; 
					 return true;
				 }
				 else if (between(_p4.x, _p1.x, _p2.x))
				 {
					 //���߶β����ص�,_p4��_p1_p2��
					 _intersectPoint.x = _p4.x; 
					 _intersectPoint.y = _p4.y;
					 return true;
				 }
				 else if (between(_p3.x, _p1.x, _p2.x) && between(_p4.x, _p1.x, _p2.x))
				 {
					 //_p1_p2������_p3_p4
					 _intersectPoint.x = _p4.x; 
					 _intersectPoint.y = _p4.y;
					 return true;
				 }
				 else
				 {
					 return false;
				 }
			 }
			 else
			 {
				 return false;
			 }
		 }
	     else 
		 {
	    	 _intersectPoint.x = ((_p3.y - _p1.y) - (k2 * _p3.x - k1 * _p1.x)) / (k1-k2);
	    	 _intersectPoint.y = k1 * (_intersectPoint.x - _p1.x) + _p1.y;
		 }

		 if (between(_intersectPoint.x, _p1.x, _p2.x) && between(_intersectPoint.x, _p3.x, _p4.x))
		 {
			 return true;
		 }
    	 else 
		 {
    		 return false;
		 }
	 }
}

// �ж��߶������ε��ཻ��ϵ,���ؽ�����
int PublicMath::linePolyRelation(PlanePoint _p1, PlanePoint _p2, BrokenLine _polygon, PlanePoint &_intersectsectPoint)
{
	int i;

	double tempDistance = getDistance(_p1, _p2);
	if (tempDistance < EPSILON)
	{
		return 0;
	}

	//�����Ϊ��ֱ�ӷ���
	int polygonPointNum = _polygon.size();
	if (polygonPointNum <= 0)
	{
		return 0;
	}

	//�Ƴ����ڵ���ͬ����
	std::vector<SpacePoint> tempPointVec;
	tempPointVec.push_back(_polygon[0]);
	PlanePoint tempPoint1, tempPoint2;

	for (i = 1; i < polygonPointNum; i++)
	{
		tempPoint1.x = _polygon[i].x;
		tempPoint1.y = _polygon[i].y;
		tempPoint2.x = tempPointVec.back().x;
		tempPoint2.y = tempPointVec.back().y;
		double distance  = getDistance(tempPoint1,tempPoint2);

		if (distance > EPSILON)
		{
			tempPointVec.push_back(_polygon[i]);
		}
	}

	//�Ƴ���_p1_p2�ص����߶�
	_polygon.clear();
	_polygon = tempPointVec;
	tempPointVec.clear();
	tempPointVec.push_back(_polygon[0]);
	polygonPointNum = _polygon.size();

	for (i = 1; i < polygonPointNum; i++)
	{
		if (fabs(tempPointVec.back().y - _p1.y) < EPSILON && fabs(_polygon[i].y - _p1.y) < EPSILON)
		{
			if (i == polygonPointNum - 1)
			{
				//�յ����ʼ��������_p1_p2�غ�
				tempPointVec.pop_back();
			}
			else
			{
				continue;
			}
		}
		else
		{
			tempPointVec.push_back(_polygon[i]);
		}
	}

	_polygon.clear();
	_polygon = tempPointVec;
	polygonPointNum = _polygon.size();

	if (polygonPointNum < 2)
	{
		return 0;
	}

	//�ж���ʼ�������Ƿ�һ��
	tempPoint1.x = _polygon.front().x;
	tempPoint1.y = _polygon.front().y;
	tempPoint2.x = _polygon.back().x;
	tempPoint2.y = _polygon.back().y;
	double distance = getDistance(tempPoint1, tempPoint2);

	if (distance > EPSILON)
	{
		_polygon.push_back(_polygon.front());
	}

	int intersectPointNum = 0; //�������
	std::vector<PlanePoint> intersectPointVec; //��ϲ����λ��ж������

	int preFlag = -1; //��һ���ཻ�Ķϲ��߱��
	PlanePoint p3, p4, temp;

	//������н���
	for (i=0; i < (polygonPointNum - 1); i++)
	{
		p3.x = _polygon[i].x;
		p3.y = _polygon[i].y;
		p4.x = _polygon[i+1].x;
		p4.y = _polygon[i+1].y;

		if (lineSegmRelation(_p1, _p2, p3, p4, temp))
		{
			intersectPointVec.push_back(temp);

			//�ж��Ƿ��������������߶εĶ˵�
			if (preFlag < 0)
			{
				intersectPointNum++;
				preFlag = i;
			}
			else
			{
				//�ж������Ƿ�����
				int indexdiff = i - preFlag;
				if (indexdiff == 1 || indexdiff == polygonPointNum - 1)
				{
					PlanePoint tp1, tp2, tp3, tp4, tp5;
					tp1.x = _polygon[i].x;
					tp1.y = _polygon[i].y;
					tp3.x = _polygon[i+1].x;
					tp3.y = _polygon[i+1].y;
					tp4.x = _polygon[i-1].x;
					tp4.y = _polygon[i-1].y;

					tp2 = _p1;
					tp5 = _p2;
					
					if (unitLineIntersect(tp1,tp2,tp3,tp4) || unitLineIntersect(tp1,tp5,tp3,tp4))
					{
						continue;
					}
					else
					{
						intersectPointNum++;
					}
				}
				else
				{
					intersectPointNum++;
				}

				preFlag = i;
			}
		}
	}

	//��������p1���Ľ���
	double minDistance;
	int vectorSize = intersectPointVec.size();

	for (i = 0; i < vectorSize; i++)
	{
		temp = intersectPointVec[i];
		tempDistance = getDistance(_p1, temp);

		if (i==0)
		{
			minDistance = tempDistance;
			_intersectsectPoint = temp;
		}
		else if (tempDistance < minDistance)
		{
			minDistance = tempDistance;
			_intersectsectPoint = temp;
		}
	}

	return intersectPointNum;
}

//�ж��߶���������ε��ཻ��ϵ
//�ཻ����true,���򷵻�false
bool PublicMath::lineSegmFaulRelation(PlanePoint _p1, PlanePoint _p2, Faultages _faultages)
{
	int i;
	int faultageNum = _faultages.size();

	for (i = 0; i < faultageNum; i++)
	{
		int flag = 0;
		PlanePoint tempPoint;

		flag = linePolyRelation(_p1, _p2, _faultages[i].polygon, tempPoint);

		if (flag > 0)
		{
			return true;
		}
	}

	return false;
}

// �жϹ�һ���߶ι�ϵ
bool PublicMath::unitLineIntersect(PlanePoint _p1, PlanePoint _p2, PlanePoint _p3, PlanePoint _p4)
{
	PlanePoint tp1,tp2,tp3,tp4;
	tp1 = _p1;
	tp2 = _p2;
	tp3 = _p3;
	tp4 = _p4;

	//���߶γ��Ƚ��й�һ��
	double distance = getDistance(tp1, tp2);
	if (distance< EPSILON)
	{
		return true;
	}
	else
	{
		tp2.x = (tp2.x - tp1.x) / distance;
		tp2.y = (tp2.y - tp1.y) / distance;
	}
	
	distance = getDistance(tp1, tp3);
	if (distance < EPSILON)
	{
		return true;
	}
	else
	{
		tp3.x = (tp3.x - tp1.x) / distance;
		tp3.y = (tp3.y - tp1.y) / distance;
	}

	distance = getDistance(tp1, tp4);
	if (distance < EPSILON)
	{
		return true;
	}
	else
	{
		tp4.x = (tp4.x - tp1.x) / distance;
		tp4.y = (tp4.y - tp1.y) / distance;
	}

	tp1.x = 0.0;
	tp1.y = 0.0;
	
	PlanePoint temp;
	if (lineSegmRelation(tp1, tp2, tp3, tp4, temp))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//�жϵ��Ƿ��ڶ������
bool PublicMath::pointOnPolygon(PlanePoint _p, BrokenLine _polygon)
{
	int i;
	//�Ƴ����ڵ���ͬ��
	int polygonPointNum = _polygon.size();

	if (polygonPointNum <= 0)
	{
		return false;
	}

	std::vector<SpacePoint> tempPointVec;
	tempPointVec.push_back(_polygon[0]);
	PlanePoint tempPoint1, tempPoint2;

	for (i = 1; i < polygonPointNum; i++)
	{
		tempPoint1.x = _polygon[i].x;
		tempPoint1.y = _polygon[i].y;
		tempPoint2.x = tempPointVec.back().x;
		tempPoint2.y = tempPointVec.back().y;

		double distance  = getDistance(tempPoint1,tempPoint2);
		if (distance > EPSILON)
		{
			tempPointVec.push_back(_polygon[i]);
		}
	}

	//�ж���ʼ�������Ƿ�һ��
	tempPoint1.x = tempPointVec.front().x;
	tempPoint1.y = tempPointVec.front().y;
	tempPoint2.x = tempPointVec.back().x;
	tempPoint2.y = tempPointVec.back().y;
	double distance = getDistance(tempPoint1, tempPoint2);

	if (distance > EPSILON)
	{
		tempPointVec.push_back(tempPointVec.front());
	}

	_polygon.clear();
	_polygon = tempPointVec;
	polygonPointNum = _polygon.size();

	if (polygonPointNum < 2)
	{
		return false;
	}

	//�жϵ��Ƿ��ڶ������,��������Ϊ������ڲ�
	for (i = 0; i < polygonPointNum - 1; i++)
	{
		tempPoint1.x = _polygon[i].x;
		tempPoint1.y = _polygon[i].y;
		tempPoint2.x = _polygon[i+1].x;
		tempPoint2.y = _polygon[i+1].y;

		if (pointOnLineSegm(_p, tempPoint1, tempPoint2))
		{
			return true;
		}
	}

	return false;
}

//�жϵ�"_p"�Ƿ����߶�"_p1_p2"��
bool PublicMath::pointOnLineSegm(PlanePoint _p, PlanePoint _p1, PlanePoint _p2)
{
	//��"_p1_p2"��y�ᴹֱ
	if (fabs(_p1.x - _p2.x) < EPSILON)
	{
		if (fabs(_p.x - _p2.x) < EPSILON && between(_p.y, _p1.y, _p2.y))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		//����б��
		double k = (_p1.y - _p2.y) / (_p1.x - _p2.x);

		if (fabs(k) < EPSILON)
		{
			if (fabs(_p.y - _p1.y) < EPSILON && between(_p.x, _p1.x, _p2.x))
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		//�ж�_p�Ƿ���_p1_p2��Ӧ��ֱ����
		double x, y;
		x = _p.x;
		y = k * (x - _p1.x) + _p1.y;

		if (fabs(y - _p.y) < EPSILON && between(_p.y, _p1.y, _p2.y))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

// �жϵ������εĹ�ϵ(����α��ϵĵ���Ϊ�ڶ�����ڲ�)
// ����true:����;false:������
bool PublicMath::pointPolyRelation(PlanePoint _p, BrokenLine _polygon)
{

	//�ж��Ƿ��ڶ���α���
	if (pointOnPolygon(_p, _polygon))
	{
		return true;
	}

	//_p��assistantPoint��һ�����ҵ�����
	PlanePoint assistantPoint;
	assistantPoint.x = INFINITY;
	assistantPoint.y = _p.y;

	int intersectPointNum = 0;
	PlanePoint tempPoint;
	intersectPointNum = linePolyRelation(_p, assistantPoint, _polygon, tempPoint);

	if (intersectPointNum % 2 == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// �жϵ���������εĹ�ϵ 
// ����true:���ٱ�����һ������ΰ���;false:������
bool PublicMath::PointFaulRelation(PlanePoint _p, Faultages _faultages)
{
	int i;
	int faultageNum = _faultages.size();

	for (i = 0; i < faultageNum; i++)
	{
		bool flag = false;
		PlanePoint tempPoint;

		flag = pointPolyRelation(_p, _faultages[i].polygon);

		if (flag)
		{
			return true;
		}
	}

	return false;
}

// �ж�ƽ����һ�����Ƿ������������㹹������Բ��
bool PublicMath::circumCircle(SpacePoint _px, SpacePoint _p1, SpacePoint _p2, SpacePoint _p3, SpacePoint &_pc, double &_r)
{
	double m1, m2, mx1, mx2, my1, my2;
	double dx, dy, rsqr, drsqr;
	
	if (fabs(_p1.y - _p2.y) < EPSILON && fabs(_p2.y - _p3.y) < EPSILON)
	{
		return (false);
	}
	
	if (fabs(_p2.y - _p1.y) < EPSILON)
	{
		m2 = -(_p3.x - _p2.x) /(_p3.y - _p2.y);
		mx2 = (_p2.x + _p3.x) / 2.0;
		my2 = (_p2.y + _p3.y) / 2.0;
		_pc.x = (_p2.x + _p1.x) / 2.0;
		_pc.y = m2 * (_pc.x - mx2) + my2;
	}
	else if (fabs(_p3.y - _p2.y) < EPSILON)
	{
		m1 = -(_p2.x - _p1.x) /(_p2.y - _p1.y);
		mx1 = (_p1.x + _p2.x) / 2.0;
		my1 = (_p1.y + _p2.y) / 2.0;
		_pc.x = (_p3.x + _p2.x) / 2.0;
		_pc.y = m1 * (_pc.x - mx1) + my1;
	}
	else	
	{
		m1 = -(_p2.x - _p1.x) / (_p2.y - _p1.y);
		m2 = -(_p3.x - _p2.x) / (_p3.y - _p2.y);
		mx1 = (_p1.x + _p2.x) / 2.0;
		mx2 = (_p2.x + _p3.x) / 2.0;
		my1 = (_p1.y + _p2.y) / 2.0;
		my2 = (_p2.y + _p3.y) / 2.0;
		_pc.x = (m1 * mx1 - m2 * mx2 + my2 - my1) /(m1 - m2);
		_pc.y = m1 *(_pc.x - mx1) + my1;
	}
	
	dx = _p2.x - _pc.x;
	dy = _p2.y - _pc.y;
	rsqr = dx * dx + dy * dy;
	_r = sqrt(rsqr);
	
	dx = _px.x - _pc.x;
	dy = _px.y - _pc.y;
	drsqr = dx * dx + dy * dy;
	
	return ((drsqr <= rsqr) ? true : false);
}