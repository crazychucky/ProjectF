#include "FishGame/AIBehaviors/AIBehaviorAlignment.h"

#define AI_WEIGHT_ALIGNMENT 3.0f

AIBehaviorAlignment::AIBehaviorAlignment(MovingGameObj* obj)
{
	m_pVehicle = obj;
	m_behaviorType = AIBehavior::allignment;
	setAIPriority(m_behaviorType);

	m_behaviorWeight = AI_WEIGHT_ALIGNMENT;
}

AIBehaviorAlignment::~AIBehaviorAlignment()
{

}

CCPoint AIBehaviorAlignment::calculateBehaviorForce()
{
	CCPoint vSteeringForce = CCPointZero;

	CCPoint AverageHeading = CCPointZero;

	if (m_pVehicle->getNeighbors()->count()==0)
	{
		return CCPointZero;
	}

	MovingGameObj* pObj = NULL;
	CCArray* pNeighbors = m_pVehicle->getNeighbors();
	const int neighborsCount = pNeighbors->count();
	for (int i = 0; i < neighborsCount; i++)
	{
		pObj = (MovingGameObj*)pNeighbors->objectAtIndex(i);

		//TODO:
		/*
		if(m_pTargetAgent1)
		{
			if (pObj==m_pTargetAgent1)
			{
				continue;
			}
		}
		*/

		AverageHeading=AverageHeading+pObj->getHeading();
	}
	AverageHeading = AverageHeading/neighborsCount;
	AverageHeading = AverageHeading-m_pVehicle->getHeading();

	vSteeringForce = AverageHeading;
	return vSteeringForce;
}