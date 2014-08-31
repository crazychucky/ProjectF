//AI行为 SteeringBehaviors的类
#ifndef __STEERINGBEHAVIORS_H__
#define __STEERINGBEHAVIORS_H__
#include "cocos2d.h"
USING_NS_CC;

class MovingGameObj;

class SteeringBehavior
{
private:
	CCPoint m_vSteeringForce;

	//param set
	//权重
	float m_dWanderJitter;
	float m_dWanderRadius;
	float m_dWanderDistance;
	CCPoint m_vWanderTarget;
	float m_fWeightSeparation;
	float m_fWeightAlignment;
	float m_fWeightCohesion;
	float m_fWeightWallAvoidance;
	float m_fWeightObstacleAvoidance;
	float m_fWeightEvade;
	float m_fWeightPursuit;
	float m_fWeightOffsetPursuit;
	float m_fWeightWander;

	MovingGameObj* m_pVehicle;
	MovingGameObj* m_pTargetAgent1;
	MovingGameObj* m_pTargetAgent2;
	CCPoint m_vOffset;

	enum behavior_type
	{
		none               = 0x00000,
		seek               = 0x00002,
		flee               = 0x00004,
		arrive             = 0x00008,
		wander             = 0x00010,
		cohesion           = 0x00020,
		separation         = 0x00040,
		allignment         = 0x00080,
		obstacle_avoidance = 0x00100,
		wall_avoidance     = 0x00200,
		follow_path        = 0x00400,
		pursuit            = 0x00800,
		evade              = 0x01000,
		interpose          = 0x02000,
		hide               = 0x04000,
		flock              = 0x08000,
		offset_pursuit     = 0x10000,
	};
	enum Deceleration
	{
		slow=3,
		normal=2,
		fast=1
	};
	int m_iFlags;
	bool AccumulateForce(CCPoint &RunningTot,CCPoint ForceToAdd);
	CCRect m_rWallRect;
	float m_fBodyRadius;
public:
	SteeringBehavior(MovingGameObj* agent);
	~SteeringBehavior();
	CCPoint Calculate();
	CCPoint Wander();
	CCPoint Pursuit(const MovingGameObj* evader);
	CCPoint Seek(CCPoint TargetPos);
	CCPoint Evade(MovingGameObj* pursuer);
	CCPoint Flee(CCPoint TargetPos);
	CCPoint WallAvoidance();
	CCPoint Arrive(CCPoint TargetPos,Deceleration deceleration);
	CCPoint OffsetPursuit(const MovingGameObj* leader,const CCPoint offset);
	CCPoint Separation();
	CCPoint SeparationAll();
	//CCPoint ObstacleAvoidance(const std::vector<BaseGameEntity*>& obstacles)
	CCPoint ObstacleAvoidance();
	CCPoint Alignment();
	CCPoint Cohesion();


	void EvadeOn(MovingGameObj* v){m_iFlags |= evade; m_pTargetAgent1 = v;}
	void EvadeOff(){if(On(evade)) m_iFlags ^=evade;}
	void PursuitOn(MovingGameObj* v){m_iFlags |= pursuit; m_pTargetAgent1 = v;}
	void PursuitOff(){if(On(pursuit)) m_iFlags ^=pursuit;}
	void WanderOn(){m_iFlags|= wander;}
	void WanderOff(){if(On(wander)) m_iFlags ^=wander;}
	void FleeOn()   {m_iFlags|=flee;}
	void FleeOff()  {if(On(flee))   m_iFlags ^=flee;}
	void WallAvoidanceOn(CCRect r)   {m_iFlags|=wall_avoidance;m_rWallRect=r;}
	void WallAvoidanceOff()  {if(On(wall_avoidance))   m_iFlags ^=wall_avoidance;}
	void OffsetPursuitOn(MovingGameObj* v1, const CCPoint offset){m_iFlags |= offset_pursuit; m_vOffset = offset; m_pTargetAgent1 = v1;}  
	void OffsetPursuitOff(){if(On(offset_pursuit)) m_iFlags ^=offset_pursuit;}
	void SeparationOn(){m_iFlags|=separation;}
	void SeparationOff(){if(On(separation)) m_iFlags^=separation;}
	void AlignmentOn(){m_iFlags|=allignment;}
	void AlignmentOff(){if(On(allignment)) m_iFlags^=allignment;}
	void CohesionOn(){m_iFlags|=cohesion;}
	void CohesionOff(){if(On(cohesion)) m_iFlags^=cohesion;}
	void ObstacleAvoidanceOn()   {m_iFlags|=obstacle_avoidance;}
	void ObstacleAvoidanceOff()  {if(On(obstacle_avoidance))   m_iFlags ^=obstacle_avoidance;}
	bool On(behavior_type bt){return (m_iFlags & bt) == bt;}
};

#endif