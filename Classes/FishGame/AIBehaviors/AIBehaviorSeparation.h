#ifndef __AIBehaviorSeparation_H__
#define __AIBehaviorSeparation_H__

#include "FishGame/AIBase/AIBehaviors.h"
#include "FishGame/AIBase/MovingGameObj.h"

class AIBehaviorSeparation:public AIBehavior
{
public:
	AIBehaviorSeparation(MovingGameObj* obj);
	virtual ~AIBehaviorSeparation();

	virtual CCPoint calculateBehaviorForce();

private:

};

#endif