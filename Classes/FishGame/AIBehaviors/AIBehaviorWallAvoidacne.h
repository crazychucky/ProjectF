#ifndef __AIBehaviorWallAvoidacne_H__
#define __AIBehaviorWallAvoidacne_H__

#include "FishGame/AIBase/AIBehaviors.h"
#include "FishGame/AIBase/MovingGameObj.h"

class AIBehaviorWallAvoidacne:public AIBehavior
{
public:
	AIBehaviorWallAvoidacne(MovingGameObj* obj,CCRect wallRect);
	virtual ~AIBehaviorWallAvoidacne();

	virtual CCPoint calculateBehaviorForce();
private:
	CCRect m_wallRect;
};

#endif