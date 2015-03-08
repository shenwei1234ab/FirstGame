#pragma once
#include "RefCounted.h"
#include "Vector2.h"
class IForce;
class Particle:public RefCounted
{
public:
	//外观的接口,
	class IAppearance
	{
	public:
		//位置有发生变化就通过m_appearance 通知GameObject;
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

	//添加力到容器中
	void AddForce(IForce *pForce);
	//添加合力的向量
	void AddForce(const Vector2 &v);
	//从容器中移出力
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
	//位置
	Vector2 m_Position;
	//速率
	Vector2 m_Velocity;
	//加速度
	Vector2 m_Acceleration;

	Vector2 m_deltaPostion;
	//衰减系数
	float m_Damping;

	//质量的倒数
	float m_InverseMass;

	//合力
	Vector2 m_AccumulatedForce;

	//外观借口
	IAppearance* m_pAppearance;


	//力的集合 
	typedef std::vector<IForce*> Forces;
	Forces m_Forces;
};