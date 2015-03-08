#pragma once
#include "RefCounted.h"
#include "Vector2.h"
class IForce;
class Particle:public RefCounted
{
public:
	//��۵Ľӿ�,
	class IAppearance
	{
	public:
		//λ���з����仯��ͨ��m_appearance ֪ͨGameObject;
		virtual void PositionUpdated(const Vector2 &pos){};
		virtual void Destroyed(){};
	};

	Particle();
	~Particle();


	void SetPosition(const Vector2 &vp)
	{
		this->m_Position = vp;
		if(m_pAppearance)
		{
			m_pAppearance->PositionUpdated(vp);
		}
	}

	const Vector2& GetPosition()const
	{
		return m_Position;
	}


	void SetVelocity(const Vector2 &vp)
	{
		this->m_Velocity = vp;
	}
	const Vector2& GetVelocity()const
	{
		return m_Velocity;
	}


	void SetAcceleration(Vector2 &vp)
	{
		this->m_Acceleration = vp;
	}
	const Vector2& GetAcceleration()const
	{
		return m_Acceleration;
	}

	void SetDamping(float damp)
	{
		m_Damping = damp;
	}
	float  GetDamping()const 
	{
		return m_Damping;
	}


	void SetMass(float mass)
	{
		m_InverseMass = 1.f/mass;
	}
	float GetMass()const 
	{
		return 1.f/m_InverseMass;
	}
	float GetInverseMass()const
	{
		return m_InverseMass;
	}

	//�������������
	void AddForce(IForce *pForce);
	//��Ӻ���������
	void AddForce(const Vector2 &v);
	//���������Ƴ���
	void UpdateForce();

	void RemoveForce(IForce *pForce);

	void Update(float deltaTime);

	void SetAppearance(IAppearance *appearance)
	{
		if (m_pAppearance) 
			{
			m_pAppearance->Destroyed();
		}
		if ((m_pAppearance = appearance)) 
		{
			m_pAppearance->PositionUpdated(m_Position);
		}
	}

	Vector2&  GetDeltaPost()
	{
		return m_deltaPostion;
	}

protected:
	//λ��
	Vector2 m_Position;
	//����
	Vector2 m_Velocity;
	//���ٶ�
	Vector2 m_Acceleration;

	Vector2 m_deltaPostion;
	//˥��ϵ��
	float m_Damping;

	//�����ĵ���
	float m_InverseMass;

	//����
	Vector2 m_AccumulatedForce;

	//��۽��
	IAppearance* m_pAppearance;


	//���ļ��� 
	typedef std::vector<IForce*> Forces;
	Forces m_Forces;
};