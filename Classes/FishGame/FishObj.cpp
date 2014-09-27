#include "FishGame/FishObj.h"
//AI
#include "FishGame/AIBase/SteeringBehaviors.h"
#include "FishGame/AIBehaviors/AIBehaviorWander.h"
#include "FishGame/AIBehaviors/AIBehaviorWallAvoidacne.h"
#include "FishGame/AIStates/AIIdleState.h"
#include "FishGame/AIStates/AICautionState.h"

#define FISH_IMAGE "circle.png"

FishObj::FishObj()
{
	m_pStateMachine = NULL;
}

FishObj::~FishObj()
{
	if (m_pStateMachine)
	{
		delete(m_pStateMachine);
	}
}

bool FishObj::init()
{
	if( false == MovingGameObj::init())
	{
		return false;
	}

	//old code
	//test start
	m_fMass=1.0f;
	m_fMaxForce=100.0f;
	m_fMaxSpeed=3.50f;
	m_fObjRadius=10.0f;
	m_vHeading=ccp(0,1.0f);
	CCSprite* sp=CCSprite::create(FISH_IMAGE);
	this->addChild(sp);
	sp->setPosition(CCPointZero);
	sp->setScale(0.2f);
	sp->setAnchorPoint(ccp(0.5,0.5));

	CCRect wall=CCRectMake(20.f,20.0f,760.0f,440.0f);
	SteeringBehaviors* pSteering=this->getSteering();

	AIBehaviorWander* pAIWander = new AIBehaviorWander(this);
	pSteering->addBehavior(pAIWander);

	AIBehaviorWallAvoidacne* pAIWallAvoidance = new AIBehaviorWallAvoidacne(this,wall);
	pSteering->addBehavior(pAIWallAvoidance);

	m_pStateMachine = new StateMachine<MovingGameObj>(this);
	m_pStateMachine->setCurrentState(AICautionState::Instance());

	
	/*
	pSteering->WallAvoidanceOn(wall);
	pSteering->WanderOn();
	pSteering->SeparationOn();
	pSteering->AlignmentOn();
	pSteering->CohesionOn();
	pSteering->ObstacleAvoidanceOn();
	*/

	scheduleUpdate();


	return true;
}

void FishObj::onEnter()
{
	MovingGameObj::onEnter();
}

void FishObj::onExit()
{
	MovingGameObj::onExit();
}

void FishObj::update(float dt)
{
	this->steeringMoving(dt);

	float ro=acos(m_vHeading.dot(ccp(0,1.0f)));
	ro=ro*180.0f/3.14;
	if (m_vHeading.x<0)
	{
		ro=-ro;
	}
	this->setRotation(ro);

	m_pStateMachine->update();
}