//Test Scene的主界面
#ifndef __TESTMAINSCENE_H__
#define __TESTMAINSCENE_H__

#include "Base/TestBaseScene.h"

class TestMainScene:public TestBaseScene
{
public:
	TestMainScene();
	virtual ~TestMainScene();
	CREATE_FUNC(TestMainScene);
	virtual bool init();
private:
	void testFishGame(CCObject* pSender,TouchEventType eventtype);

	void testWaterFilter(CCObject* pSender,TouchEventType eventtype);
};

#endif