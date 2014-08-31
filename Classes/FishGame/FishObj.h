//Fish对象
#ifndef __FISHOBJ_H__
#define __FISHOBJ_H__

#include "FishGame/AIBase/MovingGameObj.h"

class FishObj:public MovingGameObj
{
public:
	FishObj();
	virtual ~FishObj();
	CREATE_FUNC(FishObj);
	bool init();

	void onEnter();
	void onExit();
private:
	void update(float dt);

};

#endif