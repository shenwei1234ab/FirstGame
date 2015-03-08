#pragma once 
#include "base\Scene.h"
#include "base\UIButton.h"
#include "base\tinyxml.h"
#include "base\UIElement.h"
#include "base\UIFactory.h"
#include "MyGame.h"
#include "Scene1.h"
#include "base\Scene.h"
class StartScene:public Scene
{
public:
	StartScene()
	{

	}

	~StartScene()
	{

	}
	
	//ȷ�ϵĻص����� 
	void OnButtonClickedUp1(UIButton *sender )
	{
		//std::cout<<"�л�������1"<<std::endl;
		ScenePtr pNext(new Scene1);
		///////////////////////test
		/////////////////////
		MyGame::GetInstance().ChangeScene(pNext.get());
	}

	//ȡ���Ļص�����
	void OnButtonClickedUp2(UIButton *sender )
	{
		std::cout<<"ȡ��"<<std::endl;
	}

	//Update()Ҫ���ø����PhicalWorldUpdate����������
	virtual void Update(float deltaTime)
	{
		//std::cout<<this->m_uiSystem->GetRoot()->GetRef()<<std::endl;
		if(this->m_uiSystem->GetRoot()->GetRef() == 1)
		{
			int i=1;
		}
		Scene::UISystemUpdate(deltaTime);
	}

	virtual void Render()
	{
		m_uiSystem->Render();
	}

	virtual bool Initialize()
	{
		//���Ui
		UISystemPtr tmp(new UISystem);
		m_uiSystem = tmp;

		TiXmlDocument doc;
		if (doc.LoadFile("config.xml")) 
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
		UIButton *btn = dynamic_cast<UIButton *>(m_UIElements["ok"]);
		if (btn)
		{
			btn->SetEventHandler(this);
			btn->SetPressUpEvent((UIButton::PFN_PRESSUP)&StartScene::OnButtonClickedUp1);
		}
		UIButton *btn2 = dynamic_cast<UIButton *>(m_UIElements["no"]);
		if (btn2)
		{
			btn2->SetEventHandler(this);
			btn2->SetPressUpEvent((UIButton::PFN_PRESSUP)&StartScene::OnButtonClickedUp2);
		}
		return true;
	}

#pragma region �������¼�
	virtual void OnMouseEvent(const bosi::MouseEvent *pMe)
	{
		static Vector2 s_pt;
		Vector2 pt((float)pMe->x, (float)pMe->y);
		if(pMe->button == 0)
		{
			if(pMe->pressed)
			{
				s_pt = pt;
				m_uiSystem->DispatchMouseLeftButtonDown(pt);
			}
			else
			{
				m_uiSystem->DispatchMouseLeftButtonUp(pt);
			}
		}
	}

	
	 
	virtual void OnKeyEvent(const bosi::KeyEvent *pKe)
	{

	}
#pragma endregion
protected:
	typedef std::map<std::string, UIElement *> nameElement;
	nameElement m_UIElements;
};