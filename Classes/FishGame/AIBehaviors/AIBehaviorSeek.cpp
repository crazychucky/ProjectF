#include "FishGame/AIBehaviors/AIBehaviorSeek.h"

AIBehaviorSeek::AIBehaviorSeek(MovingGameObj* obj,CCPoint targetPos)
{
	m_behaviorType = AIBehavior::seek;
	setAIPriority(m_behaviorType);

	m_pVehicle = obj;

	m_targetPos = targetPos;
}

AIBehaviorSeek::~AIBehaviorSeek()
{

}

CCPoint AIBehaviorSeek::calculateBehaviorForce()
{
	CCPoint DesiredVelocity=ccpSub(m_targetPos,m_pVehicle->getPosition()).normalize()*m_pVehicle->getMaxSpeed();
	return (DesiredVelocity-m_pVehicle->getVelocity());
}

CCPoint AIBehaviorSeek::calculateBehaviorForce(CCPoint targetPos,MovingGameObj* obj)
{
	CCPoint DesiredVelocity=ccpSub(targetPos,obj->getPosition()).normalize()*obj->getMaxSpeed();
	return (DesiredVelocity - obj->getVelocity());
}
