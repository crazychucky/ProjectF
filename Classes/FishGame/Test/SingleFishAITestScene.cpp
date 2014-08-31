#include "FishGame/Test/SingleFishAITestScene.h"

SingleFishAITestScene::SingleFishAITestScene()
{

}

SingleFishAITestScene::~SingleFishAITestScene()
{

}

bool SingleFishAITestScene::init()
{
	if ( false == TestBaseScene::init())
	{
		return false;
	}

	setTitle("Single AI Test");
	return true;
}

void SingleFishAITestScene::onEnter()
{
	TestBaseScene::onEnter();
}

void SingleFishAITestScene::onExit()
{
	TestBaseScene::onExit();
}