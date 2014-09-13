#include "WaterFilter/Test/WaterFilterTestScene.h"
#include "WaterFilter/ShaderNode.h"

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
	setTitle("Water Filter Test");

	ShaderNode* shader = ShaderNode::shaderNodeWithVertex("shader.vsh","shader.fsh");
	shader->setContentSize(getContentSize());
	shader->setColor(ccc4f(1,1,1.0,.5));
	this->addChild(shader,2);

	CCSprite* sp = CCSprite::create("HelloWorld.png");
	sp->setPosition(ccp(400,240));
	this->addChild(sp);

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