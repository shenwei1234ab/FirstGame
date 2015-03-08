#pragma once //����
#include "IForce.h"
#include "Vector2.h"
class Particle;
class Gravity:public IForce
{
public:
	Gravity()
	{

	}

	//��ʼ���������ٶ�
	Gravity(const Vector2 &vg):m_GravityAcceleration(vg)
	{

	}
	virtual void  GenerateForce(Particle *pParticle)
	{
		
		pParticle->AddForce(pParticle->GetMass()*m_GravityAcceleration);
	}
protected:
	//�������ٶ�
	Vector2 m_GravityAcceleration;
};