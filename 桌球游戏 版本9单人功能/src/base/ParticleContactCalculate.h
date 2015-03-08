#pragma once
#include "Vector2.h"
//计算两个质点碰撞后的速度
class Particle;
class ParticleContactCalculate
{
public:
	ParticleContactCalculate():m_p0(0),m_p1(0),m_coefficient(1)
	{

	}

	void Init(Particle *p0,Particle *p1,const Vector2 contactNormal);

	//计算靠近速度
	float  CalculateCloseSpeed();

	//计算分离速度
	void  Resolve();
protected:
	//要计算的两个质点 
	Particle *m_p0,*m_p1;
	//碰撞点的法线向量
	Vector2 m_contactNormal;

	//恢复系数 k= u1-u0/v0-v1
	float m_coefficient;
};