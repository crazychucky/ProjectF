//运动游戏对象
#ifndef __MOVINGGAMEOBJ_H__
#define __MOVINGGAMEOBJ_H__

#include "cocos2d.h"
#include "GameObj.h"
USING_NS_CC;

class SteeringBehaviors;

class MovingGameObj:public GameObj
{
public:
	MovingGameObj();
	~MovingGameObj();

	static MovingGameObj* create(float objMass,float objMaxSpeed,float objMaxForce,CCPoint heading);

	virtual bool init();

	SteeringBehaviors*const getSteering() const;

	float getMaxForce()const{ return m_fMaxForce;}

	float getMaxSpeed()const{ return m_fMaxSpeed;}

	float getSpeed()const{ return m_vVelocity.getLength();}

	CCPoint getHeading()const{ return m_vHeading;}

	CCPoint getVelocity()const{ return m_vVelocity;}

	CCPoint getPosition() const{ return m_obPosition;}

	CCPoint getLastPosition() const{ return m_obLastPosition;}

	float getObjRadius(){ return m_fObjRadius;}

	void steeringMoving(float dt);  //moving excute

	static MovingGameObj* getMovingGameObjByID(int objID);

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

	bool isTaged()const{return m_bTag;}

	void TagMovingGameObj(float neighborRadius);

	CCArray* getNeighbors()const{return m_neighbors;};

	void onEnter();
	void onExit();

protected:
	CREATE_FUNC(MovingGameObj);
	SteeringBehaviors* m_pSteering;
	//param
	float m_fMaxForce;
	float m_fMaxSpeed;
	float m_fMass;
	float m_fObjRadius;
	CCPoint m_vHeading;
	CCPoint m_vVelocity;
	CCPoint m_obLastPosition;
	bool m_bTag;
	
	CCArray* m_neighbors;
};

#define GetMovingGameObj(d) MovingGameObj::getMovingGameObjByID(d)

#endif