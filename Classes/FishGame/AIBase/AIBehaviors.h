//AI Behaviors AI行为
#ifndef __AIBehavior_H__
#define __AIBehavior_H__

#include "cocos2d.h"
USING_NS_CC;
class AIBehaviors
{
public:
	AIBehaviors(){};
	virtual ~AIBehaviors(){};

	//计算AI牵引力
	virtual CCPoint calcAIForce()=0;
private:

};

#endif