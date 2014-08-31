#include "GameObj.h"
#include "cocos2d.h"

int GameObj::nextVaildObjID=0;
GameObj* GameObj::m_pAllGameObjs[k_Max_Obj]={};

GameObj::GameObj()
{
	this->m_iObjID=GameObj::nextVaildObjID;
	if(this->m_iObjID<k_Max_Obj)
	{
		GameObj::m_pAllGameObjs[this->m_iObjID]=this;
	}
	else
	{
		CCLOG("ERROR:GameObj Reaches the Limit: %d",this->m_iObjID);
	}
	GameObj::nextVaildObjID++;
}

GameObj::~GameObj()
{
	CCLOG("INFO:GameObj %d Deleted Safely",this->m_iObjID);
}

bool GameObj::init()
{
	if (false == CCNode::init())
	{
		return false;
	}

	return true;
}
GameObj* GameObj::getGameObjByID(int objID)
{
	if (objID<nextVaildObjID)
	{
		return m_pAllGameObjs[objID];
	}
	else
	{
		return NULL;
	}
}

void GameObj::onEnter()
{
	CCNode::onEnter();
}

void GameObj::onExit()
{
	CCNode::onExit();
}