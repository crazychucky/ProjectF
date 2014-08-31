#include "WaterFilter/Test/WaterFilterTestScene.h"

WaterFilterTestScene::WaterFilterTestScene()
{

}

WaterFilterTestScene::~WaterFilterTestScene()
{

}

bool WaterFilterTestScene::init()
{
	if (false == TestBaseScene::init())
	{
		return false;
	}

	return true;
}

void WaterFilterTestScene::onEnter()
{
	TestBaseScene::onEnter();
}

void WaterFilterTestScene::onExit()
{
	TestBaseScene::onExit();
}