#ifndef __AIBehaviorAlignment_H__
#define __AIBehaviorAlignment_H__

#include "FishGame/AIBase/AIBehaviors.h"
#include "FishGame/AIBase/MovingGameObj.h"

class AIBehaviorAlignment:public AIBehavior
{
public:
	AIBehaviorAlignment(MovingGameObj* obj);
	virtual ~AIBehaviorAlignment();

	virtual CCPoint calculateBehaviorForce();

private:

};

#endif