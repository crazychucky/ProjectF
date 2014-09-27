//状态机的 State 的模板类,并非AI专用
#ifndef STATE_H
#define STATE_H
struct Telegram;

template <class entity_type>
class State
{
public:

	virtual ~State(){}

	//this will execute when the state is entered
	virtual void onEnter(entity_type*)=0;

	//this is the states normal update function
	virtual void onExecute(entity_type*)=0;

	//this will execute when the state is exited. 
	virtual void onExit(entity_type*)=0;

	//this executes if the agent receives a message from the 
	//message dispatcher
	virtual bool onMessage(entity_type*, const Telegram&)=0;
};

#endif
