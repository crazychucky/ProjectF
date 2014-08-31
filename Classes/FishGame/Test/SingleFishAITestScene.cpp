#include "FishGame/Test/SingleFishAITestScene.h"
#include "FishGame/FishObj.h"

#define BG_IMAGE "white.jpg"

SingleFishAITestScene::SingleFishAITestScene()
{

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

	FishObj* obj = FishObj::create();
	m_fishLayer->addChild(obj);
	obj->setPosition(ccp(300,200));

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