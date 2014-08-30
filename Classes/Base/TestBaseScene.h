//TestScene的基类
#ifndef __TESTBASESCENE_H__
#define __TESTBASESCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

class TestBaseScene:public CCScene
{
public:
	TestBaseScene();
	virtual ~TestBaseScene();
	CREATE_FUNC(TestBaseScene);
	virtual bool init();

	void onEnter();
	void onExit();

protected:
	void addTestFuncBtn(const char* s,const CCPoint pt,SEL_TouchEvent selector);

protected:
	TouchGroup* m_mainTouchGroup;
private:

};

#endif //
