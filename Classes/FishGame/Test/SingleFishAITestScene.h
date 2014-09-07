//单例 AI对象测试
#ifndef __SINGLEFISHAITESTSCENE_H__
#define __SINGLEFISHAITESTSCENE_H__

#include "Base/TestBaseScene.h"
#include "FishGame/FishObj.h"

class DrawLayer:public CCLayer
{
public:
	DrawLayer();
	virtual ~DrawLayer();
	CREATE_FUNC(DrawLayer);

	void setDrawRect(CCRect r);
private:
	CCRect m_drawRect;

	void draw();
};

class SingleFishAITestScene:public TestBaseScene
{
public:
	SingleFishAITestScene();
	virtual ~SingleFishAITestScene();
	CREATE_FUNC(SingleFishAITestScene);
	bool init();

	void onEnter();
	void onExit();

private:
	CCLayer* m_bgLayer;
	CCLayer* m_fishLayer;
	FishObj* m_fishObj;
	DrawLayer* m_drawLayer;
	bool m_smallWallFlag;

private:
	void onWallTest(CCObject* pSender,TouchEventType eventtype);

};

#endif