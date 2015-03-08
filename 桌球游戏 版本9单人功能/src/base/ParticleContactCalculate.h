#pragma once
#include "Vector2.h"
//���������ʵ���ײ����ٶ�
class Particle;
class ParticleContactCalculate
{
public:
	ParticleContactCalculate():m_p0(0),m_p1(0),m_coefficient(1)
	{

	}

	void Init(Particle *p0,Particle *p1,const Vector2 contactNormal);

	//���㿿���ٶ�
	float  CalculateCloseSpeed();

	//��������ٶ�
	void  Resolve();
protected:
	//Ҫ����������ʵ� 
	Particle *m_p0,*m_p1;
	//��ײ��ķ�������
	Vector2 m_contactNormal;

	//�ָ�ϵ�� k= u1-u0/v0-v1
	float m_coefficient;
};