#include "MovingGameObj.h"
#include "cocos2d.h"
#include "Base/CommonFunction.h"
#include "FishGame/AIBase/SteeringBehaviors.h"
USING_NS_CC;

MovingGameObj::MovingGameObj()
{
	m_fMass=1.0f;
	m_fMaxForce=100.0f;
	m_fMaxSpeed=100.0f;
	m_fObjRadius=0;
	m_pSteering=new SteeringBehaviors(this);
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

bool MovingGameObj::init()
{
	if (false == GameObj::init())
	{
		return false;
	}

	return true;
}

void MovingGameObj::steeringMoving(float dt)
{
	CCPoint oldPos = this->getPosition();
	CCPoint vSteeringForce;

	vSteeringForce = m_pSteering->calculateAllBehaviorsForce();

	//Acceleration = Force/Mass
	CCPoint acceleration = vSteeringForce / m_fMass;

	//update velocity
	m_vVelocity =m_vVelocity + acceleration; 

	//make sure vehicle does not exceed maximum velocity m_vVelocity.Truncate(m_dMaxSpeed);
	CommonFunction::VectorTruncate(m_vVelocity,m_fMaxSpeed);

	//update the position m_vPos =m_vPos + m_vVelocity;
	//update the heading if the vehicle has a non zero velocity
	if (m_vVelocity.getLengthSq()>0.00001)
	{
		this->setPosition(oldPos+m_vVelocity);
		m_obLastPosition=oldPos;
		m_vHeading = m_vVelocity.normalize();
	}

	/*
	TODO:优化计算:网格等
	TODO:平滑移动
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

void MovingGameObj::onEnter()
{
	GameObj::onEnter();
}

void MovingGameObj::onExit()
{
	GameObj::onExit();
}

SteeringBehaviors*const MovingGameObj::getSteering()const
{
	return m_pSteering;
}

MovingGameObj* MovingGameObj::getMovingGameObjByID(int objID)
{
	MovingGameObj* pObj=(MovingGameObj*)MovingGameObj::getGameObjByID(objID);
	return pObj;
}