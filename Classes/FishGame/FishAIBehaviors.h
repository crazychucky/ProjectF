//SteeringBehaviors的扩展
#ifndef __FishAIBehaviors_H__
#define __FishAIBehaviors_H__
#include "FishGame/AIBase/SteeringBehaviors.h"

class FishAIBehaviors:public SteeringBehavior
{
public:
	FishAIBehaviors(MovingGameObj* agent);
	~FishAIBehaviors();

private:

};


//重写SteeringBehaviors AI驱动
//插槽式 + 驱动管理
//插槽采用单例
#endif

