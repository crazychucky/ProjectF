//µ•¿˝ AI∂‘œÛ≤‚ ‘
#ifndef __MultiFishAITestScene_H__
#define __MultiFishAITestScene_H__

#include "Base/TestBaseScene.h"
#include "FishGame/FishObj.h"
#include "FishGame/Test/DrawLayer.h"

#define MultiFishNum 40
class MultiFishAITestScene:public TestBaseScene,public DrawDelegate
{
public:
	MultiFishAITestScene();
	virtual ~MultiFishAITestScene();
	CREATE_FUNC(MultiFishAITestScene);
	bool init();

	void onEnter();
	void onExit();

	virtual void debugDraw();

	void update(float dt);
private:
	bool m_separationAIFlag;
	CCLayer* m_bgLayer;
	CCLayer* m_fishLayer;
	FishObj* m_multiFish[MultiFishNum];

private:
	void onSwitchSeparationAI(CCObject* pSender,TouchEventType eventtype);
};

#endif