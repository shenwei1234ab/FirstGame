#pragma once 
#include "base\stdafx.h"
#include "base\Particle.h"
#include "base\GameObject.h"
#include "base\Quad.h"
#include "base\TextureManager.h"
#include "base\AABox2.h"
#include "base\CNode.h"
#include "base\Scene.h"
class Ball:public CNode,public Particle::IAppearance
{
public:
	Ball(unsigned int  ballType):m_particle(NULL),m_radius(16.F),m_positionUpdated(false),m_type(ballType)
	{
		//������ͼ
		m_quad.SetColor(0xFFFFFFFF);
		SetBallType(m_type);
			Vector2 min(0,0);
			Vector2 max(1,1);
			m_quad.setTexcoords(AABox2(min,max),m_texture);	
		//�����ʵ�
		m_particle = new Particle();
		m_particle->SetAppearance(this);		
	}



	~Ball()
	{
		m_particle->release();
	}

	enum BallType
	{
		red,
		orange,
		green,
		blue,
		white,
		black,
	};
	//�������
	unsigned int  m_type;

	void SetBallType(unsigned int type)
	{
		m_type = type;
		switch (type)
		{
		case white:
			m_texture = TextureManager::instance().loadFromPNG(L"res\\white.png");
			break;
		case red:
			m_texture = TextureManager::instance().loadFromPNG(L"res\\red.png");
			break;
		case black:
			m_texture = TextureManager::instance().loadFromPNG(L"res\\black.png");
			break;
		case orange:
			m_texture = TextureManager::instance().loadFromPNG(L"res\\orange.png");
			break;
		case green:
				m_texture = TextureManager::instance().loadFromPNG(L"res\\green.png");
			break;
		case blue:
				m_texture = TextureManager::instance().loadFromPNG(L"res\\blue.png");
			break;
		default:
			m_texture = TextureManager::instance().loadFromPNG(L"res\\white.png");
			break;
			;
		}
	}



	//�������ĵ���������
	const Vector2 & GetWorldPosition()const
	{
		return CNode::GetWorldPosition();
	}


	//������λ�ƻ�����ת��������ʱ
	virtual void OnCleanDirty()
	{
			Vector2 p[4];
			//����������װ��Ϊ��������
			//Vector2 pos = this->GetPosition();
			p[0] = m_worldMatrix.transform_vector(m_location.corner_0());
			p[1] = m_worldMatrix.transform_vector(m_location.corner_1());
			p[2] = m_worldMatrix.transform_vector(m_location.corner_2());
			p[3] = m_worldMatrix.transform_vector(m_location.corner_3());
		for (int i = 0; i < 4; ++i) 
			{
				m_quad.v[i].x = p[i].x;
				m_quad.v[i].y = p[i].y;
			}
	}

	virtual const Vector2& GetLocalPosition()const 
	{
		return this->m_particle->GetPosition();
	}

	virtual void SetLocalPosition(const Vector2 &v)
	{
		this->m_particle->SetPosition(v);
	}

	virtual void Update(float deltaTime)
	{
		//�������Ҫ�ƶ�
		if(m_particle->GetVelocity() != Vector2::Zero())
		{
		}
		//����Ӱ�쵼����λ�Ƶĸı�
		if(m_positionUpdated)
		{
			m_positionUpdated = false;
			//�õ���Ե�λ��
			//const Vector2 &pos = m_particle->GetPosition();
			//�ʵ㷢�����ƶ�,�����ʵ������˶�
			CNode::SetPosition(m_particle->GetPosition());	
		}
	}

	virtual void Render()
	{
		if (m_texture) 
		{
			m_texture->bind();
		} 
		else 
		{
			bosi::setTexture(0);
		}
		m_quad.Render();
	}

	void SetRadius(float r)
	{
		m_radius = r;
		m_location.min_corner.x = -m_radius;
		m_location.min_corner.y = -m_radius;
		m_location.max_corner.x= m_radius;
		m_location.max_corner.y = m_radius;
		//m_positionUpdated = true;
	}

	float GetRadius()const 
	{
		return m_radius;
	}

	Particle* GetParticle()
	{
		return m_particle;
	}

	//������۽�ڵ�֪ͨ 
	virtual void PositionUpdated(const Vector2 &pos)
	{
		m_positionUpdated = true;
	}
	
	bool ifUpdated()const 
	{
		return m_positionUpdated;
	}
	virtual void OnContact(Ball *other)
	{

	}	
	float  GetMass()const 
	{
		return this->m_particle->GetMass();
	}

	const Vector2 & GetVelocity()const 
	{
		return this->m_particle->GetVelocity();
	}

protected:
	Particle* m_particle;
	Texture *m_texture;
	//��¼��������
	Quad m_quad;
	float m_radius;
	//�Ƿ��ƶ���
	bool m_positionUpdated;
	

	//����ʵ��λ��
	AABox2 m_location;
};


class Hole:public Ball
{
public:	
	typedef void (Scene::*PFN_GOAL)(Ball *other);
	Hole(): Ball(black),m_pFun(0),m_eventHandler(0)
	{
		
	}

	void  SetEventHandler(Scene *pEventHandler,PFN_GOAL pFun)
	{
		m_eventHandler = pEventHandler;
		m_pFun=pFun;
	}

	//�����¼��ĺ���ָ��
	virtual  void OnContact(Ball *other)
	{
		//ִ�лص�����
		if(m_pFun && m_eventHandler)
		{
			(m_eventHandler->*m_pFun)(other);
		}
	}

protected:
	PFN_GOAL m_pFun;
	Scene *m_eventHandler;
};

typedef RefCountedPtr<Ball> BallPtr;

