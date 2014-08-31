#include "TestMainScene.h"
#include "FishGame/Test/FishGameTestScene.h"
#include "WaterFilter/Test/WaterFilterTestScene.h"

TestMainScene::TestMainScene()
{

}

TestMainScene::~TestMainScene()
{

}

bool TestMainScene::init()
{
	if (false == TestBaseScene::init())
	{
		return false;
	}
	setTitle("Main Test Console");

	CCPoint pt;
	CCPoint ptOff;
	pt = ccp(100,480);
	ptOff = ccp(0,-60);

	//Fish game
	pt = pt + ptOff;
	addTestFuncBtn("Fish Game",pt,toucheventselector(TestMainScene::testFishGame));

	//Water Filter
	pt = pt + ptOff;
	addTestFuncBtn("Filter",pt,toucheventselector(TestMainScene::testWaterFilter));

	setBackBtnEnabled(false);
	return true;
}

void TestMainScene::testFishGame(CCObject* pSender,TouchEventType eventtype)
{
	if (TOUCH_EVENT_ENDED == eventtype)
	{
		FishGameTestScene* pScene =FishGameTestScene::create();
		CCDirector::sharedDirector()->pushScene(pScene);
	}
}

void TestMainScene::testWaterFilter(CCObject* pSender,TouchEventType eventtype)
{
	if (TOUCH_EVENT_ENDED == eventtype)
	{
		WaterFilterTestScene* pScene =WaterFilterTestScene::create();
		CCDirector::sharedDirector()->pushScene(pScene);
	}
}