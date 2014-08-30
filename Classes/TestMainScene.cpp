#include "TestMainScene.h"

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

	CCPoint pt = ccp(100,420);
	addTestFuncBtn("Output",pt,toucheventselector(TestMainScene::testFunc1));
	return true;
}

void TestMainScene::testFunc1(CCObject* pSender,TouchEventType eventtype)
{
	if (TOUCH_EVENT_ENDED == eventtype)
	{
		CCLOG("Touch Pressed");
	}
}