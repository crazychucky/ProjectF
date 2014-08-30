//TestSceneµÄ»ùÀà
#ifndef __TESTBASESCENE_H__
#define __TESTBASESCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class TestBaseScene:public CCScene
{
public:
	TestBaseScene();
	virtual ~TestBaseScene();
	CREATE_FUNC(TestBaseScene);
	virtual bool init();

	void onEnter();
	void onExit();

private:

};

#endif //
