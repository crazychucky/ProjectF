//Fish Game Test Scene��������
#ifndef __FISHGAMETESTSCENE_H__
#define __FISHGAMETESTSCENE_H__

#include "Base/TestBaseScene.h"

class FishGameTestScene:public TestBaseScene
{
public:
	FishGameTestScene();
	virtual ~FishGameTestScene();
	CREATE_FUNC(FishGameTestScene);
	virtual bool init();

	void onEnter();
	void onExit();

private:

};

#endif