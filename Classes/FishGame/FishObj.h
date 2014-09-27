//Fish对象
#ifndef __FISHOBJ_H__
#define __FISHOBJ_H__

#include "FishGame/AIBase/MovingGameObj.h"
#include "FishGame/AIBase/StateMachine.h"

class FishObj:public MovingGameObj
{
public:
	FishObj();
	virtual ~FishObj();
	CREATE_FUNC(FishObj);
	bool init();

	void onEnter();
	void onExit();

	StateMachine<MovingGameObj>* getFSM()const{return m_pStateMachine;}
private:
	void update(float dt);
	StateMachine<MovingGameObj> *m_pStateMachine;
};

#endif