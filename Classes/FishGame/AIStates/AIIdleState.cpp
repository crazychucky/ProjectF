#include "FishGame/AIStates/AIIdleState.h"

AIIdleState* AIIdleState::Instance()
{
	static AIIdleState instance;
	return &instance;
}

void AIIdleState::onEnter(MovingGameObj* pObj)
{
	pObj->setMaxSpeedFactor(0.3f);
}

void AIIdleState::onExecute(MovingGameObj* pObj)
{

}

void AIIdleState::onExit(MovingGameObj* pObj)
{
	pObj->setMaxSpeedFactor(1.0f);
}