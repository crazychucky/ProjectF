//×´Ì¬»úÀà
#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "FishGame/AIBase/State.h"

template <class entity_type>
class StateMachine
{
public:

	StateMachine(entity_type* owner):m_pOwner(owner),
		m_pCurrentState(NULL),
		m_pPreviousState(NULL),
		m_pGlobalState(NULL)
	{}

	virtual ~StateMachine(){}

	void setCurrentState(State<entity_type>* s){m_pCurrentState = s;}
	void setGlobalState(State<entity_type>* s) {m_pGlobalState = s;}
	void setPreviousState(State<entity_type>* s){m_pPreviousState = s;}

	void  update()const
	{
		//if a global state exists, call its execute method, else do nothing
		if(m_pGlobalState)   
			m_pGlobalState->onExecute(m_pOwner);

		//same for the current state
		if (m_pCurrentState) 
			m_pCurrentState->onExecute(m_pOwner);
	}

	bool  handleMessage(const Telegram& msg)const
	{
		//first see if the current state is valid and that it can handle
		//the message
		if (m_pCurrentState && m_pCurrentState->onMessage(m_pOwner, msg))
		{
			return true;
		}

		//if not, and if a global state has been implemented, send 
		//the message to the global state
		if (m_pGlobalState && m_pGlobalState->onMessage(m_pOwner, msg))
		{
			return true;
		}

		return false;
	}

	void  changeState(State<entity_type>* pNewState)
	{
		//keep a record of the previous state
		m_pPreviousState = m_pCurrentState;

		//call the exit method of the existing state
		m_pCurrentState->onExit(m_pOwner);

		//change state to the new state
		m_pCurrentState = pNewState;

		//call the entry method of the new state
		m_pCurrentState->onEnter(m_pOwner);
	}

	//change state back to the previous state
	void  revertToPreviousState()
	{
		changeState(m_pPreviousState);
	}

	//returns true if the current state's type is equal to the type of the
	//class passed as a parameter. 
	bool  isInState(const State<entity_type>& st)const
	{
		if (typeid(*m_pCurrentState) == typeid(st)) return true;
		return false;
	}

	State<entity_type>*  getCurrentState()  const{return m_pCurrentState;}
	State<entity_type>*  getGlobalState()   const{return m_pGlobalState;}
	State<entity_type>*  getPreviousState() const{return m_pPreviousState;}

	//only ever used during debugging to grab the name of the current state
	std::string getNameOfCurrentState()const
	{
		std::string s(typeid(*m_pCurrentState).name());

		//remove the 'class ' part from the front of the string
		if (s.size() > 5)
		{
			s.erase(0, 6);
		}

		return s;
	}
private:

	//a pointer to the agent that owns this instance
	entity_type*          m_pOwner;

	State<entity_type>*   m_pCurrentState;

	//a record of the last state the agent was in
	State<entity_type>*   m_pPreviousState;

	//this is called every time the FSM is updated
	State<entity_type>*   m_pGlobalState;
};
#endif