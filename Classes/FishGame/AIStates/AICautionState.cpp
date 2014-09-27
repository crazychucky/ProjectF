#include "FishGame/AIStates/AICautionState.h"

AICautionState* AICautionState::Instance()
{
	static AICautionState instance;
	return &instance;
}

void AICautionState::onEnter(MovingGameObj* pObj)
{
	pObj->setMaxSpeedFactor(1.5f);
}

void AICautionState::onExecute(MovingGameObj* pObj)
{

}

void AICautionState::onExit(MovingGameObj* pObj)
{
	pObj->setMaxSpeedFactor(1.0f);
}