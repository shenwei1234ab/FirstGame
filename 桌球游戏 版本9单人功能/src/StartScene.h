#pragma once 
#include "base\Scene.h"
#include "base\UIButton.h"
#include "base\tinyxml.h"
#include "base\UIElement.h"
#include "base\UIFactory.h"
#include "MyGame.h"
#include "Scene1.h"

class StartScene:public Scene,public EvenetHandler
{
public:
	StartScene()
	{
		
	}

	~StartScene()
	{

	}
	
	//确认的回调函数 
	void OnButtonClickedUp1(UIButton *sender )
	{
		//std::cout<<"切换到场景1"<<std::endl;
		Scene1 *pScene1 = new Scene1;
		///////////////////////test
		/////////////////////
		MyGame::GetInstance().ChangeScene(pScene1);
		pScene1->release();
	}

	//取消的回调函数
	void OnButtonClickedUp2(UIButton *sender )
	{
		std::cout<<"取消"<<std::endl;
	}

	//Update()要调用父类的PhicalWorldUpdate来计算物理
	virtual void Update(float deltaTime)
	{
		Scene::UISystemUpdate(deltaTime);
	}

	virtual void Render()
	{
		m_uiSystem->Render();
	}

	virtual bool Initialize()
	{
		//添加Ui
		m_uiSystem = new UISystem;
		TiXmlDocument doc;
		if (doc.LoadFile("config.xml")) 
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
		UIButton *btn = dynamic_cast<UIButton *>(m_UIElements["ok"]);
		if (btn)
		{
			btn->SetEventHandler(this);
			auto funClickedUp1 = std::bind(&StartScene::OnButtonClickedUp1, *this, std::placeholders::_1);
			btn->SetPressUpEvent(funClickedUp1);
		}

		UIButton *btn2 = dynamic_cast<UIButton *>(m_UIElements["no"]);
		if (btn2)
		{
			btn2->SetEventHandler(this);
			auto funClickedUp2 = std::bind(&StartScene::OnButtonClickedUp2, *this, std::placeholders::_1);
			btn2->SetPressUpEvent(funClickedUp2);
		}
		return true;
	}

#pragma region 鼠标键盘事件
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