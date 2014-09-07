#include "Base/CommonFunction.h"
#include "FishGame/AIBehaviors/AIBehaviorWallAvoidacne.h"

AIBehaviorWallAvoidacne::AIBehaviorWallAvoidacne(MovingGameObj* obj,CCRect wallRect)
{
	m_pVehicle = obj;
	m_wallRect = wallRect;
	m_behaviorType = AIBehavior::wall_avoidance;
	m_behaviorWeight = 10.0f;
}

AIBehaviorWallAvoidacne::~AIBehaviorWallAvoidacne()
{

}

CCPoint AIBehaviorWallAvoidacne::calculateBehaviorForce()
{
	float DistToThisIP=0;
	float DistToClosetIP=999999.0f;
	int ClosetWall=-1;
	CCPoint SteeringForce,point,ClosetPoint;
	SteeringForce=CCPointZero;
	const float feelerLen=50.0f;
	CCPoint p1=m_pVehicle->getPosition();
	CCPoint p2=p1+m_pVehicle->getHeading()*feelerLen;
	CCPoint wallLineStart,wallLineEnd;
	//judge
	//4 boarders
	//_0 |1 -2 |3
	for (int i=0;i<4;i++)
	{
		CCPoint rPt=CCPointZero;
		switch (i)
		{
		case 0:
			wallLineStart=ccp(m_wallRect.getMinX(),m_wallRect.getMinY());
			wallLineEnd  =ccp(m_wallRect.getMaxX(),m_wallRect.getMinY());
			break;
		case 1:
			wallLineStart=ccp(m_wallRect.getMaxX(),m_wallRect.getMinY());
			wallLineEnd  =ccp(m_wallRect.getMaxX(),m_wallRect.getMaxY());
			break;
		case 2:
			wallLineStart=ccp(m_wallRect.getMaxX(),m_wallRect.getMaxY());
			wallLineEnd  =ccp(m_wallRect.getMinX(),m_wallRect.getMaxY());
			break;
		case 3:
			wallLineStart=ccp(m_wallRect.getMinX(),m_wallRect.getMaxY());
			wallLineEnd  =ccp(m_wallRect.getMinX(),m_wallRect.getMinY());
			break;
		default:
			break;
		}

		if(CommonFunction::getCrossPoint(p1,p2,wallLineStart,wallLineEnd,rPt))
		{
			DistToThisIP=rPt.getDistance(m_pVehicle->getPosition());
			if (DistToThisIP<DistToClosetIP)
			{
				DistToClosetIP=DistToThisIP;
				ClosetWall=i;
				ClosetPoint=rPt;
			}
		}
	}

	if (ClosetWall>=0)
	{
		CCPoint OverShoot=p2-ClosetPoint;
		CCPoint wallAgainst;
		switch (ClosetWall)
		{
		case 0:
			wallAgainst=ccp(0,1);
			break;
		case 1:
			wallAgainst=ccp(-1,0);
			break;
		case 2:
			wallAgainst=ccp(0,-1);
			break;
		case 3:
			wallAgainst=ccp(1,0);
			break;
		default:
			break;
		}
		SteeringForce=wallAgainst*OverShoot.getLength();
	}
	return SteeringForce;
}