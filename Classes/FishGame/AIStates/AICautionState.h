//×´Ì¬»úÀà
#ifndef AICautionState_H
#define AICautionState_H

#include "FishGame/AIBase/State.h"
#include "FishGame/AIBase/MovingGameObj.h"

class AICautionState:public State<MovingGameObj>
{
public:

	static AICautionState* Instance();

	void onEnter(MovingGameObj* pObj);

	void onExecute(MovingGameObj* pObj);

	void onExit(MovingGameObj* pObj);

	bool onMessage(MovingGameObj*, const Telegram&){return false;}

private:
	AICautionState(){};
};

#endif