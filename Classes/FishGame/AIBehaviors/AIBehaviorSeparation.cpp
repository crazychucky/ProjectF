#include "FishGame/AIBehaviors/AIBehaviorSeparation.h"

AIBehaviorSeparation::AIBehaviorSeparation(MovingGameObj* obj)
{
	m_behaviorType = AIBehavior::separation;
	m_pVehicle = obj;
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


		float twoObjRadius=m_pVehicle->getContentSize().width/2.0f+obj->getContentSize().width/2.0f;  //TODO:�޸ĳ�ָ������?
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