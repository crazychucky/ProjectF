#include "FishGame/AIBase/StateMachine.h"

template <class entity_type>
StateMachine::StateMachine(entity_type* owner):m_pOwner(owner),
		m_pCurrentState(NULL),
		m_pPreviousState(NULL),
		m_pGlobalState(NULL)
{

}

