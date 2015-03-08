#include "stdafx.h"
#include "Particle.h"
#include "IForce.h"

Particle::Particle():m_Damping(DAMPING),m_InverseMass(0.0F),m_pAppearance(NULL)
{

}


Particle::~Particle()
{

}
void Particle::AddForce(IForce *pForce)
{
	assert(NULL != pForce);
	pForce->addRef();
	m_Forces.push_back(pForce);
}

void Particle::AddForce(const Vector2 &vForce)
{
	this->m_AccumulatedForce += vForce;
}


void Particle::UpdateForce()
{
	for(Forces::iterator it = m_Forces.begin();it!=m_Forces.end();++it )
	{
		(*it)->GenerateForce(this);
	}
}


void Particle::RemoveForce(IForce *pForce)
{
	assert(NULL != pForce);
	for(Forces::iterator iter= m_Forces.begin();iter!= m_Forces.end();++iter)
	{
		if( (*iter)== pForce )
		{
			pForce->release();
			m_Forces.erase(iter);
			break;
		}
	}
}


void Particle::Update(float deltaTime)
{
	//������ٶ�
	m_Acceleration = m_AccumulatedForce*m_InverseMass;

	//����ţ�ٶ��ɼ���λ�ã�����
	Vector2 pos = m_Position;
	//Xt=X0+V0t+1/2*a*t*t;
	
	m_Position += m_Velocity*deltaTime + m_Acceleration*(0.5f*deltaTime*deltaTime);
	bool ifPositionUpdate = m_Position !=  pos;
	
	m_Velocity += m_Acceleration*deltaTime ;

	if( m_Velocity != Vector2::Zero() )
	{
		m_Velocity *= powf(m_Damping,deltaTime);

		//����ٶ�С��
		if(m_Velocity.length_square() < 1.f)
		{
			m_Velocity = Vector2::Zero();
		}
	}

	//��պ���
	m_AccumulatedForce = Vector2::Zero();

	//λ���з����仯��ͨ��m_appearance ֪ͨGameObject;
	if(m_pAppearance)
	{
		if(ifPositionUpdate)
		{
			//�������ڵ����λ��
			m_pAppearance->PositionUpdated(m_Position);
		}
	}
}




