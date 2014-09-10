//AI Behaviors AI行为
#ifndef __AIBehavior_H__
#define __AIBehavior_H__

#include "cocos2d.h"
#include "FishGame/AIBase/MovingGameObj.h"

USING_NS_CC;

class AIBehavior:public CCObject
{
public:
	virtual ~AIBehavior()
	{
		CCLOG("AI Behaviors:%d deleted safely",m_behaviorType);
	};

	//计算AI牵引力
	virtual CCPoint calculateBehaviorForce()=0;
	float getBehaviorWeight()const
	{
		return m_behaviorWeight;
	}

	static enum behavior_type
	{
		none               = 0x00000,
		wall_avoidance     = 0x00002,
		obstacle_avoidance = 0x00004,
		separation         = 0x00008,
		flee               = 0x00010,
		evade              = 0x00020,
		hide               = 0x00040,
		allignment         = 0x00080,
		cohesion           = 0x00100,
		seek               = 0x00200,
		follow_path        = 0x00400,
		pursuit            = 0x00800,
		arrive             = 0x01000,
		interpose          = 0x02000,
		wander             = 0x04000,
		flock              = 0x08000,
		offset_pursuit     = 0x10000,
	};

	behavior_type getBehaviorType()const
	{
		return m_behaviorType;
	}

	int getAIPriority()const
	{
		return m_priority;
	}
	bool isAIPriorityInited()const
	{
		return m_priorityInitedFlag;
	}
protected:
	AIBehavior()
	{
		m_behaviorType = none;
		m_priorityInitedFlag = false;
		m_priority = 0;   //AI优先级
		m_behaviorWeight = 1.0f;
		this->autorelease();
	}

	void setAIPriority(int n)
	{
		if (false == m_priorityInitedFlag)
		{
			m_priorityInitedFlag = true;
		}
		m_priority = n;
	}

protected:
	behavior_type m_behaviorType;
	float m_behaviorWeight;
	MovingGameObj* m_pVehicle;

private:
	bool m_priorityInitedFlag;
	int m_priority;


};

#endif