#include "Base/CommonFunction.h"

CommonFunction::CommonFunction()
{

}

CommonFunction::~CommonFunction()
{

}

void CommonFunction::VectorTruncate(CCPoint &v,float maxLen)
{
	if (v.getLengthSq()>maxLen*maxLen)
	{
		v=v.normalize()*maxLen;
	}
}

bool CommonFunction::getCrossPoint(const CCPoint p1,const CCPoint p2,const CCPoint p3,const CCPoint p4,CCPoint &resultPt)
{
	//求直线
	float a1,b1,c1,a2,b2,c2;
	{
		int sign=1;
		a1=p2.y-p1.y;
		if (a1<0)
		{
			sign=-1;
			a1=sign*a1;
		}
		b1=sign*(p1.x-p2.x);
		c1=sign*(p1.y*p2.x-p1.x*p2.y);
	}
	{
		int sign=1;
		a2=p4.y-p3.y;
		if (a2<0)
		{
			sign=-1;
			a2=sign*a2;
		}
		b2=sign*(p3.x-p4.x);
		c2=sign*(p3.y*p4.x-p3.x*p4.y);
	}
	//先判断是否相交

	float d=a1*b2-a2*b1;
	if (abs(d)<0.001)
	{
		return false;
	}

	resultPt.x=(c2*b1-c1*b2)/d;
	resultPt.y=(a2*c1-a1*c2)/d;
	if ( (MIN(p1.x,p2.x)<=resultPt.x&&resultPt.x<=MAX(p1.x,p2.x)) && (MIN(p1.y,p2.y)<=resultPt.y&&resultPt.y<=MAX(p1.y,p2.y)) &&
		(MIN(p3.x,p4.x)<=resultPt.x&&resultPt.x<=MAX(p3.x,p4.x)) && (MIN(p3.y,p4.y)<=resultPt.y&&resultPt.y<=MAX(p3.y,p4.y))
		)
	{
		return true;
	}
	return false;
}