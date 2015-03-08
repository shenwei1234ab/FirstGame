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
	    maxDist 球杆的最大伸缩长度
		pBall 要控制的球
		width 长度
		height 宽度
		movingSpeed 移动速度
		coefficient 恢复系数
	*/
	BallArm(int maxDist,Ball *pBall,int width,int height,float movingSpeed,float coefficient):m_CurDistance(0.f),m_MaxDistance(maxDist),m_controlBall(pBall),m_width(width),m_height(height),m_Status(rotate),m_MovingSpeed(movingSpeed),m_Coefficient(coefficient)
	{
		//设置贴图
		m_texture = TextureManager::instance().loadFromPNG(L"res\\pat.png");
		if(pBall)
		{
			//父节点是m_controlBall
			pBall->AddChild(this);
			pBall->addRef();
		}

		if(m_texture)
		{
			Vector2 min(0,0);
			Vector2 max(1,1);
			m_WorldPosition.setTexcoords(AABox2(min,max),m_texture);
		}
		//设置初始位置
		Init();
	}

	//设置球杆的初始位置
	void Init()
	{
		//假设本坐标系与白球的质点重合，计算球杆的四个顶点在本坐标系中的位置
		//默认为与x轴平行
		float x= m_controlBall->GetRadius();
		m_localPosition.min_corner = Vector2(x,-m_height*0.5f);
		m_localPosition.max_corner =Vector2(x+m_width,m_height*0.5f);
		m_MousePosition.x = 0;
		m_MousePosition.y = 0;
	}


	virtual void Update(float deltaTime)
	{
		//BallArm 状态为在玩家在操作旋转
		if(this->m_enable && m_Status ==  rotate )
		{
		//当前鼠标的位置 
		Vector2 curPosition((float )bosi::getMousePosition().x,(float )bosi::getMousePosition().y);
		//计算夹角
			float theta = atan2(bosi::getMousePosition().y - m_controlBall->GetWorldPosition().y,bosi::getMousePosition().x-m_controlBall->GetWorldPosition().x);
			this->SetRotate(-theta);
			//this->SetPosition(Vector2(m_controlBall->GetRadius()+m_width/2,0));
		
		}
		//BallArm 状态为在玩家在操作移动
		else if(this->m_enable && m_Status == moving)
		{
			
			Vector2 mosVec = Vector2((float)bosi::getMousePosition().x,(float)bosi::getMousePosition().y) - m_MousePressDown;
			//计算与m_MousePressDown组成的向量在m_ParaVec的投影
			m_CurDistance = mosVec.dot_product(m_ParaVec);
			//是否大于最大移动距离
			if( m_CurDistance > m_MaxDistance )
			{
				m_CurDistance = m_MaxDistance;
			}
			//是否为负
			if( m_CurDistance < 0.f)
			{
				m_CurDistance =0.f;
			}
			//移动
			Vector2 prjVec = m_CurDistance* m_ParaVec;
			this->SetPosition(prjVec);
		}
		//BallArm 状态为在恢复移动
		else if(this->m_enable && m_Status ==  recovery)
		{
			//还在恢复中
			if( m_CurDistance > 0.f)
			{
				m_CurDistance -= m_MovingSpeed;
				Vector2 prjVec = m_CurDistance* m_ParaVec;
				this->SetPosition(prjVec);
			}
			//球杆撞到了球
			else
			{
				//小球获得了速度
				this->m_controlBall->GetParticle()->SetVelocity(m_ContactVec);
				//球杆不可见
				this->SetEnable(false);
				//设置状态
				m_Status = hitBall;
			}
		}
	}


	virtual void OnCleanDirty()
	{
		Vector2 p[4];
			//把物体坐标装换为世界坐标
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

	//鼠标按下事件
	void MousePressDown(const bosi::MouseEvent *pMe)
	{
		if(m_Status == rotate)
		{
		//球杆不能旋转了
		m_Status = moving;
		m_MousePressDown = Vector2((float )bosi::getMousePosition().x,(float )bosi::getMousePosition().y);
		//平行于球杆的单位向量
		m_ParaVec = Vector2(m_WorldPosition.v[1].x - m_WorldPosition.v[0].x,m_WorldPosition.v[1].y - m_WorldPosition.v[0].y).Unit();
		}
	}


	//鼠标弹起
	void  MousePressUp(const bosi::MouseEvent *pMe)
	{
		if(m_Status == moving)
		{
		m_Status = recovery;
		//计算撞击给小球的速度
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
	//恢复系数
	float m_Coefficient;
	//撞击给小球的速度
	Vector2 m_ContactVec;

	//恢复的速度
	float m_MovingSpeed;
	//已经移动的距离
	float  m_CurDistance;
	//最大移动距离
	float  m_MaxDistance;
	

	//记录上一次鼠标的位置
	Vector2 m_MousePosition;

	//记录上一次鼠标按下的位置
	Vector2 m_MousePressDown;

	//当前与球杆平行的向量
	Vector2 m_ParaVec;
	
	Texture *m_texture;
	
	AABox2 m_localPosition;
	
	//世界矩形
	Quad m_WorldPosition;

	int m_width;
	int m_height;
	//要控制的白球
	Ball* m_controlBall;
	
};


typedef RefCountedPtr<BallArm > BallArmPtr;