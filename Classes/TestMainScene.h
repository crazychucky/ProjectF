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
	void testFunc1(CCObject* pSender,TouchEventType eventtype);
};

#endif