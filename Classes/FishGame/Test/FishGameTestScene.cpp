#include "FishGame/Test/FishGameTestScene.h"
#include "FishGame/Test/SingleFishAITestScene.h"

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

	//Fish game
	pt = pt + ptOff;
	addTestFuncBtn("Fish Game",pt,toucheventselector(FishGameTestScene::testSingleAI));

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