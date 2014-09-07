#include "Base/TestBaseScene.h"

#define TTITLELABEL_TEXT_FONTSIZE 24

#define TESTBTN_IMAGE "TestBase/test_btn.png"

#define TESTBTN_TEXT_FONTSIZE 24

#define BACKBTN_POS ccp(70,450)
TestBaseScene::TestBaseScene()
{
	m_backBtn = NULL;
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
	this->addChild(m_mainTouchGroup,999);

	m_titleLabel = Label::create();
	CCSize winSize =CCDirector::sharedDirector()->getVisibleSize();
	m_titleLabel->setPosition(ccp(winSize.width/2.0f,winSize.height*0.8f));
	m_titleLabel->setFontSize(TTITLELABEL_TEXT_FONTSIZE);
	m_titleLabel->setText("Test Console");
	m_mainTouchGroup->addWidget(m_titleLabel);

	m_backBtn = Button::create();
	m_backBtn->loadTextureNormal(TESTBTN_IMAGE);
	m_backBtn->loadTexturePressed(TESTBTN_IMAGE);
	m_backBtn->loadTextureDisabled(TESTBTN_IMAGE);

	Label* btnText = Label::create();
	btnText->setText("Back");
	btnText->setFontSize(TESTBTN_TEXT_FONTSIZE);
	btnText->setPosition(ccp(0,0));
	btnText->setAnchorPoint(ccp(0.5,0.5));
	m_backBtn->addChild(btnText,1);

	m_backBtn->setPosition(BACKBTN_POS);

	m_backBtn->addTouchEventListener(this,toucheventselector(TestBaseScene::onBack));

	m_mainTouchGroup->addWidget(m_backBtn);


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

void TestBaseScene::setTitle(char* s)
{
	m_titleLabel->setText(s);
}

void TestBaseScene::onBack(CCObject* pSender,TouchEventType eventtype)
{
	if ( TOUCH_EVENT_ENDED == eventtype)
	{
		CCDirector::sharedDirector()->popScene();
	}
}

void TestBaseScene::setBackBtnEnabled(bool b)
{
	if (NULL != m_backBtn)
	{
		m_backBtn->setEnabled(b);
	}
}