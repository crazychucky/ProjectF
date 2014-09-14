#ifndef __AIBehaviorSeek_H__
#define __AIBehaviorSeek_H__

#include "FishGame/AIBase/AIBehaviors.h"
#include "FishGame/AIBase/MovingGameObj.h"

class AIBehaviorSeek:public AIBehavior
{
public:
	AIBehaviorSeek(MovingGameObj* obj,CCPoint targetPos);
	virtual ~AIBehaviorSeek();

	virtual CCPoint calculateBehaviorForce();

	static CCPoint calculateBehaviorForce(CCPoint targetPos,MovingGameObj* obj);

private:
	CCPoint m_targetPos;

};

#endif