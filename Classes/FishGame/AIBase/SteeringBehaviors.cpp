#include "cocos2d.h"
#include "SteeringBehaviors.h"
#include "MovingGameObj.h"
#include "Base/DSList.h"
#include "Base/CommonFunction.h"

#include <algorithm>

USING_NS_CC;

/**
 * Used for sort
 */
static int less(const CCObject* p1, const CCObject* p2)
{
    return ((AIBehavior*)p1)->getAIPriority() < ((AIBehavior*)p2)->getAIPriority();
}

SteeringBehaviors::SteeringBehaviors(MovingGameObj* pVehicle)
{
	m_pVehicle = pVehicle;
	m_allBehaviors = CCArray::create();
	m_allBehaviors->retain();
}

SteeringBehaviors::~SteeringBehaviors()
{

	m_allBehaviors->removeAllObjects();
	m_allBehaviors->release();

	CCLOG("SteeringBeehaviors deleted safely");
}

bool SteeringBehaviors::accumulateForce(CCPoint &runningTot,CCPoint forceToAdd)
{
	//calculate how much steering force the vehicle has used so far
	float MagnitudeSoFar = runningTot.getLength();

	//calculate how much steering force remains to be used by this vehicle
	float MagnitudeRemaining = m_pVehicle->getMaxForce() - MagnitudeSoFar;

	//return false if there is no more force left to use
	if (MagnitudeRemaining <= 0.0) return false;

	//calculate the magnitude of the force we want to add
	float MagnitudeToAdd = forceToAdd.getLength();

	//if the magnitude of the sum of ForceToAdd and the running total
	//does not exceed the maximum force available to this vehicle, just
	//add together. Otherwise add as much of the ForceToAdd vector is
	//possible without going over the max.
	if (MagnitudeToAdd < MagnitudeRemaining)
	{
		runningTot=runningTot+forceToAdd;
	}
	else
	{
		//add it to the steering force
		runningTot=runningTot + (forceToAdd.normalize() * MagnitudeRemaining); 
	}
	return true;
}

bool SteeringBehaviors::addBehavior(AIBehavior* pBehavior)
{
	//check for if already exist the same type
	if (true == this->isBehaviorOn(pBehavior->getBehaviorType()))
	{
			CCAssert(false,"The type is already existed");
            return false;
	}

	if (AIBehavior::none == pBehavior->getBehaviorType())
	{
		CCAssert(false,"The behavior type must be initilized");
		return false;
	}

	if (false == pBehavior->isAIPriorityInited())
	{
		CCAssert(false,"The behavior AI Priority be initilized");
		return false;
	}

	m_allBehaviors->addObject(pBehavior);

	//AI计算优先级排序
	//rearrangeBehaviors();

	CCLOG("The type %d behavior successfully added!",pBehavior->getBehaviorType());
	return true;
}

CCPoint SteeringBehaviors::calculateAllBehaviorsForce()
{
	CCPoint vSteeringForce = CCPointZero;
	CCPoint vForce = CCPointZero;

	AIBehavior* theBehavior = NULL;

	if(isBehaviorOn(AIBehavior::separation)||isBehaviorOn(AIBehavior::cohesion)||isBehaviorOn(AIBehavior::allignment))
	{
		m_pVehicle->TagMovingGameObj(70.0f);
	}

    for (unsigned int i = 0; i< m_allBehaviors->count(); i++)
	{
		theBehavior = dynamic_cast<AIBehavior*>(m_allBehaviors->objectAtIndex(i));

		vForce = theBehavior->calculateBehaviorForce() * theBehavior->getBehaviorWeight();
		if (!accumulateForce(vSteeringForce, vForce)) 
		{
			return vSteeringForce;
		}
	}
	return vSteeringForce;
}

bool SteeringBehaviors::isBehaviorOn(AIBehavior::behavior_type bType)
{
	AIBehavior*  pCurBehavior = NULL;
    for (unsigned int i = 0; i< m_allBehaviors->count(); i++)
    {
		pCurBehavior = dynamic_cast<AIBehavior*>(m_allBehaviors->objectAtIndex(i));
        if (pCurBehavior->getBehaviorType() ==  bType)
        {
            return true;
        }
    }
	return false;
}

void SteeringBehaviors::removeBehavior(AIBehavior::behavior_type bType)
{
	AIBehavior*  pCurBehavior = NULL;
    for (unsigned int i = 0; i< m_allBehaviors->count(); i++)
    {
		pCurBehavior = dynamic_cast<AIBehavior*>(m_allBehaviors->objectAtIndex(i));
        if (pCurBehavior->getBehaviorType() ==  bType)
        {
			m_allBehaviors->removeObjectAtIndex(i);
        }
    }
}

void SteeringBehaviors::rearrangeBehaviors()
{
    std::sort(m_allBehaviors->data->arr, m_allBehaviors->data->arr + m_allBehaviors->data->num, less);
}