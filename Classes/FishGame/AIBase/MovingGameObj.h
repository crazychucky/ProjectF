//运动游戏对象
#ifndef __MOVINGGAMEOBJ_H__
#define __MOVINGGAMEOBJ_H__

#include "cocos2d.h"
#include "GameObj.h"
#include "SteeringBehaviors.h"
USING_NS_CC;

class MovingGameObj:public GameObj
{
public:
	MovingGameObj();
	~MovingGameObj();
	static MovingGameObj* create(float objMass,float objMaxSpeed,float objMaxForce,CCPoint heading);
	SteeringBehavior*const getSteering() const
	{
		return m_pSteering;
	}
	float getMaxForce()const
	{
		return m_fMaxForce;
	}
	float getMaxSpeed()const
	{
		return m_fMaxSpeed;
	}
	float getSpeed()const
	{
		return m_vVelocity.getLength();
	}
	CCPoint getHeading()const
	{
		return m_vHeading;
	}
	CCPoint getVelocity()const
	{
		return m_vVelocity;
	}
	CCPoint getPosition() const
	{
		return m_obPosition;
	}
	CCPoint getLastPosition() const
	{
		return m_obLastPosition;
	}
	float getObjRadius()
	{
		return m_fObjRadius;
	}
	void steeringMoving(float dt);  //moving excute
	static MovingGameObj* getMovingGameObjByID(int objID)
	{
		MovingGameObj* pObj=(MovingGameObj*)MovingGameObj::getGameObjByID(objID);
		return pObj;
	}

	void Tag()
	{
		if (false==m_bTag)
		{
			m_bTag=true;
		}
	}
	void UnTag()
	{
		if (true==m_bTag)
		{
			m_bTag=false;
		}
	}
	bool isTaged()const
	{
		return m_bTag;
	}
	void TagMovingGameObj(float neighborRadius);
	int getNeighborsSize()const
	{
		return m_iNeighborsSize;
	}
	MovingGameObj* getNeighborByIndex(int i)
	{
		return m_neighbors[i];
	}
protected:
	CREATE_FUNC(MovingGameObj);
	SteeringBehavior* m_pSteering;
	//param
	float m_fMaxForce;
	float m_fMaxSpeed;
	float m_fMass;
	float m_fObjRadius;
	CCPoint m_vHeading;
	CCPoint m_vVelocity;
	CCPoint m_obLastPosition;
	bool m_bTag;
	
	int m_iNeighborsSize;
	MovingGameObj* m_neighbors[k_Max_Obj];
};

#define GetMovingGameObj(d) MovingGameObj::getMovingGameObjByID(d)

#endif