#include "FishGame/Test/MultiFishAITestScene.h"
#include "FishGame/AIBase/SteeringBehaviors.h"
#include "FishGame/AIBehaviors/AIBehaviorSeparation.h"
#include "FishGame/AIBehaviors/AIBehaviorCohesion.h"
#include "FishGame/AIBehaviors/AIBehaviorAlignment.h"

#include "FishGame/AIBase/StateMachine.h"
#include "FishGame/AIStates/AICautionState.h"
#include "FishGame/AIStates/AIIdleState.h"

#define BG_IMAGE "white.jpg"

MultiFishAITestScene::MultiFishAITestScene()
{
	m_separationAIFlag = false;
}

MultiFishAITestScene::~MultiFishAITestScene()
{
	GameObj::clearObjID();
}

void MultiFishAITestScene::onEnter()
{
	TestBaseScene::onEnter();
}

void MultiFishAITestScene::onExit()
{
	TestBaseScene::onExit();
}

bool MultiFishAITestScene::init()
{
	if (false == TestBaseScene::init())
	{
		return false;
	}

	setTitle("Separation Off");
	m_titleLabel->setColor(ccBLACK);

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	m_bgLayer = CCLayer::create();
	this->addChild(m_bgLayer,1);

	CCSprite* pSprite = CCSprite::create(BG_IMAGE);

	// position the sprite on the center of the screen
	pSprite->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	CCSize bgSize = pSprite->getContentSize();
	float sx,sy;
	sx = visibleSize.width/bgSize.width;
	sy = visibleSize.height/bgSize.height;
	pSprite->setScaleX(sx);
	pSprite->setScaleY(sy);
	m_bgLayer->addChild(pSprite);

	m_fishLayer = CCLayer::create();
	this->addChild(m_fishLayer,2);

	for ( int i = 0;i < MultiFishNum; i++)
	{
		FishObj* fishObj = FishObj::create();
		m_fishLayer->addChild(fishObj);
		fishObj->setPosition(ccp(400,240));
		fishObj->setScale(2.0f);
		m_multiFish[i] = fishObj;
	}

	CCPoint pt;
	CCPoint ptOff;
	pt = ccp(100,460);
	ptOff = ccp(0,-60);

	//Fish game
	pt = pt + ptOff;
	addTestFuncBtn("Separation Switch",pt,toucheventselector(MultiFishAITestScene::onSwitchSeparationAI));

	//debug draw
	this->addChild(DrawLayer::create(this));

	scheduleUpdate();
	return true;
}

void MultiFishAITestScene::onSwitchSeparationAI(CCObject* pSender,TouchEventType eventtype)
{
	if (TOUCH_EVENT_ENDED == eventtype)
	{
		SteeringBehaviors* pSteering;
		
		if (false == m_separationAIFlag)
		{
			setTitle("Separation On");
			m_separationAIFlag = true;

			for (int i = 0 ;i < MultiFishNum;i++)
			{
				pSteering = m_multiFish[i]->getSteering();

				AIBehaviorSeparation* pAI1 = new AIBehaviorSeparation(m_multiFish[i]);
				pSteering->addBehavior(pAI1);

				AIBehaviorCohesion* pAI2 = new AIBehaviorCohesion(m_multiFish[i]);
				pSteering->addBehavior(pAI2);

				AIBehaviorAlignment* pAI3 = new AIBehaviorAlignment(m_multiFish[i]);
				pSteering->addBehavior(pAI3);
			}
		}
		else
		{
			setTitle("Separation Off");
			m_separationAIFlag = false;

			for (int i = 0 ;i < MultiFishNum;i++)
			{
				pSteering = m_multiFish[i]->getSteering();
				pSteering->removeBehavior(AIBehavior::separation);
				pSteering->removeBehavior(AIBehavior::cohesion);
				pSteering->removeBehavior(AIBehavior::allignment);
			}
		}
	
	}
}

void MultiFishAITestScene::debugDraw()
{
	ccDrawColor4B(255,0,0,255);
	CCRect drawRect = CCRectMake(20.f,20.0f,760.0f,440.0f);
	CCPoint dstPt = drawRect.origin+ccp(drawRect.size.width,drawRect.size.height);
	ccDrawRect(drawRect.origin,dstPt);
}

void MultiFishAITestScene::update(float dt)
{
	static int timeCounter = 0;
	timeCounter++;
	if (timeCounter == 1000)
	{
		timeCounter = 0;
	}

	if (timeCounter == 500)
	{
		StateMachine<MovingGameObj> *p_StateMachine;
		for (int i = 0 ;i < MultiFishNum;i++)
		{
			p_StateMachine = m_multiFish[i]->getFSM();

			p_StateMachine->changeState(AIIdleState::Instance());
		}
	}
	else if (900 == timeCounter)
	{
		StateMachine<MovingGameObj> *p_StateMachine;
		for (int i = 0 ;i < MultiFishNum;i++)
		{
			p_StateMachine = m_multiFish[i]->getFSM();

			p_StateMachine->changeState(AICautionState::Instance());
		}
	}
}