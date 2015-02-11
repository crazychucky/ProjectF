#include "WaterFilter/Test/WaterFilterTestScene.h"
#include "WaterFilter/ShaderNode.h"
#include "WaterFilter/Test/RippleScene.h"

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

	/*
	ShaderNode* shader = ShaderNode::shaderNodeWithVertex("shader.vsh","shader.fsh");
	shader->setContentSize(getContentSize());
	shader->setColor(ccc4f(1,1,1.0,.5));
	this->addChild(shader,2);

	*/

#if 0
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCNode* node = CCNode::create();
	node->setTag(999);
	addChild(node);
	CCSprite* sp = CCSprite::create("HelloWorld.png");
	sp->setPosition(ccp(400,240));
	node->addChild(sp);
	//CCActionInterval * ripple3D= CCRipple3D::create(3.0f, CCSizeMake(32,24), ccp(winSize.width/2,winSize.height/2), 240, 4, 160);
	//node->runAction(ripple3D);
	CCActionInterval * shatteredTiles3D= CCShatteredTiles3D::create(1,CCSizeMake(16, 12), 5,false);
	node->runAction(shatteredTiles3D);

	this->scheduleOnce(schedule_selector(WaterFilterTestScene::testFunc), 19.0f);
#endif

	//CCActionInterval * liquid = CCLiquid::create(2, CCSizeMake(32,24), 1, 20);
	//sp->runAction(liquid);

#if 1
	CRippleLayer* pLayer = CRippleLayer::create();
	this->addChild(pLayer);
#endif

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

void WaterFilterTestScene::testFunc(float dt)
{
	CCNode* node = this->getChildByTag(999);
	if (node)
	{
		node->setGrid(NULL);
	}
}