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

//��ʼ������
const int rowCount = 4;
const float radius = 20.f;
//����һ
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

#pragma region ��ʼ��
	virtual bool Initialize()
	{
			//�������������
		srand((unsigned int )time(0));
#pragma region ��ӱ���
		SceneQuad *pBack = new SceneQuad((float )BACK_WIDTH,(float )BACK_HEIGHT);
		Texture *tex = TextureManager::instance().loadFromPNG(L"res\\back2.png");
		pBack->SetTexture(tex);
		Vector2 min(0,0);
		Vector2 max(1,1);
		pBack->SetTexcoords(AABox2(min,max));
		this->AddChild(pBack);
		pBack->SetPosition(Vector2(0.5f*WINDOWS_WIDTH,0.5f*WINDOWS_HEIGTH));
		//�����
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

		//����С������Ļص�����
		for(Holes::iterator it = m_holes.begin();it!=m_holes.end();++it)
		{
		    Hole *pHole = (Hole *)(*it);
			pHole->SetEventHandler(this,(Hole::PFN_GOAL)&Scene1::OnContact);
		}
		

#pragma endregion	

		
#pragma region  ���UI
		m_uiSystem = new UISystem;
		TiXmlDocument doc;
		if (doc.LoadFile("config1.xml")) 
		{
			UIElement *root = UIFactory::GetInstance().CreateElements(doc.RootElement());
			if (root) 
			{	
				//�������ֺ�UIԪ�ض�Ӧ�Ĳ�ѯ����
				root->BuildNameElementMap(m_UIElements);
				m_uiSystem->SetRoot(root);
				root->release();
			}
		}
		//�������������Ļص�����		
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
	
#pragma region  �������
		m_World = new World;
		//���С������ײ���
		BallCollision *bc = new BallCollision(m_balls);
		m_World->AddContact(bc);
		bc->release();

		//������border����ײ
		BorderCollision *border = new BorderCollision(m_balls, AABox2((WINDOWS_WIDTH-BACK_WIDTH)*0.5F+HOLE_LEFT, (WINDOWS_HEIGTH-BACK_HEIGHT)*0.5F+HOLE_TOP, (WINDOWS_WIDTH+BACK_WIDTH)*0.5F-HOLE_LEFT, (WINDOWS_HEIGTH+BACK_HEIGHT)*0.5F-HOLE_TOP));
		m_World->AddContact(border);
		border->release();
		
		//�����
		CreateBalls();
		
		//���õ�һ�����λ��
		Vector2 FirstPos(0.5*WINDOWS_WIDTH,0.5*WINDOWS_HEIGTH);
		SetBallsPosition(FirstPos,rowCount,radius);

		//���������λ��
		Vector2 MainPos(200,400);
		//���������λ��
		m_MainBall->SetLocalPosition(MainPos);
		
		//������
		m_ballArm = new BallArm(200,m_MainBall,200,20,5.f,100.f);
		return true;
#pragma endregion
	}
#pragma endregion 


	//Update()Ҫ���ø����PhicalWorldUpdate����������
	virtual void Update(float deltaTime)
	{
		//�Ƿ�ײ���� 
		if(m_ballArm->m_Status == BallArm::hitBall)
		{
			//�ж��Ƿ����������,�붴�˾�ɾ����
			if( !m_removeballs.empty()  )
			{
				//�����Ҫɾ������
				for( Balls::iterator itball =m_removeballs.begin(); itball != m_removeballs.end();++itball)
				{
					for(Balls::iterator it = m_balls.begin();it != m_balls.end();++it )
					{
						//�ҵ�
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

			//���򶴵���ײ���
			BallCollision::OnContacts(m_balls,m_holes);
			//�ж�С���Ƿ񶼾�ֹ��
			if(ifAllStatic() )
			{
				//���³�ʼ����˵�λ��
				m_ballArm->Init();
				//��˿ɼ���
				m_ballArm->SetEnable(true);
				m_ballArm->m_Status = BallArm::rotate;
			}
			//��С�����˶�
			else
			{
				//�����������
				Scene::PhicalWorldUpdate(deltaTime);
			}
			
		}
		Scene::UISystemUpdate(deltaTime);
	}

	virtual void Render()
	{
		m_uiSystem->Render();
	}

#pragma region ���ܺ���
//����0-num�����
	unsigned int  Random(unsigned int num)
	{
		
		return rand()%num;
	}
#pragma endregion

	
#pragma region �ص�����

	//��ʾ����
	void MouseMoveIn(UIButton *sender)
	{
		UILabel  *pLable = dynamic_cast <UILabel *>(m_UIElements["helpbrief"]);
		if(pLable)
		{
			pLable->SetVisible(true);
		}
	}
	//���ذ���
	void MouseMoveOut(UIButton *sender)
	{
			//��ʾ�����ĵ�
		UILabel  *pLable = dynamic_cast <UILabel *>(m_UIElements["helpbrief"]);
		if(pLable)
		{
			pLable->SetVisible(false);
		}
	}


	//С������Ļص�����
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


#pragma region  ��Ϸ�߼�
	//ɾ����
	void DestoryBall(Ball *pBall)
	{
		assert(pBall != NULL);
		//������������ɾ������ʵ�
		//m_World->SetUpdating(true);
		m_World->RemoveParticle(pBall->GetParticle());
		//����Ҫɾ���ļ�����
		m_removeballs.push_back(pBall);
		//�����νṹ��ɾ��
		this->RemoveChild(pBall);
	}

	//�Ƿ����е�С�򶼾�ֹ��
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


	//Բ��λ�õĳ�ʼ������һ�����λ��,�������뾶��
	void SetBallsPosition( const Vector2 &v,int rowCount,float radius) 
	{
		int i=1,j=0,k=0;
		//���õ�һ����
		m_balls[0]->SetLocalPosition(v);
		for(i=2, j=0;i<=rowCount;++i)
		{
			//ÿһ�е�һ����
			m_balls[j+i-1]->SetLocalPosition(m_balls[j]->GetLocalPosition() + Vector2((float )radius,-(float)radius));
			for(k=i+j;k< 2*i+j-1;++k)
			{
				//ÿһ��֮�����
				m_balls[k]->SetLocalPosition(m_balls[k-1]->GetLocalPosition() + Vector2(0,radius));
			}
			j=j+i-1;
		}
	}

	void CreateBalls()
	{
		//С������� = ����С��+����
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
			//��ӵ���������
			m_World->AddParticle(pBall->GetParticle());
			pBall->GetParticle()->SetVelocity(Vector2::Zero());
			pBall->GetParticle()->SetMass(1.f);
			pBall->SetRadius(radius);
			this->AddChild(pBall);
		}
		//���һ�������� 
		//m_balls[totalCount-1]->SetBallType ( Ball::BallType::white);
		m_MainBall = m_balls[totalCount-1];
		m_MainBall->addRef();
	}
#pragma endregion

#pragma region  �������¼�
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
	//����
	Ball* m_MainBall;
	//���е���
	typedef std::vector<Ball *> Balls;
	Balls m_balls;
	Balls m_removeballs;

	//���
	BallArm *m_ballArm;
	//���е���
	typedef std::vector<Ball *> Holes;
	Holes m_holes;
	//
	typedef std::map<std::string, UIElement *> nameElement;
	nameElement m_UIElements;
};