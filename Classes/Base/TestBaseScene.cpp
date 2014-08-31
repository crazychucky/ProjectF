#include "Base/TestBaseScene.h"

#define TESTBTN_IMAGE "TestBase/test_btn.png"
#define TESTBTN_TEXT_FONTSIZE 24
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

	m_mainTouchGroup = TouchGroup::create();
	this->addChild(m_mainTouchGroup);

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

	Label* btnText = Label::create();
	btnText->setText(s);
	btnText->setFontSize(TESTBTN_TEXT_FONTSIZE);
	btnText->setPosition(ccp(0,0));
	btnText->setAnchorPoint(ccp(0.5,0.5));
	btn->addChild(btnText,1);

	btn->setPosition(pt);

	btn->addTouchEventListener(this,selector);


	m_mainTouchGroup->addWidget(btn);
}