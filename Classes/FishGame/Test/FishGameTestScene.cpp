#include "FishGame/Test/FishGameTestScene.h"

FishGameTestScene::FishGameTestScene()
{

}

FishGameTestScene::~FishGameTestScene()
{

}

bool FishGameTestScene::init()
{
	if (false == TestBaseScene::init())
	{
		return false;
	}

	setTitle("Fish Game Test Console");
	return true;
}

void FishGameTestScene::onEnter()
{
	TestBaseScene::onEnter();
}

void FishGameTestScene::onExit()
{
	TestBaseScene::onExit();
}