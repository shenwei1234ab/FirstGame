#pragma once 
#include "base\CNode.h"
#include "base\Quad.h"
#include "base\AABox2.h"
#include "base\Texture.h"
#include "base\stdafx.h"
#include "Ball.h"
#include "base\AABox2.h"
#include "base\TextureManager.h"
class Ball;

class BallArm:public CNode
{
public:
	enum Status
	{
		rotate,
		moving,
		recovery,
		hitBall
	};
	unsigned int m_Status;

	/*
	    maxDist ��˵������������
		pBall Ҫ���Ƶ���
		width ����
		height ���
		movingSpeed �ƶ��ٶ�
		coefficient �ָ�ϵ��
	*/
	BallArm(int maxDist,Ball *pBall,int width,int height,float movingSpeed,float coefficient):m_CurDistance(0.f),m_MaxDistance(maxDist),m_controlBall(pBall),m_width(width),m_height(height),m_Status(rotate),m_MovingSpeed(movingSpeed),m_Coefficient(coefficient)
	{
		//������ͼ
		m_texture = TextureManager::instance().loadFromPNG(L"res\\pat.png");
		if(pBall)
		{
			//���ڵ���m_controlBall
			pBall->AddChild(this);
			pBall->addRef();
		}

		if(m_texture)
		{
			Vector2 min(0,0);
			Vector2 max(1,1);
			m_WorldPosition.setTexcoords(AABox2(min,max),m_texture);
		}
		//���ó�ʼλ��
		Init();
	}

	//������˵ĳ�ʼλ��
	void Init()
	{
		//���豾����ϵ�������ʵ��غϣ�������˵��ĸ������ڱ�����ϵ�е�λ��
		//Ĭ��Ϊ��x��ƽ��
		float x= m_controlBall->GetRadius();
		m_localPosition.min_corner = Vector2(x,-m_height*0.5f);
		m_localPosition.max_corner =Vector2(x+m_width,m_height*0.5f);
		m_MousePosition.x = 0;
		m_MousePosition.y = 0;
	}


	virtual void Update(float deltaTime)
	{
		//BallArm ״̬Ϊ������ڲ�����ת
		if(this->m_enable && m_Status ==  rotate )
		{
		//��ǰ����λ�� 
		Vector2 curPosition((float )bosi::getMousePosition().x,(float )bosi::getMousePosition().y);
		//����н�
			float theta = atan2(bosi::getMousePosition().y - m_controlBall->GetWorldPosition().y,bosi::getMousePosition().x-m_controlBall->GetWorldPosition().x);
			this->SetRotate(-theta);
			//this->SetPosition(Vector2(m_controlBall->GetRadius()+m_width/2,0));
		
		}
		//BallArm ״̬Ϊ������ڲ����ƶ�
		else if(this->m_enable && m_Status == moving)
		{
			
			Vector2 mosVec = Vector2((float)bosi::getMousePosition().x,(float)bosi::getMousePosition().y) - m_MousePressDown;
			//������m_MousePressDown��ɵ�������m_ParaVec��ͶӰ
			m_CurDistance = mosVec.dot_product(m_ParaVec);
			//�Ƿ��������ƶ�����
			if( m_CurDistance > m_MaxDistance )
			{
				m_CurDistance = m_MaxDistance;
			}
			//�Ƿ�Ϊ��
			if( m_CurDistance < 0.f)
			{
				m_CurDistance =0.f;
			}
			//�ƶ�
			Vector2 prjVec = m_CurDistance* m_ParaVec;
			this->SetPosition(prjVec);
		}
		//BallArm ״̬Ϊ�ڻָ��ƶ�
		else if(this->m_enable && m_Status ==  recovery)
		{
			//���ڻָ���
			if( m_CurDistance > 0.f)
			{
				m_CurDistance -= m_MovingSpeed;
				Vector2 prjVec = m_CurDistance* m_ParaVec;
				this->SetPosition(prjVec);
			}
			//���ײ������
			else
			{
				//С�������ٶ�
				this->m_controlBall->GetParticle()->SetVelocity(m_ContactVec);
				//��˲��ɼ�
				this->SetEnable(false);
				//����״̬
				m_Status = hitBall;
			}
		}
	}


	virtual void OnCleanDirty()
	{
		Vector2 p[4];
			//����������װ��Ϊ��������
			//Vector2 pos = this->GetPosition();
			p[0] = m_worldMatrix.transform_vector(m_localPosition.corner_0());
			p[1] = m_worldMatrix.transform_vector(m_localPosition.corner_1());
			p[2] = m_worldMatrix.transform_vector(m_localPosition.corner_2());
			p[3] = m_worldMatrix.transform_vector(m_localPosition.corner_3());
		for (int i = 0; i < 4; ++i) 
			{
				m_WorldPosition.v[i].x = p[i].x;
				m_WorldPosition.v[i].y = p[i].y;
			}
	}

	//��갴���¼�
	void MousePressDown(const bosi::MouseEvent *pMe)
	{
		if(m_Status == rotate)
		{
		//��˲�����ת��
		m_Status = moving;
		m_MousePressDown = Vector2((float )bosi::getMousePosition().x,(float )bosi::getMousePosition().y);
		//ƽ������˵ĵ�λ����
		m_ParaVec = Vector2(m_WorldPosition.v[1].x - m_WorldPosition.v[0].x,m_WorldPosition.v[1].y - m_WorldPosition.v[0].y).Unit();
		}
	}


	//��굯��
	void  MousePressUp(const bosi::MouseEvent *pMe)
	{
		if(m_Status == moving)
		{
		m_Status = recovery;
		//����ײ����С����ٶ�
		m_ContactVec = -  sqrt(m_Coefficient/m_controlBall->GetMass() )*m_CurDistance* m_ParaVec;
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
		m_WorldPosition.Render();
	}
protected:
	//�ָ�ϵ��
	float m_Coefficient;
	//ײ����С����ٶ�
	Vector2 m_ContactVec;

	//�ָ����ٶ�
	float m_MovingSpeed;
	//�Ѿ��ƶ��ľ���
	float  m_CurDistance;
	//����ƶ�����
	float  m_MaxDistance;
	

	//��¼��һ������λ��
	Vector2 m_MousePosition;

	//��¼��һ����갴�µ�λ��
	Vector2 m_MousePressDown;

	//��ǰ�����ƽ�е�����
	Vector2 m_ParaVec;
	
	Texture *m_texture;
	
	AABox2 m_localPosition;
	
	//�������
	Quad m_WorldPosition;

	int m_width;
	int m_height;
	//Ҫ���Ƶİ���
	Ball* m_controlBall;
	
};


typedef RefCountedPtr<BallArm > BallArmPtr;