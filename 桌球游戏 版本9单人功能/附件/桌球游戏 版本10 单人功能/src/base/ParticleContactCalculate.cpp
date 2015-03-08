#include "ParticleContactCalculate.h"
#include "Particle.h"


void ParticleContactCalculate::Init(Particle *p0,Particle *p1,const Vector2 contactNormal)
{
	this->m_p0 = p0;
	this->m_p1 = p1;
	this->m_contactNormal = contactNormal;
}


float  ParticleContactCalculate::CalculateCloseSpeed()
{
	// m_p0相对m_p1的速度(法线方向的相对速度)
	float closeSpeed = m_p0->GetVelocity().dot_product(m_contactNormal);
	if(m_p1)
	{
		closeSpeed -= m_p1->GetVelocity().dot_product(m_contactNormal);
	}
	return closeSpeed;
}

void  ParticleContactCalculate::Resolve()
{
	float cs = CalculateCloseSpeed();
	float ss = - m_coefficient * cs;
	float ds = ss -cs;


	float totalInverseMass = m_p0->GetInverseMass();
	if (m_p1) {
		totalInverseMass += m_p1->GetInverseMass();
	}

	if( 0 == totalInverseMass)
	{
		return ;
	}

	//计算增加的动量(冲量)
	Vector2 impulse = m_contactNormal * (ds / totalInverseMass);

	
	m_p0->SetVelocity(m_p0->GetVelocity() + impulse * m_p0->GetInverseMass());

	if (m_p1) 
	{
		m_p1->SetVelocity(m_p1->GetVelocity() - impulse * m_p1->GetInverseMass());
	}

}