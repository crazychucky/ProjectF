#ifndef __AIBehaviorWander_H__
#define __AIBehaviorWander_H__

#include "FishGame/AIBase/AIBehaviors.h"
#include "FishGame/AIBase/MovingGameObj.h"

class AIBehaviorWander:public AIBehavior
{
public:
	AIBehaviorWander(MovingGameObj* obj);
	virtual ~AIBehaviorWander();

	virtual CCPoint calculateBehaviorForce();

private:
	float m_fWanderRadius;
	float m_fWanderJitter;
	float m_fWanderDistance;
};

#endif