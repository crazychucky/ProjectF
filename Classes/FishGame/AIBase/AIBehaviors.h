//AI Behaviors AI��Ϊ
#ifndef __AIBehavior_H__
#define __AIBehavior_H__

#include "cocos2d.h"
USING_NS_CC;
class AIBehaviors
{
public:
	AIBehaviors(){};
	virtual ~AIBehaviors(){};

	//����AIǣ����
	virtual CCPoint calcAIForce()=0;
private:

};

#endif