//���� AI�������
#ifndef __SINGLEFISHAITESTSCENE_H__
#define __SINGLEFISHAITESTSCENE_H__

#include "Base/TestBaseScene.h"

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

};

#endif