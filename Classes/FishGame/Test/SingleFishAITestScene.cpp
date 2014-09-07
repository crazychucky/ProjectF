#include "FishGame/AIBase/SteeringBehaviors.h"
#include "FishGame/AIBase/AIBehaviors.h"
#include "FishGame/Test/SingleFishAITestScene.h"
#include "FishGame/AIBehaviors/AIBehaviorWallAvoidacne.h"

#define BG_IMAGE "white.jpg"


DrawLayer::DrawLayer()
{

}

DrawLayer::~DrawLayer()
{

}

void DrawLayer::setDrawRect(CCRect r)
{
	m_drawRect = r;
}

void DrawLayer::draw()
{
	ccDrawColor4B(255,0,0,255);
	CCPoint dstPt = m_drawRect.origin+ccp(m_drawRect.size.width,m_drawRect.size.height);
	ccDrawRect(m_drawRect.origin,dstPt);
}

SingleFishAITestScene::SingleFishAITestScene()
{
	m_smallWallFlag = false;
}

SingleFishAITestScene::~SingleFishAITestScene()
{

}

bool SingleFishAITestScene::init()
{
	if ( false == TestBaseScene::init())
	{
		return false;
	}

	setTitle("Single AI Test");

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

	m_fishObj = FishObj::create();
	m_fishLayer->addChild(m_fishObj);
	m_fishObj->setPosition(ccp(400,240));
	m_fishObj->setScale(2.0f);

	CCPoint pt;
	CCPoint ptOff;
	pt = ccp(100,460);
	ptOff = ccp(0,-60);

	//Fish game
	pt = pt + ptOff;
	addTestFuncBtn("Wall Switch",pt,toucheventselector(SingleFishAITestScene::onWallTest));

	m_drawLayer = DrawLayer::create();
	CCRect wall=CCRectMake(20.f,20.0f,760.0f,440.0f);
	m_drawLayer->setDrawRect(wall);
	this->addChild(m_drawLayer,998);

	return true;
}

void SingleFishAITestScene::onEnter()
{
	TestBaseScene::onEnter();
}

void SingleFishAITestScene::onExit()
{
	TestBaseScene::onExit();
}

void SingleFishAITestScene::onWallTest(CCObject* pSender,TouchEventType eventtype)
{
	if (TOUCH_EVENT_ENDED == eventtype)
	{
		if (false == m_smallWallFlag)
		{
			m_smallWallFlag = true;
			SteeringBehaviors* pSteering = m_fishObj->getSteering();
			pSteering->removeBehavior(AIBehavior::wall_avoidance);

			CCRect wall=CCRectMake(300.0f,140.0f,200,200.0f);
			AIBehaviorWallAvoidacne* pAIWallAvoidance = new AIBehaviorWallAvoidacne(m_fishObj,wall);
			pSteering->addBehavior(pAIWallAvoidance);

			m_fishObj->setPosition(ccp(400,240));

			m_drawLayer->setDrawRect(wall);
		}
		else
		{
			m_smallWallFlag = false;
			SteeringBehaviors* pSteering = m_fishObj->getSteering();
			pSteering->removeBehavior(AIBehavior::wall_avoidance);

			CCRect wall=CCRectMake(20.f,20.0f,760.0f,440.0f);
			AIBehaviorWallAvoidacne* pAIWallAvoidance = new AIBehaviorWallAvoidacne(m_fishObj,wall);
			pSteering->addBehavior(pAIWallAvoidance);

			m_fishObj->setPosition(ccp(400,240));

			m_drawLayer->setDrawRect(wall);
		}
	}
}