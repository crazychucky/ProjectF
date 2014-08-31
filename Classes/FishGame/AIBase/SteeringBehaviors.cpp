#include "cocos2d.h"
#include "SteeringBehaviors.h"
#include "MovingGameObj.h"
#include "Base/DSList.h"
#include "Base/CommonFunction.h"

//#include "ObstacleObj.h"
USING_NS_CC;

SteeringBehavior::SteeringBehavior(MovingGameObj* agent)
{
	m_pVehicle=agent;

	float theta=2*3.14*0;
	m_dWanderRadius=10.0f;
	m_vWanderTarget=ccp(m_dWanderRadius*cos(theta),m_dWanderRadius*sin(theta));

	m_dWanderJitter=80.0f;
	m_dWanderDistance=50.0f;

	m_pVehicle=agent;
	m_iFlags=none;

	m_fWeightSeparation=1.0f;
	m_fWeightAlignment=3.0f;
	m_fWeightCohesion=1.0f;
	m_fWeightWallAvoidance=12.0f;
	m_fWeightObstacleAvoidance=12.0f;
	m_fWeightEvade=1.0f;
	m_fWeightPursuit=1.0f;
	m_fWeightOffsetPursuit=0.1f;
	m_fWeightWander=0.3f;
}

SteeringBehavior::~SteeringBehavior()
{

}

bool SteeringBehavior::AccumulateForce(CCPoint &RunningTot,CCPoint ForceToAdd)
{
	//calculate how much steering force the vehicle has used so far
	float MagnitudeSoFar = RunningTot.getLength();

	//calculate how much steering force remains to be used by this vehicle
	float MagnitudeRemaining = m_pVehicle->getMaxForce() - MagnitudeSoFar;

	//return false if there is no more force left to use
	if (MagnitudeRemaining <= 0.0) return false;

	//calculate the magnitude of the force we want to add
	float MagnitudeToAdd = ForceToAdd.getLength();

	//if the magnitude of the sum of ForceToAdd and the running total
	//does not exceed the maximum force available to this vehicle, just
	//add together. Otherwise add as much of the ForceToAdd vector is
	//possible without going over the max.
	if (MagnitudeToAdd < MagnitudeRemaining)
	{
		RunningTot=RunningTot+ForceToAdd;
	}
	else
	{
		//add it to the steering force
		RunningTot=RunningTot + (ForceToAdd.normalize() * MagnitudeRemaining); 
	}
	return true;
}


CCPoint SteeringBehavior::Calculate()
{
	m_vSteeringForce=CCPointZero;
	CCPoint force=CCPointZero;

	if (On(separation) || On(allignment) || On(cohesion))
	{
		m_pVehicle->TagMovingGameObj(60.0f);
	}

	if (On(separation))
	{
		force = Separation()*m_fWeightSeparation;
		if (!AccumulateForce(m_vSteeringForce, force)) 
			return m_vSteeringForce;
	}
	if (On(allignment))
	{
		force = Alignment()*m_fWeightAlignment;
		if (!AccumulateForce(m_vSteeringForce, force)) 
			return m_vSteeringForce;
	}
	if (On(cohesion))
	{
		force = Cohesion()*m_fWeightCohesion;
		if (!AccumulateForce(m_vSteeringForce, force)) 
			return m_vSteeringForce;
	}
	if (On(wall_avoidance))
	{
		force = WallAvoidance()*m_fWeightWallAvoidance;
		if (!AccumulateForce(m_vSteeringForce, force)) 
			return m_vSteeringForce;
	}
	if (On(obstacle_avoidance))
	{
		force = ObstacleAvoidance()*m_fWeightObstacleAvoidance;
		if (!AccumulateForce(m_vSteeringForce, force)) 
			return m_vSteeringForce;
	}
	if (On(evade))
	{
		CCAssert((!m_pTargetAgent1),"ERROR:Evade target not assigned");
		force = Evade(m_pTargetAgent1)*m_fWeightEvade;
		if (!AccumulateForce(m_vSteeringForce, force)) 
			return m_vSteeringForce;
	}

	if (On(wander))
	{
		force = Wander()*m_fWeightWander;
		if (!AccumulateForce(m_vSteeringForce, force)) 
			return m_vSteeringForce;
	}
	if (On(seek))
	{
		;
	}
	if (On(flee))
	{
		;
	}
	if (On(pursuit))
	{
		CCAssert(m_pTargetAgent1,"ERROR:Pursuit target not assigned");
		force = Pursuit(m_pTargetAgent1)*m_fWeightPursuit;
		if (!AccumulateForce(m_vSteeringForce, force)) 
			return m_vSteeringForce;
	}
	if (On(offset_pursuit))
	{
		force = OffsetPursuit(m_pTargetAgent1,m_vOffset)*m_fWeightOffsetPursuit;
		if (!AccumulateForce(m_vSteeringForce, force)) 
			return m_vSteeringForce;
	}
	return m_vSteeringForce;
}
CCPoint SteeringBehavior::Wander()
{
	float rollX=1-CCRANDOM_0_1()*2;
	float rollY=1-CCRANDOM_0_1()*2;

	CCPoint newAdd=ccp(rollX*m_dWanderJitter,rollY*m_dWanderJitter);
	float len=newAdd.getLength();
	CCPoint finPt=ccp(newAdd.x/len,newAdd.y/len);
	CCPoint targetPt=finPt*m_dWanderRadius;

	CCPoint disPt=ccpAdd(targetPt,ccp(m_dWanderDistance,0));

	//转换
	float sinA,cosA;
	float sinB,cosB;
	sinA=(float)(m_pVehicle->getHeading().y/m_pVehicle->getHeading().getDistance(CCPointZero));
	cosA=(float)(m_pVehicle->getHeading().x/m_pVehicle->getHeading().getDistance(CCPointZero));
	sinB=(float)(disPt.y/disPt.getDistance(CCPointZero));
	cosB=(float)(disPt.x/disPt.getDistance(CCPointZero));
	float wx,wy;
	/*
	wx=disPt.getDistance(CCPointZero)*(cosA*cosB-sinA*sinB);
	wy=disPt.getDistance(CCPointZero)*(cosA*sinB+sinA*cosB);
	wx=0;
	wy=0;
	*/
	wx=disPt.x*m_pVehicle->getHeading().x-disPt.y*m_pVehicle->getHeading().y;
	wy=disPt.x*m_pVehicle->getHeading().y+disPt.y*m_pVehicle->getHeading().x;
	return ccp(wx,wy);

}

CCPoint SteeringBehavior::Pursuit(const MovingGameObj* evader)
{
	if (!evader)
	{
		return CCPointZero;
	}
	CCPoint ToEvader=evader->getPosition()-m_pVehicle->getPosition();
	float RelativeHeading=m_pVehicle->getHeading().dot(evader->getHeading());
	if((ToEvader.dot(m_pVehicle->getHeading())>0)&&(RelativeHeading<-0.95))
	{
		return Seek(evader->getPosition());
	}

	float LookAheadTime=ToEvader.getLength()/(m_pVehicle->getMaxSpeed()+evader->getSpeed());
	return Seek(evader->getPosition()+evader->getVelocity()*LookAheadTime);
}

CCPoint SteeringBehavior::Flee(CCPoint TargetPos)
{
	const float PanicDistanceSq=100.0*100.0;
	if(m_pVehicle->getPosition().getDistanceSq(TargetPos)>PanicDistanceSq)
	{
		return CCPointZero;
	}
	CCPoint DesiredVelocity=ccpSub(m_pVehicle->getPosition(),TargetPos).normalize();
	return (DesiredVelocity-m_pVehicle->getVelocity());

}

CCPoint SteeringBehavior::Evade(MovingGameObj* pursuer)
{
	if (!pursuer)
	{
		return CCPointZero;
	}
	CCPoint ToPursuer=pursuer->getPosition()-m_pVehicle->getPosition();
	float LookAheadTime=ToPursuer.getLength()/(m_pVehicle->getMaxSpeed()+pursuer->getSpeed());
	return Flee(pursuer->getPosition()+pursuer->getVelocity()*LookAheadTime);
}

CCPoint SteeringBehavior::Seek(CCPoint TargetPos)
{
	CCPoint DesiredVelocity=ccpSub(TargetPos,m_pVehicle->getPosition()).normalize()*m_pVehicle->getMaxSpeed();
	return (DesiredVelocity-m_pVehicle->getVelocity());
}

CCPoint SteeringBehavior::Arrive(CCPoint TargetPos,Deceleration deceleration)
{
	CCPoint ToTarget=TargetPos - m_pVehicle->getPosition();

	float dist=ToTarget.getLength();
	if (dist>10.0f)
	{
		const float DecelerationTweaker=0.3f;
		float speed=dist/(deceleration*DecelerationTweaker);
		if (speed>m_pVehicle->getMaxSpeed())
		{
			speed=m_pVehicle->getMaxSpeed();
		}
		CCPoint DesiredVelocity=ToTarget*speed/dist;
		return (DesiredVelocity-m_pVehicle->getVelocity());
	}
	else
	{
		return (CCPointZero-m_pVehicle->getVelocity());
	}
	return CCPointZero;
}

CCPoint SteeringBehavior::OffsetPursuit(const MovingGameObj* leader,const CCPoint offset)
{
	if (m_pVehicle->getMaxSpeed()>leader->getSpeed())
	{
		float wx,wy;
		wx=offset.x*leader->getHeading().x-offset.y*leader->getHeading().y;
		wy=offset.x*leader->getHeading().y+offset.y*leader->getHeading().x;
		CCPoint WorldOffsetPos=ccp(wx,wy)+leader->getPosition();
		CCPoint ToOffeset=WorldOffsetPos-m_pVehicle->getPosition();
		float LookAheadTime=ToOffeset.getLength()/(m_pVehicle->getMaxSpeed()-leader->getSpeed());
		return Arrive(WorldOffsetPos+leader->getVelocity()*LookAheadTime,fast);
	}
	else
	{
		CCLOG("ATTENTION!:CAN NOT OFFSET PURSUIT");
		return Pursuit(leader);
	}
}

CCPoint SteeringBehavior::SeparationAll()
{
	CCPoint SteeringForce=CCPointZero;
	int i=0;
	MovingGameObj* obj=NULL;
	const float minLen=80.0f;
	float len=0.0f;
	float twoObjRadius;
	for (i=0;i<GetMaxGameObjID();i++)
	{
		if (i==m_pVehicle->getObjID())
		{
			continue;
		}
		obj=GetMovingGameObj(i);
		CCPoint ToAgent=m_pVehicle->getPosition()-obj->getPosition();
		len=ToAgent.getLength();
		twoObjRadius=m_pVehicle->getObjRadius()+obj->getObjRadius();
		len=len-twoObjRadius;
		if (len<=0)
		{
			len=0.0000001f;
		}
		if (len<minLen)
		{
			SteeringForce=SteeringForce+ToAgent.normalize()/len;
		}
	}
	return SteeringForce;
}

CCPoint SteeringBehavior::Alignment()
{
	CCPoint AverageHeading=CCPointZero;
	if (m_pVehicle->getNeighborsSize()==0)
	{
		return AverageHeading;
	}

	MovingGameObj* pNeighbor=NULL;
	for (int i = 0; i < m_pVehicle->getNeighborsSize(); i++)
	{
		pNeighbor=m_pVehicle->getNeighborByIndex(i);
		if(m_pTargetAgent1)
		{
			if (pNeighbor==m_pTargetAgent1)
			{
				continue;
			}
		}

		AverageHeading=AverageHeading+pNeighbor->getHeading();
	}
	AverageHeading=AverageHeading/m_pVehicle->getNeighborsSize();
	AverageHeading=AverageHeading-m_pVehicle->getHeading();
	return AverageHeading;
}

CCPoint SteeringBehavior::Separation()
{
	CCPoint SteeringForce=CCPointZero;
	if (m_pVehicle->getNeighborsSize()==0)
	{
		return SteeringForce;
	}

	float twoObjRadius = 10;
	float len;
	MovingGameObj* pNeighbor=NULL;
	for (int i = 0; i < m_pVehicle->getNeighborsSize(); i++)
	{
		pNeighbor=m_pVehicle->getNeighborByIndex(i);
		CCPoint ToAgent=m_pVehicle->getPosition()-pNeighbor->getPosition();

		len=ToAgent.getLength();
		//特殊 太近就不避让了
		/*
		if (len<twoObjRadius+20.0f)
		{
			continue;
		}
		*/
		twoObjRadius=m_pVehicle->getObjRadius()+pNeighbor->getObjRadius();
		len=len-twoObjRadius;
		if (len<=0)
		{
			len=0.001f;
		}
		SteeringForce=SteeringForce+ToAgent.normalize()/len;
	}
	return SteeringForce;
}

CCPoint SteeringBehavior::Cohesion()
{
	CCPoint CenterMass,SteeringForce;
	SteeringForce=CCPointZero;
	CenterMass=CCPointZero;
	if (m_pVehicle->getNeighborsSize()==0)
	{
		return SteeringForce;
	}

	MovingGameObj* pNeighbor=NULL;
	for (int i = 0; i < m_pVehicle->getNeighborsSize(); i++)
	{
		pNeighbor=m_pVehicle->getNeighborByIndex(i);
		CenterMass=CenterMass+pNeighbor->getPosition();
	}
	CenterMass=CenterMass/m_pVehicle->getNeighborsSize();
	SteeringForce=Seek(CenterMass);
	return SteeringForce;
}

CCPoint SteeringBehavior::ObstacleAvoidance()
{
	//in orginal code there're three feelers
	//but here only use one
	/*
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
	CCPoint wallAgainst;
	Element<ObstacleObj>* pElem=g_allObstacleObjs->getHead();
	while (pElem)
	{
		ObstacleObj* pObj=pElem->pData;
		//可以出 不能进!
		if (pObj->isPointInPolygon(m_pVehicle->getPosition()))
		{
			pElem=pElem->pNext;
			continue;
		}
		int nPoints=pObj->getPointsNum();
		CCPoint rPt;
		for (int i=0;i<nPoints;i++)
		{
			const CCPoint wallLineStart=pObj->getPointByIndex(i);
			const CCPoint wallLineEnd=pObj->getPointByIndex(((i+1)%nPoints));
			if(getCrossPoint(p1,p2,wallLineStart,wallLineEnd,rPt))
			{
				DistToThisIP=rPt.getDistance(m_pVehicle->getPosition());
				if (DistToThisIP<DistToClosetIP)
				{
					DistToClosetIP=DistToThisIP;
					ClosetWall=i;
					ClosetPoint=rPt;
					wallAgainst=(wallLineEnd-wallLineStart).getPerp();
					if (wallAgainst.dot(p1-wallLineEnd)<0)
					{
						wallAgainst=(wallLineEnd-wallLineStart).getRPerp();
					}
					wallAgainst=wallAgainst.normalize();
				}
			}
		}
		pElem=pElem->pNext;
	}

	if (ClosetWall>=0)
	{
		CCPoint OverShoot=p2-ClosetPoint;
		SteeringForce=wallAgainst*OverShoot.getLength();
	}
	return SteeringForce;
	*/
	return CCPointZero;
}

CCPoint SteeringBehavior::WallAvoidance()
{
	//in orginal code there're three feelers
	//but here only use one
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
			wallLineStart=ccp(m_rWallRect.getMinX(),m_rWallRect.getMinY());
			wallLineEnd  =ccp(m_rWallRect.getMaxX(),m_rWallRect.getMinY());
			break;
		case 1:
			wallLineStart=ccp(m_rWallRect.getMaxX(),m_rWallRect.getMinY());
			wallLineEnd  =ccp(m_rWallRect.getMaxX(),m_rWallRect.getMaxY());
			break;
		case 2:
			wallLineStart=ccp(m_rWallRect.getMaxX(),m_rWallRect.getMaxY());
			wallLineEnd  =ccp(m_rWallRect.getMinX(),m_rWallRect.getMaxY());
			break;
		case 3:
			wallLineStart=ccp(m_rWallRect.getMinX(),m_rWallRect.getMaxY());
			wallLineEnd  =ccp(m_rWallRect.getMinX(),m_rWallRect.getMinY());
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

