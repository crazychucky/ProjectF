#ifndef __AIBehaviorCohesion_H__
#define __AIBehaviorCohesion_H__

#include "FishGame/AIBase/AIBehaviors.h"
#include "FishGame/AIBase/MovingGameObj.h"

class AIBehaviorCohesion:public AIBehavior
{
public:
	AIBehaviorCohesion(MovingGameObj* obj);
	virtual ~AIBehaviorCohesion();

	virtual CCPoint calculateBehaviorForce();

private:

};

#endif