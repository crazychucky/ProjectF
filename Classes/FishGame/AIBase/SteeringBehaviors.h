//AI行为 SteeringBehaviors的类
#ifndef __STEERINGBEHAVIORS_H__
#define __STEERINGBEHAVIORS_H__

#include "cocos2d.h"

#include "FishGame/AIBase/MovingGameObj.h"
#include "FishGame/AIBase/AIBehaviors.h"

USING_NS_CC;


class SteeringBehaviors
{
public:
	SteeringBehaviors(MovingGameObj* pVehicle);
	~SteeringBehaviors();

	CCPoint calculateAllBehaviorsForce();

	bool addBehavior(AIBehavior* pBehavior);

	bool accumulateForce(CCPoint &runningTot,CCPoint forceToAdd);

	bool isBehaviorOn(AIBehavior::behavior_type bType);

	void removeBehavior(AIBehavior::behavior_type bType);
protected:
	CCArray* m_allBehaviors;
	MovingGameObj* m_pVehicle;
};

#endif