#pragma once 
#include "base\stdafx.h"
#include "base\Scene.h"
#include "MyGame.h"
#include "base\Vector2.h"
#include "Ball.h"
#include "base\World.h"
#include "base\Gravity.h"
#include "BallCollision.h"
#include "BorderCollision.h"
#include "base\UISystem.h"
#include "base\tinyxml.h"
#include "base\UIFactory.h"
#include "base\UIElement.h"
#include "base\UIButton.h"
#include "BallArm.h"
#include "base\SceneQuad.h"
#include "base\UILabel.h"

//起始的排数
const int rowCount = 4;
const float radius = 20.f;
//场景一
class Scene1:public Scene,public EvenetHandler
{
public:
	int testId;
	Scene1():m_Score(0),testId(0)
	{
		
		
	}

	~Scene1()
	{
		m_MainBall->release();
		m_ballArm->release();
		for(Balls::iterator it = m_balls.begin();it!=m_balls.end();++it)
		{
			(*it)->release();
		}
		for(Holes::iterator it = m_holes.begin();it!=m_holes.end();++it)
		{
			(*it)->release();
		}
		/*for(nameElement::iterator it = m_UIElements.begin();it!=m_UIElements.end();++it)
		{
			(*it).second->release();
		}*/

	}

#pragma region 初始化
	virtual bool Initialize()
	{
			//设置随机数种子
		srand((unsigned int )time(0));
#pragma region 添加背景
		SceneQuad *pBack = new SceneQuad((float )BACK_WIDTH,(float )BACK_HEIGHT);
		Texture *tex = TextureManager::instance().loadFromPNG(L"res\\back2.png");
		pBack->SetTexture(tex);
		Vector2 min(0,0);
		Vector2 max(1,1);
		pBack->SetTexcoords(AABox2(min,max));
		this->AddChild(pBack);
		pBack->SetPosition(Vector2(0.5f*WINDOWS_WIDTH,0.5f*WINDOWS_HEIGTH));
		//添加球洞
		for(int i=0;i<6;++i)
		{
			static  Vector2 vFirstPos;
			if(i == 0)
			{
				vFirstPos.x=(WINDOWS_WIDTH-BACK_WIDTH)*0.5F+HOLE_LEFT;
				vFirstPos.y=(WINDOWS_HEIGTH-BACK_HEIGHT)*0.5F+HOLE_TOP;	  
			}
			if( i == 3 )
			{
				vFirstPos.x=(WINDOWS_WIDTH-BACK_WIDTH)*0.5F+HOLE_LEFT;
				vFirstPos.y=(WINDOWS_HEIGTH-BACK_HEIGHT)*0.5F+HOLE_TOP+HOLE_HORIZ_HEIGHT;	  
			}
			Ball *phole1 = new Hole;
			phole1->SetRadius(radius);
			phole1->SetLocalPosition(vFirstPos);
			vFirstPos += Vector2(HOLE_HORIZ_WIDTH,0);
			this->AddChild(phole1);
			m_holes.push_back(phole1);
		}

		//设置小球进洞的回调函数
		for(Holes::iterator it = m_holes.begin();it!=m_holes.end();++it)
		{
		    Hole *pHole = (Hole *)(*it);
			pHole->SetEventHandler(this,(Hole::PFN_GOAL)&Scene1::OnContact);
		}
		

#pragma endregion	

		
#pragma region  添加UI
		m_uiSystem = new UISystem;
		TiXmlDocument doc;
		if (doc.LoadFile("config1.xml")) 
		{
			UIElement *root = UIFactory::GetInstance().CreateElements(doc.RootElement());
			if (root) 
			{	
				//创建名字和UI元素对应的查询集合
				root->BuildNameElementMap(m_UIElements);
				m_uiSystem->SetRoot(root);
				root->release();
			}
		}
		//设置鼠标点击弹起的回调函数		
		UIButton *btn = dynamic_cast<UIButton *>(m_UIElements["help"]);
		if (btn)
		{
			
			btn->SetEventHandler(this);

			auto funMovIn = std::bind(&Scene1::MouseMoveIn, this, std::placeholders::_1);
			btn->SetMouseMoveInEvent(funMovIn);
			auto funMovOut = std::bind(&Scene1::MouseMoveIn, this, std::placeholders::_1);
			btn->SetMouseMoveOutEvent(funMovOut);
		}
	

#pragma endregion
	
#pragma region  添加物理
		m_World = new World;
		//添加小球间的碰撞检测
		BallCollision *bc = new BallCollision(m_balls);
		m_World->AddContact(bc);
		bc->release();

		//添加球和border的碰撞
		BorderCollision *border = new BorderCollision(m_balls, AABox2((WINDOWS_WIDTH-BACK_WIDTH)*0.5F+HOLE_LEFT, (WINDOWS_HEIGTH-BACK_HEIGHT)*0.5F+HOLE_TOP, (WINDOWS_WIDTH+BACK_WIDTH)*0.5F-HOLE_LEFT, (WINDOWS_HEIGTH+BACK_HEIGHT)*0.5F-HOLE_TOP));
		m_World->AddContact(border);
		border->release();
		
		//添加球
		CreateBalls();
		
		//设置第一个球的位置
		Vector2 FirstPos(0.5*WINDOWS_WIDTH,0.5*WINDOWS_HEIGTH);
		SetBallsPosition(FirstPos,rowCount,radius);

		//设置主球的位置
		Vector2 MainPos(200,400);
		//设置主球的位置
		m_MainBall->SetLocalPosition(MainPos);
		
		//添加球杆
		m_ballArm = new BallArm(200,m_MainBall,200,20,5.f,100.f);
		return true;
#pragma endregion
	}
#pragma endregion 


	//Update()要调用父类的PhicalWorldUpdate来计算物理
	virtual void Update(float deltaTime)
	{
		//是否撞倒球 
		if(m_ballArm->m_Status == BallArm::hitBall)
		{
			//判断是否有球进洞了,入洞了就删除球
			if( !m_removeballs.empty()  )
			{
				//先清除要删除的球
				for( Balls::iterator itball =m_removeballs.begin(); itball != m_removeballs.end();++itball)
				{
					for(Balls::iterator it = m_balls.begin();it != m_balls.end();++it )
					{
						//找到
						if(( *itball ) == *it)
						{
							(*it)->release();
							m_balls.erase(it);
							break;
						}
					}
				}
				m_removeballs.clear();
			}

			//与球洞的碰撞检测
			BallCollision::OnContacts(m_balls,m_holes);
			//判断小球是否都静止了
			if(ifAllStatic() )
			{
				//重新初始化球杆的位置
				m_ballArm->Init();
				//球杆可见了
				m_ballArm->SetEnable(true);
				m_ballArm->m_Status = BallArm::rotate;
			}
			//有小球还在运动
			else
			{
				//物理世界更新
				Scene::PhicalWorldUpdate(deltaTime);
			}
			
		}
		Scene::UISystemUpdate(deltaTime);
	}

	virtual void Render()
	{
		m_uiSystem->Render();
	}

#pragma region 功能函数
//生成0-num随机数
	unsigned int  Random(unsigned int num)
	{
		
		return rand()%num;
	}
#pragma endregion

	
#pragma region 回调函数

	//显示帮助
	void MouseMoveIn(UIButton *sender)
	{
		UILabel  *pLable = dynamic_cast <UILabel *>(m_UIElements["helpbrief"]);
		if(pLable)
		{
			pLable->SetVisible(true);
		}
	}
	//隐藏帮助
	void MouseMoveOut(UIButton *sender)
	{
			//显示帮助文档
		UILabel  *pLable = dynamic_cast <UILabel *>(m_UIElements["helpbrief"]);
		if(pLable)
		{
			pLable->SetVisible(false);
		}
	}


	//小球进洞的回调函数
	void OnContact(Ball *other)
	{
		UILabel *pLabel =  dynamic_cast <UILabel *>(m_UIElements["score"]);
		wchar_t buf[1024];
		std::wstring w_score;
		switch(other->m_type)
		{
		case Ball::white:
			return ;
			break;
		case Ball::red:
			m_Score +=1;
			break;
		case Ball::blue:
			m_Score +=2;
			break;
		case Ball::orange:
			m_Score +=3;
			break;
		case Ball::green:
			m_Score +=4;
			break;
		default:
			;
		}
		if(pLabel)
			{
				int ret = swprintf(buf,L"%d",m_Score);
				w_score.assign(buf,ret);
				pLabel->SetText(w_score);
			}
			DestoryBall(other);
		}
#pragma endregion


#pragma region  游戏逻辑
	//删除球
	void DestoryBall(Ball *pBall)
	{
		assert(pBall != NULL);
		//从物理世界中删除球的质点
		//m_World->SetUpdating(true);
		m_World->RemoveParticle(pBall->GetParticle());
		//放入要删除的集合中
		m_removeballs.push_back(pBall);
		//从树形结构中删除
		this->RemoveChild(pBall);
	}

	//是否所有的小球都静止了
	bool ifAllStatic()
	{
		bool bret = true;
		for(Balls::iterator it =m_balls.begin();it !=m_balls.end();++it)
		{
			if( (*it)-> GetVelocity() != Vector2::Zero())
			{
				bret = false;
			}
		}
		return bret;
	}


	//圆球位置的初始化（第一个球的位置,排数，半径）
	void SetBallsPosition( const Vector2 &v,int rowCount,float radius) 
	{
		int i=1,j=0,k=0;
		//设置第一个球
		m_balls[0]->SetLocalPosition(v);
		for(i=2, j=0;i<=rowCount;++i)
		{
			//每一列第一个球
			m_balls[j+i-1]->SetLocalPosition(m_balls[j]->GetLocalPosition() + Vector2((float )radius,-(float)radius));
			for(k=i+j;k< 2*i+j-1;++k)
			{
				//每一列之后的球
				m_balls[k]->SetLocalPosition(m_balls[k-1]->GetLocalPosition() + Vector2(0,radius));
			}
			j=j+i-1;
		}
	}

	void CreateBalls()
	{
		//小球的总数 = 其他小球+主球
		int totalCount = (1+rowCount)*rowCount /2 + 1 ;
		m_balls.reserve(totalCount);
		for(int i=0;i<totalCount;++i)
		{
			unsigned int type = Random(4);
			if( i== totalCount -1 )
			{
				type =  Ball::white;
			}
			Ball *pBall = new Ball(type);
			m_balls.push_back(pBall);
			pBall->addRef();
			//添加到物理世界
			m_World->AddParticle(pBall->GetParticle());
			pBall->GetParticle()->SetVelocity(Vector2::Zero());
			pBall->GetParticle()->SetMass(1.f);
			pBall->SetRadius(radius);
			this->AddChild(pBall);
		}
		//最后一个是主球 
		//m_balls[totalCount-1]->SetBallType ( Ball::BallType::white);
		m_MainBall = m_balls[totalCount-1];
		m_MainBall->addRef();
	}
#pragma endregion

#pragma region  鼠标键盘事件
	virtual void OnMouseEvent(const bosi::MouseEvent *pMe)
	{
		Vector2 pt((float )bosi::getMousePosition().x,(float )bosi::getMousePosition().y);
		if(pMe->button == 0)
		{
			if(pMe->pressed)
			{
				m_uiSystem->DispatchMouseLeftButtonDown(pt);
				m_ballArm->MousePressDown(pMe);
			}
			else
			{
				m_uiSystem->DispatchMouseLeftButtonUp(pt);
				m_ballArm->MousePressUp(pMe);
			}
		}
	}


	virtual void OnKeyEvent(const bosi::KeyEvent *pKe)
	{

	}
#pragma endregion 	             

protected:
	int m_Score;
	//主球
	Ball* m_MainBall;
	//所有的球
	typedef std::vector<Ball *> Balls;
	Balls m_balls;
	Balls m_removeballs;

	//球杆
	BallArm *m_ballArm;
	//所有的球洞
	typedef std::vector<Ball *> Holes;
	Holes m_holes;
	//
	typedef std::map<std::string, UIElement *> nameElement;
	nameElement m_UIElements;
};