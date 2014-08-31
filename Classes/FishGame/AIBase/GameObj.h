//游戏对象
#ifndef __GAMEOBJ_H__
#define __GAMEOBJ_H__

#include "cocos2d.h"
USING_NS_CC;

#define k_Max_Obj 50

class GameObj:public CCNode
{
public:
	GameObj();
	~GameObj();
	virtual bool init();

	int getObjID() const
	{
		return m_iObjID;
	}

	static GameObj* getGameObjByID(int objID);

	static int getMaxGameObjID()
	{
		return (nextVaildObjID-1);
	}

	void onEnter();
	void onExit();
private:
	int m_iObjID;
	static int nextVaildObjID;
	static GameObj* m_pAllGameObjs[k_Max_Obj];     //type cast  may be needed
};

#define GetGameObj(d) GameObj::getGameObjByID(d)
#define GetMaxGameObjID() GameObj::getMaxGameObjID()

#endif