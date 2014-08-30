#include "Base/TestBaseScene.h"

TestBaseScene::TestBaseScene()
{

}

TestBaseScene::~TestBaseScene()
{

}

bool TestBaseScene::init()
{
	if (false == CCScene::init())
	{
		return false;
	}

	return true;
}

void TestBaseScene::onEnter()
{
	CCScene::onEnter();
}

void TestBaseScene::onExit()
{
	CCScene::onExit();
}