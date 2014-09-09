#include "FishGame/AIBehaviors/AIBehaviorSeparation.h"

AIBehaviorSeparation::AIBehaviorSeparation(MovingGameObj* obj)
{
	m_behaviorType = AIBehavior::separation;
	m_pVehicle = obj;
	m_behaviorWeight = 10.0f;
}

AIBehaviorSeparation::~AIBehaviorSeparation()
{

}

CCPoint AIBehaviorSeparation::calculateBehaviorForce()
{
	CCPoint vSteeringForce = CCPointZero;

	MovingGameObj* obj=NULL;
	const float minLen=80.0f;
	float len=0.0f;
	for (int i = 0;i < GetMaxGameObjID();i++)
	{
		if (i==m_pVehicle->getObjID())
		{
			continue;
		}

		obj=GetMovingGameObj(i);
		CCPoint ToAgent=m_pVehicle->getPosition()-obj->getPosition();
		len=ToAgent.getLength();


		float twoObjRadius = 32.0f;  //TODO:修改成指定参数?
		len=len-twoObjRadius;
		if (len<=0)
		{
			len = 0.00001f;
		}
		if (len<minLen)
		{
			vSteeringForce = vSteeringForce+ToAgent.normalize()/len;
		}
	}

	return vSteeringForce;
}