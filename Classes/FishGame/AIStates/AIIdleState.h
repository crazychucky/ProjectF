//×´Ì¬»úÀà
#ifndef AIIdleState_H
#define AIIdleState_H

#include "FishGame/AIBase/State.h"
#include "FishGame/AIBase/MovingGameObj.h"

class AIIdleState:public State<MovingGameObj>
{
public:

	static AIIdleState* Instance();

	void onEnter(MovingGameObj* pObj);

	void onExecute(MovingGameObj* pObj);

	void onExit(MovingGameObj* pObj);

	bool onMessage(MovingGameObj*, const Telegram&){return false;}

private:
	AIIdleState(){};
};

#endif