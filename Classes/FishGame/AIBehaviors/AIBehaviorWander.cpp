#include "FishGame/AIBehaviors/AIBehaviorWander.h"


#define BehaviorWander_WanderJitter 80.0f  //不明

#define BehaviorWander_WanderRadius 5.0f  //转动角度 过大产生抽风

#define BehaviorWander_WanderDistance 30.0f  //好像和计算的最终力有关?过大会抵消WallAvoid


AIBehaviorWander::AIBehaviorWander(MovingGameObj* obj)
{
	m_behaviorType = AIBehavior::wander;
	m_pVehicle = obj;

	m_fWanderJitter = BehaviorWander_WanderJitter;
	m_fWanderRadius = BehaviorWander_WanderRadius;
	m_fWanderDistance = BehaviorWander_WanderDistance;

}

AIBehaviorWander::~AIBehaviorWander()
{

}

CCPoint AIBehaviorWander::calculateBehaviorForce()
{
	float rollX=1-CCRANDOM_0_1()*2;
	float rollY=1-CCRANDOM_0_1()*2;

	CCPoint newAdd=ccp(rollX*m_fWanderJitter,rollY*m_fWanderJitter);
	float len=newAdd.getLength();
	CCPoint finPt=ccp(newAdd.x/len,newAdd.y/len);
	CCPoint targetPt=finPt*m_fWanderRadius;

	CCPoint disPt=ccpAdd(targetPt,ccp(m_fWanderDistance,0));

	//转换
	float sinA,cosA;
	float sinB,cosB;
	sinA=(float)(m_pVehicle->getHeading().y/m_pVehicle->getHeading().getDistance(CCPointZero));
	cosA=(float)(m_pVehicle->getHeading().x/m_pVehicle->getHeading().getDistance(CCPointZero));
	sinB=(float)(disPt.y/disPt.getDistance(CCPointZero));
	cosB=(float)(disPt.x/disPt.getDistance(CCPointZero));
	float wx,wy;

	wx=disPt.x*m_pVehicle->getHeading().x-disPt.y*m_pVehicle->getHeading().y;
	wy=disPt.x*m_pVehicle->getHeading().y+disPt.y*m_pVehicle->getHeading().x;
	return ccp(wx,wy);
}