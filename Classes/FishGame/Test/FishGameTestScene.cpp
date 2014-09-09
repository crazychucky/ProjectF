#include "FishGame/Test/FishGameTestScene.h"
#include "FishGame/Test/SingleFishAITestScene.h"
#include "FishGame/Test/MultiFishAITestScene.h"

FishGameTestScene::FishGameTestScene()
{

}

FishGameTestScene::~FishGameTestScene()
{

}

bool FishGameTestScene::init()
{
	if (false == TestBaseScene::init())
	{
		return false;
	}

	setTitle("Fish Game Test Console");

	CCPoint pt;
	CCPoint ptOff;
	pt = ccp(100,460);
	ptOff = ccp(0,-60);

	//single fish ai
	pt = pt + ptOff;
	addTestFuncBtn("Single AI",pt,toucheventselector(FishGameTestScene::testSingleAI));

	//mulit fish ai test
	pt = pt + ptOff;
	addTestFuncBtn("Multi AI",pt,toucheventselector(FishGameTestScene::testMultiAI));

	return true;
}

void FishGameTestScene::onEnter()
{
	TestBaseScene::onEnter();
}

void FishGameTestScene::onExit()
{
	TestBaseScene::onExit();
}

void FishGameTestScene::testSingleAI(CCObject* pSender,TouchEventType eventtype)
{
	if ( TOUCH_EVENT_ENDED == eventtype)
	{
		SingleFishAITestScene* pScene =SingleFishAITestScene::create();
		CCDirector::sharedDirector()->pushScene(pScene);
	}
}

void FishGameTestScene::testMultiAI(CCObject* pSender,TouchEventType eventtype)
{
	if ( TOUCH_EVENT_ENDED == eventtype)
	{
		MultiFishAITestScene* pScene =MultiFishAITestScene::create();
		CCDirector::sharedDirector()->pushScene(pScene);
	}
}