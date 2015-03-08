#pragma once //重力
#include "IForce.h"
#include "Vector2.h"
class Particle;
class Gravity:public IForce
{
public:
	Gravity()
	{

	}

	//初始化重力加速度
	Gravity(const Vector2 &vg):m_GravityAcceleration(vg)
	{

	}
	virtual void  GenerateForce(Particle *pParticle)
	{
		
		pParticle->AddForce(pParticle->GetMass()*m_GravityAcceleration);
	}
protected:
	//重力加速度
	Vector2 m_GravityAcceleration;
};