#pragma once 
#include "base\stdafx.h"
#include "base/CGame.h"
#include "base\Scene.h"
class MyGame:public CGame::IDelegate
{
public:
	bool Initialize();

	void AddScene(std::string sceneName,Scene* pScene);
	void DeleteScene(std::string sceneName,Scene* pScene);
	void SetCurrentScene(Scene* pScene);
	static MyGame& GetInstance()
	{
		static MyGame s_manager;
		return s_manager;
	}
	void Update(float deltaTime);
	void Render();
	 void ChangeScene(Scene* pNextScene);
	void Final();
	void OnMouseEvent(const bosi::MouseEvent *pMe);
	void OnKeyEvent(const bosi::KeyEvent *pKe);
	~MyGame(){};
private:
	typedef std::map<std::string,Scene*> Scenes;
	Scenes m_Scenes;
	MyGame():m_CurrentScene(0)
	{}
	ScenePtr  m_CurrentScene;
};