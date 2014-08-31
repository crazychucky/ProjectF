#include "MovingGameObj.h"
#include "cocos2d.h"
#include "Base/CommonFunction.h"
USING_NS_CC;

MovingGameObj::MovingGameObj()
{
	m_fMass=1.0f;
	m_fMaxForce=100.0f;
	m_fMaxSpeed=100.0f;
	m_fObjRadius=0;
	m_pSteering=new SteeringBehavior(this);
	m_bTag=false;
	m_iNeighborsSize=0;
	for (int i=0;i<k_Max_Obj;i++)
	{
		m_neighbors[i]=NULL;
	}
}

MovingGameObj::~MovingGameObj()
{
	if (m_pSteering)
	{
		delete(m_pSteering);
	}
}

MovingGameObj* MovingGameObj::create(float objMass,float objMaxSpeed,float objMaxForce,CCPoint heading)
{
	MovingGameObj* pObj=MovingGameObj::create();
	pObj->m_fMass=objMass;
	pObj->m_fMaxSpeed=objMaxSpeed;
	pObj->m_fMaxForce=objMaxForce;
	pObj->m_vHeading=heading;
	return pObj;
}

void MovingGameObj::steeringMoving(float dt)
{

	CCPoint OldPos = this->getPosition();
	CCPoint SteeringForce;

	//calculate the combined force from each steering behavior in the vehicle's list
	SteeringForce = m_pSteering->Calculate();

	//Acceleration = Force/Mass
	CCPoint acceleration = SteeringForce / m_fMass;

	//update velocity
	m_vVelocity =m_vVelocity + acceleration; 

	//make sure vehicle does not exceed maximum velocity m_vVelocity.Truncate(m_dMaxSpeed);
	CommonFunction::VectorTruncate(m_vVelocity,m_fMaxSpeed);

	//update the position m_vPos =m_vPos + m_vVelocity;
	//update the heading if the vehicle has a non zero velocity
	if (m_vVelocity.getLengthSq()>0.00001)
	{
		this->setPosition(OldPos+m_vVelocity);
		m_obLastPosition=OldPos;
		m_vHeading = m_vVelocity.normalize();
	}

	/*
	if(SteeringForce.getLengthSq()>0.00001)
	{
	}
	*/
	//EnforceNonPenetrationConstraint(this, World()->Agents());
	/*
	//treat the screen as a toroid
	WrapAround(m_vPos, m_pWorld->cxClient(), m_pWorld->cyClient());

	//update the vehicle's current cell if space partitioning is turned on
	if (Steering()->isSpacePartitioningOn())
	{
		World()->CellSpace()->UpdateEntity(this, OldPos);
	}

	if (isSmoothingOn())
	{
		m_vSmoothedHeading = m_pHeadingSmoother->Update(Heading());
	}
	*/
}

void MovingGameObj::TagMovingGameObj(float neighborRadius)
{
	MovingGameObj* checkObj=NULL;
	int nCount=0;
	for (int i=0;i<=GameObj::getMaxGameObjID();i++)
	{
		if (i==this->getObjID())
		{
			continue;
		}

		checkObj=GetMovingGameObj(i);
		if ( checkObj->getPosition().getDistanceSq(this->getPosition())<neighborRadius*neighborRadius )
		{
			m_neighbors[nCount]=checkObj;
			nCount++;
		}
	}
	m_iNeighborsSize=nCount;
}