#include "FishGame/AIBehaviors/AIBehaviorCohesion.h"
#include "FishGame/AIBehaviors/AIBehaviorSeek.h"

#define AI_WEIGHT_COHESION 1.0f

AIBehaviorCohesion::AIBehaviorCohesion(MovingGameObj* obj)
{
	m_pVehicle = obj;
	m_behaviorType = AIBehavior::cohesion;
	setAIPriority(m_behaviorType);

	m_behaviorWeight = AI_WEIGHT_COHESION;
}

AIBehaviorCohesion::~AIBehaviorCohesion()
{

}

CCPoint AIBehaviorCohesion::calculateBehaviorForce()
{
	CCPoint vSteeringForce = CCPointZero;

	CCPoint CenterMass = CCPointZero;

	if (0 == m_pVehicle->getNeighbors()->count())
	{
		return CCPointZero;
	}

	CCArray* pNeighbors = m_pVehicle->getNeighbors();
	int neighborsCount = pNeighbors->count();

	MovingGameObj* pObj = NULL;
	for (int i = 0; i < neighborsCount; i++)
	{
		pObj = (MovingGameObj*)pNeighbors->objectAtIndex(i);
		CenterMass = CenterMass + pObj->getPosition();
	}
	CenterMass=CenterMass/neighborsCount;

	vSteeringForce = AIBehaviorSeek::calculateBehaviorForce(CenterMass,m_pVehicle);  //TODO:´ý¸ÄÉÆ

	return vSteeringForce;
}