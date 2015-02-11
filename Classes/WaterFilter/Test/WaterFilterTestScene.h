//水波滤镜的Test Scene
#ifndef __WATERFILTERTESTSCENE_H__
#define __WATERFILTERTESTSCENE_H__

#include "Base/TestBaseScene.h"

class WaterFilterTestScene:public TestBaseScene
{
public:
	WaterFilterTestScene();
	virtual ~WaterFilterTestScene();
	CREATE_FUNC(WaterFilterTestScene);
	virtual bool init();

	void onEnter();
	void onExit();

private:
	void testFunc(float dt);

};

#endif