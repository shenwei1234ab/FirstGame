#include "MyGame.h"
#include "base/stdafx.h"
#include "base/Scene.h"
#include "base/World.h"
#include "Scene1.h"
#include "StartScene.h"
#include "Scene2.h"
bool MyGame::Initialize()
{
	ScenePtr tmp(new StartScene);
	m_CurrentScene = tmp;
	m_CurrentScene->Initialize();


	return true;
}

void MyGame::AddScene(std::string sceneName,Scene* pScene)
{
	assert(pScene);

}
void MyGame::DeleteScene(std::string sceneName,Scene* pScene)
{
	assert(pScene);
}
void MyGame::SetCurrentScene(Scene* pScene)
{

}

void MyGame::ChangeScene(Scene* pNextScene)
{
	m_CurrentScene->Final();
	m_CurrentScene = pNextScene;
	m_CurrentScene->Initialize();
}

//µÝ¹éÖ´ÐÐm_CurrentSceneµÄUpdateº¯Êý
void MyGame::Update(float deltaTime)
{
#ifdef _GAME_FRAMETEST
	static float s_timer = 0;
	static int s_count = 0;
	s_timer += deltaTime;
	++s_count;
	if (s_timer >= 1.f) {
		printf("%.2f\n", s_count / s_timer);
		s_count = 0;
		s_timer = 0;
	}
#endif
	if( NULL == m_CurrentScene )
	{
		return ;
	}
	//µÝ¹éº¯Êý
	m_CurrentScene->_Update(deltaTime);
}

void MyGame::Render()
{
	//µÝ¹éº¯Êý
	m_CurrentScene->_Render();
}

void MyGame::Final(void)
{
	//m_CurrentScene->release();
}


void MyGame::OnMouseEvent(const bosi::MouseEvent *pMe)
{
	this->m_CurrentScene->OnMouseEvent(pMe);
}


void MyGame::OnKeyEvent(const bosi::KeyEvent *pKe)
{
	this->m_CurrentScene->OnKeyEvent(pKe);
}
