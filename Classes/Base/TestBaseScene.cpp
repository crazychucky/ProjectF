#include "Base/TestBaseScene.h"

#define TESTBTN_IMAGE "TestBase/test_btn.png"
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

void TestBaseScene::addTestFuncBtn(const char* s,const CCPoint pt,SEL_TouchEvent selector)
{
	Button* btn = Button::create();
	btn->loadTextureNormal(TESTBTN_IMAGE);
	btn->loadTexturePressed(TESTBTN_IMAGE);
	btn->loadTextureDisabled(TESTBTN_IMAGE);

	CCSize btnSize =btn->getSize();
	CCLabelTTF* btnText = CCLabelTTF::create(s,"Arial",22);
	btnText->setPosition(ccp(btnSize.width/2.0f,btnSize.height/2.0f));
	btn->addChild(btnText,1);

	btn->addTouchEventListener(this,selector);

	btn->setPosition(pt);
	this->addChild(btn);
}