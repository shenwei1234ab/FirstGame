#include "Scene.h"
#include "GameObject.h"
#include "CNode.h"
#include "World.h"
#include "UISystem.h"
World*  Scene::GetPhysicWorld()
{
	return m_World;
}

Scene::Scene():m_World(NULL),m_uiSystem(NULL)
{
	this->m_pParent = NULL;
}

Scene::~Scene()
{
	//free all childNode
	if(!m_Childrens.empty())
	{
		for( Childrens::iterator it = m_Childrens.begin();it != m_Childrens.end();++it )
		{
			(*it)->release();
		}
	}
	////////////////////////
	if(m_World)
	{
		delete m_World;
	}
	/*if(m_uiSystem)
	{
		delete m_uiSystem;
	}*/
}

void Scene::PhicalWorldUpdate(float deltaTime)
{
	if(m_World)
	{
		m_World->Update(deltaTime);
	}
}

void Scene::UISystemUpdate(float deltaTime)
{
	if(m_uiSystem)
	{
		m_uiSystem->Update(deltaTime);
	}
}

void Scene::Update(float deltaTime)
{

}


void Scene::Render()
{

}


